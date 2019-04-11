#ifndef _USER_H__
#define _USER_H__
#include"Ball.h"
#include"Board.h"

// Tested by another cpp file
const int kWidth = 118;
const int kHeight = 29;

// Check the relevant position between ball and board
bool BallWithinBoard(void);
bool BallOnBoard(void);
bool BallOut(void);

// Console functions
void HideCursor(void);
void GotoXY(int x, int y);
void ShowTime(long long, long long);

// The functions of this program 
void Initialize(Ball &, Board &);
void LevelUp(Ball &, int);
void Start(void);
bool IsGameOver(void);
void End(long long);

#endif /* _USER_H_ ends */
