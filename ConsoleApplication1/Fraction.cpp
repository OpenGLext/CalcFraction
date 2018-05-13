#include "Fraction.h"

Fraction::Fraction()
{
}
Fraction::~Fraction()
{
}
void Fraction::InputDrob()
{
	std::cin >> drobA.chisl >> drobA.znamenatel >> drobB.chisl >> drobB.znamenatel;
	if (!CheckDrobONZero(drobA) && !CheckDrobONZero(drobB))
	{
		std::cout << "����� �������,���������� �� ����� ������" << endl;
		exit;
		if (!CheckDrobONZero(drobA) || !CheckDrobONZero(drobB))
		{
			std::cout << "����� �������,���������� �� ����� ������" << endl;
			exit;
		}

		if (!CheckNormalDrob(drobA))
		{
			std::cout << "��������� ������ �����������,��������� ����� � ���������" << endl;
			NonNormalDrobInSmechannuy();
			ShowDrob(smDrobA);
		}
	}
}
void Fraction::InputDrobSm(SmDrob a, SmDrob b)
{
	std::cin >> a.Natur >> a.chisl >> a.znamenatel >> b.Natur >> b.chisl >> b.znamenatel;
}
void  Fraction::ShowDrob(SmDrob smDrobA)
{
		if (smDrobA.Natur >= 1 && smDrobA.znamenatel > 1 )
	{
//	std::cout << smDrobA.chisl  << smDrobA.Natur<<" " << " ---" << "\n" << "   " << smDrobA.znamenatel << "\n" << endl;
			std::cout << smDrobA.Natur << " " << smDrobA.chisl << "/" << smDrobA.znamenatel;
	std::cout << "" << endl;
	}
	else
		std::cout << "  " << smDrobA.chisl << "\n" << endl;
	    std::cout << "" << endl;
}
void Fraction::NonNormalDrobInSmechannuy()
{


	/*�������� ��������� ����� �� �� �����������;
	+	������� �� ������� �������� � ��������� ����������� �������� �������;
	+	��������� �� ������� �������� � �������� ����� �����.*/
	/*
		smDrobA.chisl = resultDrob.chisl % resultDrob.znamenatel;
	    smDrobA.znamenatel = resultDrob.znamenatel;
	
		smDrobA.Natur = resultDrob.chisl / resultDrob.znamenatel;
	smDrobA.chisl = resultDrob.chisl % resultDrob.znamenatel;
	smDrobA.znamenatel = resultDrob.znamenatel;*/

	tmp.chisl = drobA.chisl % drobA.znamenatel;
	tmp.znamenatel = drobA.znamenatel;

	smDrobA.Natur = drobA.chisl / drobA.znamenatel;
	smDrobA.chisl = drobA.chisl % drobA.znamenatel;
	smDrobA.znamenatel = drobA.znamenatel;
}
bool  Fraction::CheckNormalFraction(SmDrob a)
{
	if (a.Natur == 0)
	{
		if (a.chisl > a.znamenatel) return false;
		if (a.chisl < a.znamenatel) return true;
	}
	if (a.Natur < 0) return false;
	if (a.Natur > 0) return false;


}
void Fraction::ShowDrob(drob a)
{
	if (a.znamenatel == 1) { std::cout << a.chisl << endl; }
	else
	std::cout << a.chisl << "/"  << a.znamenatel;
	//std::cout << " " << endl;
}
int  Fraction::NOD(int a, int b)
{
		int c;

		while (b)
		{

			c = a % b;

			a = b;

			b = c;

		}

		return a;
	
}
bool Fraction::CheckNormalDrob(drob dr)
{
	if (dr.chisl < dr.znamenatel) return true;
	if (dr.chisl > dr.znamenatel) return false;
	if (dr.chisl == dr.znamenatel) return false;

}
bool Fraction::CheckDrobONZero(drob dr)
{
	if (dr.chisl == 0) return false;
	if (dr.znamenatel == 0) return false;
}
int  Fraction::NOK(int a, int b)
{
   return std::abs((a*b) / NOD(a, b));
}
int  Fraction::NOKDrobs(drob drobA, drob drobB)
{
	int a = 0, b = 0;
	a = drobA.znamenatel;
	b = drobB.znamenatel;
	return NOK(a, b);
}
bool Fraction::CheckDrobObZnamenatel(drob drobA, drob drobB)
{
	if (drobA.znamenatel == drobB.znamenatel) return true;
	else return false;
}
bool Fraction::CheckDrobObZnamenatel(SmDrob a, SmDrob b)
{
	if (a.znamenatel == b.znamenatel) return true;
	else return false;
}
void Fraction::SummaDrobsPositive()
{
	summa.chisl = drobA.chisl + drobB.chisl;
	summa.znamenatel = drobA.znamenatel;

	//

	/* display equation */

	ShowDrob(drobA);
	std::cout << "  +  ";
	ShowDrob(drobB);
	std::cout << "  =  ";
	

   drobA = summa;

}
void Fraction::SokrDrob(drob a)
{
	
	tmpA.chisl = a.chisl / (NOD(a.chisl, a.znamenatel))  ;
	tmpA.znamenatel =  a.znamenatel / (NOD(a.chisl, a.znamenatel));
	
	drobA = tmpA;
}
bool Fraction::CheckSokrDrob(drob a)
{
	if (NOD(a.chisl, a.znamenatel) == 1) return false;
	else return true;
}
void Fraction::GetDrobA()
{

}
void Fraction::GetDrobB()
{

}
bool Fraction::CheckNormalFraction(drob a)
{
	if (a.chisl > a.znamenatel) return false;
	if (a.chisl < a.znamenatel) return true;

}

