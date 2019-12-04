#include "GiaoVien.h"

//Cac ham khoi tao
GiaoVien::GiaoVien() {

	_id = 0;
	_name = "\0";
	_basicSalary = 0;
	_hs = 0;
	_dayOff = 0;
}

GiaoVien::GiaoVien(string name, int id) {

	_name = name;
	_id = id;
	_basicSalary = 0;
	_hs = 0;
	_dayOff = 0;

}

GiaoVien::GiaoVien(string name, int id, int basicSalary) {

	_name = name;
	_id = id;
	_basicSalary = basicSalary;
	_hs = 0;
	_dayOff = 0;

}

GiaoVien::GiaoVien(string name, int id, int basicSalary, float hs) {

	_name = name;
	_id = id;
	_basicSalary = basicSalary;
	_hs = hs;
	_dayOff = 0;

}

GiaoVien::GiaoVien(string name, int id, int basicSalary, float hs, int dayOff) {

	_name = name;
	_id = id;
	_basicSalary = basicSalary;
	_hs = hs;
	_dayOff = dayOff;

}


//Ham Sao Chep
GiaoVien::GiaoVien(const GiaoVien& a) {

	_name = a._name;
	_id = a._id;
	_basicSalary = a._basicSalary;
	_hs = a._hs;
	_dayOff = a._dayOff;
}

//ham Huy
GiaoVien::~GiaoVien() {

	_id = 0;
	_name = "\0";
	_basicSalary = 0;
	_hs = 0;
	_dayOff = 0;
}

//Ham Getter
int GiaoVien::GetId() {

	return _id;
}

string GiaoVien::GetName() {

	return _name;
}

int GiaoVien::GetBasicSalary() {

	return _basicSalary;
}

float GiaoVien::GetHeSo() {

	return _hs;
}

int GiaoVien::GetDayOff() {

	return _dayOff;
}

//Cac ham setter
void GiaoVien::SetId(int id) {

	_id = id;
}

void GiaoVien::SetName(string name) {

	_name = name;
}

void GiaoVien::SetBasicSalary(int basicSalary) {

	_basicSalary = basicSalary;
}

void GiaoVien::SetHeSo(float heSo) {

	_hs = heSo;
}

void GiaoVien::SetDayOff(int dayOff) {

	_dayOff = dayOff;
}


//Nhap
void GiaoVien::Input() {

	cout << "Nhap ma giao vien: ";
	cin >> _id;
	cin.ignore();

	cout << "Nhap ten giao vien: ";
	getline(cin, _name);

	cout << "He so luong: ";
	cin >> _hs;

	cout << "Nhap Luong co ban: ";
	cin >> _basicSalary;

	cout << "So ngay nghi: ";
	cin >> _dayOff;
}

void GiaoVien::Output() {

	cout << "Ma giao vien: " << _id << "\n";
	cout << "Ten giao vien: " << _name << "\n";
	cout << "Luong co ban: " << _basicSalary << "\n";
	cout << "He so luong: " << _hs << "\n";
	cout << "So ngay nghi: " << _dayOff << "\n";
}

//tinh luong
int GiaoVien::Salary() {

	return _hs * _basicSalary - _dayOff * 100000;
}


//Kiem tra loai giao vien tra ve 0 la giao vien khong chu nhiem
int GiaoVien::checkLoaiGv() {

	return 0;
}
