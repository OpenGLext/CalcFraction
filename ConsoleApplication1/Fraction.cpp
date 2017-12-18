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
		std::cout << "Дробь нулевая,вычисления не имеют смысла" << endl;
		exit;
		if (!CheckDrobONZero(drobA) || !CheckDrobONZero(drobB))
		{
			std::cout << "Дробь нулевая,вычисления не имеют смысла" << endl;
			exit;
		}

		if (!CheckNormalDrob(drobA))
		{
			std::cout << "Числитель больше знаменателя,переведем дробь в смешанную" << endl;
			NonNormalDrobInSmechannuy();
			ShowDrob(smDrobA);
		}
	}
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
	/*поделить числитель дроби на ее знаменатель;
	остаток от деления записать в числитель знаменатель оставить прежним;
	результат от деления записать в качестве целой части.*/

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
	
	tmp.chisl = a.chisl / (NOD(a.chisl, a.znamenatel))  ;
	tmp.znamenatel =  a.znamenatel / (NOD(a.chisl, a.znamenatel));
	
	drobA = tmp;
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
