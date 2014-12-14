#include <stdlib.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>
#include <fcntl.h>

#include <QtCore/QCoreApplication>

#include "fbd.h"

void daemonize();

int main(int argc, char *argv[])
{
	//daemonize();
	QCoreApplication a(argc, argv);

	fbd fusionbraindaemon;

	return a.exec();
}

void daemonize()
{
	int i=0;
	if(getppid() == 1)
	{
		return;	// already a daemon
	}
	if((i = fork()) < 0)
	{
		fprintf(stderr, "%s:%s(%d) - fork error: %s", __FILE__, __FUNCTION__, __LINE__, strerror(errno));
		exit(1);
	}
	if(i > 0)
	{
		exit(0);	// parent exits
	}	// child (daemon) continues
	setsid();	// obtain a new process group
	for(i = getdtablesize(); i >= 0; --i)
	{
		close(i);	// close all descriptors
	}
	{	// handle standard I/O
		i = open("/dev/null", O_RDWR);
		int ret = dup(i);
		ret = dup(i);
	}
	// first instance continues
}
