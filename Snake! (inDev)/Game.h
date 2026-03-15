#pragma once
#include "Grid.h"
#include "SnakePlayer.h"
#include "Food.h"
#include "GameFrame.h"
#include "Player.h"
#include "titleStart.h"
#include "Wall.h"

class Game
{
public:
	Game(unsigned short, unsigned short, unsigned short, unsigned short, unsigned short, unsigned short, int, unsigned short, unsigned short, unsigned short, unsigned short);
	~Game();

	// F U N C T I O N S !
	inline void showGrid(Grid***);
	inline void startGame();
	inline void showDeathMessage(unsigned short);

	// E X P E R I M E N T A L !
	inline void PreRenderGame();

private:
	Grid*** theGrid;
	SnakePlayer* theSnake;
	GameFrame* theFrame;
	Player* thePlayer;
	vector<Wall*> theWall;
	vector<Food*> theFood;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD theCoords;

	unsigned short h_console, w_console;
	unsigned short h, w;
	unsigned short xSnake, ySnake;
	unsigned short xPosLct, yPosLct;
	unsigned short xPosFrm, yPosFrm;
	int amountSleep, scoreToExport;
	char tilePressed;
	unsigned short gameIsOver;
	unsigned short auxNum;
	unsigned short ticksInGame;
	unsigned short scoreChain;

	// E X P E R I M E N T A L !
	unsigned short w_wall, h_wall;
	unsigned short xPos_wall, yPos_wall;
};

Game::Game(unsigned short _H_CONSOLE, unsigned short _W_CONSOLE, unsigned short _WIDTH, unsigned short _HEIGHT, unsigned short _xSnake, unsigned short _ySnake, int _amountSleep, unsigned short xPos_Location, unsigned short yPos_Location, unsigned short xPos_Frame, unsigned short yPos_Frame)
{
	this->h_console = _H_CONSOLE;
	this->w_console = _W_CONSOLE;
	this->h = _HEIGHT;
	this->w = _WIDTH;
	this->gameIsOver = false;
	this->xSnake = _xSnake;
	this->ySnake = _ySnake;
	this->amountSleep = _amountSleep;
	this->xPosLct = xPos_Location;
	this->yPosLct = yPos_Location;
	this->xPosFrm = xPos_Frame;
	this->yPosFrm = yPos_Frame;
	this->ticksInGame = 0;
	this->scoreChain = 0;

	this->h_wall = 10;
	this->w_wall = 20;
	this->xPos_wall = 5;
	this->yPos_wall = 5;

	theGrid = new Grid * *[h];
	for (unsigned short i = 0; i < h; i = i + 1)
	{
		theGrid[i] = new Grid * [w];
		for (unsigned short c = 0; c < w; c = c + 1)
		{
			theGrid[i][c] = new Grid();
		}
	}

	theSnake = new SnakePlayer(xSnake, ySnake, 1, 2, 'o', 219, h, w, xPosLct, yPosLct, "Player", 3);
	theFrame = new GameFrame(xPosFrm, yPosFrm, w, h);
	thePlayer = new Player();

	// F o o d !
	for (unsigned short i = 0; i < 9; i = i + 1)
	{
		theFood.push_back(new Food(10, 10, 4, 254, xPosLct, yPosLct, w, h));
	}

	// Wall position!
	for (unsigned short i = 0; i < h_wall; i = i + 1)
	{
		for (unsigned short c = 0; c < w_wall; c = c + 1)
		{
			if ((i == 0) || (i == (h_wall - 1)) || (c == 0) || (c == (w_wall - 1)))
			{
				theWall.push_back(new Wall(this->yPos_wall + c, xPos_wall + i, 15, 205, xPosLct, yPosLct));
			}
		}
	}
	for (unsigned short i = 0; i <= 3; i = i + 1)
	{
		theWall.erase(theWall.begin() + (int(this->w_wall / 2) - i + 1));
		theWall.erase(theWall.end() - (int(this->w_wall / 2) - i + 2));
	}


	/* General Definition in Board! */
	for (unsigned short i = 0; i < theWall.size(); i = i + 1)
	{
		theGrid[theWall.at(i)->GET_yPos()][theWall.at(i)->GET_xPos()]->SET_valueID(3);
	}
}
Game::~Game() {}

