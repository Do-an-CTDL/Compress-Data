#include <conio.h>
#include "Huffman.h"


int main() {
	/*string _name;
	cout << "Input name: ";
	getline(cin, _name);*/

	string _in = "University.exe";
	string b = "test.txt";
	string _out = "result.exe";
	string a = "test01";
	
	/*fstream _input;
	_input.open(a, ios::in | ios::binary);
	vector <char> _Data;
	int flag = 0;
	for (int i = 0;;) {
		char* Buffer = new char;
		if (_input.read(Buffer, 1)) {
			if (*Buffer == NULL) {
				if (flag == 1) {
					break;
				}
				else {
					flag = 1;
					_Data.push_back(*Buffer);
				}
			}
			_Data.push_back(*Buffer);
		}
		delete Buffer;

	}
	_input.close();

	cout << _Data.size();*/



	
	//Huffman::Encoding(_in);
	Huffman::Decoding(a,_out);

	

	return 0;
	_getch();
}