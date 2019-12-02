<<<<<<< HEAD
#include "Huffman.h"
#include "Folder.h"
#include "Menu.h"
#include <conio.h>


int main() {
	Menu::ZoomConsole();
	Menu::Select();
=======
#include <conio.h>
#include "Folder.h"


int main() {
	/*vector <char> _name;
	cout << "Input name: ";
	getline(cin, _name);*/

	//string _in = "University.exe";
	/*string b = "test.txt";
	string _out = "result.txt";
	string a = "test01";*/
	//


	string _in = "University.exe";
	string b = "a.bmp";
	string _out = "result.bmp";
	string a = "test01";
	

	
	
	Folder thuMuc;


	//Nen
	thuMuc.Input(1);
	
	//Giai nen
	thuMuc.Input(0);

	
>>>>>>> 8122d14765e38e424439eae958601cd6ff9ec479

	return 0;
}