inline void Game::showGrid(Grid*** theGrid)
{
	for (unsigned short i = 0; i < h; i = i + 1)
	{
		//Console::SetCursorPosition(0, i);
		for (unsigned short c = 0; c < w; c = c + 1)
		{
			cout << theGrid[i][c]->GET_valueID() << " ";
		}
		cout << endl;
	}
}
inline void Game::startGame()
{
	// Extra definitions before entering the loops!
	while (gameIsOver == 0)
	{
		if (kbhit())
		{
			tilePressed = toupper(getch());
			theSnake->changeDir(tilePressed);
		}
		theSnake->CLR_snake(theGrid);
		gameIsOver = theSnake->MOV_snake(theGrid);
		theSnake->SHW_WholeSnake(theGrid);
		
		for (unsigned short i = 0; i < theFood.size(); i = i + 1)
		{
			theFood.at(i)->checkParity(theSnake, theGrid, ticksInGame, scoreChain);
		}
		this->ticksInGame = this->ticksInGame + 1;

		/* Text in screen! */

		/*
		// GameTicks
		Console::SetCursorPosition(0, 0);
		cout << this->ticksInGame << " - " << this->scoreChain;
		*/

		// Combo 
		Console::SetCursorPosition(xPosLct - 1 + 18, yPosLct - 2);
		cout << "      ";
		Console::SetCursorPosition(xPosLct - 1 + 18, yPosLct - 2);
		Console::ForegroundColor = ConsoleColor::White;
		cout << "x" << scoreChain;

		Sleep(amountSleep);
	}

	showDeathMessage(gameIsOver);
	Sleep(100000);
}
inline void Game::showDeathMessage(unsigned short _deathN)
{
	switch (_deathN)
	{
	case 1:
		this->auxNum = (theSnake->GET_myName().size() / 2) + 18;
		break;

	case 2:
		this->auxNum = (theSnake->GET_myName().size() / 2) + 12;
		break;

	case 3:
		this->auxNum = (theSnake->GET_myName().size() / 2) + 6;
		break;

	default:
		this->auxNum = 6;
		break;
	}

	Console::BackgroundColor = ConsoleColor::White;
	Console::ForegroundColor = ConsoleColor::Black;
	this->theCoords.X = this->xPosLct + this->w - 8; this->theCoords.Y = this->yPosLct + ((this->h - 1) / 2);
	SetConsoleCursorPosition(hConsole, this->theCoords);
	cout << " ~ YOU DIED! ~ ";

	Console::BackgroundColor = ConsoleColor::Black;
	Console::ForegroundColor = ConsoleColor::White;
	this->theCoords.X = this->xPosLct + this->w - this->auxNum; this->theCoords.Y = this->yPosLct + (this->h / 2);
	SetConsoleCursorPosition(hConsole, this->theCoords);

	switch (_deathN)
	{
	case 1:
		cout << theSnake->GET_myName() << ((theSnake->GET_myName().at(theSnake->GET_myName().size() - 1) != 's') ? "'s" : "'") << " speed couldn't destroy the board.";
		break;

	case 2:
		cout << theSnake->GET_myName() << " tried to eat themself.";
		break;

	case 3:
		cout << theSnake->GET_myName() << " hit a wall.";
		break;

	default:
		cout << "Accident_MISSING_SNAKE";
		break;
	}
}

// E X P E R I M E N T A L !
inline void Game::PreRenderGame()
{
	theFrame->SHW_gameFrame();
	for (unsigned short i = 0; i < theFood.size(); i = i + 1)
	{
		theFood.at(i)->DRW_object();
	}
	Console::SetCursorPosition(xPosLct - 1, yPosLct - 2);
	Console::ForegroundColor = ConsoleColor::DarkCyan;
	cout << "Score: ";
	Console::ForegroundColor = ConsoleColor::White;
	cout << "0";

	Console::SetCursorPosition(xPosLct + 9, yPosLct - 2);
	Console::ForegroundColor = ConsoleColor::DarkYellow;
	cout << " Combo: ";
	Console::ForegroundColor = ConsoleColor::White;
	cout << "x0";

	Console::SetCursorPosition(xPosLct + (w * 2) - 14, yPosLct - 2);
	Console::ForegroundColor = ConsoleColor::Red;
	cout << "Difficulty: ";
	Console::ForegroundColor = ConsoleColor::White;
	cout << ((float(150 - amountSleep) / 50) + 1); // 32.5 -> 5.

	/* / / / / / / / / / */
	theSnake->SHW_WholeSnake(theGrid);

	for (unsigned short i = 0; i < theWall.size(); i = i + 1)
	{
		theWall.at(i)->DRW_alignBoxes(theGrid);
	}
}