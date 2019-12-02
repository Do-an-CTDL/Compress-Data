<<<<<<< HEAD
#include "Huffman.h"
#include "Folder.h"
const string  space = "                                                         ";
=======
#include "Folder.h"
>>>>>>> 8122d14765e38e424439eae958601cd6ff9ec479


Folder::Folder() {

	_name.clear();
	_buff.clear();
}

//chuyen doi
char* Folder::stringtoChar(string in) {

	char* out = new char[in.size() + 1];

	for (int i = 0; i < in.size(); i++)
		out[i] = in[i];
	out[in.size()] = '\0';
	return out;
}

void Folder::RemoveFolder() {
	
	try {
		
		vector <string> name = GetNameFolder(_nameFolderOut);

		//xoa tung file
		for (int i = 0; i < name.size(); i++) {
			
			name[i] = _nameFolderOut + '/' + name[i];
			char* tmp = stringtoChar(name[i]);

			int check = remove(tmp);
		}

	}
	catch (...){
<<<<<<< HEAD
		cout << space << "Khong the tim thay thu muc\n";
=======
		cout << "Khong the tim thay thu muc\n";
>>>>>>> 8122d14765e38e424439eae958601cd6ff9ec479
	}
}

//Tao thu muc
void Folder::InitFolder() {


	char* Name = stringtoChar(_nameFolderOut);
	int check = _mkdir(Name);
	
	//Neu thu muc do da co thi xoa het tat ca file trong do
	if (check == -1) {
		RemoveFolder();
		
	}

	for (int i = 0; i < _name.size(); i++) {
		string tmp = _name[i];

		bool flag = 0;
		for (int j = tmp.size() - 1; j >= 0; j--) {
			
			
			if (tmp[j] == '/') {
				tmp[j] = '\0';
				flag = 1;
				break;
			}
		}
		if (flag) {
			tmp = _nameFolderOut + "/" + tmp;
			int count = 0; // Dem so ky tu '/'

			string nameFolder = "";
			for (int j = 0; j < tmp.size(); j++) {
				
				
				if (tmp[j] == '/' || j == tmp.size() - 1) {
					count++;
					if (count >= 2) {

						char* chuyenconvert = stringtoChar(nameFolder);
						int check = _mkdir(chuyenconvert);
					}
				}
				nameFolder += tmp[j];
			}
		}
	}
}

<<<<<<< HEAD
=======

>>>>>>> 8122d14765e38e424439eae958601cd6ff9ec479
//Doc tat ca cac file trong folder
vector<string> Folder::GetNameFolder(string folder)
{
	vector<string> names;
	string search_path = folder + "/*.*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			
			
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				names.push_back(fd.cFileName);
			}
			//----------------------------------------------
			if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				vector <string> s;

				string(fd.cFileName) = folder + "/" + string(fd.cFileName);

				string tmp = string(fd.cFileName);


				if (tmp == "." || tmp == "..")
					continue;
				else
					tmp = folder + "/" + tmp;
				s = GetNameFolder(tmp);

				for (int i = 0; i < s.size(); i++) {
					s[i] = string(fd.cFileName) + "/" + s[i];
				}
				names.insert(names.end(), s.begin(), s.end());

			}

			//----------------------------------------------
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
}

<<<<<<< HEAD
//Nen ca thu muc
void Folder::EncodeFolder() {


	for (int i = 0; i < _name.size(); i++) {
		
		
		string out = _name[i];
		_name[i] = _nameFolder + '/' + _name[i];

		out = _nameFolderOut + '/' + out;
		
		Huffman::Encoding(_name[i], out);
	}
}

//Giai nen ca thu muc
void Folder::DecodeFolder() {

	
	for (int i = 0; i < _name.size(); i++) {

		
		
		string out = _name[i];
		_name[i] = _nameFolder + '/' + _name[i];

		out = _nameFolderOut + '/' + out;
		

		Huffman::Decoding(_name[i], out);
	}
}

=======
>>>>>>> 8122d14765e38e424439eae958601cd6ff9ec479
//1: nen, 0 giai nen
void Folder::Input(bool flag) {

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

<<<<<<< HEAD
	cout << space << "Nhap ten thu muc: ";
	cin.ignore();
=======
	cout << "Nhap Ten thu muc: ";

>>>>>>> 8122d14765e38e424439eae958601cd6ff9ec479
	getline(cin, _nameFolder);

	char* tmp = new char[_nameFolder.size() + 1];

<<<<<<< HEAD

=======
	
>>>>>>> 8122d14765e38e424439eae958601cd6ff9ec479

	for (int i = 0; i <= _nameFolder.size(); i++) {

		tmp[i] = (_nameFolder[i]);
	}

<<<<<<< HEAD

=======
	
>>>>>>> 8122d14765e38e424439eae958601cd6ff9ec479

	const char* tmp2 = tmp;

	hFind = FindFirstFile(tmp2, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
<<<<<<< HEAD
		cout << space << "Khong the tim thay file dau tien (" << GetLastError() << ")" << endl;
=======
		printf("FindFirstFile failed (%d)\n", GetLastError());
>>>>>>> 8122d14765e38e424439eae958601cd6ff9ec479
		return;
	}
	else
	{
<<<<<<< HEAD
		//printf(TEXT("%sFile dau tien la: %s\n"), space, FindFileData.cFileName);
=======
		printf(TEXT("The first file found is %s\n"),
			FindFileData.cFileName);
>>>>>>> 8122d14765e38e424439eae958601cd6ff9ec479

		_name = GetNameFolder(FindFileData.cFileName);
		if (flag == 1) {
			_nameFolderOut = _nameFolder + "Compress";
<<<<<<< HEAD

			InitFolder();
			EncodeFolder();

		}
		else {
			_nameFolderOut = _nameFolder;
			int pos = _nameFolderOut.find("Compress");

			_nameFolderOut.replace(pos, 8, "Decompress");
			cout << space << _nameFolderOut << "\n";

			InitFolder();
			DecodeFolder();

		}
		FindClose(hFind);
	}
=======
			
			InitFolder();
			EncodeFolder();
			
		}
		else {
			_nameFolderOut = _nameFolder ;
			int pos = _nameFolderOut.find("Compress");

			_nameFolderOut.replace(pos, 8, "Decompress");
			cout << _nameFolderOut << "\n";

			InitFolder();
			DecodeFolder();
		
		}
		FindClose(hFind);
	}
}


//Nen ca thu muc
void Folder::EncodeFolder() {


	for (int i = 0; i < _name.size(); i++) {
		
		
		string out = _name[i];
		_name[i] = _nameFolder + '/' + _name[i];

		out = _nameFolderOut + '/' + out;
		
		Huffman::Encoding(_name[i], out);
	}
}

//Giai nen ca thu muc
void Folder::DecodeFolder() {

	
	for (int i = 0; i < _name.size(); i++) {

		
		
		string out = _name[i];
		_name[i] = _nameFolder + '/' + _name[i];

		out = _nameFolderOut + '/' + out;
		

		Huffman::Decoding(_name[i], out);
	}
>>>>>>> 8122d14765e38e424439eae958601cd6ff9ec479
}