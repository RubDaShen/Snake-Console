#pragma once
#include "basicObject.h"

class SnakeBody : public basicObject
{
public:
	SnakeBody(short, short, short, char, short, short, char);
	~SnakeBody();

	inline void SET_isVertical(bool);
	inline bool GET_isVertical();
	inline char GET_verticalSideForm();

private:
	char verticalSideForm;
	bool isVertical;
};

SnakeBody::SnakeBody(short _xPos, short _yPos, short _colorID, char _form, short _xPosLct, short _yPosLct, char _vForm) : basicObject(_xPos, _yPos, _colorID, _form, _xPosLct, _yPosLct)
{
	this->verticalSideForm = _vForm;
	this->isVertical = false;
}
SnakeBody::~SnakeBody() {}

inline void SnakeBody::SET_isVertical(bool _TorF)
{
	this->isVertical = _TorF;
}
inline bool SnakeBody::GET_isVertical()
{
	return this->isVertical;
}
inline char SnakeBody::GET_verticalSideForm()
{
	return this->verticalSideForm;
}