#include <math.h>
#include <stdio.h>
#include <process.h>
#include <iostream>
#include <string>
#include <sstream>
#include "Fraction.h"
using namespace std;

int a=0, b=0,c=0;
int operation = 0;
int formatDrobs = 0;
Fraction fraction;

struct drob
{
	bool IsObZnamenatel;
	bool IsSmDrob;
	bool IsDigDrob;
	bool IsMinus;
	int digitDrob;
	int Natur;
	int chisl;
	int znamenatel;
	
};
struct DecDrob
{
	int chisl;       // 2,
	int znamenatel; //  3
	float zelview;    // 2,3
	float Natur;     // целая часть дроби
	float fractionFrac; // дробная часть дроби
	drob  DecInNormDrob; // 2 2/3
};

drob drobA,drobB, drobATemp, drobBTemp,smechannayDrob,resultDrob;
DecDrob decDrobA,decDrobB,otvetDecDrob;
std::string inputDrob,resString;

struct drobsObZnamenatel
{
	drob drobAObZnamenatel;
	drob drobBObZnamenatel;
};

drobsObZnamenatel drobsWithObZnamenatel;

 struct SmDrob
{
	int Natur;
	int chisl;
	int znamenatel;
};

//SmDrob smDrobA,smDrobB;
// наименьший общий делитель
int NOD(int a, int b) 
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
// наименьшее общее кратное
int NOK(int a, int b)
{
	return std::abs((a*b) / NOD(a, b));
}
int NOKDrobs(drob drobA, drob drobB)
{
	int a = 0, b = 0;
	a = drobA.znamenatel;
	b = drobB.znamenatel;
	return NOK(a,b);
}
bool CheckNormalDrob(drob dr)
{
	if (dr.chisl < dr.znamenatel) return true;
	if (dr.chisl > dr.znamenatel) return false;
	if (dr.chisl == dr.znamenatel) return false;
	
}
//не нулевая ли дробь? числитель = 0 или грубая ошибка знаменатель = 0
bool CheckDrobONZero(drob dr)
{
	if (dr.chisl == 0) return false;
	if (dr.znamenatel == 0) return false;
}
//проверим две дроби на общий знаменатель
bool CheckDrobObZnamenatel(drob drobA,drob drobB)
{
	if (drobA.znamenatel == drobB.znamenatel) return true;
	else return false;
}
// выведем дробь без целой части
void ShowDrob(drob a)
{
	std::cout << a.chisl << "\n" << "---" << "\n" << a.znamenatel<<"\n"<<endl;
	std::cout << "" << endl;
}
//выведем на экран дробь в виде целая часть + дробь
void ShowDrob(SmDrob smDrobA)
{
//	if (smDrobA.Natur >= 1)
	//{
		std::cout << "   " << smDrobA.chisl << "\n" << smDrobA.Natur << " ---" << "\n" << "   " << smDrobA.znamenatel << "\n" << endl;
		std::cout << "" << endl;
	//}
	//else
	//	std::cout << "  " << smDrobA.chisl << "\n" << "---" << "\n" << " " << smDrobA.znamenatel << "\n" << endl;
	//    std::cout << "" << endl;
}
//вывод целочисленной дроби на экран
void ShowDrob(DecDrob a)
{
	std::cout << a.zelview << "\n" << endl;
}
// создадим общий знаменатель результат в drobA->drobATemp drobB->drobBTemp
void CreateObZnamenatel(drob drobA, drob drobB)
{
	/***----- DrobA ------***/
	
	
	std::cout << "Общий знаменатель " << NOKDrobs(drobA, drobB) << "\n";
	std::cout << "Найден доп множитель " << (NOKDrobs(drobA, drobB) / drobA.znamenatel) << "\n";

    drobA.chisl = (NOKDrobs(drobA, drobB) / drobA.znamenatel) * drobA.chisl;
	drobA.znamenatel = NOKDrobs(drobA, drobB);

	/***----- DrobB ------***/
	std::cout << "Найден доп множитель " << (NOKDrobs(drobA, drobB) / drobB.znamenatel) << "\n"<<endl;
	drobB.chisl = (NOKDrobs(drobA, drobB) / drobB.znamenatel) * drobB.chisl;
	drobB.znamenatel = NOKDrobs(drobA, drobB);
	

	drobATemp = drobA; drobBTemp = drobB;

    ShowDrob(drobA);

    ShowDrob(drobB);
}
//сумма целых дробей
drob SummaDrobsPositive(drob a,drob b)
{
	drob c;
	c.chisl = a.chisl + b.chisl;
	c.znamenatel = a.znamenatel;
	return c;
}

