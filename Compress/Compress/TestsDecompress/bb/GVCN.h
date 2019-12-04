#pragma once
#include "GiaoVien.h"

class GVCN : public GiaoVien {

	string _className;

public:

	GVCN();
	GVCN(int, string, int, float, int, string);
	GVCN(GiaoVien);
	GVCN(string);
	GVCN(GiaoVien, string);

	GVCN(const GVCN&);
	~GVCN();
public:

	void SetClassName(string);
public:

	string GetClassName();
public:

	void Input();
	void Output();
public:

	int Salary();
public:

	int checkLoaiGv();
};