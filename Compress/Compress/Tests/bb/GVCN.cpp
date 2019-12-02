#include "GVCN.h"

GVCN::GVCN() {

	_className = "\n";
}

GVCN::GVCN(GiaoVien a) : GiaoVien(a) {

	_className = "\n";
}

GVCN::GVCN(int Id, string Name, int BasicSalary, float Heso, int DayOff, string ClassName) : GiaoVien(Name, Id, BasicSalary, Heso, DayOff) {

	_className = ClassName;
}

GVCN::GVCN(string ClassName) : GVCN() {

	_className = ClassName;
}

GVCN::GVCN(GiaoVien a, string ClassName) : GiaoVien(a) {

	_className = ClassName;
}

//ham tao sao chep
GVCN::GVCN(const GVCN& a) :GiaoVien((GVCN&)a) {

	_className = a._className;
}

//Ham huy
GVCN::~GVCN() {
	
	_className = "\0";
}

//Ham setter
void GVCN::SetClassName(string ClassName) {

	_className = ClassName;
}

//Ham getter
string GVCN::GetClassName() {

	return _className;
}

//Tinh luong
int GVCN::Salary() {

	return GiaoVien::Salary() + 500000;
}

//Ham Nhap
void GVCN::Input() {

	GiaoVien::Input();
	cout << "Nhap lop day: ";
	cin.ignore();
	getline(cin, _className);
}

//Ham xuat
void GVCN::Output() {

	cout << "Giao Vien Chu Nhiem\n";
	GiaoVien::Output();
	cout << "Lop day: " << _className << "\n";
	
}

//Kiem tra loai Giao vien tra ve 1 la giao vien chu nhiem
int GVCN::checkLoaiGv() {

	return 1;
}