//сумма смещанных дробей
drob SummaSmFractions(SmDrob a, SmDrob b)
{
	drob t,w,q;

	t.chisl = 0; t.znamenatel = t.chisl;
	w.chisl = t.chisl; w.znamenatel = t.chisl;
	q.chisl = 0; q.znamenatel = 0;

	t.chisl = (a.Natur * a.znamenatel) + a.chisl;
	t.znamenatel = a.znamenatel;

	q.chisl = (b.Natur * b.znamenatel) + b.chisl;
	q.znamenatel = b.znamenatel;

	if (CheckDrobObZnamenatel(t, q))
	{
		std::cout << "Дроби с общим знаменателем" << "\n";
      w.chisl = t.chisl + q.chisl;
	  w.znamenatel = t.znamenatel;
      return w;

	}
	else
	{
		std::cout << "Найдем общий знаменатель..." << "\n";
		CreateObZnamenatel(t, q);
		t = drobATemp; q = drobBTemp;
		w.chisl = t.chisl + q.chisl;
		w.znamenatel = t.znamenatel;
		return w;
	}

	
}
//Разность двух дробей с одинаковым знаменателем
drob RaznostDrobsPositive(drob a,drob b)
{
	drob c;

	c.znamenatel = a.znamenatel;
	c.chisl = a.chisl - b.chisl;
	return c; 
}
//Из неправильной дроби сделаем смешанную
//void NonNormalDrobInSmechannuy(drob resultDrob)
//{
//	/*поделить числитель дроби на ее знаменатель;
//	остаток от деления записать в числитель знаменатель оставить прежним;
//	результат от деления записать в качестве целой части.*/
//
//	smechannayDrob.chisl = resultDrob.chisl % resultDrob.znamenatel;
//	smechannayDrob.znamenatel = resultDrob.znamenatel;
//
//	smDrobA.Natur = resultDrob.chisl / resultDrob.znamenatel;
//	smDrobA.chisl = resultDrob.chisl % resultDrob.znamenatel;
//	smDrobA.znamenatel = resultDrob.znamenatel;
//}
//void NonNormalDrobInSmechannuy(DecDrob resultDrob)
//{
//	/*поделить числитель дроби на ее знаменатель;
//	остаток от деления записать в числитель знаменатель оставить прежним;
//	результат от деления записать в качестве целой части.*/
//
//	smechannayDrob.chisl = resultDrob.chisl / resultDrob.znamenatel;
//	smechannayDrob.znamenatel = resultDrob.znamenatel;
//
//	smDrobA.Natur = resultDrob.chisl / resultDrob.znamenatel;
//	smDrobA.chisl = resultDrob.chisl % resultDrob.znamenatel;
//	smDrobA.znamenatel = resultDrob.znamenatel;
//}
//проверим дробь нормальная ? если да то тру
bool CheckNormalFraction(drob a)
{
	if (a.chisl > a.znamenatel) return false;
	if (a.chisl < a.znamenatel) return true;
	
}
bool CheckNormalFraction(DecDrob a)
{
	if (a.chisl > a.znamenatel) return false;
	if (a.chisl < a.znamenatel) return true;

}
bool CheckNormalFraction(SmDrob a)
{
	if (a.Natur == 0)
	{
      if (a.chisl > a.znamenatel) return false;
	  if (a.chisl < a.znamenatel) return true;
	}
	if (a.Natur < 0) return false;
	if (a.Natur > 0) return false;
	

}
//сократим дробь
drob SokrDrob(SmDrob a)
{
   drob res;

   res.chisl =	a.chisl / (NOD(a.chisl, a.znamenatel)) ;
   res.znamenatel = a.znamenatel /(NOD(a.chisl, a.znamenatel)) ;
   
   return res;
}
// можно ли дробь сократить
bool CheckSokrDrob(SmDrob smDrobA)
{
	if (NOD(smDrobA.chisl, smDrobA.znamenatel) == 1) return false;
	else return true;
}
bool CheckSokrDrob(drob a)
{
	if (NOD(a.chisl, a.znamenatel) == 1) return false;
	else return true;
}

