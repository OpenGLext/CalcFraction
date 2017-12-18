#pragma once
#include <iostream>
using namespace std;

class Fraction
{
public:
	Fraction();
	~Fraction();

	typedef struct drob
	{
		int Natur;
		int chisl;
		int znamenatel;
	};
	typedef struct SmDrob
	{
		int Natur;
		int chisl;
		int znamenatel;
	};

	drob drobA, drobB;
	drob *drA, *drB;
	SmDrob smDrobA;

	void ShowDrob(drob a);

	bool CheckDrobObZnamenatel(drob drobA, drob drobB);
	void SummaDrobsPositive();
	void InputDrob();
	void Fraction::ShowDrob(SmDrob smDrobA);
	void GetDrobA();
	void  GetDrobB();
	bool CheckNormalFraction(drob a);
	bool CheckNormalFraction(SmDrob a);
	/* -- перенести в прайвит -- */
	bool CheckSokrDrob(drob a);
	
	void SokrDrob(drob a);
	void NonNormalDrobInSmechannuy();
	/* -- перенести в прайвит -- */

private:

	drob tmp;
	drob summa;

	// наименьший общий делитель
	int NOD(int a, int b);
	int NOK(int a, int b);
	int NOKDrobs(drob drobA, drob drobB);
	bool CheckNormalDrob(drob dr);
	//не нулевая ли дробь? числитель = 0 или грубая ошибка знаменатель = 0
	bool CheckDrobONZero(drob dr);

	
	
	
	
	

	
};

