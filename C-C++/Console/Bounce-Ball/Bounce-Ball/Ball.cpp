#include<iostream>
#include<ctime>
#include"User.h"
#include"Ball.h"

void Ball::Initialize(void) {
	srand(time(NULL));
	speed_x_ = 1;
	speed_y_ = 1;
	dir_x_ = dir_y_ = 1;
	x_ = rand() % 10;
	y_ = rand() % 80;
}

void Ball::SpeedUp(int level) {
	speed_x_ = static_cast<float>(level);
	speed_y_ = static_cast<float>(level);
}

void Ball::Move(void) {
	// The speed of x and y must be integers
	x_ += static_cast<int>(dir_x_ * speed_x_);
	y_ += static_cast<int>(dir_y_ * speed_y_);
	ChangeDirection();
}

void Ball::ShowBall(void) {
	GotoXY(y_, x_);
	std::cout << 'O';
}

void Ball::ChangeDirection(void) {
	if (x_ >= kHeight || x_ <= 0) {
		dir_x_ *= -1;
	}
	if (y_ >= kWidth || y_ <= 0) {
		dir_y_ *= -1;
	}
}
