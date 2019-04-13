#include<iostream>
#include<cstring>
#include<conio.h>
#include"Board.h"
#include"User.h"

void Board::Initialize(void) {
	is_long_ = false;
	speed_ = 5;
	length_ = strlen(SHAPE);
	x_ = kHeight;
	y_ = kWidth / 2;
}

void Board::Show(void) {
	GotoXY(y_, x_);
	if (is_long_) {
		std::cout << LONGSHAPE;
	}
	else {
		std::cout << SHAPE;
	}
}

void Board::Move(char direction) {
	switch (direction) {
	case 'a':
	case 'A':
		y_ -= speed_;
		break;
	case 'd':
	case 'D':
		y_ += speed_;
		break;
	}
}

void Board::GetLonger(void) {
	length_ = strlen(LONGSHAPE);
	is_long_ = true;
}