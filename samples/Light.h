#pragma once
#include <string>
#include <iostream>
#include "tset.h"

class Light {
public:
	Light() {};
	virtual bool isGreen() = 0;
	virtual bool isYellow() = 0;
	virtual bool isRed() = 0;
	virtual void change() = 0;
	void print(std::ostream& out);
};

class cLight : public Light {
private:
	TSet signal;
public:
	cLight(uint8_t sg = 0);
	bool isGreen();
	bool isYellow();
	bool isRed();
	void change();
};

class hLight : public Light {
private:
	TSet signal;
public:
	hLight(uint8_t sg = 0);
	bool isGreen();
	bool isYellow();
	bool isRed();
	void change();
};

class Road {
private:
	cLight& cl;
	hLight& hl;
public:
	Road(cLight& cli, hLight& hli) : cl(cli), hl(hli) {}
	void switchLights();
	friend std::ostream& operator<< (std::ostream& out, const Road& road);
};