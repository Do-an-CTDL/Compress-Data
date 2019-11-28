#include <conio.h>
#include "Huffman.h"


int main() {
	/*string _name;
	cout << "Input name: ";
	getline(cin, _name);*/

	string _name = "test.txt";
	

	Huffman::Encoding(_name);
	
	//Huffman::Decoding(_name);

	//_input.close();


	return 0;
	_getch();
}