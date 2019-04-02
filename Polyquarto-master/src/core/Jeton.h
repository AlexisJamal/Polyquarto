#ifndef _JETON_H
#define _JETON_H

using namespace std;

class Jeton {

private :
	
	bool isUsed;
	bool isSelected;
	bool isRed;
	bool isCircle;
	bool isHoled;
	bool isBig;

public :

	Jeton();
	Jeton(bool u, bool s, bool r, bool c, bool h, bool b);
	~Jeton();

	bool getIsUsed();
	bool getIsSelected();
	bool getIsRed();
	bool getIsCircle();
	bool getIsHoled();
	bool getIsBig();

	void setIsUsed(bool b);
	void setIsSelected(bool b);
	void setIsRed(bool b);
	void setIsCircle(bool b);
	void setIsHoled(bool b);
	void setIsBig(bool b);

};


#endif
