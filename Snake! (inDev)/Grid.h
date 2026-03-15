#pragma once
#include <conio.h>
#include <Windows.h>
#include <iostream>

class Grid
{
public:
	Grid();
	~Grid();

	inline void SET_valueID(short);
	inline short GET_valueID();

private:
	short valueID;
};

Grid::Grid()
{
	this->valueID = 0;
}
Grid::~Grid() {}

inline void Grid::SET_valueID(short _valueID)
{
	this->valueID = _valueID;
}
inline short Grid::GET_valueID()
{
	return this->valueID;
}