//����� ��������� ������ ��������� � w
void Fraction::SummaSmFractions(SmDrob a, SmDrob b)
{
	drob t, w, q;

	t.chisl = 0; t.znamenatel = t.chisl;
	w.chisl = t.chisl; w.znamenatel = t.chisl;
	q.chisl = 0; q.znamenatel = 0;

	t.chisl = (a.Natur * a.znamenatel) + a.chisl;
	t.znamenatel = a.znamenatel;

	q.chisl = (b.Natur * b.znamenatel) + b.chisl;
	q.znamenatel = b.znamenatel;

	if (CheckDrobObZnamenatel(t, q))
	{
		std::cout << "����� � ����� ������������" << "\n";
		w.chisl = t.chisl + q.chisl;
		w.znamenatel = t.znamenatel;
		ShowDrob(w);
		exit;

	}
	else
	{
		std::cout << "������ ����� �����������..." << "\n";
		CreateObZnamenatel(t, q);
		t = tmpA; q = tmpB;
		w.chisl = t.chisl + q.chisl;
		w.znamenatel = t.znamenatel;
		ShowDrob(w);
		exit;
	}


}
// �������� ����� ����������� ��������� � drobA->drobATemp drobB->drobBTemp
void Fraction::CreateObZnamenatel(drob drobA, drob drobB)
{
	/***----- DrobA ------***/


	std::cout << "����� ����������� " << NOKDrobs(drobA, drobB) << "\n";
	std::cout << "������ ��� ��������� " << (NOKDrobs(drobA, drobB) / drobA.znamenatel) << "\n";

	drobA.chisl = (NOKDrobs(drobA, drobB) / drobA.znamenatel) * drobA.chisl;
	drobA.znamenatel = NOKDrobs(drobA, drobB);

	/***----- DrobB ------***/
	std::cout << "������ ��� ��������� " << (NOKDrobs(drobA, drobB) / drobB.znamenatel) << "\n" << endl;
	drobB.chisl = (NOKDrobs(drobA, drobB) / drobB.znamenatel) * drobB.chisl;
	drobB.znamenatel = NOKDrobs(drobA, drobB);


	tmpA = drobA; tmpB = drobB;

	ShowDrob(drobA);

	ShowDrob(drobB);
}
