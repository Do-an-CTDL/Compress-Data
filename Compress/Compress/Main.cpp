#include <conio.h>
#include "Huffman.h"


int main() {
	/*vector <char> _name;
	cout << "Input name: ";
	getline(cin, _name);*/

<<<<<<< HEAD
	//string _in = "University.exe";
	/*string b = "test.txt";
	string _out = "result.txt";
	string a = "test01";*/
	//
=======
	string _in = "University.exe";
	string b = "a.bmp";
	string _out = "result.bmp";
	string a = "test01";
	
>>>>>>> e2dc90d750a8b5f0ff7dcc256286b37b8500eb7d
	
	
	////Huffman::Encoding(b);
	//
	////Huffman::Decoding(a,_out);

	
<<<<<<< HEAD
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
=======
	Huffman::Encoding(b);
	
	//cout << int('•');
	Huffman::Decoding(a,_out);
>>>>>>> e2dc90d750a8b5f0ff7dcc256286b37b8500eb7d


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