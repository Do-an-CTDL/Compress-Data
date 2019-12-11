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

bool Huffman::CreateNode(string _name, vector <Huffman*>& _arr) {

	//Mo file
	ifstream _input;
	_input.open(_name, ios::in | ios::binary);


	if (_input.fail()) {
		cout << space << "Khong the mo file nay" << endl;
		return false;
	}

	

	
	int Table[256];
	for (int i = 0; i < 256; i++)
		Table[i] = -1;

	//Duyet file va tao bang tan so
	int dem = 0;
	while (!_input.eof()) {
		char* Buffer = new char;
		if (_input.read(Buffer, 1)) {
			int pos = -1;

			pos = Table[int(unsigned char(*Buffer))];

			if (pos != -1) {							//Kiem tra ki tu do da co trong bang chua		
				_arr[pos]->_frq++;						//Neu roi thi tang tan so
			}
			else {
				Table[int(unsigned char(*Buffer))] = dem++;
				Huffman* tmp = new Huffman(*Buffer);	//Neu chua thi tao moi va them vao bang
				_arr.push_back(tmp);
			}
		}
		delete Buffer;
	}

	//Dong flie
	_input.close();
	return true;
}

//----------------
//CAC HAM DE TAO CAY HUFFMAN VA MA HUFFMAN
void Huffman::QSort(vector <Huffman*> & a, int l, int r) {

	int x = a[(l + r) / 2]->_frq;
	int i = r;
	int j = l;
	while (i > j) {
		while (a[i]->_frq > x) i--;
		while (a[j]->_frq < x) j++;

		if (i >= j) {

			swap(a[i], a[j]);
			i--;
			j++;
		}
	}

	if (i > l)
		QSort(a, l, i);

	if (j < r)
		QSort(a, j, r);

}


