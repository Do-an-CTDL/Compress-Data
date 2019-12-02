#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

class GiaoVien {

private:
	int _id;
	string _name;
	float _hs;
	int _basicSalary;
	int _dayOff;

public:
	GiaoVien();
	virtual ~GiaoVien();
	GiaoVien(const GiaoVien&);
	GiaoVien(string, int);
	GiaoVien(string, int, int);
	GiaoVien(string, int, int,float);
	GiaoVien(string, int, int, float, int);
public:

	int GetId();
	string GetName();
	float GetHeSo();
	int GetBasicSalary();
	int GetDayOff();
public:

	void SetId(int);
	void SetName(string);
	void SetHeSo(float);
	void SetBasicSalary(int );
	void SetDayOff(int);
public:

	virtual void Input();
	virtual void Output();
public:

	virtual int Salary();
public:

	virtual int checkLoaiGv();
};