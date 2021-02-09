#pragma once
#include<string>
#include<fstream>
#include<iostream>
using namespace std;
class saveDataLogger
{
private:
	ofstream outputStream;
public:
	saveDataLogger()
	{
		try
		{
			outputStream.open("log.txt", ios::out);
		}
		catch(const char* msg)
		{
			cerr << msg << endl;
		}
	}
	~saveDataLogger()
	{
		try
		{
			outputStream.close();
		}
		catch (const char* msg)
		{
			cerr << msg << endl;
		}
	}
	void log(string message)
	{
		try
		{
			outputStream << message << endl << flush;
		}
		catch (const char* msg)
		{
			cerr << msg << endl;
		}
	}
};