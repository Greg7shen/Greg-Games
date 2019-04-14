#include<iostream>
#include<ctype.h>
#include<ctime>
#include<windows.h>
#include<conio.h>
#include"User.h"
#include"Ball.h" 

// Using C syntax 
extern Ball ball;
extern Board board;

HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

bool BallWithinBoard(void) {
	return (ball.y_ >= board.y_) && (ball.y_ <= board.y_ + board.length_);
}

/* Define all the condition for the ball and the board */
bool BallOut(void) {
	return (ball.x_ >= kHeight) && !(BallWithinBoard());
}

bool BallOnBoard(void) {
	return (ball.x_ >= kHeight) && (BallWithinBoard());
}

void HideCursor(void) {
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(handle, &cursor_info);
}

void GotoXY(int x, int y) {
	COORD pos;
	pos.X = x;  pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void ShowTime(long long start, long long end) {
	GotoXY(1, kHeight);
	long long time = (end - start) / CLOCKS_PER_SEC;
	cout << "Time: " << time;
}

void Initialize(Ball &ball, Board &board, Buff &buff1, Buff &buff2) {
	/* Initialize the initial condition
	   And level up when needed */
	ball.Initialize();
	board.Initialize();
	// why this two objects use the same variables?
	buff1.Initialize();
	buff2.Initialize();
}

void LevelUp(Ball &ball, int level) {
	ball.SpeedUp(level);
}

void Start(void) {
	/* Make the initial interface */
	char ch;
	GotoXY(kWidth / 2 - 10, kHeight / 2);
	cout << "Enter R to play!";
	GotoXY(kWidth / 2 - 23, kHeight / 2 + 1);
	cout << "(press w to move left side, and d to move right side)";
	// The user aren't allowed to play unless press the 'q' or 'Q'
	while (tolower(ch = _getch()) == 'q') {}
}

bool IsGameOver(void) {
	if (BallOut()) {
		return true;
	}
	else {
		return false;
	}
}

void End(long long delta_time) {
	/* Make the ending interface */
	GotoXY(kWidth / 2 - 10, kHeight / 2);
	cout << "Thanks for playing!";
	// Show the next lineS
	GotoXY(kWidth / 2 - 13, kHeight / 2);
	cout << "You've insist:" << delta_time / CLOCKS_PER_SEC << " seconds";
	GotoXY(kWidth / 2 - 10, kHeight / 2 + 2);
	cout << "Press R to play again";
	GotoXY(kWidth / 2 - 10, kHeight / 2 + 3);
	cout << "Press Q to quit";
}