Huffman* Huffman::CreateTree(vector <Huffman*>& _arr) {
	/*Thuat toan xay dung cay Huffman
	Su dung thuat toan tham lam de tao cay
	Lan luot 2 nut co trong so nho nhat trong bang (2 nut dau bang)
	va tao mot nut cha co ky tu la NULL va tan so bang tong tan so cua 2 nut con
	va co 2 con la 2 nut do. Lap lai cho den khi trong bang chi con 1 nut duy nhat*/
	//Sap xep lai bang tan so theo thu tu tang dan
	
	while (_arr.size() != 1) {
		QSort(_arr, 0, _arr.size() - 1);
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
//
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

string Huffman::BinaryTo256(string& s) {
	vector <Huffman*> _dic;							//Tao bang ma 256

	_dic.resize(256);
	unordered_map<string, char> table;

	string x ;
	for (int i = 0; i < 256; i++) {

		x = DecimalToBinary(i);
		table[x] = i;
		
	}

	while (s.size() % 8 != 0) {						//Them cho du so bit
		s = '0' + s;
	}

	string result;

	for (int i = 0; i < s.length(); i += 8) {
		string tmp = s.substr(i, 8);
		

		result.push_back(table[tmp]);

	}

	for (int i = 0; i < _dic.size(); i++) {
		delete _dic[i];
	}
	_dic.clear();
	return result;
}

string Huffman::_256ToBinary(vector <char> & s) {
	
	vector <Huffman*> _dic;							//Tao bang ma 256
	
	string table[256];

	string x;
	for (int i = 0; i < 256; i++) {
		table[i] = DecimalToBinary(i);

	}

	string result;
	for (int i = 0; i < s.size(); i++) {
		
		
		result += table[int(unsigned char(s[i]))];
	}

	for (int i = 0; i < _dic.size(); i++) {
		delete _dic[i];
	}
	_dic.clear();
	return result;
}
//-------------
//HAM NEN FILE

bool Huffman::Encoding(string _name, string _nameOut) {

	//Lay phan mo rong cua file can nen
	string filename = "";
	for (int i = _name.size() - 1; i >= 0; i--) {
		if (_name[i] == '.') {
			filename = _name.substr(i);
		}
	}

	vector <Huffman*> _arr;
	if (!CreateNode(_name, _arr)) {
		return false;
	}
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
		return false;
	}
	
	//Bat dau ma hoa
	_output << filename << "\n";				//Luu tru lai phan mo rong de su dung trong luc giai nen
	
	//Luu tru cay Huffman de su dung trong viec giai nen
	_output << _tmp.size() << "\n";				//Ghi lai so luong ki tu trong bang tan so
	
	for (int i = 0; i < _tmp.size(); i++) {
		_output.write(&_tmp[i]->_char, sizeof(char)) ;  //Ghi lai ki tu va tan so cua chung
		
		_output.write(reinterpret_cast<char*> (&_tmp[i]->_frq), sizeof(int));
	}
	
	//Tao tu dien
	unordered_map<char, string> table;

	for (int i = 0; i < _tmp.size(); i++) {
		table[char(_tmp[i]->_char)] = _tmp[i]->_code;
	}
	
	string Table[256];

	for (int i = 0; i < _tmp.size(); i++) {

		Table[int(unsigned char(_tmp[i]->_char))] = _tmp[i]->_code;
	}

	/*Chuyen tat ca cac ki tu trong file can ma hoa sang ma nhi phan va luu tru
	trong vector <char> s*/
	string s;
	string Code;
	while (!_input.eof()) {
		char* Buffer = new char;
		if (_input.read(Buffer, 1)) {
			s += Table[int(unsigned char(*Buffer))];
		}
		delete Buffer;
	}
	
	/*Ghi lai chieu dai cua ma nhi phan da ma hoa vi luc giai chuoi se duoc them
	nhung bit 0 o dau cho du bit va lam thay doi chieu dai */
	//_output << s.size() << "\n";
	int size = s.size();
	_output.write(reinterpret_cast<char*>(& size), sizeof(int));
	//Chuyen chuoi nhi phan vua ma hoa thanh bang he 256
	

	s = BinaryTo256(s);
	
	//Chep chuoi 256 vua ma hoa vao file ket qua
	for (int i = 0; i < s.size(); i++) {
		_output.write(&s[i], sizeof(char));
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
	return true;
}

//--------
//HAM GIAI NEN FILE


bool Huffman::Decoding(string _name, string& _out) {
	fstream _input;
	_input.open(_name, ios::in | ios::binary);
	if (_input.fail()) {
		cout << space << "Khong the mo file" << endl;
		return false;
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
		
		char c;
		int f;
		_input.read(&c, sizeof(char));

		_input.read(reinterpret_cast<char*> (&f), sizeof(int));
		Huffman* a = new Huffman;
		
		a->_char = c;
		a->_frq = f;
		_dic.push_back(a);

		char ignore;

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

	unordered_map<string, char> table;


	for (int i = 0; i < _dic.size(); i++) {

		table[(_dic[i]->_code)] = _dic[i]->_char;
	}
	//Lay do dai cua chuoi ban dau (vi khi ma hoa co them bit '0' de du bit)
	
	int len;
	_input.read(reinterpret_cast<char*> (&len), sizeof(int));


	vector <char> _data ;											//Luu tru ma can ma hoa
	char c;
	while (_input.read(&c, sizeof(char))) {

		_data.push_back(c);
	}

	
	_input.close();
		
	string a;										//Chua chuoi sau khi ma hoa
	a = _256ToBinary(_data);

	if (a.size() > len) {								//Chuan hoa chuoi thanh co so bit bang dung chuoi ban dau
		a.erase(a.begin(), a.begin() + a.size() - len);
	}

	//Bat dau ma hoa 
	fstream _output;
	_output.open(_out, ios::out | ios::binary);

	string s; //chuoi s de luu chuoi
	string s1; //chuoi s1 dung de so sanh

	bool flag1 = 0, flag2 = 0;						//Thu thuat co hieu, flag = 1 khi tim duoc ky tu
	for (int i = 0; i < a.size(); i++) {

		s.push_back(a[i]);
		if (i + 1 < a.size()) {
			s1 += s;
		}
		else
			s1.push_back('3');

		char finda, findb;
		if (table.find(s) != table.end()) {
			flag1 = 1;
			finda = table.find(s)->second;
		}
		if (table.find(s1) != table.end()) {
			flag2 = 1;
		}

		if (flag1 == 1 && flag2 == 0) {

			_output.write(&finda, sizeof(char));
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
	return true;
}



