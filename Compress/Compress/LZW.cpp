#include "LZW.h"


bool LZW::encoding(vector <float> _data, int w, int h, float radius, string fileOut)
{
	unordered_map<string, int> table;
	int next_code = 256;
	vector<int> output_code;

	for (unsigned int i = 0; i < 256; i++)
		table[string(1, (char)i)] = i;

	string result;
	result = _data[0];
	string current_string = "";



	for (int i = 0; i < _data.size(); i++) {
		if (i != _data.size() - 1)
			current_string += _data[i + 1];
		if (table.find(result + current_string) != table.end()) {
			result = result + current_string;
		}
		else {

			output_code.push_back(table[result]);
			table[result + current_string] = next_code;
			next_code++;
			result = current_string;
		}
		current_string.clear();
	}

	output_code.push_back(table[result]);

	ofstream _output(fileOut, ios::out | ios::binary);

	if (!_output) {

		cout << space << "Khong the file nay";
		_output.close();
		return 0;
	}

	_output << CheckFile << "\n";
	_output << w << ' ' << h << ' ' << radius;

	for (int i = 0; i < output_code.size(); i++) {
		int x = output_code[i];
		_output.write(reinterpret_cast<char*> (&x), sizeof(int));
	}
	_output.close();
	return 1;
}

vector<float> LZW::decoding(string fileIn, int &checkDecode)
{
	ifstream _input(fileIn, ios::in | ios::binary);

	vector <float> out;
	if (!_input) {

		_input.close();
		checkDecode = 0;
		return out;
	}

	unordered_map<int, string> table;
	
	int checkData;
	_input >> checkData;

	if (checkData != CheckFile) {

		checkDecode = -1;

		return out;
	}
	//bo 3 so dau
	int ignore;
	_input >> ignore;
	_input >> ignore;
	_input >> ignore;

	

	//doc so dau truoc
	int pre;
	_input.read(reinterpret_cast<char*> (&pre), sizeof(int));
	if (pre > 128)
		out.push_back(pre - 256);
	else
		out.push_back(pre);
	int current;
	string s = table[(pre)];
	string c;
	c = s[0];

	for (int unsigned i = 0; i < 256; i++)
		table[i] = string(1, i);


	
	int count = 256;
	int x;

	while (_input.read(reinterpret_cast<char*> (&x), sizeof(int))) {
		current = x;
		if (table.find(current) == table.end()) {
			s = table[pre];
			s = s + c;
		}
		else {
			s = table[current];
		}
		out.insert(out.end(), s.begin(), s.end());
		c.clear();
		c = s[0];
		table[count] = table[pre] + c;

		pre = current;
		count++;
	}

	_input.close();

	return out;
}