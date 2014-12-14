/**
 * fbd - fusion brain daemon service for interaction between apps and the fusion brain device
 * Copyright (C) 2009 Kevron Rees
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
#include "fb.h"

fb::fb()
{
	fusionbrain = new fblib();

}

fb::~fb()
{
	delete fusionbrain;
}

bool fb::start()
{
	bool enabled=false;
	if( (enabled = fusionbrain->init()) )
	{
		enabled = fusionbrain->connect();
	}

	return enabled;
}

void fb::FireAnalogValue(int analognum, double value)
{
	// Test temp
	if ( analognum == 1 )
	{
		float temp = ((value-0.4) * 1000) / 19.53;
		int val = temp*1.8 + 32; // farenheit
		printf("AnalogValueChanged: %f %i\n", value, val);
		emit AnalogValueChanged(analognum, val);
	}
	else
	emit AnalogValueChanged(analognum, value);
}

void fb::SetSingleOutput(int ionum, bool active)
{
	fusionbrain->setSingleOutput(ionum,active);
}

void fb::SetAllOutput(int low, int high)
{
	fusionbrain->setAllOutput((unsigned char)low,(unsigned char)high);
}

double fb::GetAnalogValue(int analognum, int sample)
{
	return fusionbrain->getAnalogValue(analognum,sample);
}

