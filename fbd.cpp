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
#include "fbd.h"
#include "fbddbus.h"

#include <QDBusConnection>
#include <iostream>

using namespace std;

fbd::fbd()
{
	fusionbrain = new fb();

	new FusionbrainAdaptor(fusionbrain);
	QDBusConnection connection = QDBusConnection::systemBus();
	if(!connection.registerObject("/org/openice/fbd", fusionbrain))
	{
		cout<<"Failed to register dbus object "<<endl;
	}
	if(!connection.registerService("org.openice.fbd"))
	{
		cout<<"Failed to register service: 'org.openice.fbd' on the system bus"<<endl;
		exit(-1);
	}

	///preload all the input values with 0's:
	for(int i=0;i<13;i++)
		oldAnalogValues.append(0);
	if(fusionbrain->start())
	{
		PollTimer = new QTimer();
		connect(PollTimer,SIGNAL(timeout()),this,SLOT(run()));
		PollTimer->start(10);
	}
}

fbd::~fbd()
{
	delete (fusionbrain);
}

void fbd::run()
{
	///poll the inputs, fire any events
	for(int i=0;i<13;i++)
	{
		double value = fusionbrain->GetAnalogValue(i,10);
		//fire the signal if we detect a 500mV change:
		double delta = 0.005; // TODO: make this configurable per input
		//printf("%i: %f %f %f\n", i, oldAnalogValues[i], value, fabs(oldAnalogValues[i]-value));
		if(fabs(oldAnalogValues[i]-value) >= delta)
		{
			fusionbrain->FireAnalogValue(i,value);

			// only store off values presented
			oldAnalogValues[i] = value;
		}
	}
}


