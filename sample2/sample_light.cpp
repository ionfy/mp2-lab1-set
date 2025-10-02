#include <iostream>
#include "Light.h"
#include "tset.h"



int main() {
	cLight cli = cLight(0);
	hLight hli = hLight(1);
	Road r = Road(cli, hli);
	std::cout << r;
	r.switchLights();
	std::cout << r;
	r.switchLights();
	std::cout << r;
	r.switchLights();
	std::cout << r;
	r.switchLights();
	std::cout << r;
	r.switchLights();
}