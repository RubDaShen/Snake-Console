#pragma once
#include "iostream"
#include "Windows.h"
#include "string"

using namespace System;

class textInScreen
{
public:
	textInScreen(std::string);
	textInScreen(void);
	~textInScreen();

	inline void doFade();
	inline void doType();

	inline void SET_thisMessage(std::string);
	inline void SET_speedFade(int);
	inline void SET_timeFade(int);

	inline int GET_timeFade();
	inline int GET_speedFade();
	
	std::string GET_thisMessage();

private:
	std::string yourMessage;
	/* / / / / / / / / / */
	bool enableInfiLoop;
	int timeFade;
	int speedFade;

	bool oneCycle;
	bool doubleCycle;

	int a, b, c;
};

textInScreen::textInScreen(std::string _theMessage)
{
	this->yourMessage = _theMessage;
	enableInfiLoop = false;
	timeFade = 100;
	speedFade = 10;

	oneCycle = true;
	doubleCycle = false;

	a = b = c = 0;
}
textInScreen::textInScreen(void)
{
	this->yourMessage = "RBN";
	enableInfiLoop = false;
	timeFade = 100;
	speedFade = 1;

	oneCycle = true;
	doubleCycle = false;

	a = b = 0;
}
textInScreen::~textInScreen()
{}

inline void textInScreen::doFade()
{
	if (oneCycle)
	{
		switch (a)
		{
		case 0:
			a = a + 1;
			Console::ForegroundColor = ConsoleColor::White;
			break;

		case 1:
			a = a + 1;
			Console::ForegroundColor = ConsoleColor::Gray;
			break;

		case 2:
			a = a + 1;
			Console::ForegroundColor = ConsoleColor::DarkGray;
			break;

		case 3:
			a = 0;
			Console::ForegroundColor = ConsoleColor::Black;
			break;
		}

		std::cout << yourMessage;
		Console::ForegroundColor = ConsoleColor::White;
	}
	else
	{
		if (doubleCycle)
		{
			switch (b)
			{
			case 0:
				b = b + 1;
				Console::ForegroundColor = ConsoleColor::White;
				break;

			case 1:
				b = b + 1;
				Console::ForegroundColor = ConsoleColor::Gray;
				break;

			case 2:
				b = b + 1;
				Console::ForegroundColor = ConsoleColor::DarkGray;
				break;

			case 3:
				b = b + 1;
				Console::ForegroundColor = ConsoleColor::Black;
				break;

			case 4:
				b = b + 1;
				Console::ForegroundColor = ConsoleColor::DarkGray;
				break;

			case 5:
				b = 0;
				Console::ForegroundColor = ConsoleColor::Gray;
				break;
			}

			std::cout << yourMessage;
			Console::ForegroundColor = ConsoleColor::White;
		}
	}
}
inline void textInScreen::doType()
{
	if (this->c < yourMessage.size())
	{
		std::cout << yourMessage.at(c);
		this->c = this->c + 1;
	}
}

inline void textInScreen::SET_thisMessage(std::string yourMessage)
{
	this->yourMessage = yourMessage;
}
inline void textInScreen::SET_timeFade(int _timeFade)
{
	this->timeFade = _timeFade;
}
inline void textInScreen::SET_speedFade(int _speedFade)
{
	this->speedFade = _speedFade;
}

inline std::string textInScreen::GET_thisMessage()
{
	return this->yourMessage;
}
inline int textInScreen::GET_timeFade()
{
	return this->timeFade;
}
inline int textInScreen::GET_speedFade()
{
	return this->speedFade;
}