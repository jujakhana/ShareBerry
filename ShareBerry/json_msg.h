#ifndef __JSON_MSG_H__
#define __JSON_MSG_H__


#ifdef __cplusplus
extern "C"{
#endif 

#include<stdio.h>

typedef enum MessageType{
	Contol, Transmit, Receive
}msgtype;

typedef enum FileType{
	Regular, Directory, Link, Block, Character, Pipe, Socket
}filetype;

/* supported file operation cmd */
typedef enum CmdType{
	Mkdir, 
	Mkfile, 
	Remove,
	Change,
	Move
}cmd_type;

/* file command message structure */
typedef struct FileCmd{
	cmd_type type;
	char path[BUFSIZ];
	char name[BUFSIZ];
	char newpath[BUFSIZ];
}filecmd;

/* file transmit message structure*/
typedef struct FileInfo{
	filetype type;
	char path[BUFSIZ];
	char name[BUFSIZ];
	int offset;
	int size;
}fileinfo;

#ifdef __cplusplus
}
#endif

#endif

