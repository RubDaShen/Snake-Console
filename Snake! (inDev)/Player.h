#pragma once
#include <string>
#include <vector>

using namespace std;

class Player
{
public:
	Player();
	~Player();

	inline void addOnePointToScore();

	inline void SET_score(int);
	inline int GET_score();

private:
	int score;
	short colorID_score;
	vector<string> textIn;
	vector<short> colorID_Text;
};

Player::Player()
{
	this->score = 0;
	this->colorID_score = 3;
	textIn.push_back("Score: ");
	colorID_Text.push_back(15);
}
Player::~Player() {}

inline void Player::addOnePointToScore()
{
	this->score = this->score + 1;
}
inline void Player::SET_score(int _newScore)
{
	this->score = _newScore;
}