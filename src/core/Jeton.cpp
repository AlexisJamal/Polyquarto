#include <iostream>
#include "Jeton.h"

using namespace std;

Jeton::Jeton() {
	isUsed = false;
	isSelected = false;
	isRed = false;
	isCircle = false;
	isHoled = false;
	isBig = false;
}

Jeton::Jeton(bool u, bool s, bool r, bool c, bool h, bool b) {
	isUsed = u;
	isSelected = s;
	isRed = r;
	isCircle = c;
	isHoled = h;
	isBig = b;
}

Jeton::~Jeton() {
}

bool Jeton::getIsUsed(){
	return isUsed;
}
bool Jeton::getIsSelected(){
	return isSelected;
}
bool Jeton::getIsRed(){
	return isRed;
}
bool Jeton::getIsCircle(){
	return isCircle;
}
bool Jeton::getIsHoled(){
	return isHoled;
}
bool Jeton::getIsBig(){
	return isBig;
}

void Jeton::setIsUsed(bool b) {
	isUsed = b;
}
void Jeton::setIsSelected(bool b) {
	isSelected = b;
}
void Jeton::setIsRed(bool b) {
	isRed = b;
}
void Jeton::setIsCircle(bool b) {
	isCircle = b;
}
void Jeton::setIsHoled(bool b) {
	isHoled = b;
}
void Jeton::setIsBig(bool b) {
	isBig = b;
}

