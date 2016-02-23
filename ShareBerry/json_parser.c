#include<stdio.h>
#include<string.h>
#include<json-c/json.h>
#include "json_parser.h"
#include "json_msg.h"
#include "daemonLog.h"

//this function create json_object when you need json_object
struct json_object* json_createObject(void)
{
	struct json_object *ret;

	ret = json_object_new_object();

	if(ret==NULL)
	{
		//Log record code
		//exit
	}

	return ret;
}

const char* json_object_to_fileInfo(filetype type, char *path, 
									char *name, int offset,	int size)
{
	json_object *header, *body;

	header = json_object_new_object();
	body = json_object_new_object();

	json_addObject(body, "filetype", INTEGER, (void*)type);
	json_addObject(body, "path", STRING, (void*)path);
	json_addObject(body, "name", STRING, (void*)name);
	json_addObject(body, "offset", INTEGER, (void*) offset);
	json_addObject(body, "size", INTEGER, (void*) size);
	
	json_addObject(header, "header", OBJECT, body);
	json_object_serialize(header);

	return json_object_to_json_string(header);
}

void json_addObject(struct json_object* obj, const char *key, 
		jsonType type, void* data)
{
	switch(type){
		case BOOLEAN:	
			json_object_object_add(obj, key, 
					json_object_new_boolean((int)data));
			break;
		case INTEGER:
			json_object_object_add(obj, key, 
					json_object_new_int((int)data));
			break;
		case STRING:
			json_object_object_add(obj, key, 
					json_object_new_string((const char *) data));
			break;
		case OBJECT:
			json_object_object_add(obj, key,(struct json_object*)data);
			break;
		default:
			break;
	}
}

const char* json_object_toString(struct json_object* obj)
{
	return (const char*)json_object_to_json_string(obj);
}

int json_getObjectLength(struct json_object* obj)
{
	return json_object_object_length(obj);
}

void json_useObject(struct json_object *obj)
{
	json_object_get(obj);
}

void json_unuseObject(struct json_object *obj)
{
	json_object_put(obj);
}

void json_object_serialize(struct json_object* obj)
{
	json_object_set_serializer(obj, NULL, NULL, NULL);
}

json_bool json_getObject(struct json_object* obj, const char *key,
						 struct json_object** value)
{
	return json_object_object_get_ex(obj, key, value);
}

filecmd* parse_fileCmd(json_object* obj)
{
	filecmd *cmd = NULL;
	json_object *body, *ret;
	
	cmd = (filecmd*)malloc(sizeof(filecmd));

	if(cmd == NULL)
		return NULL;

	//get filetype
	json_object_object_get_ex(obj, "header", &body);

	json_object_object_get_ex(body, "filetype", &ret);
	cmd->type = (cmd_type)json_object_get_int(ret);

	//get filepath
	json_object_object_get_ex(body, "path", &ret);
	strcpy(cmd->path, json_object_get_string(ret));

	json_object_object_get_ex(body, "name", &ret);
	strcpy(cmd->name, json_object_get_string(ret));

	json_object_object_get_ex(body, "newpath", &ret);
	strcpy(cmd->newpath, json_object_get_string(ret));

	return cmd;
}

fileinfo* parse_fileTransmit(json_object* obj)
{
	fileinfo *info = NULL;
	json_object *body, *ret;

	info = (fileinfo*)malloc(sizeof(fileinfo));
	if(info == NULL)
		return NULL;

	json_object_object_get_ex(obj, "header", &body);

	json_object_object_get_ex(body, "type", &ret);
	info->type= (filetype)json_object_get_int(ret);

	json_object_object_get_ex(body, "path", &ret);
	strcpy(info->path, json_object_get_string(ret));

	json_object_object_get_ex(body, "name", &ret);
	strcpy(info->name, json_object_get_string(ret));

	json_object_object_get_ex(body, "offset", &ret);
	info->offset = json_object_get_int(ret);

	json_object_object_get_ex(body, "size", &ret);
	info->size = json_object_get_int(ret);

	return info;
}


