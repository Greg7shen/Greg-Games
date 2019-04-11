#include<iostream>
#include<cstdlib>
#include<ctime>
#include"User.h"
#include"Board.h"
#include"Buff.h"

// ����contact�ǹ�ͬ����Ϊ��������Ӧ�ô�����ô���������أ�
// ������࣬���������ת��Ϊ�����
// ��������û�м̳й�ϵ�Ķ���֮��Ĺ�ϵʱʹ��friend
bool IsContact(Board& board, Buff& Buff) {
	if (Buff.x_ >= kHeight && (Buff.y_ >= board.y_ && Buff.y_ <= board.y_ + board.length_)) {
		return true;
	}
	return false;
}

void Buff::Initialize(void) {
	srand(time(NULL));
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

// ������������������Ľ�
inline void Buff::Disappear(void) {
	flag = false;
}

// ������������ظĽ�
void SpeedLowBuff::Show(void) {
	if (flag) {
		GotoXY(y_, x_);
		cout << "@";
	}
}

void GetLongerBuff::Show(void) {
	if (flag) {
		GotoXY(y_ + 20, x_);
		cout << "#";
	}
}

