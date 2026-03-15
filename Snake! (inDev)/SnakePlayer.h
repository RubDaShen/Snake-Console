#pragma once
#include "SnakeHead.h"
#include "SnakeBody.h"
#include "Grid.h"

class SnakePlayer
{
public:
	SnakePlayer(unsigned short, unsigned short, unsigned short, unsigned short, char, char, unsigned short, unsigned short, unsigned short, unsigned short, string, unsigned short);
	~SnakePlayer();

	// F U N C T I O N S !
	inline void changeDir(char);
	inline void SHW_snake(Grid***);
	inline void CLR_snake(Grid***);
	inline unsigned short MOV_snake(Grid***);
	inline void ADD_toBody(unsigned short, unsigned short);
	inline void FreezeSnake(bool);

	// G E T T E R S !
	inline unsigned short GET_xPos_main();
	inline unsigned short GET_yPos_main();
	inline string GET_myName();

	// S E T T E R S - N - H A C K S!
	inline void SET_myName(string);
	inline void SET_xPos_main(unsigned short);
	inline void SET_yPos_main(unsigned short);

	// Allocated for score only!
	inline int GET_scoreTemp();
	inline void SET_scoreTemp(int);
	inline void CHN_scoreTemp();

	// E X P E R I M E N T A L !
	inline void SHW_WholeSnake(Grid***);

private:
	//SnakeHead* OBJ_head;
	SnakeBody** OBJ_body;
	SnakeBody* NEW_body;

	string myName;

	unsigned short amountBody;
	unsigned short xPos_main, yPos_main;
	short xDpz, yDpz;
	unsigned short h, w;
	unsigned short colorIDHead, colorIDBody; char formHead, formBody;
	unsigned short dirFacing;
	unsigned short indexMoving;
	unsigned short indexShowing;
	int scoreTemp;
	unsigned short xPosLct, yPosLct;
	unsigned short xDpz_saved, yDpz_saved;
};

SnakePlayer::SnakePlayer(unsigned short _xPos_main, unsigned short _yPos_main, unsigned short _colorIDHead, unsigned short _colorIDBody, char _formHead, char _formBody, unsigned short _HEIGHT, unsigned short _WIDTH, unsigned short _xPosLct, unsigned short _yPosLct, string _myName, unsigned short _amountBody)
{
	this->xPos_main = _xPos_main;
	this->yPos_main = _yPos_main;
	this->colorIDHead = _colorIDHead;
	this->colorIDBody = _colorIDBody;
	this->formHead = _formHead;
	this->formBody = _formBody;
	this->amountBody = _amountBody;
	this->dirFacing = 2;
	this->xDpz = 1;
	this->yDpz = 0;
	this->w = _WIDTH;
	this->h = _HEIGHT;
	this->indexMoving = 0;
	this->scoreTemp = 0;
	this->xPosLct = _xPosLct;
	this->yPosLct = _yPosLct;
	this->myName = _myName;

	OBJ_body = new SnakeBody * [amountBody];
	for (unsigned short i = 0; i < amountBody; i = i + 1)
	{
		OBJ_body[i] = new SnakeBody(xPos_main + 0 + i, yPos_main, colorIDBody, formBody, xPosLct, yPosLct, 219);
	}

	// E X P E R I M E N T A L !
	this->xPos_main = this->xPos_main + this->amountBody - 1;
}
SnakePlayer::~SnakePlayer() {}

