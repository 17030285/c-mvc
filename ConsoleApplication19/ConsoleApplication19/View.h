#pragma once
#include<stdint.h>
#include"Sensor.h"
#include"Model.h"
#include"authority.h"
#include<string>
#include<Windows.h>
#include<iostream>
#include <stdio.h>
#include <conio.h>
#include<iomanip>
#include <stdlib.h>
#define  NR(x)   (sizeof(x)/sizeof(x[0]+0))
#define  TITLE  "Automatic Auxiliary Brake"
#define  AUTHOR "Author: WEI WEI"
#define  DATE   "DATE:2021/1/29"
using namespace std;
char* menu[] =
{
	(char*)"£ª Information£ª",
	(char*)"£ª    Read    £ª",
	(char*)"£ª  Save Data £ª",
	(char*)"£ª   Logout   £ª",
	(char*)"£ª    Quit    £ª",
};
char* menu2[] =
{
	(char*)"£ª Login  £ª",
	(char*)"£ª Exit   £ª"
};
CONSOLE_CURSOR_INFO cci;
COORD pos = { 0,0 };
enum keys :uint16_t
{
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	RIGHT = 77,
	ENTER = 13,
	ESC = 27,
};

class View
{
public:
	void printModelDetails(Model& m) 
	{
		system("cls");
		m.setSpeed(rand() % 171 + 50);
		m.setAcceler(rand() % 11 - 0);
		m.setDistance(rand() % 101 - 0);
		cout << "***********************************" << endl;
		cout << "Device Name:" << m.getName()<<endl;
		cout << "Speed:" << m.getSpeed()<<endl;
		cout << "Accelerated Speed:" << m.getAcceler() << endl;
		cout << "Distance:" << m.getDistance() << endl;
		cout << "***********************************" << endl;
		int get=_getch();
		fflush(NULL);
	}
	void displayHeader(void)
	{
		cout << "Time" << setw(10) << "speed" << setw(6) << "accelerate" << setw(6) << "distance" << endl;
		cout << "[second]" << setw(10) << "[m/s]" << setw(6) << "[m/s^2]" << setw(6) << "[m]" << endl;
	}
	void displayData(int hour, int speed,int a, int distance,string brakeInfo)
	{
		ios init(NULL);
		init.copyfmt(cout);
		cout << setfill('0') << setw(2) << hour;
		cout.copyfmt(init);
		cout << setw(10) << speed << setw(10) << a << setw(10) << distance <<setw(10)<<brakeInfo<< endl;
	}
	void showmenu(HANDLE hOut, char** menu, int size, int index)
	{
		int i;
		system("cls");
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | 0x8); 
		pos.X = 28;
		pos.Y = 0;
		SetConsoleCursorPosition(hOut, pos); 
		printf("%s", TITLE);
		pos.X = 32;
		pos.Y = 1;
		SetConsoleCursorPosition(hOut, pos);
		printf("%s", AUTHOR);
		pos.X = 32;
		pos.Y = 2;
		SetConsoleCursorPosition(hOut, pos);
		printf("%s", DATE);
		for (i = 0; i < size; i++)
		{
			if (i == index)
			{
				SetConsoleTextAttribute(hOut, FOREGROUND_RED | 0x8);
				pos.X = 32;
				pos.Y = 5 + i;
				SetConsoleCursorPosition(hOut, pos);
				printf("%s", menu[i]);
			}
			else
			{
				SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				pos.X = 32;
				pos.Y = 5 + i;
				SetConsoleCursorPosition(hOut, pos);    
				printf("%s", menu[i]);
			}
		} 
		fflush(stdout);
	} 
	int  get_userinput(int* index, int size)
	{
		int ch;
		ch = _getch();
		switch (ch)
		{
		case UP: if (*index > 0)  *index -= 1;  break; 
		case DOWN:if (*index < size - 1)  *index += 1;  break;
		case LEFT:
		case 97:return 0;
		case RIGHT:return 0;
		case ENTER: return ENTER;
		case ESC: return ESC;
		}
		return 0;
	}
};
