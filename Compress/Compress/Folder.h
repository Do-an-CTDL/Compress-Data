<<<<<<< HEAD
#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <direct.h>

class Folder : public Huffman {
=======

#include "Huffman.h"
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <direct.h>

class Folder : public Huffman{
>>>>>>> 8122d14765e38e424439eae958601cd6ff9ec479

	string _nameFolder;
	string _nameFolderOut;
	vector <string> _name;
	vector < vector <Huffman*> >  _buff;
	vector <vector <char> > _data;

<<<<<<< HEAD
=======
	string chartoString(char *);
>>>>>>> 8122d14765e38e424439eae958601cd6ff9ec479
	char* stringtoChar(string);
	void RemoveFolder();
public:

	Folder();

	void Input(bool);
	vector <string> GetNameFolder(string);
	void EncodeFolder();
	void DecodeFolder();
<<<<<<< HEAD
=======
	//void Output();
>>>>>>> 8122d14765e38e424439eae958601cd6ff9ec479
	void InitFolder();
	~Folder() = default;
};


