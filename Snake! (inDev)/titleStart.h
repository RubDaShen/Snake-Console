#pragma once
#include "textInScreen.h"

class titleStart
{
private:
	int xPos, yPos;
	textInScreen** arrayText;

	short a;
	unsigned short i, c;

public:
	titleStart(int, int);
	~titleStart();

	void doShow(bool&);
	void SET_timeSleepText_ALL(int);

	inline int GET_speedFade_at(unsigned short);
	inline int GET_timeFade_at(unsigned short);
};

titleStart::titleStart(int _xPos, int _yPos)
{
	arrayText = new textInScreen * [4];
	for (int i = 0; i < 4; i = i + 1)
	{
		arrayText[i] = new textInScreen();
	}
	arrayText[0]->SET_thisMessage("  T H R E E  ");
	arrayText[1]->SET_thisMessage("    T W O    ");
	arrayText[2]->SET_thisMessage("    O N E    ");
	arrayText[3]->SET_thisMessage("    G O !    ");

	this->xPos = _xPos;
	this->yPos = _yPos;
	this->i = 0;
	this->c = 0;
}
titleStart::~titleStart()
{
	for (int i = 0; i < 4; i = i + 1)
	{
		arrayText[i]->~textInScreen();
	}
}

void titleStart::doShow(bool& textIsOver)
{
	if (i < 4)
	{
		a = (arrayText[i]->GET_thisMessage().length()) / 3;
		if (xPos < a)
		{
			xPos = a;
		}

		if (c < 4)
		{
			Console::SetCursorPosition(xPos - a, yPos);
			arrayText[i]->doFade();
			this->c = this->c + 1;
		}
		else
		{
			this->c = 0;
			this->i = this->i + 1;
		}
	}
	else
	{
		i = 0;
		textIsOver = true;
	}
}
void titleStart::SET_timeSleepText_ALL(int _timeFade)
{
	for (int i = 0; i < 4; i = i + 1)
	{
		arrayText[i]->SET_timeFade(_timeFade);
	}
}

inline int titleStart::GET_speedFade_at(unsigned short _index)
{
	return this->arrayText[_index]->GET_speedFade();
}
inline int titleStart::GET_timeFade_at(unsigned short _index)
{
	return this->arrayText[_index]->GET_timeFade();
}