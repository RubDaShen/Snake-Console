#pragma once
#include <Windows.h>
#include <iostream>

class GameFrame
{
public:
	GameFrame(short, short, short, short);
	~GameFrame();

	inline void SHW_gameFrame();

private:
	short xStart, yStart;
	short w, h;
};

GameFrame::GameFrame(short _xStart, short _yStart, short WIDTH, short HEIGHT)
{
	this->xStart = _xStart;
	this->yStart = _yStart;
	this->w = WIDTH;
	this->h = HEIGHT;
}
GameFrame::~GameFrame() {}

inline void GameFrame::SHW_gameFrame()
{
	for (short i = 0; i < (h + 2); i = i + 1)
	{
		for (short c = 0; c < ((w + 1) * 2); c = c + 1)
		{
			if ((i == 0) || (i == (h + 1)))
			{
				System::Console::SetCursorPosition(xStart + c, yStart + i);
				std::cout << char(205);
			}
			else
			{
				if ((c == 0) || (c == ((2 * w) + 1)))
				{
					System::Console::SetCursorPosition(xStart + c, yStart + i);
					std::cout << char(186);
				}
			}
		}
	}

	System::Console::SetCursorPosition(xStart, yStart); cout << char(201);
	System::Console::SetCursorPosition(xStart + ((2 * w) + 1), yStart); cout << char(187);
	System::Console::SetCursorPosition(xStart, yStart + (h + 1)); cout << char(200);
	System::Console::SetCursorPosition(xStart + ((2 * w) + 1), yStart + (h + 1)); cout << char(188);
}