#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <direct.h>

class Folder : public Huffman {

	string _nameFolder;
	string _nameFolderOut;
	vector <string> _name;
	vector < vector <Huffman*> >  _buff;
	vector <vector <char> > _data;

	char* stringtoChar(string);
	void RemoveFolder();
public:

	Folder();

	void Input(bool);
	vector <string> GetNameFolder(string);
	void EncodeFolder();
	void DecodeFolder();
	void InitFolder();
	~Folder() = default;
};