//сократим дробь resultDrob
void SokrDrob(drob a)
{
	resultDrob.chisl = (NOD(a.chisl, a.znamenatel)) / a.chisl;
	resultDrob.znamenatel = (NOD(a.chisl, a.znamenatel)) / a.znamenatel;
}
//умнож целой дроби на дробь,дроби с общим знаменателем
drob UmnojDrobsPositive( drob a, drob b)
{
	drob c;

	
		c.chisl = a.chisl * b.chisl;
		c.znamenatel = a.znamenatel * b.znamenatel;
		return c;
	}
//Умножим натуральное число N на дробь получим дробь
drob UmnojNaturOnDrob(int N, drob a)
{
	drob c;
	c.znamenatel = a.znamenatel;
	c.chisl = a.chisl * N;
	return c;
}
//переведем целое число в дробь 5 = 5/1
drob ViewNaturInDrob(int N)
{
	drob c;
	c.chisl = N;
	c.znamenatel = 1;

	return c;
}
DecDrob SummaDecDrobs(DecDrob a, DecDrob b)
{
	DecDrob res;

	res.zelview = a.zelview + b.zelview;

   std::cout<<a.zelview<<" + "<<b.zelview<<" = "<<res.zelview<<"\n"<<endl;

	return res;
}
void ParseInputDrob()
{
	//если это десятичная дробь до 3х разрядов до и после запятой 100,200
	
	//если это одноразрядная дробь 2,3
	
	std::string substr(",");

	
	std::size_t found = inputDrob.find(substr);
	if (found != std::string::npos)
	{
		// найдена запятая
	}
	
}
void InitDecDrob(DecDrob a)
{
	     //отделим числитель от знаменателя копирование строки и в инт или флоат преобразую
	//std::string str = std::to_string(a.zelview);
	  // a.chisl =  str.substr(0,1);
		//a.znamenatel = ;

	std::ostringstream ss;
	size_t st = 1;
	ss << a.zelview;
	std::string s(ss.str());

	std::string StrChisl(1, 1);
	std::string StrZname(3, 1);

	string c, z;
	c = StrChisl.c_str();
	z = StrZname.c_str();

	//a.chisl = (float)c;
}
//преобразуем целочисленную дробь < 0  0.025
SmDrob TransformDecDrobMinZero(DecDrob a)
{
	SmDrob sm;
	int calcbits = 0;

	sm.znamenatel = 1;

	while (floor(a.zelview) != a.zelview)
	{
		calcbits++;
		a.zelview = a.zelview * 10;
	}
		
	         sm.chisl = a.zelview;
		sm.znamenatel = sm.znamenatel * pow(10, calcbits);
		return sm;
}
// преобразуем целочисленную дробь > 0 2.25
SmDrob TransformDecDrobBigZero(DecDrob a)
{
	SmDrob sm;
	//отделить целую часть round(a.zelview) 

	//а дробную так же 
		
	sm.Natur = round(a.zelview);
		a.zelview =  abs(a.zelview - (round(a.zelview)));
	//sm = TransformDecDrobMinZero(a);
	return sm;
}
// проверим десятичная дробь (> 0) or (< 0)   true = > 0 
bool CheckDecDrobBigZeroIs(DecDrob a)
{
	 return ((round(a.zelview)));
}
void RazlojOnMnoj(int a)
{
	

	int i = 2; int j = 0;
	while (i*i <= a && j != 1)
	{
		if ((a%i) == 0) j = 1;
		else i += 1;
	}
	if (j == 1) std::cout <<a <<" Составное число"<<"\n";
	else std::cout <<a <<" Простое число"<<"\n";

	
}
void RazlojOnMnojDrob(drob a)
{
	RazlojOnMnoj(a.chisl);
	RazlojOnMnoj(a.znamenatel);
}
void RazlojOnMnojDrobRational(DecDrob a)
{
	RazlojOnMnoj(a.zelview);
}
void primeDivisors(int n)
{
	int t, k;

	std::cout << n << " = ";
	if (n <= 1) std::cout << " " << n;
	else t = ceill(sqrt(n));
	k = 2;
	while (k <= t)
	{
		if ((n % k) == 0)
		{
			n = n / k;
			std::cout << " " << k;
			while (n % k == 0)
			{
				n = n / k;
				std::cout << " " << k;
			}
			t = ceill(sqrt(n));
		}
		k += 1;
	}
	// k >t -простых делителей меньше n уже нет
	if (n>1) std::cout << " " << n << " Простое число! " << endl;
}
void RazlojOnMnojFloat(DecDrob a)
{
	//int aa = 0;
	float ratFraction = a.zelview;

	//while (  a.zelview > temp ) //(floor(a.zelview) != a.zelview)
	//{
	//	a.zelview = a.zelview * 10;
	//}
	////aa = NOD(a.zelview, a.zelview);

	//int i = 2; int j = 0;
	//while (i*i <= a.zelview && j != 1)
	//{
	//	//if ((a.zelview % i) == 0) j = 1;
	//	//else i += 1;
	//}
	//if (j == 1) std::cout << aa << " Составное число" << "\n";
	//else std::cout << aa << " Простое число" << "\n";

	if (NOD(a.zelview * 100, a.zelview * 100) >= 1)
	{
		a.zelview * 100;
		a.fractionFrac = modf(a.zelview, &a.Natur);
		if (a.Natur >= 1)
		{
			// рассматриваем целочисленную дробь с целой частью >= 1
		}
		else
		{
			 //дробь без целой части = 0

		}
		std::cout << a.Natur << " " << a.fractionFrac;

		//primeDivisors(a.zelview);
	}
}

