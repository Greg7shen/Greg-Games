#include<iostream>
#include<cstdlib>
#include<ctime>
#include"User.h"
#include"Board.h"
#include"Buff.h"

// 这里contact是共同的行为，但是我应该传入怎么样的类型呢？
// 传入基类，派生类可以转换为其基类
// 讨论两个没有继承关系的对象之间的关系时使用friend
bool IsContact(Board& board, Buff& Buff) {
	if (Buff.x_ >= kHeight && (Buff.y_ >= board.y_ && Buff.y_ <= board.y_ + board.length_)) {
		return true;
	}
	return false;
}

void Buff::Initialize(void) {
	// There are no need to use srand() again.
	flag = true;
	x_ = 0; y_ = rand() % kWidth;
	// Limit the speed under 3
	speed_ = rand() % 3 + 1;
}

void Buff::Move(void) {
	if (flag) {
		x_ += speed_;
		if (x_ >= kHeight) {
			Disappear();
		} 
	}
}

// 这里可以用析构函数改进
inline void Buff::Disappear(void) {
	flag = false;
}

// 这里可以用重载改进
void SpeedLowBuff::Show(void) {
	if (flag) {
		GotoXY(y_, x_);
		cout << "@";
	}
}

void GetLongerBuff::Show(void) {
	if (flag) {
		GotoXY(y_, x_);
		cout << "#";
	}
}

