#include<stdlib.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<errno.h>
#include<time.h>
#include<sys/types.h>
#include<sys/stat.h>

#include"daemonLog.h"
#include"ename.c.inc"

static const char *LOG_PATH = "/tmp/shareberry.log";
static FILE *logfp;

void createLogfile()
{
	mode_t m;

	m = umask(077);
	logfp = fopen(LOG_PATH, "a");
	umask(m);

	if(logfp == NULL) 
		exit(EXIT_FAILURE);

	setbuf(logfp, NULL);

	LogI("Create Log File");
	LogI("Start logging");
}

static void terminate()
{
	char *s;

	s = getenv("EF_DUMPCORE");

	/*
	 	EF_DUMPCORE 환경 변수가 비어있지 않으 문자열로 정의되어 있으면
		코어를 덤프하고, 그렇지 않으면 Boolean 값에 따라 exit(3)이나
		exit(2)를 호출한다.
	 */

	closeLogfile();

	if( s != NULL && *s != '\0')
		abort();
	else
		_exit(EXIT_FAILURE);
}


void writeLogMessage(const char *mode, const char* msg)
{
#define TS_BUF_SIZE sizeof("YYYY-MM-DD HH:MM:SS")

	const char *TIMESTAMP_FMT = "%F %X";	/* = yyyy-mm-dd HH:MM:SS */
	char timestamp[TS_BUF_SIZE];
	time_t t;
	struct tm *loc;
	int errsv;

	t = time(NULL);
	loc = localtime(&t);

	// record the time when called logMsg
	if(loc == NULL || strftime(timestamp, TS_BUF_SIZE, TIMESTAMP_FMT, loc)==0)
		fprintf(logfp, "[Unknown time][%s] : ", mode);
	else
		fprintf(logfp, "[%s][%s] : ", timestamp, mode);

	errsv = errno;
	if(errsv != 0)
		fprintf(logfp, "%s : %s ", ename[errsv], strerror(errsv));
	else
		fprintf(logfp, "%s", msg);
	
	fprintf(logfp, "\n");

	errno = errsv;
}


void closeLogfile()
{
	if(logfp == NULL) exit(EXIT_FAILURE);

	LogI("close Log file");
	fclose(logfp);
}

/*
 * Exit process after print stdout buffer and call exit handler
 */
void errExit(char* msg)
{
	writeLogMessage("Error", msg);
	terminate();
}
