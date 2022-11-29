#pragma once
#include <iostream>
#include <conio.h>
#include <ctime>
#include <windows.h>
#include <queue>
#include <vector>
#include <stdio.h>
#include <math.h>
#include <fstream>
#include <cstring>
#include <set>

using namespace std;

struct Cell
{
    int ValueOfMine;
    bool Mine, Flag, DigOut;
};

enum colors
{
    Red =           FOREGROUND_INTENSITY | FOREGROUND_RED,
    Blue =          FOREGROUND_INTENSITY | FOREGROUND_BLUE,
    Green =         FOREGROUND_INTENSITY | FOREGROUND_GREEN,
    White =         FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
    Gray =          FOREGROUND_INTENSITY,
    Yellow =        FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
    Magenta =       FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
    Cyan =          FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
    DarkRed =       FOREGROUND_RED,
    DarkBlue =      FOREGROUND_BLUE,
    DarkMagenta =   FOREGROUND_RED | FOREGROUND_BLUE,
    DarkYellow =    FOREGROUND_RED | FOREGROUND_GREEN,
    DarkGreen =     FOREGROUND_GREEN,
    Black =         0
};
bool Move(COORD& pt, char& symbol, const int& x_Size, const int& y_Size);
int TableOfRecords(const int& Time,const bool& End_Of_Game, char& difficult);
int COUT(Cell cell, bool& End_Of_Game);
int Generation(bool& Mine, int& ValueOfMine, const int& x_Size, const int& y_Size, const int& x, const int& y, int& AmountOfMines, int& i, int& j);
