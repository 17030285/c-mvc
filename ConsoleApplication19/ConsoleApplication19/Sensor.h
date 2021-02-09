#pragma once
#include<stdint.h>
#include<iostream>
using namespace std;
class speedSensor
{
private:
	uint16_t speed{};
	const uint16_t maxSpeed = 220;
public:
	uint16_t read(void) const
	{
		return speed;
	}
	void write(uint16_t SPEED)
	{
		if (SPEED > maxSpeed)
		{
			throw("Exceed the range");
		}
		else
		{
			speed = SPEED;
		}
	}
};
class accelerometer
{
private:
	uint16_t acceleratedSpeed{};
	const uint16_t maxASpeed = 10;
public:
	uint16_t read(void) const
	{
		return acceleratedSpeed;
	}
	void write(uint16_t aSpeed)
	{
		if (aSpeed > maxASpeed)
		{
			throw("Exceed the range");
		}
		else
		{
			acceleratedSpeed = aSpeed;
		}
	}
};
class distanceSensor
{
private:
	uint16_t distance{};
	const uint16_t maxDistance = 100; 
public:
	uint16_t read(void) const
	{
		return distance;
	}
	void write(uint16_t d)
	{
		if (d > maxDistance)
		{
			throw("Exceed the range");
		}
		else
		{
			distance = d;
		}
	}
};

