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
#include <usb.h>
#include <stdio.h>


class fblib
{
public:
	fblib();
	~fblib();
	bool init();
	bool connect();
	int setSingleOutput(int ionum, bool active);
	int setAllOutput(unsigned char low, unsigned char high);
	double getAnalogValue(int analognum,int samplenum);
private:
	struct usb_device *fusionBrain;
	usb_dev_handle *fbHandle;
	char data_recv[64];
	unsigned char EP_OUT;
	unsigned char EP_IN;
};

