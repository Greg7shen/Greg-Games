/* No rights reserved */

#include<iostream>
#include<windows.h>
#include<time.h>
#include<conio.h>
#include"Board.h"
#include"Buff.h"
#include"Ball.h"
#include"User.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void DrawingTheScreen(void);
void MovingTheObject(void);

// Before every game beginning, we'll create the same two
// objects, so why not put them out of the main function?
char key;
Ball ball;
Board board;
SpeedLowBuff buff1;
GetLongerBuff buff2;
long long start_time, end_time;

int main(int argc, char *argv[]) {
	char choice;
	int level;
	int count;

	// Hide the cursor 
	HideCursor();
	// Display the user interface
	Start();
replay:
	Initialize(ball, board, buff1, buff2);
	level = 1; count = 0;
	start_time = clock();
	while (true) {
		system("cls");
		// Should all the process run at the same time?
		LevelUp(ball, level);

		DrawingTheScreen();
		MovingTheObject();

		// Check the ball and the board
		// Counting the number when ball and board contact
		if (BallOnBoard()) {
			++count;
		}
		// Judge whether the game is over
		if (IsGameOver()) {
			// Remember to clear the screen
			// Otherwise the borad and the ball will
			// Remain on the screen. :)
			system("cls");
			// The two parameters are used to calculate the passing time
			End(end_time - start_time);
			// Get the user choice and control the flow
			do {
				choice = _getch();
				if (tolower(choice) == 'r') {
					goto replay;
				}
				else if (tolower(choice) == 'q') {
					exit(EXIT_SUCCESS);
				}
			} while (choice != 'r' || choice != 'q');
		}
		level = count + 1;
		// Display time
		end_time = clock();
		// Notice here are 0.1 seconds paused
		// Control the circuling speed
		Sleep(100);
	}
	system("pause>nul");
	return 0;
}

void DrawingTheScreen(void) {
	/* Draw all things that needed */
	buff1.Show();
	buff2.Show();
	ShowTime(start_time, end_time);
	board.Show();
	ball.ShowBall();
	// Remember to go back to the (0, 0)
	// Other wise the screen will move down
	GotoXY(0, 0);
}

void MovingTheObject(void) {
	/* Move the ball and borad according to the keyboard inputs */
	ball.Move();
	buff1.Move();
	if (IsContact(board, buff1)) {
		ball.SpeedDown();
	}
	buff2.Move();
	if (IsContact(board, buff2)) {
		board.GetLonger();
	}
	if (_kbhit()) {
		key = _getch();
		board.Move(key);
	}
}
