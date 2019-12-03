#include "LZW.h"


void LZW::encoding(vector <float> _data,int w, int h, float radius,  string fileOut)
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

	_output << w << ' ' << h << ' ' << radius << "\n";

	for (int i = 0; i < output_code.size(); i++)
		_output << output_code[i] << ' ';

	_output.close();

}

vector<float> LZW::decoding(string fileIn)
{
	ifstream _input(fileIn, ios::in | ios::binary);

	unordered_map<int, string> table;
	vector <float> out;

	//bo 3 so dau
	int ignore;
	_input >> ignore;
	_input >> ignore;
	_input >> ignore;

	int pre;

	//doc so dau truoc
	_input >> pre;
	if (pre > 0)
		out.push_back(pre - 256);
	else
		out.push_back(pre);
	int current;
	string s = table[(pre)];
	string c;
	c = s[0];

	for (int unsigned i = 0; i < 256; i++)
		table[i] = string(1, i);


	//cout << s;
	int count = 256;
	int x;
	
	while (_input >> x) {
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