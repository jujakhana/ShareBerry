#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>

#include"daemonLog.h"
#include"becomeDaemon.h"

int becomeDaemon(void)
{
	int maxfd, fd;

	switch(fork()){
		case -1 : 
	//		err_Exit("Create child process fail");
			return DAEMON_CREATE_FAIL;
		case 0 : break;
		default : _exit(EXIT_SUCCESS);
	}

	/* become session create and process group leader */
	if(setsid() == -1) {
	//	err_Exit("Session create fail");
		return DAEMON_CREATE_SUCCESS;
	}

	switch(fork()){
		case -1 : 
	//		err_Exit("Create child process fail");
			return DAEMON_CREATE_FAIL;
		case 0 : break;
		default : _exit(EXIT_SUCCESS);
	}


	umask(0);		/* Erase file mode creation mask*/

	chdir("/");		/* Change current directory to root directory*/

	/* Close all open files*/
	maxfd = sysconf(_SC_OPEN_MAX);

	if(maxfd == -1)
		maxfd = BD_MAX_CLOSE;

	for(fd = 0; fd < maxfd ; fd++)
		close(fd);

	/* Open again the standart fd to /dev/null */
	close(STDIN_FILENO);

	fd = open("/dev/null", O_RDWR);

	if(fd != STDIN_FILENO)
		return DAEMON_CREATE_FAIL;
	if(dup2(STDIN_FILENO, STDOUT_FILENO) != STDOUT_FILENO)
		return DAEMON_CREATE_FAIL;
	if(dup2(STDIN_FILENO, STDERR_FILENO) != STDERR_FILENO)
		return DAEMON_CREATE_FAIL;

	LogI("Daemon process create success");

	return 0;
}
