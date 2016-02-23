#include<iostream>
#include<json-c/json.h>
#include "json_parser.h"
#include "json_msg.h"
#include "daemonLog.h"

using namespace std;

int main()
{
	json_object *header, *body;
	filecmd *cmd;

	createLogfile();

	/*
	header = json_createObject();
	body = json_createObject();

	json_addObject(body, "filetype", INTEGER, (void*)1);
	json_addObject(body, "path", STRING, (void*)"~/test/path\0");
	json_addObject(body, "name", STRING, (void*)"filename\0");
	json_addObject(body, "newpath", STRING, (void*)"new path\0");
	json_addObject(header, "header", OBJECT, body);
	json_object_serialize(header);

	cmd = parse_fileCmd(header);

	LogD(cmd->path);
	LogD(cmd->name);
	LogD(cmd->newpath);

	*/

	LogD(json_object_to_fileInfo(Regular, "~/Shareberry/", "newfile", 101, 300));

	closeLogfile();

	return 0;
}
