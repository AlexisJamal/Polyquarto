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
	Jeton(Jeton const & jeton);
	~Jeton();

	bool getIsUsed() const;
	bool getIsSelected() const;
	bool getIsRed() const;
	bool getIsCircle() const;
	bool getIsHoled() const;
	bool getIsBig() const;

	void setIsUsed(bool b);
	void setIsSelected(bool b);
	void setIsRed(bool b);
	void setIsCircle(bool b);
	void setIsHoled(bool b);
	void setIsBig(bool b);

};


#endif
