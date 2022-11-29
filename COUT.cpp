#include <iostream>
#include "functions.h"

using namespace std;

void ChangeColor(const colors& Color);
int COUT(Cell cell, bool& End_Of_Game)
{
    if (End_Of_Game)
    {
        if (cell.Mine)
        {
            ChangeColor(DarkRed);
            cout << '*';
            return 0;
        }
        if (cell.Flag)
        {
            ChangeColor(DarkMagenta);
            cout << "\2";;
            return 0;
        }
    }
    switch(cell.ValueOfMine)
    {
    case 0:
        if (cell.DigOut)
        {
            ChangeColor(Gray);
            cout << 0;
            break;
        }
    case 1:
        if (cell.DigOut)
        {
            ChangeColor(Blue);
            cout << 1;
            break;
        }
    case 2:
        if (cell.DigOut)
        {
            ChangeColor(Green);
            cout << 2;
            break;
        }
    case 3:
        if (cell.DigOut)
        {
            ChangeColor(Red);
            cout << 3;
            break;
        }
    case 4:
        if (cell.DigOut)
        {
            ChangeColor(Magenta);
            cout << 4;
            break;
        }
    case 5:
        if (cell.DigOut)
        {
            ChangeColor(Yellow);
            cout << 5;
            break;
        }
    case 6:
        if (cell.DigOut)
        {
            ChangeColor(DarkMagenta);
            cout << 6;
            break;
        }
    case 7:
        if (cell.DigOut)
        {
            ChangeColor(DarkYellow);
            cout << 7;
            break;
        }
    case 8:
        if (cell.DigOut)
        {
            ChangeColor(DarkGreen);
            cout << 8;
            break;
        }
    default:
        if (cell.Flag)
        {
            ChangeColor(Cyan);
            cout << 'F';
            break;
        }
        ChangeColor(White);
        cout << '#';
        break;
    }
    return 0;
}
void ChangeColor(const colors& Color)
{
    HANDLE stdcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(stdcon, Color);
}
