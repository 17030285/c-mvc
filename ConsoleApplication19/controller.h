#pragma once
#include<stdint.h>
#include<string>
#include<Windows.h>
#include<iostream>
#include <stdio.h>
#include<thread>
#include <conio.h>
#include <atomic> 
#include <stdlib.h>
#include"Model.h"
#include"View.h"
#include"authority.h"
using namespace std;
class controller
{
private:
	Model model;
	View view;
	bool logged=false;
	string username;
	string roleName;
	uint16_t Promission;
public:
	void configureSensor(void);
	void readData(void)
	{
		system("cls");
		int speed = model.getSpeed();
		int a = model.getAcceler();
		int distance = model.getDistance();
		view.displayHeader();
		for (int i = 1; i <= 60; i=i+3)
		{
			model.setSpeed( rand() % 171 +50);
			model.setAcceler( rand() % 11 - 0);
			model.setDistance(rand() % 101 - 0);
			view.displayData(i, model.getSpeed(), model.getAcceler(), model.getDistance(),brake());
			std::this_thread::sleep_for(std::chrono::milliseconds(model.getSampling()));
		}
		int get = _getch();
		fflush(NULL);
	}
	double fun(double a,double b,double c)
	{
		double A = 2*a;
		double discriminant = b * b - 4 * a * c;
		double x1, x2;	
		if (discriminant > 0) {
			x1 = (-b + sqrt(discriminant)) / (A);
			x2 = (-b - sqrt(discriminant)) / (A);
			if (x1 > x2)
			{
				return x1;
			}
			else 
			{
				return x2;
			}
		}
		else if (discriminant == 0) {
			x1 = (-b + sqrt(discriminant)) / (A);
			return x1;
		}
		else {
			return NULL;
		}
	}
	string brake(void)
	{
		double time = fun((model.getAcceler() / 2), model.getSpeed()*0.27, -(model.getDistance()));
		if (time < 2)
		{
			return "brake!!!";
		}
		else
		{
			return"not need brake";
		}
	}
	bool login(void)
	{
		system("cls");
		Subject subject;
		Authenticator authenticator;
		ProofOfId proofofid;
		Role role;
		promission p;
		subject.enterId();
		proofofid = authenticator.authenticateUser(subject);
		cout << "subject proof of id =" << subject.getProffId() << endl;
		cout << "system proof of id =" << proofofid.getProofID() << endl;
		if ((!proofofid.getProofID().empty()) & (proofofid.getProofID() == subject.getProffId()))
		{
			cout<<"\nlogin success"<<endl;
			logged=true;
			username = subject.getId();
			roleName = role.getRoleName(username);
			Promission = p.getPromission(roleName);
		}
		else
		{
			cout << "\nlogin false" << endl;
			logged = false;
		}
		int get=_getch();
		fflush(NULL);
		return logged;
	}
	void save(void)
	{
		system("cls");
		cout << "start to save" << endl;
		for (int i = 1; i < 60; i = i + 3)
		{
			model.setSpeed(rand() % 171 + 50);
			model.setAcceler(rand() % 11 - 0);
			model.setDistance(rand() % 101 - 0);
			model.saveData(i, model.getSpeed(), model.getAcceler(), model.getDistance(), brake());
		}
		cout << "finish" << endl;
		int get = _getch();
		fflush(NULL);
	}
	int run(void)
	{   front:
		//int i;
		int ret;
		int index = 0;
		HANDLE hOut;
		SetConsoleTitleA(TITLE);
		//获取当前的句柄---设置为标准输出句柄 
		hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		//获取光标信息
		GetConsoleCursorInfo(hOut, &cci);
		//设置光标大小   
		cci.dwSize = 1;
		//设置光标不可见 FALSE   
		cci.bVisible = 0;
		//设置(应用)光标信息
		SetConsoleCursorInfo(hOut, &cci);
		t:
		while (1)
		{
			if (logged == true)
			{
				view.showmenu(hOut, menu, NR(menu), index);
				ret = view.get_userinput(&index, NR(menu));
				if (ret == ESC)
					break;
				if (ret == ENTER)
				{
					switch (index)
					{
					case 0:   
					{
						if ((Promission&R))
						{
							view.printModelDetails(model); 
							break;
						}
						else
						{
							system("cls");
							cout << username << " denied" << endl;
							int get = _getch();
							fflush(NULL);
							goto t;
						}
					}
					case 1:
					{
						if ((Promission&W))
						{
							readData();
							break;
						}
						else
						{
							system("cls");
							cout << username << " denied" << endl;
							int get = _getch();
							fflush(NULL);
							goto t;
						}
					}
					case 2:
					{
						if ((Promission&X))
						{
							save();
							break;
						}
						else
						{
							system("cls");
							cout << username << " denied" << endl;
							int get = _getch();
							fflush(NULL);
							goto t;
						}
					}
					case 3:
					{
						logged = false;
						goto front;
					}
					case 4:
					{
						return 0;
					}
					}
				}
			}
			else
			{
				view.showmenu(hOut, menu2, NR(menu2), index);
				ret = view.get_userinput(&index, NR(menu2));
				if(ret==ESC)
				{
					break;
				}
				if (ret ==ENTER)
				{
					switch (index)
					{
					case 0: login(); break;
					case 1: return 0;
					}
				}
			}	
		}
		return 0;
	}
};
