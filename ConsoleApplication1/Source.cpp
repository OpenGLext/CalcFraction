#include <math.h>
#include <stdio.h>
#include <process.h>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int a=0, b=0,c=0;
int operation = 0;
int formatDrobs = 0;
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
	float chisl;       // 2,
	float znamenatel; //  3
	float zelview;    // 2,3
	drob  DecInNormDrob; // 2 2/3
};

drob drobA,drobB, drobATemp, drobBTemp,smechannayDrob,resultDrob;
DecDrob decDrobA,decDrobB,otvetDecDrob;
std::string inputDrob;

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

SmDrob smDrobA;
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
	if (smDrobA.Natur >= 1)
	{
		std::cout << "  " << smDrobA.chisl << "\n" << smDrobA.Natur << "---" << "\n" << " " << smDrobA.znamenatel << "\n" << endl;
		std::cout << "" << endl;
	}
	else
		std::cout << "  " << smDrobA.chisl << "\n" << "---" << "\n" << " " << smDrobA.znamenatel << "\n" << endl;
	    std::cout << "" << endl;
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
	
	drobA.chisl = (NOKDrobs(drobA, drobB) / drobA.znamenatel) * drobA.chisl;
	drobA.znamenatel = NOKDrobs(drobA, drobB);
	ShowDrob(drobA);

	/***----- DrobB ------***/
	
	drobB.chisl = (NOKDrobs(drobA, drobB) / drobB.znamenatel) * drobB.chisl;
	drobB.znamenatel = NOKDrobs(drobA, drobB);
	ShowDrob(drobB);

	drobATemp = drobA; drobBTemp = drobB;
}
//сумма целых дробей
drob SummaDrobsPositive(drob a,drob b)
{
	drob c;
	c.chisl = a.chisl + b.chisl;
	c.znamenatel = a.znamenatel;
	return c;
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
void NonNormalDrobInSmechannuy(drob resultDrob)
{
	/*поделить числитель дроби на ее знаменатель;
	остаток от деления записать в числитель знаменатель оставить прежним;
	результат от деления записать в качестве целой части.*/

	smechannayDrob.chisl = resultDrob.chisl % resultDrob.znamenatel;
	smechannayDrob.znamenatel = resultDrob.znamenatel;

	smDrobA.Natur = resultDrob.chisl / resultDrob.znamenatel;
	smDrobA.chisl = resultDrob.chisl % resultDrob.znamenatel;
	smDrobA.znamenatel = resultDrob.znamenatel;
}
//сократим дробь
void SokrDrob(SmDrob smDrobA)
{
   resultDrob.chisl =	(NOD(smDrobA.chisl, smDrobA.znamenatel)) / smDrobA.chisl;
   resultDrob.znamenatel = (NOD(smDrobA.chisl, smDrobA.znamenatel)) % smDrobA.znamenatel;
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
//сократим дробь
void SokrDrob(drob a)
{
	resultDrob.chisl = (NOD(a.chisl, a.znamenatel)) / a.chisl;
	resultDrob.znamenatel = (NOD(a.chisl, a.znamenatel)) / a.znamenatel;
}
//сократим две дроби
//void 

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
	

	//if ((float)((int)a.zelview) == a.zelview) //Целое
	//{
	//	sm.chisl = a.zelview;
	//	
	//}
	//else
	//{

	SmDrob sm;
	int calcbits = 0;

	sm.znamenatel = 1;

		/*do
		{
            calcbits++;
			a.zelview = a.zelview * 10;
		} while (((float)((int)a.zelview) != a.zelview));*/

	/*while (((float)((int)a.zelview) != a.zelview))
	{
		if (((float)((int)a.zelview) == a.zelview)) break;

		calcbits++;
		a.zelview = a.zelview * 10;
	}*/

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
void TransformDecDrobBigZero(DecDrob a)
{

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
	std::cin >> formatDrobs;

	if (formatDrobs == 1)
	{
		//std::cout << "Ввод десятичной дроби 2,3 через (.) две дроби через пробел " << "\n" <<
		//	"Выбор операции над дробями [1] - [2] + [3] * [4] / "<<"\n"<< endl;
		//std::cin >> decDrobA.zelview>>decDrobB.zelview>>operation;
		////иниц числ и знаменатель дабы перевести в норм или смещ дробь
		//InitDecDrob(decDrobA); InitDecDrob(decDrobB);
		//switch (operation)
		//{
		//
		//case 2: otvetDecDrob = SummaDecDrobs(decDrobA, decDrobB);  std::cin >> operation; break;
		//case 1: break;
		//case 3: break;
		//case 4: break;
		//case 0: exit; break;
		//default: exit; break;
		//}

		//тест преобразования десят дроби < 0 0.025
		std::cout << "Ввод десятичной дроби МЕНЬШЕ 0 (0.025) через (.) для преобразования в нормальную дробь " << "\n" << endl;
		std::cin >> decDrobA.zelview;
		std::cout << " \n";
		smDrobA = TransformDecDrobMinZero(decDrobA);
		ShowDrob(smDrobA);
		if (CheckSokrDrob(smDrobA))
		{
			std::cout << "Можно сократить (НОД != 1),сокращаю...\n" << endl;
			std::wcout << "NOD = " << NOD(smDrobA.chisl, smDrobA.znamenatel) <<"\n"<< endl;
			SokrDrob(smDrobA);
			ShowDrob(smDrobA);
		}
		else std::cout << "Дробь нельзя сократить т.к НОД дроби = 1...\n" << endl;
		std::cin >> decDrobA.zelview;
	}

	if (formatDrobs == 2)
	{
		


	}

	if (formatDrobs == 3)
	{

	}

	//std::cin >> inputDrob;
	//ParseInputDrob();
	//std::cin >> drobA.chisl >> drobA.znamenatel;
	//std::cin >> drobB.chisl >> drobB.znamenatel;

	//if (drobA.znamenatel == )

	/*std::cin >> drobA.chisl>>drobA.znamenatel;
	std::cin >> drobB.chisl >> drobB.znamenatel;*/

	// debug input
	//drobA.chisl = 2; drobA.znamenatel = 3; drobB.chisl = 4; drobB.znamenatel = 7;

	//debug output
	std::cout <<" "<< drobA.chisl << endl;
	std::cout << "---" << endl;
	std::cout << " "<<drobA.znamenatel << endl;
	std::cout << "" << endl;

	std::cout << " " << drobB.chisl << endl;
	std::cout << "---" << endl;
	std::cout << " " << drobB.znamenatel << endl;
	std::cout << "" << endl;

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
	//				drobA.chisl = (NOD(drobA.chisl, drobA.znamenatel)) / drobA.chisl;
	//				drobA.znamenatel = (NOD(drobA.chisl,drobA.znamenatel)) / drobA.znamenatel;
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
	
	