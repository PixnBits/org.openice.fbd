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
#ifndef FBD_H
#define FBD_H

#include "fb.h"
#include <QTimer>
#include <QList>

class fbd: public QObject
{
Q_OBJECT
public:
	fbd();
	virtual ~fbd();

public slots:
	void run();

private:
	fb *fusionbrain;
	QTimer *PollTimer;
	QList<double> oldAnalogValues;
};

#endif // FBD_H
