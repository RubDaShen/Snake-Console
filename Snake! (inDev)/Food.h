#pragma once
#include "basicObject.h"
#include "Grid.h"
#include "SnakePlayer.h"

class Food : public basicObject
{
public:
	Food(short, short, short, char, short, short, unsigned short, unsigned short);
	~Food();

	inline void checkParity(SnakePlayer*, Grid***, unsigned short&, unsigned short&);

private:
	unsigned short w_grid, h_grid;
};

Food::Food(short _xPos, short _yPos, short _colorID, char _form, short _xPosLct, short _yPosLct, unsigned short _w_grid, unsigned short _h_grid) : basicObject(_xPos, _yPos, _colorID, _form, _xPosLct, _yPosLct)
{
	this->w_grid = _w_grid;
	this->h_grid = _h_grid;
}
Food::~Food() {}

inline void Food::checkParity(SnakePlayer* theSnake, Grid*** theGrid, unsigned short& _ticksInGame, unsigned short& _scoreChain)
{
	if ((xPos == theSnake->GET_xPos_main()) && (yPos == theSnake->GET_yPos_main()))
	{
		Random dm;
		theSnake->CHN_scoreTemp();
		theSnake->ADD_toBody(xPos, yPos);

		_ticksInGame = 0;
		_scoreChain = _scoreChain + 1;

		Console::SetCursorPosition(xPosLct - 1, yPosLct - 2);
		Console::ForegroundColor = ConsoleColor::DarkCyan;
		cout << "Score: ";
		Console::SetCursorPosition(xPosLct + 6, yPosLct - 2);
		Console::ForegroundColor = ConsoleColor::White;
		cout << theSnake->GET_scoreTemp();

		Console::ForegroundColor = ConsoleColor::DarkYellow;
		cout << "  Combo: ";
		Console::SetCursorPosition(xPosLct - 1 + 18, yPosLct - 2);
		cout << "      ";
		Console::SetCursorPosition(xPosLct - 1 + 18, yPosLct - 2);
		Console::ForegroundColor = ConsoleColor::White;
		cout << "x" << _scoreChain;

		do
		{
			this->xPos = dm.Next(0, w_grid);
			this->yPos = dm.Next(0, h_grid);
		} while (theGrid[yPos][xPos]->GET_valueID() != 0);
		theGrid[yPos][xPos]->SET_valueID(2);

		Food::DRW_object();
	}
	if (_ticksInGame > 25)
	{
		_scoreChain = 0;
	}
}