/**
 * fblib - low level interaction with the fusion brain device
 * Copyright (C) 2009 Michael Carpenter
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 */
#include "fblib.h"



fblib::fblib()
{
	fusionBrain=0;
	EP_OUT = 0x01;
	EP_IN = 0x81;
}
fblib::~fblib()
{
	usb_release_interface(fbHandle,0);
	usb_close(fbHandle);
}
bool fblib::init()
{
	struct usb_bus *bus;
	struct usb_device *dev;
	usb_init();
	usb_find_busses();
	usb_find_devices();
	struct usb_bus *busses = usb_get_busses();
	usb_find_devices();
	for (bus = busses;bus;bus = bus->next)
	{
		//printf("BUS!\n");
		for (dev = bus->devices;dev;dev = dev->next)
		{
			//printf("Device: 0x%4x\n",dev->descriptor.idVendor);
			if ((dev->descriptor.idVendor == 0x04D8) && (dev->descriptor.idProduct == 0x000E))
			{
				printf("Fusion Brain V4 found!\n");
				fusionBrain = dev;
				return true;
			}
		}
	}
	return false;
}
bool fblib::connect()
{
	printf("Attempting to open interface...\n");
	fbHandle = usb_open(fusionBrain);
	if (!fbHandle)
	{
		printf("Failed to open interface!\n");
		return false;
	}
	if (usb_claim_interface(fbHandle,0))
	{
		printf("Failed to claim interface!\n");
		return false;
	}
	printf("Fusion Brain connected!\n");
	return true;
}
int fblib::setSingleOutput(int ionum, bool active)
{
	if ((ionum < 0) || (ionum > 15))
	{
		return -1;
	}
	for (int i=0;i<64;i++)
	{
		data_recv[i]=0;
	}
	int dataSendResult = 0;
	int dataRecvResult=0;
	bool stop = false;
	while (!stop)
	{
		dataRecvResult = usb_bulk_read(fbHandle,EP_IN,data_recv,64,500);
		if (active)
		{
			data_recv[ionum*2] = 0b00000001;
		}
		else
		{
			data_recv[ionum*2] = 0b00000000;
		}
		dataSendResult = usb_bulk_write(fbHandle,EP_OUT,data_recv,64,500);
		dataRecvResult = usb_bulk_read(fbHandle,EP_IN,data_recv,64,500);
		if (active)
		{
			if (data_recv[ionum*2] == 1)
			{
				stop = true;
			}
		}
		else
		{
			if (data_recv[ionum*2] == 0)
			{
				stop = true;
			}
		}
	}
	return 0;
}
int fblib::setAllOutput(unsigned char low, unsigned char high)
{
	for (int i=0;i<64;i++)
	{
		data_recv[i]=0;
	}
	int dataSendResult = 0;
	int dataRecvResult=0;
	bool stop = false;
	while (!stop)
	{
		dataRecvResult = usb_bulk_read(fbHandle,EP_IN,data_recv,64,500);
		for (int i=0;i<8;i++)
		{
			data_recv[i * 2] = (low >> i) & 1;
			data_recv[(i+8)*2] = (high >> i) & 1;
		}
		dataSendResult = usb_bulk_write(fbHandle,EP_OUT,data_recv,64,500);
		dataRecvResult = usb_bulk_read(fbHandle,EP_IN,data_recv,64,500);
		stop = true;
		for (int i=0;i<8;i++)
		{
			if ((data_recv[i * 2] != ((low >> i) & 1)) || (data_recv[(i + 8) * 2] != ((high >> i) & 1)))
			{
				stop = false;
			}
		}
	}
	return 0;
}

double fblib::getAnalogValue(int analognum,int samplenum)
{
	// Avoid doing any work if invalid sample number is given
	if ( samplenum == 0 )
	{
		return 0;
	}

	// Analog ports are 0-12
	if ( analognum < 0 || analognum > 12 )
	{
		return -1;
	}

	int dataRecvResult=0;
	int retVal=0;
	int count = 0;
        int offset=0;
	unsigned char low=0;
	unsigned char high=0;
	for (int i=0;i<samplenum;i++)
	{
		// clear buffer
		for (int j=0;j<64;j++)
		{
			data_recv[j]=0;
		}

		dataRecvResult = usb_bulk_read(fbHandle,EP_IN,data_recv,64,500);
		if ( dataRecvResult > 0 )
		{
			count++;
			offset = (analognum * 2) + 32; // V4
			// first cast to unsigned char to limit to 8 chars captured
			low = (unsigned char)data_recv[offset];
			high = (unsigned char)data_recv[offset+1];
			// Then multiply low byte by 256 and add to high
			retVal += ((int)low << 8) + (int)high;
		}
		// TODO: what about read failures or less than 64 read?
        }
	
	if ( count > 0 )
	{
		// Convert to voltage and return average
		// TODO: Will the reference voltage always be 5v?
		//printf("getAnalogValue: %i %i %f\n", analognum, retVal/count, (5.0*(retVal/count))/1023);
		return (5.0*(retVal / count))/1023;	
	}
	else
	{
		return 0.0;
	}
}
