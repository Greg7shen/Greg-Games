#pragma once

#ifdef _WINDLL
#define CONSOLE_GAME_API_ __declspec(dllexport)
#else
#define CONSOLE_GAME_API_ __declspec(dllimport)
#endif	// _WINDLL

#include<Windows.h>
#include<conio.h>
#include<cstdlib>
#include<ctime>

HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

CONSOLE_GAME_API_ void GameStart(const char*);
CONSOLE_GAME_API_ void GameOver(long);

/*---------------------------------------------------------------------------------------------*/

/* Dealing with the keyboard input */
#define KBHIT _kbhit()
#define GETKEY _getch()
/*---------------------------------------------------------------------------------------------*/

/* Dealing with the random part*/
#define RANDOMIZE srand(static_cast<unsigned int>(time(NULL)))

template<class T>
T Random(T start, T end) {
	/* Return a random number which is between the two given numbers */
	T num = rand() % (end - start + 1) + start;
	return num;
}

/*---------------------------------------------------------------------------------------------*/


/* Dealing with the time part */
#define WAITING(X) Sleep(X)
// Using the thought of seed.
#define COUNTINGTIME (start_time = clock())
#define PassingTime ((clock() - start_time) / 1000.0)
// Visual Studio can identify the marco function? That's good.

/*---------------------------------------------------------------------------------------------*/

/* Dealing with screen and cursor parts */
// Actually, Only one cursor exists.
// So there's no need to set x and y.
class Cursor {
public:
	void GotoXY(int x, int y);
	void HideCursor(void);

protected:

private:
	int x_, y_;		// x_: the x position of the screen, y_: the y position of the screen.
};

class Screen {
public:
	Screen(Cursor cursor) : cursor_(cursor) {}
	void Draw(void);
	void Clear(void);

	// The two variables should be public
	const int kWidth = 118;
	const int kHeight = 29;

protected:

private:
	Cursor cursor_;
};
/*---------------------------------------------------------------------------------------------*/
// Debuging...
// Not knowing why, the two functions have to be put there,
// Otherwise the compliation will fail.
void Screen::Clear(void) {
	/* clear the screen */
	system("cls");
}

void Cursor::GotoXY(int x, int y) {
	/* Go to any position of the console */
	COORD pos;
	pos.X = x;  pos.Y = y;
	// Update x_ and y_
	x_ = x; y_ = y;
	SetConsoleCursorPosition(handle, pos);
}
/*---------------------------------------------------------------------------------------------*/
// After defination of cursor and screen, you can use them.
Cursor cursor;
Screen screen(cursor);