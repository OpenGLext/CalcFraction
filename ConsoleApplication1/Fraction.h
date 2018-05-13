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
	SmDrob smDrobA,smDrobB;

	void ShowDrob(drob a);

	bool CheckDrobObZnamenatel(drob drobA, drob drobB);
	bool CheckDrobObZnamenatel(SmDrob a, SmDrob b);
	void SummaDrobsPositive();
	void SummaSmFractions(SmDrob a, SmDrob b);
	void InputDrob();
	void InputDrobSm(SmDrob a, SmDrob b);
	void Fraction::ShowDrob(SmDrob smDrobA);
	void GetDrobA();
	void  GetDrobB();
	bool CheckNormalFraction(drob a);
	bool CheckNormalFraction(SmDrob a);
	/* -- ��������� � ������� -- */
	bool CheckSokrDrob(drob a);
	void CreateObZnamenatel(drob drobA, drob drobB);
	
	void SokrDrob(drob a);
	void NonNormalDrobInSmechannuy();
	/* -- ��������� � ������� -- */

private:

	drob tmpA,tmpB,tmp;
	drob summa;
	drob w, t, q;

	// ���������� ����� ��������
	int NOD(int a, int b);
	int NOK(int a, int b);
	int NOKDrobs(drob drobA, drob drobB);
	bool CheckNormalDrob(drob dr);
	//�� ������� �� �����? ��������� = 0 ��� ������ ������ ����������� = 0
	bool CheckDrobONZero(drob dr);

	
	
	
	
	

	
};

