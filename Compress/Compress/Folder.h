#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <direct.h>


class Folder : public Huffman {

	string _nameFolder;	
	string _nameFolderOut;
	vector <string> _name;


	char* stringtoChar(string);
	void RemoveFolder();
public:

	Folder();
	~Folder() = default;

	bool Input(bool);
	vector <string> GetNameFolder(string);
	bool EncodeFolder();
	bool DecodeFolder();
	void InitFolder();
	
};


