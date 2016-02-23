#ifndef __FILEMANAGER_H__
#define __FILEMANAGER_H__

#include<string>
#include<vector>
#include<map>

using namespace std;

class FileManager{
	private:
		map<string, Directory*> childDirList;
		map<string, File*> childFileList;

	public:
		FileManager();
		void initChildList();
		vector<Directory*> getChildDirectoryList(string path);
		vector<File*> getChildFileList(string path);
		bool makeDirectory(string path, string name);
		void addFile(string path, string name, int size);
		bool removeDirectory(string path, string name);
		bool renameFile(string path, string preName, string newName);
		bool renameDirectory(string path, string preName, string newName);
		int getFileSize(string path, string name);
		File* getFile(string path, string name);
		Directory* getDirectory(string path, string name);
		~FileManager();
}

#endif

