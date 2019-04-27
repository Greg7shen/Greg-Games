#include"core.h"
#include<iostream>

using namespace std;

void Cursor::HideCursor(void) {
	/* Hide the cursor to get better feelings */
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(handle, &cursor_info);
}


// This function don't works so well...
// So I don't intend to use it.
void Screen::Draw(void) {
	/* Fullfill the screen, limit the space */
	// First row
	cursor_.GotoXY(1, 1);
	for (int i = 1; i <= kWidth; i++) cout << '*';
	// Next few lines
	for (int i = 2; i <= kHeight - 1; i++) {
		cursor_.GotoXY(i, 1); cout << '*';
		cursor_.GotoXY(i, kWidth); cout << '*';
	}
	// Last row
	cursor_.GotoXY(kHeight, 1);
	for (int i = 1; i <= kWidth; i++) cout << '*';
	// Back to origin.
	cursor_.GotoXY(1, 1);
}

void GameStart(const char* say) {
	/* Make the initial interface */
	char ch;
	cursor.HideCursor();
	cursor.GotoXY(screen.kWidth / 2 - 10, screen.kHeight / 2);
	cout << "Enter R to play!";
	cursor.GotoXY(screen.kWidth / 2 - 23, screen.kHeight / 2 + 1);
	cout << say;
	// The user aren't allowed to play unless press the 'q' or 'Q'
	while (tolower(ch = GETKEY) == 'q') {}
}

void GameOver(long delta_time) {
	/* Make the ending interface */
	cursor.GotoXY(screen.kWidth / 2 - 10, screen.kHeight / 2);
	cout << "Thanks for playing!";
	// Show the next lines
	cursor.GotoXY(screen.kWidth / 2 - 13, screen.kHeight / 2);
	cout << "You've insist:" << delta_time << " seconds";
	cursor.GotoXY(screen.kWidth / 2 - 10, screen.kHeight / 2 + 2);
	cout << "Press R to play again";
	cursor.GotoXY(screen.kWidth / 2 - 10, screen.kHeight / 2 + 3);
	cout << "Press Q to quit";
}