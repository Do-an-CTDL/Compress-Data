#pragma once
#include <map>
#include <vector>
#include <unordered_map>
#include <iterator>
#include <fstream>
#include <string>
#include <Windows.h>
#include <iostream>
#include <sstream> 


#define CheckFile 7032000
using namespace std;


const string  space = "                                                         ";

class LZW {

public:
	static bool encoding(vector <float>,int, int, float, string);
	static vector <float> decoding(string, int& );
};
