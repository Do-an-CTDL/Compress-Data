#include "Huffman.h"

//--------------
//CAC HAM KHOI TAO VA HAM HUY

Huffman::Huffman() {
	_char = NULL;
	_frq = 0;
	_left = NULL;
	_right = NULL;
}

Huffman::Huffman(char c) {
	_char = c;
	_frq = 1;
	_left = NULL;
	_right = NULL;
}

Huffman::~Huffman() {
	if (_left != NULL) {
		delete _left;
	}
	if (_right != NULL) {
		delete _right;
	}

}

//------------
//CAC HAM GETTER VA SETTER

char Huffman::GetChar() const {
	return _char;
}

string Huffman::GetCode() const {
	return _code;
}

int Huffman::GetFreq() const {
	return _frq;
}

void Huffman::SetChar(char c) {
	_char = c;
}

void Huffman::SetCode(string s) {
	_code = s;
}

//--------------
//CAC HAM DE TAO BANG TAN SO

int Huffman::IsAvailable(char c, vector <Huffman*> _arr) {
	for (int i = 0; i < _arr.size(); i++) {
		if (_arr[i]->_char == c) {
			return i;
		}
	}
	return -1;
}

void Huffman::CreateNode(string _name, vector <Huffman*>& _arr) {

	//Mo file
	ifstream _input;
	_input.open(_name, ios::in | ios::binary);


	if (_input.fail()) {
		cout << space << "Khong the mo file nay" << endl;
		return;
	}

	//Duyet file va tao bang tan so
	while (!_input.eof()) {
		char* Buffer = new char;
		if (_input.read(Buffer, 1)) {
			int pos = IsAvailable(*Buffer, _arr);
			if (pos != -1) {							//Kiem tra ki tu do da co trong bang chua		
				_arr[pos]->_frq++;						//Neu roi thi tang tan so
			}
			else {
				Huffman* tmp = new Huffman(*Buffer);	//Neu chua thi tao moi va them vao bang
				_arr.push_back(tmp);
			}
		}
		delete Buffer;
	}

	//Dong flie
	_input.close();
}

//----------------
//CAC HAM DE TAO CAY HUFFMAN VA MA HUFFMAN

void Huffman::Arrange(vector <Huffman*>& _arr) {
	for (int i = 0; i < _arr.size() - 1; i++) {
		for (int j = i + 1; j < _arr.size(); j++) {
			if (_arr[i]->_frq > _arr[j]->_frq) {
				swap(_arr[i], _arr[j]);
			}
		}
	}
}

Huffman* Huffman::CreateTree(vector <Huffman*>& _arr) {
	/*Thuat toan xay dung cay Huffman
	Su dung thuat toan tham lam de tao cay
	Lan luot 2 nut co trong so nho nhat trong bang (2 nut dau bang)
	va tao mot nut cha co ky tu la NULL va tan so bang tong tan so cua 2 nut con
	va co 2 con la 2 nut do. Lap lai cho den khi trong bang chi con 1 nut duy nhat*/

	while (_arr.size() != 1) {
		Arrange(_arr);									//Sap xep lai bang tan so theo thu tu tang dan
		Huffman* tmp = new Huffman;
		tmp->_char = NULL;								//Tao nut cha co ky tu la NULL
		tmp->_frq = _arr[0]->_frq + _arr[1]->_frq;		//va co tan so bang tong tan so cua 2 nut con
		tmp->_left = _arr[0];							//Gan 2 nut con vao nut cha
		tmp->_right = _arr[1];
		_arr.push_back(tmp);							//Them nut cha moi vua tao vao bang tan so
		_arr.erase(_arr.begin(), _arr.begin() + 2);		//Xoa 2 nut con vua su dung ra khoi banhg
	}
	return _arr[0];										//Tra gia tri cua nut goc cua cay Huffman
}

void Huffman::AddCode(Huffman* _root, string code) {
	/*Y tuong de sinh ma Huffman
	Moi ky tu bay gio la deu la nut la cua cay ma Huffman la duong di tu nut goc den nut la do
	Neu di sang trai thi them bit 0, sang phai thi them bit 1*/

	if (_root->_left == NULL && _root->_right == NULL) {
		_root->_code = code;
	}
	else {
		AddCode(_root->_left, code + '0');
		AddCode(_root->_right, code + '1');
	}
}

//----------
//CAC HAM TIM KIEM

vector <char> Huffman::FindCode(vector <Huffman*> _arr, char c) {
	string s;
	for (int i = 0; i < _arr.size(); i++) {
		if (_arr[i]->_char == c) {
			s = _arr[i]->_code;
			break;
		}
	}
	vector<char> S;
	for (int i = 0; i < s.length(); i++) {
		S.push_back(s[i]);
	}
	return S;
}

char Huffman::FindChar(string s, vector <Huffman*> _arr, int& flag) {
	for (int i = 0; i < _arr.size(); i++) {
		if (_arr[i]->_code == s) {
			flag = 1;
			return _arr[i]->_char;
		}
	}
	return EOF;
}

