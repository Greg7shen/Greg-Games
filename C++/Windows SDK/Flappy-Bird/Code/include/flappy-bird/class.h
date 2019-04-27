#pragma once
#pragma once
#include"core.h"
#include<iostream>
#include<ctype.h>
#include<cstdlib>

extern Cursor cursor;
extern Screen screen;

struct Gap {
	int start_y;
	int end_y;
	int length;
};

class Bird;
class Obstacle {
public:
	Obstacle();

	friend bool IsObjectCollision(const Bird&, const Obstacle&);

	void Move(void);
	void Show(void);
	bool IsExist(void) {
		if (x_ > 1) return true;
		return false;
	}

protected:

private:
	bool flag;	// Whether the obstacle is still exist;
	int x_;		// x_: the x position of obstacle
	int speed_;
	Gap gap_;
};

class Bird {
public:
	// Using the constructor function
	Bird(char shape) : shape_(shape) {}

	friend bool IsObjectCollision(const Bird&, const Obstacle&);

	void Initialize(void);
	void Show(void);
	void Move(char choice);

protected:

private:
	char shape_;
	int x_, y_;		// x_: the y position of the bird, y_: the x position of the bird
	int speed_;
};

/* Define bird's functions */
void Bird::Initialize(void) {
	/* Set some properties of the bird */
	x_ = screen.kHeight / 2;
	y_ = 7;
	speed_ = 1;
}

void Bird::Show(void) {
	/* Display the bird on the screen */
	cursor.GotoXY(y_, x_);
	std::cout << shape_;
}

void Bird::Move(char choice) {
	/* Let the bird move according to the para choice */
	switch (choice) {
	case 'w':
		// Always remember to limit the space;
		if (x_ >= 1) {
			x_ -= speed_;
		}
		break;
	case 's':
		if (x_ <= screen.kHeight) {
			x_ += speed_;
		}
		break;
	}
}

/* Define obstacle's functions */
Obstacle::Obstacle(void) {
	/* Class of Obstacle's constructor function */
	flag = true;
	x_ = screen.kWidth;
	speed_ = Random(1, 3);
	gap_.start_y = Random(5, screen.kHeight - 10);
	gap_.length = Random(3, 7);
	gap_.end_y = gap_.start_y + gap_.length;
}

void Obstacle::Show(void) {
	/* Drawing the obstacle on the screen */
	for (int i = 0; i <= gap_.start_y; i++) {
		cursor.GotoXY(x_, i);
		std::cout << '*';
	}
	for (int i = gap_.end_y; i <= screen.kHeight; i++) {
		cursor.GotoXY(x_, i);
		std::cout << '*';
	}
}

void Obstacle::Move(void) {
	/* The speed of obstacle is a constant number */
	x_ -= speed_;
}