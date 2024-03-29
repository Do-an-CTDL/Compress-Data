#include "Huffman.h"
#include "Folder.h"


Folder::Folder() {

	_name.clear();

}

//Chuyen doi
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
		cout << space << "Khong the tim thay thu muc\n";
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

//Nen ca thu muc
bool Folder::EncodeFolder() {

	bool check = 1;
	for (int i = 0; i < _name.size(); i++) {
		
		
		string out = _name[i];
		_name[i] = _nameFolder + '/' + _name[i];

		out = _nameFolderOut + '/' + out;
		
		//Cat duoi dinh dang ra

		bool flag = 0;
		for (int j = out.size() - 1; j >= 0; j--) {

			if (out[j] == '.') {
				out.erase(j, out.size() - j);
				flag = 1;
				break;
			}
		}
		
		out += '_' + to_string(i);
		
		check = check & Huffman::Encoding(_name[i], out);
	}

	if (check) {
		cout << space << "Ten thu muc giai nen: " << _nameFolderOut << "\n";
		return 1;
	}

	return 0;
}

//Giai nen ca thu muc
bool Folder::DecodeFolder() {

	bool check = 1;
	for (int i = 0; i < _name.size(); i++) {

		
		
		string out = _name[i];
		_name[i] = _nameFolder + '/' + _name[i];

		out = _nameFolderOut + '/' + out;
		
		for (int j = out.size() - 1; j >= 0; j--) {

			if (out[j] == '_') {
				out.erase(j, out.size() - j);

				break;
			}
		}

		check = check & Huffman::Decoding(_name[i], out);
	}

	if (check) {
		cout << space << "Ten thu muc giai nen: " << _nameFolderOut << "\n";
		return 1;
	}
	return 0;
}

//1: nen, 0 giai nen
bool Folder::Input(bool flag) {

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	cout << space << "Nhap ten thu muc: ";
	cin.ignore();
	getline(cin, _nameFolder);
	cout << space << "Xin doi trong giay lat" << endl;

	char* tmp = new char[_nameFolder.size() + 1];



	for (int i = 0; i <= _nameFolder.size(); i++) {

		tmp[i] = (_nameFolder[i]);
	}

	bool check = 0;

	const char* tmp2 = tmp;

	hFind = FindFirstFile(tmp2, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		cout << space << "Khong tim thay thu muc\n";
		return false;
	}
	else
	{

		_name = GetNameFolder(FindFileData.cFileName);
		if (flag == 1) {
			_nameFolderOut = _nameFolder + "_Compress";

			InitFolder();
			check = EncodeFolder();

		}
		else {
			_nameFolderOut = _nameFolder;
			int pos = _nameFolderOut.find("Compress");

			_nameFolderOut.replace(pos, 8, "Decompress");

			InitFolder();
			check = DecodeFolder();

		}
		FindClose(hFind);
	}

	if (!check)
		return 0;


	return true;
}
