/*
	using dev::listingEnum
	def{varType = list} for valueID:
		dev-----0x0		void
		dev-----0x1		player:
			drv --> 0x11	playerBody
		dev-----0x2		food:
			drv	--> 0x21	cherry
		dev-----0x3		block:
			drv --> 0x21	wall
*/
#include "SnakePlayer.h"
#include "pch.h"
#include "Game.h"
#include <vector>

#define theHEIGHT              45
#define theWIDTH               150

int amountSleep = 90; // 32.5: 20, 65, 150. 

void main()
{
	SetConsoleTitleA("Snake! - Also try Tetris!");
	Console::SetWindowSize(theWIDTH, theHEIGHT);
	unsigned short W = Console::WindowWidth;
	unsigned short H = Console::WindowHeight;
	Console::CursorVisible = false;
	
	/* - D E F I N I T I O N S - */
	
	// Not so difficult!
	unsigned short xPos_frameGen, yPos_frameGen;                      xPos_frameGen = 15, yPos_frameGen = 18;
	unsigned short W_grid, H_grid;                                        W_grid = 30; H_grid = 20;
	unsigned short h_letterGrid, w_letterGrid;                            h_letterGrid = 6, w_letterGrid = 33;
	unsigned short colorID_straightLines;                                colorID_straightLines = 8;
	unsigned short h_letterGrid_box1, w_letterGrid_box1;                h_letterGrid_box1 = 10; w_letterGrid_box1 = (xPos_frameGen + W_grid);
	unsigned short h_letterGrid_box2, w_letterGrid_box2;                h_letterGrid_box2 = 34; w_letterGrid_box2 = (xPos_frameGen + W_grid);
	unsigned short h_letterGrid_box3, w_letterGrid_box3;                h_letterGrid_box3 = 45; w_letterGrid_box3 = ((150 - 2) / 2) - w_letterGrid_box1;

	int timeSpeedInClock;                                                  timeSpeedInClock = 20;
	int gameTick;                                                           gameTick = 0;
	int delayFunction_logo;                                                delayFunction_logo = 2;
	int delayFunction_straightLine;                                        delayFunction_straightLine = 1;
	int delayFunction_middleText;                                          delayFunction_middleText = 4;
	int yPos_controlText, yPos_controlText_Stats;                        yPos_controlText = 2; yPos_controlText_Stats = 15;
	int auxLoop_zero;                                                     auxLoop_zero = 0;
	int auxLoop_one;                                                      auxLoop_one = 0;
	int auxLoop_two;                                                       auxLoop_two = 0;
	int auxLoop_three;                                                    auxLoop_three = 0;
	int auxLoop_four;                                                     auxLoop_four = 0;
	int auxLoop_five;                                                      auxLoop_five = 0;
	int auxLoop_six;                                                       auxLoop_six = 0;
	int auxLoop_seven;                                                    auxLoop_seven = 0;

	bool textIsOver;                                                       textIsOver = false;
	// Kinda green!
	vector<SnakePlayer*> letterSnake;
	vector<SnakePlayer*> straigthLineSnake;
	vector<textInScreen*> theTextsInScreen;

	titleStart* theTitle;                                                    theTitle = new titleStart(xPos_frameGen + W_grid - 3, yPos_frameGen + ((H_grid - 1) / 2));
	Grid*** letterGrid;
	Grid*** lineGrid_box1;
	Grid*** lineGrid_box2;
	Grid*** lineGrid_box3;

	// Main(s) definitions as well!
	Game* theGame = new Game(theHEIGHT, theWIDTH, W_grid, H_grid, 8, 8, amountSleep, xPos_frameGen, yPos_frameGen, xPos_frameGen - 1, yPos_frameGen - 1);

	/* - E N D - */



	/* - D E F I N I T I O N S    F O R    V E C T O R S    &    P O I N T E R S ! - */
	
	// Texts in screen
	theTextsInScreen.push_back(new textInScreen("[  W  ]  -  Press to Up"));
	theTextsInScreen.push_back(new textInScreen("[  A  ]  -  Press to Left"));
	theTextsInScreen.push_back(new textInScreen("[  S  ]  -  Press to Down"));
	theTextsInScreen.push_back(new textInScreen("[  D  ]  -  Press to Right"));
	theTextsInScreen.push_back(new textInScreen("  C O N T R O L S  "));
	theTextsInScreen.push_back(new textInScreen("  Y O U R     S T A T S  "));
	theTextsInScreen.push_back(new textInScreen("Score: 0"));
	theTextsInScreen.push_back(new textInScreen("Combo: x0"));

	// letterGrid is for the SNAKE logo.
	letterGrid = new Grid * *[h_letterGrid];
	for (unsigned short i = 0; i < h_letterGrid; i = i + 1)
	{
		letterGrid[i] = new Grid * [w_letterGrid];
		for (unsigned short c = 0; c < w_letterGrid; c = c + 1)
		{
			letterGrid[i][c] = new Grid();
		}
	}
	// lineGrid is for all straigth lines!
	lineGrid_box1 = new Grid * *[h_letterGrid_box1];
	for (unsigned short i = 0; i < h_letterGrid_box1; i = i + 1) // theHEIGHT
	{
		lineGrid_box1[i] = new Grid * [w_letterGrid_box1];
		for (unsigned short c = 0; c < w_letterGrid_box1; c = c + 1) // 1
		{
			lineGrid_box1[i][c] = new Grid();
		}
	}
	lineGrid_box2 = new Grid * *[h_letterGrid_box2];
	for (unsigned short i = 0; i < h_letterGrid_box2; i = i + 1) // theHEIGHT
	{
		lineGrid_box2[i] = new Grid * [w_letterGrid_box2];
		for (unsigned short c = 0; c < w_letterGrid_box2; c = c + 1) // 1
		{
			lineGrid_box2[i][c] = new Grid();
		}
	}
	lineGrid_box3 = new Grid * *[h_letterGrid_box3];
	for (unsigned short i = 0; i < h_letterGrid_box3; i = i + 1) // theHEIGHT
	{
		lineGrid_box3[i] = new Grid * [w_letterGrid_box3];
		for (unsigned short c = 0; c < w_letterGrid_box3; c = c + 1) // 1
		{
			lineGrid_box3[i][c] = new Grid();
		}
	}

	// This pack is for letters S N A K E and L I N E S.
	letterSnake.push_back(new SnakePlayer(2, 5, 12, 12, 'o', 219, h_letterGrid, w_letterGrid, xPos_frameGen - 3, 2, "S", 1));
	letterSnake.push_back(new SnakePlayer(8, 5, 14, 14, 'o', 219, h_letterGrid, w_letterGrid, xPos_frameGen - 3, 2, "N", 1));
	letterSnake.push_back(new SnakePlayer(14, 5, 10, 10, 'o', 219, h_letterGrid, w_letterGrid, xPos_frameGen - 3, 2, "A", 1));
	letterSnake.push_back(new SnakePlayer(20, 0, 3, 3, 'o', 219, h_letterGrid, w_letterGrid, xPos_frameGen - 3, 2, "K", 1));
	letterSnake.push_back(new SnakePlayer(31, 0, 13, 13, 'o', 219, h_letterGrid, w_letterGrid, xPos_frameGen - 3, 2, "E", 1));

	straigthLineSnake.push_back(new SnakePlayer(0, 0, 15, colorID_straightLines, 'o', 219, h_letterGrid_box1, w_letterGrid_box1, 0, 0, "StraightLine", 1));
	straigthLineSnake.push_back(new SnakePlayer(0, 0, 15, colorID_straightLines, 'o', 219, h_letterGrid_box1, w_letterGrid_box1, 0, 0, "DownLine", 1));
	straigthLineSnake.push_back(new SnakePlayer(0, h_letterGrid_box1 - 1, 15, colorID_straightLines, 'o', 219, h_letterGrid_box1, w_letterGrid_box1, 0, 0, "StraightLine_down", 1));
	straigthLineSnake.push_back(new SnakePlayer(w_letterGrid_box1 - 1, 0, 15, colorID_straightLines, 'o', 219, h_letterGrid_box1, w_letterGrid_box1, 0, 0, "DownLine_right", 1));

	straigthLineSnake.push_back(new SnakePlayer(0, 0, 15, colorID_straightLines, 'o', 219, h_letterGrid_box2, w_letterGrid_box2, 0, h_letterGrid_box1 + 1, "StraightLine_gameBox", 1));
	straigthLineSnake.push_back(new SnakePlayer(w_letterGrid_box2 - 1, 0, 15, colorID_straightLines, 'o', 219, h_letterGrid_box2, w_letterGrid_box2, 0, h_letterGrid_box1 + 1, "StraightLine_gameBox", 1));
	straigthLineSnake.push_back(new SnakePlayer(0, 0, 15, colorID_straightLines, 'o', 219, h_letterGrid_box2, w_letterGrid_box2, 0, h_letterGrid_box1 + 1, "StraightLine_gameBox", 1));
	straigthLineSnake.push_back(new SnakePlayer(0, h_letterGrid_box2 - 1, 15, colorID_straightLines, 'o', 219, h_letterGrid_box2, w_letterGrid_box2, 0, h_letterGrid_box1 + 1, "StraightLine_gameBox", 1));

	straigthLineSnake.push_back(new SnakePlayer(0, 0, 15, colorID_straightLines, 'o', 219, h_letterGrid_box3, w_letterGrid_box3, (w_letterGrid_box2 + 1) * 2, 0, "StraightLine_gameBox", 1));
	straigthLineSnake.push_back(new SnakePlayer(0, 0, 15, colorID_straightLines, 'o', 219, h_letterGrid_box3, w_letterGrid_box3, (w_letterGrid_box2 + 1) * 2, 0, "StraightLine_gameBox", 1));
	straigthLineSnake.push_back(new SnakePlayer(w_letterGrid_box3 - 1, 0, 15, colorID_straightLines, 'o', 219, h_letterGrid_box3, w_letterGrid_box3, (w_letterGrid_box2 + 1) * 2, 0, "StraightLine_gameBox", 1));
	straigthLineSnake.push_back(new SnakePlayer(0, h_letterGrid_box3 - 1, 15, colorID_straightLines, 'o', 219, h_letterGrid_box3, w_letterGrid_box3, (w_letterGrid_box2 + 1) * 2, 0, "StraightLine_gameBox", 1));

	straigthLineSnake.at(0)->changeDir('D'); straigthLineSnake.at(1)->changeDir('S'); straigthLineSnake.at(2)->changeDir('D'); straigthLineSnake.at(3)->changeDir('S');
	straigthLineSnake.at(4)->changeDir('D'); straigthLineSnake.at(5)->changeDir('S'); straigthLineSnake.at(6)->changeDir('S'); straigthLineSnake.at(7)->changeDir('D'); 
	straigthLineSnake.at(8)->changeDir('D'); straigthLineSnake.at(9)->changeDir('S'); straigthLineSnake.at(10)->changeDir('S'); straigthLineSnake.at(11)->changeDir('D');

	/* - E N D - */

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //
	// Before starting the game, I'm setting some variables and functions...
	theTitle->SET_timeSleepText_ALL(timeSpeedInClock * delayFunction_middleText);

	/* Here we start with while loops! */
	theGame->PreRenderGame();
	while (textIsOver == false)
	{
		/* You can use GET_xPos/yPos, but I see this a easier way (and understandable xd).
		   Also, I tried using switc, but it got a little bit of a problem. Of course, I'm on my way to improve this...
		*/
		// Letter 'S' 
		if (gameTick == (4 * delayFunction_logo))
		{
			letterSnake.at(0)->changeDir('W');
		}
		else
		{
			if (gameTick == (6 * delayFunction_logo))
			{
				letterSnake.at(0)->changeDir('A');
			}
			else
			{
				if (gameTick == (9 * delayFunction_logo))
				{
					letterSnake.at(0)->changeDir('W');
				}
				else
				{
					if (gameTick == (12 * delayFunction_logo))
					{
						letterSnake.at(0)->changeDir('D');
					}
					else
					{
						if (gameTick == (15 * delayFunction_logo))
						{
							letterSnake.at(0)->FreezeSnake(false);
						}
					}
				}
			}
		}
		// Letter 'N'
		if (gameTick == (1 * delayFunction_logo))
		{
			letterSnake.at(1)->changeDir('W');
		}
		else
		{
			if (gameTick == (7 * delayFunction_logo))
			{
				letterSnake.at(1)->changeDir('S');
			}
			else
			{
				if (gameTick == (9 * delayFunction_logo))
				{
					letterSnake.at(1)->changeDir('D');
				}
				else
				{
					if (gameTick == (10 * delayFunction_logo))
					{
						letterSnake.at(1)->changeDir('S');
					}
					else
					{
						if (gameTick == (12 * delayFunction_logo))
						{
							letterSnake.at(1)->changeDir('D');
						}
						else
						{
							if (gameTick == (13 * delayFunction_logo))
							{
								letterSnake.at(1)->changeDir('S');
							}
							else
							{
								if (gameTick == (15 * delayFunction_logo))
								{
									letterSnake.at(1)->changeDir('D');
								}
								else
								{
									if (gameTick == (16 * delayFunction_logo))
									{
										letterSnake.at(1)->changeDir('S');
									}
									else
									{
										if (gameTick == (17 * delayFunction_logo))
										{
											letterSnake.at(1)->SET_xPos_main(12); letterSnake.at(1)->SET_yPos_main(4);
											letterSnake.at(1)->changeDir('A');
											letterSnake.at(1)->changeDir('W');
										}
										else
										{
											if (gameTick == (21 * delayFunction_logo))
											{
												letterSnake.at(1)->FreezeSnake(false);
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
		// Letter 'A'
		if (gameTick == (1 * delayFunction_logo))
		{
			letterSnake.at(2)->changeDir('W');
		}
		else
		{
			if (gameTick == (7 * delayFunction_logo))
			{
				letterSnake.at(2)->changeDir('S');
			}
			else
			{
				if (gameTick == (9 * delayFunction_logo))
				{
					letterSnake.at(2)->changeDir('D');
				}
				else
				{
					if (gameTick == (12 * delayFunction_logo))
					{
						letterSnake.at(2)->changeDir('S');
					}
					else
					{
						if (gameTick == (17 * delayFunction_logo))
						{
							letterSnake.at(2)->SET_xPos_main(15); letterSnake.at(2)->SET_yPos_main(1);
							letterSnake.at(2)->changeDir('D');
						}
						else
						{
							if (gameTick == (19 * delayFunction_logo))
							{
								letterSnake.at(2)->SET_xPos_main(15); letterSnake.at(2)->SET_yPos_main(3);
							}
							else
							{
								if (gameTick == (21 * delayFunction_logo))
								{
									letterSnake.at(2)->FreezeSnake(false);
								}
							}
						}
					}
				}
			}
		}
		// Letter 'K'
		if (gameTick == (1 * delayFunction_logo))
		{
			letterSnake.at(3)->changeDir('S');
		}
		else
		{
			if (gameTick == (6 * delayFunction_logo))
			{
				letterSnake.at(3)->SET_xPos_main(21); letterSnake.at(3)->SET_yPos_main(2);
				letterSnake.at(3)->changeDir('D');
			}
			else
			{
				if (gameTick == (8 * delayFunction_logo))
				{
					letterSnake.at(3)->SET_xPos_main(24); letterSnake.at(3)->SET_yPos_main(2);
					letterSnake.at(3)->changeDir('W');
				}
				else
				{
					if (gameTick == (10 * delayFunction_logo))
					{
						letterSnake.at(3)->SET_xPos_main(22); letterSnake.at(3)->SET_yPos_main(2);
						letterSnake.at(3)->changeDir('A');
						letterSnake.at(3)->changeDir('S');
					}
					else
					{
						if (gameTick == (11 * delayFunction_logo))
						{
							letterSnake.at(3)->SET_xPos_main(23); letterSnake.at(3)->SET_yPos_main(3);
						}
						else
						{
							if (gameTick == (12 * delayFunction_logo))
							{
								letterSnake.at(3)->SET_xPos_main(24); letterSnake.at(3)->SET_yPos_main(4);
							}
							else
							{
								if (gameTick == (13 * delayFunction_logo))
								{
									letterSnake.at(3)->FreezeSnake(false);
								}
							}
						}
					}
				}
			}
		}
		// Letter 'E'
		if (gameTick == (0 * delayFunction_logo))
		{
			letterSnake.at(4)->changeDir('S');
			letterSnake.at(4)->changeDir('A');
		}
		else
		{
			if (gameTick == (4 * delayFunction_logo))
			{
				letterSnake.at(4)->changeDir('S');
			}
			else
			{
				if (gameTick == (9 * delayFunction_logo))
				{
					letterSnake.at(4)->changeDir('D');
				}
				else
				{
					if (gameTick == (12 * delayFunction_logo))
					{
						letterSnake.at(4)->SET_xPos_main(28); letterSnake.at(4)->SET_yPos_main(0);
						letterSnake.at(4)->changeDir('S');
					}
					else
					{
						if (gameTick == (18 * delayFunction_logo))
						{
							letterSnake.at(4)->SET_xPos_main(28); letterSnake.at(4)->SET_yPos_main(2);
							letterSnake.at(4)->changeDir('D');
						}
						else
						{
							if (gameTick == (20 * delayFunction_logo))
							{
								letterSnake.at(4)->FreezeSnake(false);
							}
						}
					}
				}
			}
		}

		Console::BackgroundColor = ConsoleColor::DarkYellow;
		Console::ForegroundColor = ConsoleColor::Black;
		if ((auxLoop_four < theTextsInScreen.at(4)->GET_thisMessage().size()) && ((gameTick % 2) == 0))
		{
			Console::SetCursorPosition(((w_letterGrid_box2 + 1) * 2) + w_letterGrid_box3 + auxLoop_three - (theTextsInScreen.at(4)->GET_thisMessage().size() / 2) - 1, 1 + yPos_controlText);
			theTextsInScreen.at(4)->doType();

			auxLoop_four = auxLoop_four + 1;
		}
		Console::BackgroundColor = ConsoleColor::Black;
		Console::ForegroundColor = ConsoleColor::White;
		if ((auxLoop_zero < theTextsInScreen.at(0)->GET_thisMessage().size()) && ((gameTick % 2) == 0))
		{
			Console::SetCursorPosition(((w_letterGrid_box2 + 1) * 2) + w_letterGrid_box3 + auxLoop_zero - (theTextsInScreen.at(3)->GET_thisMessage().size() / 2), 3 + yPos_controlText);
			theTextsInScreen.at(0)->doType();

			auxLoop_zero = auxLoop_zero + 1;
		}
		if ((auxLoop_one < theTextsInScreen.at(1)->GET_thisMessage().size()) && ((gameTick % 2) == 0))
		{
			Console::SetCursorPosition(((w_letterGrid_box2 + 1) * 2) + w_letterGrid_box3 + auxLoop_one - (theTextsInScreen.at(3)->GET_thisMessage().size() / 2), 5 + yPos_controlText);
			theTextsInScreen.at(1)->doType();

			auxLoop_one = auxLoop_one + 1;
		}
		if ((auxLoop_two < theTextsInScreen.at(2)->GET_thisMessage().size()) && ((gameTick % 2) == 0))
		{
			Console::SetCursorPosition(((w_letterGrid_box2 + 1) * 2) + w_letterGrid_box3 + auxLoop_two - (theTextsInScreen.at(3)->GET_thisMessage().size() / 2), 7 + yPos_controlText);
			theTextsInScreen.at(2)->doType();

			auxLoop_two = auxLoop_two + 1;
		}
		if ((auxLoop_three < theTextsInScreen.at(3)->GET_thisMessage().size()) && ((gameTick % 2) == 0))
		{
			Console::SetCursorPosition(((w_letterGrid_box2 + 1) * 2) + w_letterGrid_box3 + auxLoop_three - (theTextsInScreen.at(3)->GET_thisMessage().size() / 2), 9 + yPos_controlText);
			theTextsInScreen.at(3)->doType();

			auxLoop_three = auxLoop_three + 1;
		}

		Console::BackgroundColor = ConsoleColor::DarkCyan;
		Console::ForegroundColor = ConsoleColor::Black;
		if ((auxLoop_five < theTextsInScreen.at(5)->GET_thisMessage().size()) && ((gameTick % 2) == 0))
		{
			Console::SetCursorPosition(((w_letterGrid_box2 + 1) * 2) + w_letterGrid_box3 + auxLoop_three - (theTextsInScreen.at(3)->GET_thisMessage().size() / 2) - 1, yPos_controlText_Stats);
			theTextsInScreen.at(5)->doType();

			auxLoop_five = auxLoop_five + 1;
		}
		Console::BackgroundColor = ConsoleColor::Black;
		Console::ForegroundColor = ConsoleColor::White;
		if ((auxLoop_six < theTextsInScreen.at(6)->GET_thisMessage().size()) && ((gameTick % 2) == 0))
		{
			Console::SetCursorPosition(((w_letterGrid_box2 + 1) * 2) + w_letterGrid_box3 + auxLoop_zero - (theTextsInScreen.at(3)->GET_thisMessage().size() / 2), 2 + yPos_controlText_Stats);
			theTextsInScreen.at(6)->doType();

			auxLoop_six = auxLoop_six + 1;
		}
		if ((auxLoop_seven < theTextsInScreen.at(7)->GET_thisMessage().size()) && ((gameTick % 2) == 0))
		{
			Console::SetCursorPosition(((w_letterGrid_box2 + 1) * 2) + w_letterGrid_box3 + auxLoop_zero - (theTextsInScreen.at(3)->GET_thisMessage().size() / 2), 4 + yPos_controlText_Stats);
			theTextsInScreen.at(7)->doType();

			auxLoop_seven = auxLoop_seven + 1;
		}

		// Letter of S N A K E !      &      Straight Lines - - - 
		if ((gameTick % delayFunction_logo) == 0)
		{
			for (unsigned short i = 0; i < letterSnake.size(); i = i + 1)
			{
				letterSnake.at(i)->MOV_snake(letterGrid);
				letterSnake.at(i)->SHW_snake(letterGrid);
			}
		}
		
		if (straigthLineSnake.at(0)->GET_xPos_main() < (w_letterGrid_box1 - 1))
		{
			straigthLineSnake.at(0)->SHW_snake(lineGrid_box1);
			straigthLineSnake.at(0)->MOV_snake(lineGrid_box1);
		}
		else
		{
			straigthLineSnake.at(3)->SHW_snake(lineGrid_box1);
			straigthLineSnake.at(3)->MOV_snake(lineGrid_box1);
		}
		if (straigthLineSnake.at(1)->GET_yPos_main() < (h_letterGrid_box1 - 1))
		{
			straigthLineSnake.at(1)->SHW_snake(lineGrid_box1);
			straigthLineSnake.at(1)->MOV_snake(lineGrid_box1);
		}
		else
		{
			straigthLineSnake.at(2)->SHW_snake(lineGrid_box1);
			straigthLineSnake.at(2)->MOV_snake(lineGrid_box1);
		}

		if (straigthLineSnake.at(4)->GET_xPos_main() < (w_letterGrid_box2 - 1))
		{
			straigthLineSnake.at(4)->SHW_snake(lineGrid_box2);
			straigthLineSnake.at(4)->MOV_snake(lineGrid_box2);
		}
		else
		{
			straigthLineSnake.at(5)->SHW_snake(lineGrid_box2);
			straigthLineSnake.at(5)->MOV_snake(lineGrid_box2);
		}
		if (straigthLineSnake.at(6)->GET_yPos_main() < (h_letterGrid_box2 - 1))
		{
			straigthLineSnake.at(6)->SHW_snake(lineGrid_box2);
			straigthLineSnake.at(6)->MOV_snake(lineGrid_box2);
		}
		else
		{
			straigthLineSnake.at(7)->SHW_snake(lineGrid_box2);
			straigthLineSnake.at(7)->MOV_snake(lineGrid_box2);
		}

		if (straigthLineSnake.at(8)->GET_xPos_main() < (w_letterGrid_box3 - 1))
		{
			straigthLineSnake.at(8)->SHW_snake(lineGrid_box3);
			straigthLineSnake.at(8)->MOV_snake(lineGrid_box3);
		}
		else
		{
			straigthLineSnake.at(10)->SHW_snake(lineGrid_box3);
			straigthLineSnake.at(10)->MOV_snake(lineGrid_box3);
		}
		if (straigthLineSnake.at(9)->GET_yPos_main() < (h_letterGrid_box3 - 1))
		{
			straigthLineSnake.at(9)->SHW_snake(lineGrid_box3);
			straigthLineSnake.at(9)->MOV_snake(lineGrid_box3);
		}
		else
		{
			straigthLineSnake.at(11)->SHW_snake(lineGrid_box3);
			straigthLineSnake.at(11)->MOV_snake(lineGrid_box3);
		}

		// MiddleTitle screen...
		if ((gameTick % delayFunction_middleText) == 0)
		{
			theTitle->doShow(textIsOver);
		}

		gameTick = gameTick + 1;
		Sleep(timeSpeedInClock); // Still finding the perfect TPS (Ticks Per Second). I was thinking from 20 to 40 or even more.
	}
	theGame->startGame();
}