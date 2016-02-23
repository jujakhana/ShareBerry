#ifndef __BECOME_DAEMON_H__
#define __BECOME_DAEMON_H__

#ifdef __cplusplus
extern "C" {
#endif

#include<syslog.h>

#define BD_MAX_CLOSE			8192

#define DAEMON_CREATE_FAIL		-1
#define DAEMON_CREATE_SUCCESS 	0

int becomeDaemon(void);

#ifdef __cplusplus
}
#endif

#endif