char Huffman::FindChar(vector <char> s, vector <Huffman*> _arr, int& flag) {

	for (int i = 0; i < _arr.size(); i++) {

		int n = min(s.size(), _arr[i]->_code.length());

		int check = 0;
		for (int j = 0; j < n; j++) {

			if (s[j] != _arr[i]->_code[j]) {
				check = 1;
				break;
			}
		}

		if (!check && s.size() == _arr[i]->_code.size()) {

			flag = 1;
			return _arr[i]->_char;
		}
	}
	return EOF;
}

//-----------
//CAC HAM MA HOA


int Huffman::BinaryToDecimal(string& s) {
	int result = 0;
	for (int i = 0; i < s.size(); i++)
		result = result * 2 + s[i] - '0';
	return result;
}

string Huffman::DecimalToBinary(int x)
{
	string temp = "";
	string result = "";

	while (x) {
		temp += ('0' + x % 2);
		x /= 2;
	}

	result.append(8 - temp.size(), '0');
	for (int i = temp.size() - 1; i >= 0; i--) {
		result += temp[i];
	}

	return result;
}

vector <char> Huffman::BinaryTo64(string& s) {
	vector <Huffman*> _dic;							//Tao bang ma 64

	for (int i = 0; i < 64; i++) {
		_dic.resize(i + 1);
		_dic[i] = new Huffman;
		if (i < 10) {
			_dic[i]->_char = i + '0';				//Tu 0-9 se quy dinh ma la 0-9
		}
		else if (i >= 10 && i <= 35) {
			_dic[i]->_char = char(65 + i - 10);		//Tu 10-35 se quy dinh ma la A-Z
		}
		else {
			_dic[i]->_char = char(97 + i - 36);		//Tu 36 tro di se quy dinh la tu a tro di
		}
		_dic[i]->_code = DecimalToBinary(i);
	}

	while (s.size() % 6 != 0) {						//Them cho du so bit
		s = '0' + s;
	}

	vector <char> result;

	for (int i = 0; i < s.length(); i += 6) {
		string tmp = s.substr(i, 6);
		for (int i = 0; i < 2; i++) {
			tmp = '0' + tmp;
		}
		int x;
		result.push_back(FindChar(tmp, _dic, x));
	}

	for (int i = 0; i < _dic.size(); i++) {
		delete _dic[i];
	}
	_dic.clear();
	return result;
}

vector <char> Huffman::_64ToBinary(string& s) {
	vector <Huffman*> _dic;									//Tao bang tra cuu
	for (int i = 0; i < 64; i++) {
		_dic.resize(i + 1);
		_dic[i] = new Huffman;
		if (i < 10) {
			_dic[i]->_char = i + '0';
		}
		else if (i >= 10 && i <= 35) {
			_dic[i]->_char = char(65 + i - 10);
		}
		else {
			_dic[i]->_char = char(97 + i - 36);
		}
		_dic[i]->_code = DecimalToBinary(i);
	}

	vector <char> result;
	for (int i = 0; i < s.length(); i++) {
		vector <char> tmp = FindCode(_dic, s[i]);
		tmp.erase(tmp.begin(), tmp.begin() + 2);
		result.insert(result.end(), tmp.begin(), tmp.end());
	}

	for (int i = 0; i < _dic.size(); i++) {
		delete _dic[i];
	}
	_dic.clear();
	return result;
}

//-------------
//HAM NEN FILE

