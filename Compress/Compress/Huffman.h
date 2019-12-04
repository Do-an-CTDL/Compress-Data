#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

class Huffman {
private:
	char _char;					//Ki tu luu tru
	int _frq;					//Tan so xuat hien cua ki tu do
	string _code;				//Ma Huffman cua ki tu do
	Huffman* _left;				//Dia chi cua nut ben trai trong cay Huffman
	Huffman* _right;			//Dia chi cua nut ben phai trong cay Huffman
public:

	//Cac ham khoi tao va ham huy

	Huffman();					//Ham tao khong doi so
	Huffman(char);				//Ham tao co doi so la char
	virtual ~Huffman();			//Ham huy
	

	//Cac ham setter va getter

	char GetChar() const;		//Lay ki tu cua doi tuong
	string GetCode() const;		//Lay ma Huffman cua doi tuong
	int GetFreq() const;		//Lay tan so cua doi tuong
	void SetChar(char);			//Cai dat ki tu cho doi tuong
	void SetCode(string);		//Cai dat ma cho doi tuong

	// Cac ham de tao bang tan so

	static int IsAvailable(char c, vector <Huffman*>_arr);			//Kiem tra ky tu do da xuat hien chua
	static void CreateNode(string _name, vector <Huffman*>& _arr);	//Tao bang tan so va n cay con dua tren so luong ky tu trong bang tan so

	//Cac ham de xay dung cay Huffman va ma Huffman

	static void Arrange(vector <Huffman*>& _arr);					//Sap xep bang tan so theo thu tu tan so tang dan
	static Huffman* CreateTree(vector <Huffman*>& _arr);			//Xay dung cay Huffman
	static void AddCode(Huffman* Root, string _code);				//Tao ma Huffman cho tung ky tu

	//Cac ham  tim kiem

	static vector <char> FindCode(vector <Huffman*>_arr, char c);			//Dua vao ma va tim ky tu cua no	
	static char FindChar(string, vector <Huffman*> _arr, int& flag);		//Dua vao ky tu va tim ma cua no (truyen vao string)
	static char FindChar(vector <char>, vector <Huffman*> _arr, int& flag);	//Dua vao ky tu va tim ma cua no (truyen vao vector <char>)

	//Cac ham ma hoa

	static int BinaryToDecimal(string& s);						//Chuyen tu nhi phan sang thap phan
	static string DecimalToBinary(int x);						//Chuyen tu thap phan sang nhi phan
	static vector <char> BinaryTo64(string& s);					//Chuyen tu nhi phan sang ma 64
	static vector <char> _64ToBinary(string& s);				//Chuyen tu ma 64 sang nhi phan

	// Ham nen file

	static void Encoding(string _name, string _nameout);		//Nen file

	// Cac ham giai nen file

	static void Split(string& s, char& c, int& frq);			//Tach du lieu cua tung dong
	static void Decoding(string _in, string& _out);				//Giai nen file
};

