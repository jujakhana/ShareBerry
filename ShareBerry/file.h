#ifndef __FILE_H__
#define __FILE_H__

#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

class File{
	private:
		typedef struct fileStatus{
			string path;
			string name;
			mode_t file_mode;
			off_t file_size;
		}file_status;

	public:

}

#endif

