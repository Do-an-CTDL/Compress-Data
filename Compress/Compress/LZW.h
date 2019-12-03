#pragma once
#include <map>
#include <vector>
#include <unordered_map>
#include <iterator>
#include <fstream>
#include <string>
#include <Windows.h>
#include <iostream>
#include <vector>
#include <sstream> 

using namespace std;
class LZW {

public:
	static void encoding(vector <float>,int, int, float, string);
	static vector <float> decoding(string);
};
