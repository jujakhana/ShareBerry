#ifndef __DAEMON_LOG_H__
#define __DAEMON_LOG_H__

#include<stdio.h>
#include<string.h>

#define LogD(log) writeLogMessage("Debug", log)
#define LogI(log) writeLogMessage("Info" , log)
#define LogW(log) writeLogMessage("Warning", log)
#define LogE(log) errExit(log)

#ifdef __cplusplus
extern "C" {
#endif

void createLogfile();
void closeLogfile();
void writeLogMessage(const char *mode, const char* msg); 
void errExit(const char* msg);

#ifdef __cplusplus
}
#endif

#endif
