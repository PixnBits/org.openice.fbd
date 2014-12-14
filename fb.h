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
#ifndef FB_H
#define FB_H

#include <QObject>
#include "fblib.h"

class fb: public QObject
{
Q_OBJECT
public:
	fb();
	virtual ~fb();
	bool start();
public Q_SLOTS:
	void FireAnalogValue(int analognum, double value);
	void SetSingleOutput(int ionum, bool active);
	void SetAllOutput(int low, int high);
	double GetAnalogValue(int analognum, int sample);
Q_SIGNALS:
	void AnalogValueChanged(int analognum, double value);

private:
	fblib *fusionbrain;

};

#endif // FB_H
