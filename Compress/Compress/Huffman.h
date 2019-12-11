#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_map>

using namespace std;
const string  space = "                                                         ";





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

	static bool CreateNode(string _name, vector <Huffman*>& _arr);	//Tao bang tan so va n cay con dua tren so luong ky tu trong bang tan so

	//Cac ham de xay dung cay Huffman va ma Huffman

	static void QSort(vector <Huffman*>& , int , int );
	static Huffman* CreateTree(vector <Huffman*>& _arr);			//Xay dung cay Huffman
	static void AddCode(Huffman* Root, string _code);				//Tao ma Huffman cho tung ky tu

	//Cac ham  tim kiem

	static vector <char> FindCode(vector <Huffman*>_arr, char c);			//Dua vao ma va tim ky tu cua no	
	static char FindChar(string, vector <Huffman*> _arr, int& flag);		//Dua vao ky tu va tim ma cua no (truyen vao string)
	

	//Cac ham ma hoa

	static int BinaryToDecimal(string& s);						//Chuyen tu nhi phan sang thap phan
	static string DecimalToBinary(int x);						//Chuyen tu thap phan sang nhi phan
	static string BinaryTo256(string& s);						//Chuyen tu nhi phan sang ma 256
	static string _256ToBinary(vector <char>& s);				//Chuyen tu ma 256 sang nhi phan

	// Ham nen file

	static bool Encoding(string _name, string _nameout);		//Nen file

	// Cac ham giai nen file

	static bool Decoding(string _in, string& _out);				//Giai nen file
};
