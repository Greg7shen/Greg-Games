#ifndef _BORAD_H__
#define _BORAD_H__

#define SHAPE "---------------" 

class Board {
public:
	friend bool IsGameOver(void);
	friend bool BallWithinBoard(void);
	friend bool BallOut(void);
	friend bool BallOnBoard(void);

	void Initialize(void);
	void Show(void);
	void Move(char);

private:
	float speed_;
	int length_;
	int x_, y_;
};
#endif /* _BORAD_H__ ends */#pragma once
