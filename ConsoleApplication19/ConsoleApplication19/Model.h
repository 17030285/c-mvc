#pragma once
#include<stdint.h>
#include"Sensor.h"
#include<string>
#include<stdlib.h>
#include"logger.h"
using namespace std;
class Model
{
private:
	speedSensor speed;
	accelerometer acceler;
	distanceSensor distance;
	string name;
	int samplingPeriod{ 500 };
	unique_ptr<saveDataLogger>logger;

public:
	Model(void)
	{
		retriveDataFromDatabase();
	}
	const string getName(void) const
	{
		return name;
	}
	void setName(string name)
	{
		this->name = name;
	}
	void  setSpeed(const uint16_t speed)
	{
		this->speed.write(speed);
	}
	uint16_t getSpeed(void)const
	{
		return this->speed.read();
	}
	void setAcceler(const int16_t a)
	{
		this->acceler.write(a);
	}
	uint16_t getAcceler(void) const
	{
		return this->acceler.read();
	}
	uint16_t getDistance(void) const
	{
		return this->distance.read();
	}
	void setDistance(const uint16_t d)
	{
		this->distance.write(d);
	}
	void retriveDataFromDatabase(void)
	{
		setName("Automatic Auxiliary Brake");
		setSpeed(rand() % 171 + 50);
		setAcceler(rand() % 11 - 0);
		setDistance(rand() % 101 - 0);
	}
	void setSampling(const int sampling)
	{
		samplingPeriod = sampling;
	}
	int getSampling(void)
	{
		return samplingPeriod;
	}
	void saveData(int time,int speed,int a,int distance,string brake)
	{
		string output;
		output += to_string(time);
		output += " ";
		output += to_string(speed);
		output += " ";
		output += to_string(a);
		output += " ";
		output += to_string(distance);
		output += " ";
		output += brake;
		logger->log(output);
	}
};