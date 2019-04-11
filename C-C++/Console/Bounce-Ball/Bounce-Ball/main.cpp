/* No rights reserved */

#include<iostream>
#include<windows.h>
#include<time.h>
#include<conio.h>
#include"Board.h"
#include"Ball.h"
#include"User.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

// Before every game beginning, we'll create the same two
// objects, so why not put them out of the main function?
Ball ball;
Board board;

long long start_time, end_time;

int main(int argc, char *argv[]) {
	char key;
	char choice;
	int level;
	int count;

	// Hide the cursor 
	HideCursor();
	// Display the user interface
	Start();
replay:
	Initialize(ball, board);
	level = 1; count = 0;
	start_time = clock();
	while (true) {
		// Should all the process run at the same time?
		LevelUp(ball, level);
		// Display time
		end_time = clock();
		ShowTime(start_time, end_time);
		system("cls");
		// Draw the borad and the ball
		board.Show();
		ball.ShowBall();
		// Move the ball and borad according to the keyboard inputs
		ball.Move();
		if (_kbhit()) {
			key = _getch();
			board.Move(key);
		}
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
		// Notice here are 0.1 seconds paused
		// Control the circuling speed
		Sleep(100);
	}
	system("pause>nul");
	return 0;
}