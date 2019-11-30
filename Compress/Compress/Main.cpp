#include <conio.h>
#include "Huffman.h"


int main() {
	/*vector <char> _name;
	cout << "Input name: ";
	getline(cin, _name);*/

	string _in = "University.exe";
	string b = "a.bmp";
	string _out = "result.bmp";
	string a = "test01";
	
	
	

	
	Huffman::Encoding(b);
	
	//cout << int('•');
	Huffman::Decoding(a,_out);

	

	return 0;
	//_getch();
}