void Huffman::Encoding(string _name, string _nameOut) {

	//Lay phan mo rong cua file can nen
	string filename = "";
	for (int i = _name.size() - 1; i >= 0; i--) {
		if (_name[i] == '.') {
			filename = _name.substr(i);
		}
	}

	vector <Huffman*> _arr;
	CreateNode(_name, _arr);
	vector <Huffman*> _tmp = _arr; //Sao chep mang luu tru cac ky tu

	//Tao ma cho tung nut
	/*Neu so luong ky tu trong bang tan so lon hon 1 thi ta tien hanh
	xay cay va sinh ma Huffman, nguoc lai ta khong xay cay va mac dinh
	ma Huffman cua no la '0' (TH file chi co 1 ky tu lap di lap lai nhieu lan*/

	if (_arr.size() > 1) {
		string code = "";
		AddCode(CreateTree(_arr), code);
	}
	else {
		_arr[0]->_code = '0';
	}

	//Mo file
	fstream _input;
	fstream _output;
	_input.open(_name, ios::in | ios::binary);
	_output.open(_nameOut, ios::out | ios::binary);

	if (_input.fail()) {
		cout << space << "Khong the mo file nay" << endl;
		return;
	}
	
	//Bat dau ma hoa
	_output << filename << "\n";				//Luu tru lai phan mo rong de su dung trong luc giai nen
	
	//Luu tru cay Huffman de su dung trong viec giai nen
	_output << _tmp.size() << "\n";				//Ghi lai so luong ki tu trong bang tan so

	for (int i = 0; i < _tmp.size(); i++) {
		_output << int(_tmp[i]->_char) << " ";  //Ghi lai ki tu va tan so cua chung
		_output << _tmp[i]->_frq << "\n";
	}

	/*Chuyen tat ca cac ki tu trong file can ma hoa sang ma nhi phan va luu tru
	trong vector <char> s*/
	vector <char> s;
	while (!_input.eof()) {
		char* Buffer = new char;
		if (_input.read(Buffer, 1)) {
			vector<char> ss = FindCode(_tmp, *Buffer);
			s.insert(s.end(), ss.begin(), ss.end());
		}
		delete Buffer;
	}

	/*Ghi lai chieu dai cua ma nhi phan da ma hoa vi luc giai chuoi se duoc them
	nhung bit 0 o dau cho du bit va lam thay doi chieu dai */
	_output << s.size() << "\n";

	//Chuyen chuoi nhi phan vua ma hoa thanh bang he 64
	string ss;
	for (int i = 0; i < s.size(); i++) {
		ss += s[i];
	}
	s = BinaryTo64(ss);

	//Chep chuoi 64 vua ma hoa vao file ket qua
	for (int i = 0; i < s.size(); i++) {
		_output << s[i];
	}

	//Giai phong bo nho
	for (int i = 0; i < _tmp.size(); i++) {
		delete _tmp[i];
	}
	_arr.clear();
	_tmp.clear();


	//Dong file
	_input.close();
	_output.close();
}

//--------
//HAM GIAI NEN FILE

void Huffman::Split(string& s, char& c, int& frq) {
	//Cau truc 1 dong nhu sau
	//Ma ascii cua ki tu - tan so (ngan cach boi dau cach)

	string tmp;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == ' ') {
			string ss = s.substr(i + 1);
			frq = atoi(ss.c_str());			//Luu lai tan so
			break;
		}
		tmp += s[i];
	}
	int x = atoi(tmp.c_str());
	c = char(x);							//Luu lai ky tu
}

void Huffman::Decoding(string _name, string& _out) {
	fstream _input;
	_input.open(_name, ios::in | ios::binary);
	if (_input.fail()) {
		cout << space << "Khong the mo file" << endl;
		return;
	}

	//Lay phan mo rong cua file can giai nen
	string filename;
	getline(_input, filename);
	_out += filename;
	

	//Xay lai cay va tao bang ma Huffman cua ky tu

	vector <Huffman*> _dic;							//Bang de tra cuu ma Huffman
	string buffer;									//Xu ly bo nho dem

	int N;											//Ghi lai so luong ky tu co trong bang tan so
	_input >> N;
	getline(_input, buffer);						//Doi vi tri con tro

	//Tao bang tan so
	for (int i = 0; i < N; i++) {
		string tmp;
		getline(_input, tmp);
		Huffman* a = new Huffman;
		Split(tmp, a->_char, a->_frq);
		_dic.push_back(a);
	}

	//Xay lai cay va sinh ma Huffman
	if (_dic.size() > 1) {
		vector <Huffman*> tmp = _dic;
		AddCode(CreateTree(tmp), "");
		tmp.clear();
	}
	else {
		_dic[0]->_code = '0';
	}

	//Lay do dai cua chuoi ban dau (vi khi ma hoa co them bit '0' de du bit)
	
	int len;
	_input >> len;
	getline(_input, buffer);							//Doi vi tri con tro

	string _data;										//Luu tru ma can ma hoa
	getline(_input, _data);
	_input.close();

	vector <char> a;									//Chua chuoi sau khi ma hoa
	a = _64ToBinary(_data);								//Ma hoa chuoi he 64 thanh he nhi phan
	if (a.size() > len) {								//Chuan hoa chuoi thanh co so bit bang dung chuoi ban dau
		a.erase(a.begin(), a.begin() + a.size() - len);
	}

	//Bat dau ma hoa 
	fstream _output;
	_output.open(_out, ios::out | ios::binary);

	vector <char> s; //chuoi s de luu chuoi
	vector <char> s1; //chuoi s1 dung de so sanh

	int flag1 = 0, flag2 = 0;						//Thu thuat co hieu, flag = 1 khi tim duoc ky tu
	for (int i = 0; i < a.size(); i++) {

		s.push_back(a[i]);
		if (i + 1 < a.size()) {
			s1 = s;
			s1.push_back(a[i + 1]);
		}
		else
			s1.push_back('3');
		char a = FindChar(s, _dic, flag1);
		char b = FindChar(s1, _dic, flag2);
		if (flag1 == 1 && flag2 == 0) {

			_output << a;
			s.clear();
			s1.clear();
		}
		flag1 = flag2 = 0;


	}

	_output.close();

	//Giai phong bo nho
	for (int i = 0; i < _dic.size(); i++) { 
		delete _dic[i];
	}
}
