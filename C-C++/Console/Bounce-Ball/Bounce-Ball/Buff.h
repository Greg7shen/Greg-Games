#ifndef _Buff_H__
#define _Buff_H__

#include"Board.h"

class Board;

class Buff {
public:	
	friend bool IsContact(Board&, Buff&);

	void Initialize(void);
	void Move(void);

protected:
	// That's why the protected exist
	// In fact, there's no need to use protected key word
	void Disappear(void);

	bool flag;	// Whether the Buff exist
	int x_, y_;
	int speed_;
private:
};

class SpeedLowBuff:public Buff {
public:
	void Show(void);
protected:
private:
};

class GetLongerBuff:public Buff {
public:
	void Show(void);
protected:
private:
};

#endif /* _Buff_H__ ends */
