#ifndef __JSON_PARSER_H__
#define __JSON_PARSER_H__

#include "json_msg.h"

#ifdef __cplusplus
extern "C"{
#endif

/* supported json object types*/
typedef enum jsonType{
	Null,
	BOOLEAN,
	DOUBLE,
	INTEGER,
	OBJECT,
	ARRAY,
	STRING,
}jsonType;

struct json_object* json_createObject(void);
void json_addObject(struct json_object* obj, const char *key, 
		jsonType type, void* data);

int json_getObjectLength(struct json_object *obj);
const char* json_object_toString(struct json_object* obj);
void json_object_serialize(struct json_object *obj);
void json_useObject(struct json_object *obj);
void json_unuseObject(struct json_object *obj);

/* This function is parsing file command from json-object */
filecmd* parse_fileCmd(json_object *obj);

fileinfo* parse_fileTransmit(json_object *obj);

const char* json_object_to_fileInfo(filetype type, char *path,
									char *name, int offset, int size);



#ifdef __cplusplus
}
#endif

#endif

