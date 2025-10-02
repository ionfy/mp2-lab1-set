#include "Light.h"

cLight::cLight(uint8_t sg): signal(4) {
	signal.InsElem((sg + 4)%4);
}
bool cLight::isGreen() {
	if (signal.IsMember(0)) {
		return true;
	}
	else {
		return false;
	}
}
bool cLight::isYellow() {
	if (signal.IsMember(1) || signal.IsMember(3)) {
		return true;
	}
	else {
		return false;
	}
}
bool cLight::isRed() {
	if (signal.IsMember(2)) {
		return true;
	}
	else {
		return false;
	}
}
void cLight::change() {
	if (signal.IsMember(3)) {
		signal.DelElem(3);
		signal.InsElem(0);
	}
	else if (signal.IsMember(2)) {
		signal.DelElem(2);
		signal.InsElem(3);
	}
	else if (signal.IsMember(1)) {
		signal.DelElem(1);
		signal.InsElem(2);
	}
	else if (signal.IsMember(0)) {
		signal.DelElem(0);
		signal.InsElem(1);
	}
}
void Light::print(std::ostream& out){
	if (this->isGreen()) out << "Green";
	if (this->isYellow()) out << "Yellow";
	if (this->isRed()) out << "Red";
}

hLight::hLight(uint8_t sg): signal(2) {
	signal.InsElem((sg + 2)%2);
}
bool hLight::isGreen() {
	if (signal.IsMember(0)) {
		return true;
	}
	else {
		return false;
	}
}
bool hLight::isYellow() {
	return false;
}
bool hLight::isRed() {
	if (signal.IsMember(1)) {
		return true;
	}
	else {
		return false;
	}
}
void hLight::change() {
	if (signal.IsMember(1)) {
		signal.DelElem(1);
		signal.InsElem(0);
	}
	else if (signal.IsMember(0)) {
		signal.DelElem(0);
		signal.InsElem(1);
	}
}

void Road::switchLights() {
	cl.change();
	if (cl.isRed() || cl.isYellow()) {
		while (!hl.isGreen()) {
			hl.change();
		}
	}
	else {
		while (hl.isGreen()) {
			hl.change();
		}
	}
}

std::ostream& operator<<(std::ostream& out, const Road& road)
{
	out << "Car: "; road.cl.print(out); out << "\n";
	out << "Human: "; road.hl.print(out); out << "\n";
	return out;
}
