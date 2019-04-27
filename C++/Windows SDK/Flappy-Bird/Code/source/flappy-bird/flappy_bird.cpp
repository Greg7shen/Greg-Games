#include"core.h"
#include"class.h"
#include<vector>
#include<cmath>
#include<ctype.h>
using namespace std;

typedef vector<Obstacle>::iterator obs_iter;

constexpr auto PROMPT = "(Press 'w' to move upwards, 's' to move downwards)";
clock_t start_time;

bool IsCollision(Bird&, vector<Obstacle>);
bool IsObjectCollision(const Bird&, const Obstacle&);

int main(int argc, char* argv[]) {
	int count = 0;
	char choice, direction;
	float passing_time;
	Bird bird('@');
	vector<Obstacle>obs_list;

	GameStart(PROMPT);
replay:
	// Start to randomize and count time...
	RANDOMIZE;
	COUNTINGTIME;
	bird.Initialize();
	while (true) {
		bird.Show();
		// Receive the keyboard inputs and make response
		if (KBHIT) {
			direction = tolower(GETKEY);
			if ((direction == 'w') || (direction == 's')) {
				bird.Move(direction);
			}
		}
		if (IsCollision(bird, obs_list)) {
			// When game is over
			// Due to the replay, this block can't put into function
			screen.Clear();
			GameOver(PassingTime);
			do {
				choice = GETKEY;
				if (tolower(choice) == 'r') {
					vector<Obstacle>new_obs;
					obs_list.assign(new_obs.begin(), new_obs.end());
					goto replay;
				}
				else if (tolower(choice) == 'q') {
					exit(EXIT_SUCCESS);
				}
			} while (choice != 'r' || choice != 'q');
		}
		for (obs_iter i = obs_list.begin(); i != obs_list.end(); ++i) {
			if (i->IsExist()) {
				i->Show();
				i->Move();
			}
		}
		// When passing specific time, create new obstacle
		passing_time = PassingTime;
		// In fact it doesn't fit my original thought
		// But it worked!
		if (fabs(passing_time - static_cast<int>(passing_time)) <= 1e-1) {
			obs_list.push_back(Obstacle());
		}
		WAITING(100);
		screen.Clear();		// In order not to include extra headers
	}
	return 0;
}

bool IsCollision(Bird& bird, vector<Obstacle> obs_list) {
	/* Check the bird and obstacle's list */
	if (!obs_list.size()) {
		return false;
	}
	for (obs_iter i = obs_list.begin(); i != obs_list.end(); ++i) {
		if (IsObjectCollision(bird, *i)) {
			return true;
		}
	}
	return false;
}

bool IsObjectCollision(const Bird& bird, const Obstacle& obs) {
	/* Check whether the bird touch the obstacle */
	bool IsInGap = (bird.x_ > obs.gap_.start_y) && (bird.x_ < obs.gap_.end_y);
	// Using another way to test
	if ((bird.y_ == obs.x_) && (!IsInGap)) return true;
	return false;
}