void main() 
{
	/*while (a != 1)
	{
		std::cout << "Enter a and b int... Or 1 1 for quit...\n";
		std::cin >> a >> b;
		c = NOD(a, b);

		std::cout << "NOK( " << a << "," << b << "" << ")" << " " << "= " <<  std::abs((a*b) / NOD(a, b)) << endl;
		std::cout << "NOD(" << a << "," << b << "" << ")" << " " << "= " << std::abs(NOD(a, b)) << endl;
	}*/

	setlocale(LC_ALL, "Russian");

	std::cout << "Ввод дроби через пробел..." << endl;
	std::cout << " " << endl;
	std::cout << "Ввод десятичной дроби 2,3  [1]" << "\n" << endl;
	std::cout << "Ввод нормальной дроби 2/3  [2]" << "\n" << endl;
	std::cout << "Ввод смещанной дроби 2 2/3 [3]" << "\n" << endl;
	std::cin >> formatDrobs>>operation;

	if (formatDrobs == 2 && operation == 2 )
	{
      fraction.InputDrob();
	  fraction.ShowDrob(fraction.drobA);
	  fraction.ShowDrob(fraction.drobB);
	  fraction.SummaDrobsPositive();

	  if (fraction.CheckSokrDrob(fraction.drobA)) { fraction.SokrDrob(fraction.drobA); }
	  else
	  {
		  std::cout << "Дробь не сокращается т.к НОД = 1" << endl;
		  fraction.NonNormalDrobInSmechannuy();
		  //fraction.ShowDrob(fraction.smDrobA);
	  }
	 // fraction.ShowDrob(fraction.drobA);
	  fraction.InputDrob();
	}
	

	//if (formatDrobs == 1)
	//{
	////	//std::cout << "Ввод десятичной дроби 2,3 через (.) две дроби через пробел " << "\n" <<
	////	//	"Выбор операции над дробями [1] - [2] + [3] * [4] / "<<"\n"<< endl;
	////	//std::cin >> decDrobA.zelview>>decDrobB.zelview>>operation;
	////	////иниц числ и знаменатель дабы перевести в норм или смещ дробь
	////	//InitDecDrob(decDrobA); InitDecDrob(decDrobB);
	////	//switch (operation)
	////	//{
	////	//
	////	//case 2: otvetDecDrob = SummaDecDrobs(decDrobA, decDrobB);  std::cin >> operation; break;
	////	//case 1: break;
	////	//case 3: break;
	////	//case 4: break;
	////	//case 0: exit; break;
	////	//default: exit; break;
	////	//}

	////	//тест преобразования десят дроби < 0 0.025
	//	std::cout << "Ввод десятичной дроби  через(.) для преобразования в нормальную дробь " << "\n" << endl;
	//	//"Ввод десятичной дроби МЕНЬШЕ 0 (0.025) через (.) для преобразования в нормальную дробь " << "\n" << endl;
	//	std::cin >> decDrobA.zelview;  //decDrobA.zelview;

	//	if (NOD(decDrobA.zelview, decDrobA.zelview) == 1)
	//	{
	//		std::cout << "простое число,не разложить";
	//	}
	//	else
	//	{
	//		std::cout << "можно разложить\n";
	//		RazlojOnMnojFloat(decDrobA);
	//	}
	//	// проверка дроби > 0 ?
	//	//if (CheckDecDrobBigZeroIs(decDrobA))
	//	//{
	//	//	TransformDecDrobBigZero(decDrobA); // Да
	//	//	/*if (!CheckNormalFraction(decDrobA))
	//	//	{
	//	//		NonNormalDrobInSmechannuy(decDrobA);
	//	//		ShowDrob(smDrobA);
	//	//	}*/

	//	//	//ShowDrob(decDrobA);
	//	//	//std::cin >> drobA.digitDrob;
	//	//}
	//	//else
	//	std::cout << " \n";
	//	//smDrobA = TransformDecDrobMinZero(decDrobA); // Нет
	//	//NonNormalDrobInSmechannuy(decDrobA);
	//	//ShowDrob(smDrobA);
	//	/*if (!CheckNormalFraction(smDrobA))
	//	{
	//		NonNormalDrobInSmechannuy(decDrobA);
	//		ShowDrob(smDrobA);
	//	}*/
	///*	if (CheckSokrDrob(smDrobA))
	//	{
	//		std::cout << "Можно сократить (НОД != 1),сокращаю...\n" << endl;
	//		std::wcout << "NOD = " << NOD(smDrobA.chisl, smDrobA.znamenatel) <<"\n"<< endl;
	//		resultDrob = SokrDrob(smDrobA);
	//		ShowDrob(resultDrob);
	//	}
	//	else std::cout << "Дробь нельзя сократить т.к НОД дроби = 1...\n" << endl;*/

	//	///*if (!CheckNormalFraction(decDrobA))
	//	//{
	//	//	NonNormalDrobInSmechannuy(decDrobA);
	//	//	ShowDrob(smDrobA);
	//	//}*/

	//	std::cin >> decDrobA.zelview;
	//}

	//if (formatDrobs == 2)
	//{
	//	
	//	std::cout << "Ввод нормальной дроби " << "\n" << endl;
	//	
	//	std::cin >> drobA.chisl>>drobA.znamenatel>>drobB.chisl>>drobB.znamenatel;
	//	
	//	std::cout << endl;

	//	ShowDrob(drobA); ShowDrob(drobB);

	//	std::cout << "Enter operation [1] + [2] - [3] * [4] / " << "\n"; std::cin >> operation;



	//	switch (operation)
	//	{
	//	case 1:

	//		if (CheckDrobObZnamenatel(drobA, drobB)) std::cout << "Дроби с общим знаменателем" << endl;
	//		else CreateObZnamenatel(drobA, drobB);
 //           if (CheckNormalDrob(drobA)) std::cout << "Дробь правильная,не требуется перевод в смешанную" << "\n";
	//		else
	//		{
	//			std::cout << "Дробь не правильная,создадим смещанную" << "\n" << endl;
	//			NonNormalDrobInSmechannuy(drobA);
	//			ShowDrob(smDrobA);
	//		}
	//		    drobATemp = SummaDrobsPositive(drobA, drobB);

 //               ShowDrob(drobATemp);

	//		/*if (CheckSokrDrob(drobA))
	//		{
	//			std::cout << "Сокращаем дробь..." << "\n";
	//			SokrDrob(drobA);
	//			
	//		}
	//		else std::cout << "Дробь нельзя сократить" << "\n";*/
	//		if (!CheckNormalDrob(drobATemp)) 
	//		{
	//			drobATemp.chisl = drobATemp.chisl / drobATemp.znamenatel;
	//			std::cout << "Дробь превратилась в натуральное число! " << drobATemp.chisl << endl;
	//			
	//		}

	//		


	//		break;

	//	case 2: break;
	//	case 3: break;
	//	case 4: break;
	//	}

	//	//if (!CheckSokrDrob(drobA))
	//	//{
	//	//	std::cout << "Число простое,его нельзя разложить!";
	//	//}
	//	//else
	//	////RazlojOnMnojDrob(drobA);
	//	//primeDivisors(drobA.chisl);
	//	//std::cout << endl;
	//	//primeDivisors(drobA.znamenatel);
	//	
	//}

	//if (formatDrobs == 3)
	//{
	//	// enter fractions
	//	std::cin >> smDrobA.Natur>>smDrobA.chisl>>smDrobA.znamenatel >>smDrobB.Natur>>smDrobB.chisl>>smDrobB.znamenatel;
 //       ShowDrob(smDrobA); ShowDrob(smDrobB);
	//	std::cout << "Enter operation [1] + [2] - [3] * [4] / " << "\n"; std::cin >> operation;

	//	

	//	switch (operation)
	//	{
	//	  case 1: 
	//		       if (CheckDrobObZnamenatel(drobA, drobB)) std::cout << "Дроби с общим знаменателем" << endl;
	//		       else CreateObZnamenatel(drobA, drobB);

	//		       drobA = SummaSmFractions(smDrobA, smDrobB); 
	//			 
	//			  if (CheckNormalDrob(drobA)) std::cout << "Дробь правильная,не требуется перевод в смешанную" << "\n";
	//			  else
	//			  {
	//				  std::cout << "Дробь не правильная,создадим смещанную" << "\n"<<endl;
	//				  NonNormalDrobInSmechannuy(drobA);
	//				  ShowDrob(smDrobA);
	//			  }

	//			  if (CheckSokrDrob(drobA))
	//			  {
	//				  std::cout << "Сокращаем дробь..." << "\n";
	//				  SokrDrob(drobA);
	//				  ShowDrob(resultDrob);
	//			  }
	//			  else std::cout << "Дробь нельзя сократить" << "\n";

	//			  ShowDrob(drobA);

	//		  
	//		      break;

	//	  case 2: break;
	//	  case 3: break;
	//	  case 4: break;
	//	}

	//}

	////std::cin >> inputDrob;
	////ParseInputDrob();
	////std::cin >> drobA.chisl >> drobA.znamenatel;
	////std::cin >> drobB.chisl >> drobB.znamenatel;

	////if (drobA.znamenatel == )

	//std::cin >> drobA.chisl>>drobA.znamenatel;
	//std::cin >> drobB.chisl >> drobB.znamenatel;

	//// debug input
	////drobA.chisl = 2; drobA.znamenatel = 3; drobB.chisl = 4; drobB.znamenatel = 7;

	////debug output
	//std::cout <<" "<< drobA.chisl << endl;
	//std::cout << "---" << endl;
	//std::cout << " "<<drobA.znamenatel << endl;
	//std::cout << "" << endl;

	//std::cout << " " << drobB.chisl << endl;
	//std::cout << "---" << endl;
	//std::cout << " " << drobB.znamenatel << endl;
	//std::cout << "" << endl;

	//if (!CheckDrobONZero(drobA)) { std::cout << "Drob = ZERO,enter non zero drob" << endl; }
	//if (!CheckDrobONZero(drobB)) { std::cout << "Drob = ZERO,enter non zero drob" << endl; }
	//else
	//{
	//	std::cout << " <<<<<<<<<< Выбери операцию >>>>>>>>>" << "\n" << endl;
	//	std::cout << " +[1] -[2] *[3]" << endl;
	//	std::cout << " " << endl;
	//	std::cin >> operation;
	//	std::cout << " " << endl;
	//	if (operation == 1)
	//	{
	//		/*--- Суммируем дроби ---*/
	//		/*--- Проверим общий знаменатель ---*/
	//		if (!CheckDrobObZnamenatel(drobA, drobB))
	//		{
	//			std::cout << "Дроби без общего знаменателя! " << endl;
	//			std::cout << " " << endl;
	//			std::cout << "Знаменатель найден... " << NOKDrobs(drobA, drobB)<< endl;
	//			std::cout << " " << endl;

	//			CreateObZnamenatel(drobA, drobB);
	//			///*----------    ------*/
	//			//drobATemp.chisl = drobA.chisl;
	//			//drobATemp.chisl = (NOKDrobs(drobA, drobB) / drobA.znamenatel) * drobA.chisl;
	//			//drobATemp.znamenatel = NOKDrobs(drobA, drobB);
	//			//std::cout << "New drob " << drobATemp.chisl<<"/"<<drobATemp.znamenatel << endl;

	//			//drobBTemp.chisl = drobB.chisl;
	//			//drobBTemp.chisl = (NOKDrobs(drobA, drobB) / drobB.znamenatel) * drobB.chisl;
	//			//drobBTemp.znamenatel = NOKDrobs(drobA, drobB);
	//			//std::cout << "New drob " << drobBTemp.chisl << "/" << drobBTemp.znamenatel << endl;
	//			std::cout << "Суммируем...\n" << endl;;
	//			std::cout << " " << endl;
	//			resultDrob = SummaDrobsPositive(drobATemp, drobBTemp);
	//			ShowDrob(resultDrob);

	//			NonNormalDrobInSmechannuy(resultDrob);
	//			std::cout << "\n"<<endl;
	//			std::cout << "Смешанная дробь " << "\n" << endl;
	//			ShowDrob(smDrobA);
	//			
	//			if (CheckSokrDrob(smDrobA))
	//			{
	//				std::cout << "Можно сократить,сокращаю...\n" << endl;
	//				SokrDrob(smDrobA);
	//				std::cout << resultDrob.chisl << "\n" << endl << "---\n" << resultDrob.znamenatel << endl;
	//			}
	//			else
	//			{
	//				std::cout << "Дробь нельзя сократить т.к НОД дроби = 1...\n" << endl;
	//			}
	//			/*resultDrob.chisl = drobsWithObZnamenatel.drobAObZnamenatel.chisl +
	//				drobsWithObZnamenatel.drobBObZnamenatel.chisl;

	//			resultDrob.znamenatel = NOKDrobs(drobA, drobB);*/

	//			/*std::cout << "" << resultDrob.chisl << endl << "---" << endl << resultDrob.znamenatel << endl<<" "<<endl;

	//			std::cout << " Transforming drob... \n"<<endl;
	//			std::cout << " " << endl;
	//			std::cout << "Non Normal Drob \n" << endl;
	//			std::cout << resultDrob.chisl << endl << "---" << endl << resultDrob.znamenatel << endl;
	//			std::cout << " " << endl;
	//			NonNormalDrobInSmechannuy(resultDrob);
	//			std::cout << "Smechannay drob " << "\n" << endl;
	//			std::cout<<smDrobA.Natur << "  " << smDrobA.chisl <<"\n" << "  ---" << "\n" << endl <<"  "<< smDrobA.znamenatel << endl;*/

	//		}
	//		
	//		
	//			               
	//		std::cin >> a;
	//	}
	//	if (operation == 2)
	//	{
	//		/*--- Разность дробей ---*/
	//		/*--- Проверим общий знаменатель ---*/
	//		if (!CheckDrobObZnamenatel(drobA, drobB))
	//		{
	//			std::cout << "Дроби без общего знаменателя! " << endl;
	//			std::cout << " " << endl;
	//			std::cout << "Знаменатель найден... " << NOKDrobs(drobA, drobB) << endl;
	//			std::cout << " " << endl;

	//			CreateObZnamenatel(drobA, drobB);
	//			drobA = RaznostDrobsPositive(drobATemp, drobBTemp);
	//			if (!CheckDrobONZero(drobA)) { std::cout << "Drob = ZERO,enter non zero drob" << endl; }
	//			else ShowDrob(drobA);
	//		}
	//		drobATemp =RaznostDrobsPositive(drobA, drobB);
	//		if (!CheckDrobONZero(drobATemp)) { std::cout << "Drob = ZERO,enter non zero drob" << endl; }
	//		else ShowDrob(drobATemp);

	//		std::cin >> a;
	//	}

	//	if (operation == 3)
	//	{
	//		//if (!CheckDrobObZnamenatel(drobA, drobB))
	//		//{
	//			/*std::cout << "Дроби без общего знаменателя! " << endl;
	//			std::cout << " " << endl;
	//			std::cout << "Знаменатель найден... " << NOKDrobs(drobA, drobB) << endl;
	//			std::cout << " " << endl;*/

	//			//CreateObZnamenatel(drobA, drobB);
	//		if (!CheckDrobONZero(drobA)) { std::cout << "Drob = ZERO,enter non zero drob" << endl; }
	//		if (!CheckDrobONZero(drobB)) { std::cout << "Drob = ZERO,enter non zero drob" << endl; }
	//		
	//			drobA = UmnojDrobsPositive(drobA, drobB);
	//			//if (!CheckDrobONZero(drobA)) { std::cout << "Drob = ZERO,enter non zero drob" << endl; }
	//			 ShowDrob(drobA);
	//			if (CheckSokrDrob(drobA))
	//			{
	//				std::cout << "Можно сократить,сокращаю...\n" << endl;
	//			/*	drobA.chisl = (NOD(drobA.chisl, drobA.znamenatel)) / drobA.chisl;
	//				drobA.znamenatel = (NOD(drobA.chisl,drobA.znamenatel)) / drobA.znamenatel;*/
	//				SokrDrob(drobA);
	//			}
	//			ShowDrob(drobA);
	//			std::cin >> a;
	//		//}
	//		/*drobATemp = UmnojDrobsPositive(drobA, drobB);
	//		if (!CheckDrobONZero(drobATemp)) { std::cout << "Drob = ZERO,enter non zero drob" << endl; }
	//		
	//		else ShowDrob(drobATemp);
 //           if (CheckSokrDrob(drobATemp)) { SokrDrob(drobATemp); }
	//		ShowDrob(resultDrob);
	//		std::cin >> a;*/
	//	}
	//}
	}
	
	