// F U N C T I O N S !
inline void SnakePlayer::SHW_snake(Grid*** theGrid)
{
	OBJ_body[indexMoving]->useColor();
	Console::SetCursorPosition((OBJ_body[indexMoving]->GET_xPos() * 2) + xPosLct, OBJ_body[indexMoving]->GET_yPos() + yPosLct);
	theGrid[OBJ_body[indexMoving]->GET_yPos()][OBJ_body[indexMoving]->GET_xPos()]->SET_valueID(1);
	if (OBJ_body[indexMoving]->GET_isVertical())
	{
		std::cout << OBJ_body[indexMoving]->GET_verticalSideForm() << OBJ_body[indexMoving]->GET_verticalSideForm();
	}
	else
	{
		std::cout << OBJ_body[indexMoving]->GET_characterForm() << OBJ_body[indexMoving]->GET_characterForm();
	}
}
inline void SnakePlayer::CLR_snake(Grid*** theGrid)
{
	//Console::SetCursorPosition(xPos_main, yPos_main);
	//cout << " ";

	Console::SetCursorPosition((OBJ_body[indexMoving]->GET_xPos() * 2) + xPosLct, OBJ_body[indexMoving]->GET_yPos() + yPosLct);
	theGrid[OBJ_body[indexMoving]->GET_yPos()][OBJ_body[indexMoving]->GET_xPos()]->SET_valueID(0);
	std::cout << "  ";
}
inline unsigned short SnakePlayer::MOV_snake(Grid*** theGrid)
{
	if ((((xPos_main + xDpz) != w) && ((xPos_main + xDpz) != -1)) && ((yPos_main + yDpz) != h) && ((yPos_main + yDpz) != -1))
	{
		if ((theGrid[yPos_main + yDpz][xPos_main + xDpz]->GET_valueID() == 2) || (theGrid[yPos_main + yDpz][xPos_main + xDpz]->GET_valueID() == 0))
		{
			xPos_main = xPos_main + xDpz;
			yPos_main = yPos_main + yDpz;

			//cout << "This is new!";
			//getch();
		}
		else
		{
			if (theGrid[yPos_main + yDpz][xPos_main + xDpz]->GET_valueID() == 1)
			{
				//cout << "I got here 2!";
				//getch();
				return 2; // Death by hitting its own body!
			}
			else
			{
				if (theGrid[yPos_main + yDpz][xPos_main + xDpz]->GET_valueID() == 3)
				{
					//cout << "I got here 3!";
					//getch();
					return 3; // Death by hitting something strange. A wall, maybe.
				}
			}
		}
	}
	else
	{
		//cout << "I got here 1!";
		//getch();
		return 1; // Death by trying to get out the board!
	}

	OBJ_body[indexMoving]->SET_xPos(xPos_main);
	OBJ_body[indexMoving]->SET_yPos(yPos_main);
	switch (dirFacing)
	{
	case 1: case 3:
		OBJ_body[indexMoving]->SET_isVertical(true);
		break;

	case 2: case 4:
		OBJ_body[indexMoving]->SET_isVertical(false);
		break;
	}

	indexMoving = indexMoving + 1;
	if (indexMoving == amountBody)
	{
		indexMoving = 0;
	}

	return 0;
}
inline void SnakePlayer::changeDir(char tilePressed)
{
	switch (tilePressed)
	{
	case 'W':
		if (dirFacing != 3)
		{
			yDpz = -1;
			xDpz = 0;
			dirFacing = 1;
		}
		break;

	case 'A':
		if (dirFacing != 2)
		{
			xDpz = -1;
			yDpz = 0;
			dirFacing = 4;
		}
		break;

	case 'S':
		if (dirFacing != 1)
		{
			yDpz = 1;
			xDpz = 0;
			dirFacing = 3;
		}
		break;

	case 'D':
		if (dirFacing != 4)
		{
			xDpz = 1;
			yDpz = 0;
			dirFacing = 2;
		}
		break;
	}
}
inline void SnakePlayer::ADD_toBody(unsigned short _xPos_food, unsigned short _yPos_food)
{
	SnakeBody** tmp;
	tmp = new SnakeBody * [amountBody + 1];
	for (int i = 0; i < amountBody; i = i + 1)
	{
		tmp[i] = OBJ_body[i];
	}
	NEW_body = new SnakeBody(_xPos_food, _yPos_food, colorIDBody, formBody, xPosLct, yPosLct, 219);
	tmp[amountBody] = NEW_body;
	OBJ_body = tmp;
	amountBody = amountBody + 1;
}
inline void SnakePlayer::FreezeSnake(bool isUnfreeze)
{
	this->xDpz_saved = this->xDpz;
	this->yDpz_saved = this->yDpz;

	this->xDpz = 0; this->yDpz = 0;

	if (isUnfreeze)
	{
		this->xDpz = this->xDpz_saved;
		this->yDpz = this->yDpz_saved;
	}
}

// G E T T E R S !
inline unsigned short SnakePlayer::GET_xPos_main()
{
	return this->xPos_main;
}
inline unsigned short SnakePlayer::GET_yPos_main()
{
	return this->yPos_main;
}
inline string SnakePlayer::GET_myName()
{
	return this->myName;
}

// S E T T E R S - N - H A C K S !
inline void SnakePlayer::SET_myName(string _newName)
{
	this->myName = _newName;
}
inline void SnakePlayer::SET_xPos_main(unsigned short _xPos_main)
{
	this->xPos_main = _xPos_main;
}
inline void SnakePlayer::SET_yPos_main(unsigned short _yPos_main)
{
	this->yPos_main = _yPos_main;
}

// Allocated for score only :D
inline int SnakePlayer::GET_scoreTemp()
{
	return this->scoreTemp;
}
inline void SnakePlayer::SET_scoreTemp(int _newScoreTemp)
{
	this->scoreTemp = _newScoreTemp;
}
inline void SnakePlayer::CHN_scoreTemp()
{
	this->scoreTemp = this->scoreTemp + 1;
}

// E X P E R I M E N T A L !
inline void SnakePlayer::SHW_WholeSnake(Grid*** theGrid)
{
	for (int i = 0; i < amountBody; i = i + 1)
	{
		OBJ_body[i]->useColor();
		Console::SetCursorPosition((OBJ_body[i]->GET_xPos() * 2) + xPosLct, OBJ_body[i]->GET_yPos() + yPosLct);
		theGrid[OBJ_body[i]->GET_yPos()][OBJ_body[i]->GET_xPos()]->SET_valueID(1);
		if (OBJ_body[i]->GET_isVertical())
		{
			std::cout << OBJ_body[i]->GET_verticalSideForm() << OBJ_body[i]->GET_verticalSideForm();
		}
		else
		{
			std::cout << OBJ_body[i]->GET_characterForm() << OBJ_body[i]->GET_characterForm();
		}
	}
}
/*
if (((xPos_main + xDpz) != w) && ((xPos_main + xDpz) != -1))
	{
		xPos_main = xPos_main + xDpz;
	}
	if (((yPos_main + yDpz) != h) && ((yPos_main + yDpz) != -1))
	{
		yPos_main = yPos_main + yDpz;
	}
*/