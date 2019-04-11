#ifndef _BALL_H__
#define _BALL_H__

#define SPACE ' '
using namespace std;

class Ball {
public:
	friend bool IsGameOver(void);
	friend bool BallWithinBoard(void);
	friend bool BallOut(void);
	friend bool BallOnBoard(void);

	void Move(void);
	void Initialize(void);
	void SpeedUp(int);
	void ShowBall(void);

private:
	void ChangeDirection(void);

	// Speeds
	/* Do not use const variables!!! */
	float speed_x_;
	float speed_y_;

	// Directions
	short dir_x_, dir_y_;

	// Position
	// X: row number
	// Y: column number
	int x_, y_;
};

#endif /* _BALL_H_ ends */
