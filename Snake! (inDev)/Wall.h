#pragma once
#include "basicObject.h"
#include "Grid.h"

class Wall : public basicObject
{
public:
	Wall(short, short, short, char, short, short);
	~Wall();

	inline void DRW_times_continuousObject()
	{
		Console::ForegroundColor = ConsoleColor(this->colorID);
		Console::SetCursorPosition((this->xPos * 2) + this->xPosLct, this->yPos + this->yPosLct);
		cout << this->characterForm;
		switch (this->characterForm)
		{
			case char(200) : case char(201) : case char(202) : case char(203) : case char(205) : case char(206) :
				cout << char(205);
				break;
		}
	}
	inline void DRW_alignBoxes(Grid***);
};

Wall::Wall(short _xPos, short _yPos, short _colorID, char _form, short _xPosLct, short _yPosLct) : basicObject(_xPos, _yPos, _colorID, _form, _xPosLct, _yPosLct) {}
Wall::~Wall() {}

inline void Wall::DRW_alignBoxes(Grid*** theGrid)
{
	// theGrid[this->xPos][this->yPos]->GET_valueID() instead of 3 so this will be general.

	if ((theGrid[this->yPos][this->xPos]->GET_valueID() == theGrid[this->yPos][this->xPos - 1]->GET_valueID()) &&
		(theGrid[this->yPos][this->xPos]->GET_valueID() == theGrid[this->yPos][this->xPos + 1]->GET_valueID()) &&
		(theGrid[this->yPos][this->xPos]->GET_valueID() == theGrid[this->yPos - 1][this->xPos]->GET_valueID()) &&
		(theGrid[this->yPos][this->xPos]->GET_valueID() == theGrid[this->yPos + 1][this->xPos]->GET_valueID()))
	{
		this->characterForm = 206;
	}
	else
	{
		if ((theGrid[this->yPos][this->xPos]->GET_valueID() == theGrid[this->yPos - 1][this->xPos]->GET_valueID()) &&
			(theGrid[this->yPos][this->xPos]->GET_valueID() == theGrid[this->yPos + 1][this->xPos]->GET_valueID()) &&
			(theGrid[this->yPos][this->xPos]->GET_valueID() == theGrid[this->yPos][this->xPos - 1]->GET_valueID()))
		{
			this->characterForm = 185;
		}
		else
		{
			if ((theGrid[this->yPos][this->xPos]->GET_valueID() == theGrid[this->yPos + 1][this->xPos]->GET_valueID()) &&
				(theGrid[this->yPos][this->xPos]->GET_valueID() == theGrid[this->yPos][this->xPos + 1]->GET_valueID()) &&
				(theGrid[this->yPos][this->xPos]->GET_valueID() == theGrid[this->yPos][this->xPos - 1]->GET_valueID()))
			{
				this->characterForm = 203;
			}
			else
			{
				if ((theGrid[this->yPos][this->xPos]->GET_valueID() == theGrid[this->yPos - 1][this->xPos]->GET_valueID()) &&
					(theGrid[this->yPos][this->xPos]->GET_valueID() == theGrid[this->yPos + 1][this->xPos]->GET_valueID()) &&
					(theGrid[this->yPos][this->xPos]->GET_valueID() == theGrid[this->yPos][this->xPos + 1]->GET_valueID()))
				{
					this->characterForm = 204;
				}
				else
				{
					if ((theGrid[this->yPos][this->xPos]->GET_valueID() == theGrid[this->yPos - 1][this->xPos]->GET_valueID()) &&
						(theGrid[this->yPos][this->xPos]->GET_valueID() == theGrid[this->yPos + 1][this->xPos]->GET_valueID()) &&
						(theGrid[this->yPos][this->xPos]->GET_valueID() == theGrid[this->yPos][this->xPos + 1]->GET_valueID()))
					{
						this->characterForm = 202;
					}
					else
					{
						if ((theGrid[this->yPos][this->xPos]->GET_valueID() == theGrid[this->yPos - 1][this->xPos]->GET_valueID()) &&
							(theGrid[this->yPos][this->xPos]->GET_valueID() == theGrid[this->yPos][this->xPos - 1]->GET_valueID()))
						{
							this->characterForm = 188;
						}
						else
						{
							if ((theGrid[this->yPos][this->xPos]->GET_valueID() == theGrid[this->yPos + 1][this->xPos]->GET_valueID()) &&
								(theGrid[this->yPos][this->xPos]->GET_valueID() == theGrid[this->yPos][this->xPos - 1]->GET_valueID()))
							{
								this->characterForm = 187;
							}
							else
							{
								if ((theGrid[this->yPos][this->xPos]->GET_valueID() == theGrid[this->yPos + 1][this->xPos]->GET_valueID()) &&
									(theGrid[this->yPos][this->xPos]->GET_valueID() == theGrid[this->yPos][this->xPos + 1]->GET_valueID()))
								{
									this->characterForm = 201;
								}
								else
								{
									if ((theGrid[this->yPos][this->xPos]->GET_valueID() == theGrid[this->yPos - 1][this->xPos]->GET_valueID()) &&
										(theGrid[this->yPos][this->xPos]->GET_valueID() == theGrid[this->yPos][this->xPos + 1]->GET_valueID()))
									{
										this->characterForm = 200;
									}
									else
									{
										if ((theGrid[this->yPos - 1][this->xPos]->GET_valueID() == theGrid[this->yPos][this->xPos]->GET_valueID()) || (theGrid[this->yPos + 1][this->xPos]->GET_valueID() == theGrid[this->yPos][this->xPos]->GET_valueID()))
										{
											this->characterForm = 186;
										}
										else
										{
											if ((theGrid[this->yPos][this->xPos - 1]->GET_valueID() == theGrid[this->yPos][this->xPos]->GET_valueID()) || (theGrid[this->yPos][this->xPos + 1]->GET_valueID() == theGrid[this->yPos][this->xPos]->GET_valueID()))
											{
												this->characterForm = 205;
											}
											else
											{
												this->characterForm = 177; // eNull
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	DRW_times_continuousObject();
}