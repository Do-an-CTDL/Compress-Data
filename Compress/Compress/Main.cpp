#include <conio.h>
#include "Huffman.h"


int main() {
	/*vector <char> _name;
	cout << "Input name: ";
	getline(cin, _name);*/

	//string _in = "University.exe";
	/*string b = "test.txt";
	string _out = "result.txt";
	string a = "test01";*/
	//
	
	
	////Huffman::Encoding(b);
	//
	////Huffman::Decoding(a,_out);

	
	vector <float*> a;
	for (int i = 0; i < 3; i++) {
		float* b = new float;
		*b = 65 + i;
		a.push_back(b);
	}
	Huffman::EncodingBitmap(a);
	for (int i = 0; i < 3; i++) {
		delete a[i];
	}


	string aa = "test02";
	vector <float*> b = Huffman::DecodingBitmap(aa);

	for (int i = 0; i < b.size(); i++) {
		cout << *b[i] << " ";
	}
	for (int i = 0; i < b.size(); i++) {
		delete b[i];
	}
	b.clear();

	return 0;
	//_getch();
}