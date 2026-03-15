#pragma once
#include <Windows.h>
#include <iostream>

using namespace std;
using namespace System;

class basicObject
{
public:
	basicObject(short, short, short, char, short, short);
	~basicObject();

	inline void SET_xPos(short);
	inline void SET_yPos(short);
	inline void SET_colorID(short);
	inline void SET_characterForm(char);

	inline short GET_xPos();
	inline short GET_yPos();
	inline short GET_colorID();
	inline char GET_characterForm();

	inline void DRW_object();
	inline void CLR_object();
	inline void useColor();

	inline virtual void DRW_times_continuousObject() {}
	inline void drawComplexBox(Grid***);

protected:
	short xPos, yPos;
	short colorID;
	char characterForm;
	short xPosLct, yPosLct;
};

basicObject::basicObject(short _xPos, short _yPos, short _colorID, char _form, short _xPosLct, short _yPosLct)
{
	this->xPos = _xPos;
	this->yPos = _yPos;
	this->colorID = _colorID;
	this->characterForm = _form;
	this->xPosLct = _xPosLct;
	this->yPosLct = _yPosLct;
}
basicObject::~basicObject() {}

inline void basicObject::SET_xPos(short _xPos)
{
	this->xPos = _xPos;
}
inline void basicObject::SET_yPos(short _yPos)
{
	this->yPos = _yPos;
}
inline void basicObject::SET_colorID(short _colorID)
{
	this->colorID = _colorID;
}
inline void basicObject::SET_characterForm(char _newForm)
{
	this->characterForm = _newForm;
}

inline short basicObject::GET_xPos()
{
	return this->xPos;
}
inline short basicObject::GET_yPos()
{
	return this->yPos;
}
inline short basicObject::GET_colorID()
{
	return this->colorID;
}
inline char basicObject::GET_characterForm()
{
	return this->characterForm;
}

inline void basicObject::DRW_object()
{
	Console::ForegroundColor = ConsoleColor(colorID);
	Console::SetCursorPosition((xPos * 2) + xPosLct, yPos + yPosLct);
	cout << characterForm;
}
inline void basicObject::CLR_object()
{
	Console::SetCursorPosition((xPos * 2) + xPosLct, yPos + yPosLct);
	cout << " ";
}
inline void basicObject::useColor()
{
	Console::ForegroundColor = ConsoleColor(colorID);
}