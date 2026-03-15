#pragma once
#include "basicObject.h"

class SnakeHead : public basicObject
{
public:
	SnakeHead(short, short, short, char, short, short);
	~SnakeHead();
};

SnakeHead::SnakeHead(short _xPos, short _yPos, short _colorID, char _form, short _xPosLct, short _yPosLct) : basicObject(_xPos, _yPos, _colorID, _form, _xPosLct, _yPosLct) {}
SnakeHead::~SnakeHead() {}