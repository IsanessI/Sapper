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
#include "functions.h"

#define fr first
#define sc second

using namespace std;

struct timer
{
    clock_t Begin, End, Total;
};

struct SystemValues
{
    int x_Size, y_Size, AmountOfMines, x, y, TimeBegin, TimeEnd;
    bool End_Of_Game, Skip_Cout, FirstDig;
    char symbol, difficult;
    COORD pt;
    const pair <int, int> Check[8] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    vector < vector <Cell> > Field;
    timer Time;
};

void ClearConsole();
void ChangeColor(const colors& Color);
void ChangeSizeOfWindow(const int& x_Size, const int& y_Size);
char Key(char& symbol);
char ReChange(char& symbol);

int main()
{
    SystemValues _system;

    srand(time(nullptr));

    _system.x_Size = 400;
    _system.y_Size = -100;
    ChangeSizeOfWindow(_system.x_Size, _system.y_Size);
    ChangeColor(White);


    cout << "Welcome to the Sapper.\n";

    while (true)
    {
        _system.x_Size = 400;
        _system.y_Size = -100;
        if (_system.End_Of_Game) _system.End_Of_Game = 0;
        ChangeSizeOfWindow(_system.x_Size, _system.y_Size);
        _system.FirstDig = 1;

        cout << "If you want to continue, enter 'Y'.\n"
             << "If you want to exit game, press 'ESC'.\n"
             << "For checking table of records press 'T'.\n";

        _system.symbol = Key(_system.symbol);
        if (_system.symbol == VK_ESCAPE)
            break;
        _system.symbol = ReChange(_system.symbol);
        if (_system.symbol == 'T')
        {
            cout << "Type a difficult:\nEasy - E, Normal - N, Hard - H, Custom - C\n";

            Key(_system.difficult);
            ReChange(_system.difficult);

            while (_system.difficult != 'E' && _system.difficult != 'N' && _system.difficult != 'H' && _system.difficult != 'C')
            {
                Key(_system.difficult);
                ReChange(_system.difficult);
            }

            TableOfRecords(0, 0, _system.difficult);
            continue;
        }
        if (_system.symbol == 'Y')
        {
            cout << "Enter difficult of game: \nEasy - E, Normal - N, Hard - H, Custom - C.\n";

            Key(_system.difficult);
            ReChange(_system.difficult);

            while (_system.difficult != 'E' && _system.difficult != 'N' && _system.difficult != 'H' && _system.difficult != 'C')
            {
                Key(_system.difficult);
                ReChange(_system.difficult);
            }

            switch (_system.difficult)
            {
            case 'E':

                _system.x_Size = rand() % 5 + 5;
                _system.y_Size = rand() % 5 + 5;
                _system.AmountOfMines = rand() % 6 + 6;

                break;

            case 'N':

                _system.x_Size = rand() % 3 + 10;
                _system.y_Size = rand() % 3 + 10;
                _system.AmountOfMines = rand() % 10 + rand() % 10 + 10;

                break;
            case 'H':

                _system.x_Size = rand() % 3 + 10;
                _system.y_Size = rand() % 3 + 10;
                _system.AmountOfMines = rand() % 10 + rand() % 10 + 30;
                break;

            case 'C':

                cout << "Please, type enter the dimensions of the field size NxM.\n";

                cin >> _system.y_Size >> _system.x_Size;

                while (_system.x_Size > 100 || _system.x_Size < 1 || _system.y_Size > 100 || _system.y_Size < 1)
                {
                    cout << "Incorrect value.\n";
                    cin >> _system.x_Size >> _system.y_Size;
                }

                cout << "Enter a amount of mines.\n";

                cin >> _system.AmountOfMines;

                while (_system.AmountOfMines > _system.x_Size * _system.y_Size)
                {
                    cout << "Incorrect value. Please, try again.\n";
                    cin >> _system.AmountOfMines;
                }

                break;
            }

            if (!_system.Field.empty()) _system.Field.clear();
            _system.Field.resize(_system.x_Size+2);
            for (int i = 0; i <= _system.x_Size+1; i++)
                _system.Field[i].resize(_system.y_Size+2);

            while (_system.AmountOfMines > (_system.x_Size * _system.y_Size) / 2)
            {
                cout << "Incorrect value.\n";
                cin >> _system.AmountOfMines;
            }

            cout << "Game stated in... \n";

            Sleep(1000);

            cout << 3;

            Sleep(1000);

            cout << "\n" << 2;

            Sleep(1000);

            cout << "\n" << 1;

            Sleep(1000);

            ChangeSizeOfWindow(_system.x_Size, _system.y_Size);

            HANDLE stdcon = GetStdHandle(STD_OUTPUT_HANDLE);
            CONSOLE_SCREEN_BUFFER_INFO screen;
            GetConsoleScreenBufferInfo(stdcon, &screen);

            _system.pt.X = 0;
            _system.pt.Y = 0; // текущие координаты курсора
            while (!_system.End_Of_Game)
            {
                if (!_system.Skip_Cout)
                {
                    system ("cls");
                    _system.Time.End = clock();
                    bool f1 = false;
                    for (int i = 1; i <= _system.x_Size; i++)
                    {
                        for (int j = 1; j <= _system.y_Size; j++)
                        {
                            if (!_system.Field[i][j].DigOut && !_system.Field[i][j].Mine)
                            {
                                f1 = true;
                                break;
                            }
                        }
                        if (f1) break;
                    }
                    if (!f1)
                    {
                        cout << "YOU WIN! Press any key to continue.\n";

                        _system.Time.Total = _system.Time.End - _system.Time.Begin;

                        _system.End_Of_Game = true;
                    }
                    for (int i = 1; i <= _system.x_Size; i++)
                    {
                        for (int j = 1; j <= _system.y_Size; j++)
                            COUT(_system.Field[i][j], _system.End_Of_Game);
                        cout << "\n";
                    }
                    ChangeColor(White);
                    if (!_system.End_Of_Game) cout  << "F - place flag.\nENTER - dig out.\n"
                                                        << "Free flags:" << _system.AmountOfMines;
                    else
                    {
                        _getch();
                        TableOfRecords(_system.Time.Total / CLOCKS_PER_SEC, _system.End_Of_Game, _system.difficult);
                        ClearConsole();
                        continue;
                    }
                    SetConsoleCursorPosition(stdcon, _system.pt);
                }

                _system.Skip_Cout = false;

                while (Move(_system.pt, _system.symbol, _system.x_Size, _system.y_Size))
                {
                    if (_system.symbol == 13 || _system.symbol == 'F' || _system.symbol == VK_ESCAPE)
                        break;
                }

                _system.x = _system.pt.Y + 1;
                _system.y = _system.pt.X + 1;

                if (_system.symbol == VK_ESCAPE)
                {
                    system("cls");
                    break;
                }

                if (_system.symbol == 'F')
                {

                    if (_system.Field[_system.x][_system.y].Flag)
                    {
                        _system.Field[_system.x][_system.y].Flag = 0;
                        _system.AmountOfMines++;
                        continue;
                    }
                    else
                    {
                        if (_system.Field[_system.x][_system.y].DigOut)
                        {
                            _system.Skip_Cout = 0;
                            continue;
                        }
                        if (_system.AmountOfMines > 0)
                        {
                            _system.Field[_system.x][_system.y].Flag = 1;
                            _system.AmountOfMines--;
                            continue;
                        }
                        else
                        {
                            _system.Skip_Cout = 1;
                            continue;
                        }
                    }
                    continue;
                }
                if (_system.symbol == 13)
                {
                    if (_system.FirstDig) //Generation of field
                    {
                        int AmountOfMines = _system.AmountOfMines;
                        while (true)
                        {
                            bool f = 1;
                            for (int i = 1; i <= _system.x_Size; i++)
                            {
                                for (int j = 1; j <= _system.y_Size; j++)
                                    f = Generation(_system.Field[i][j].Mine, _system.Field[i][j].ValueOfMine, _system.x_Size, _system.y_Size, _system.x, _system.y, AmountOfMines, i, j);
                                if (!f) break;
                            }
                            if (!f) break;
                        }
                        for (int i = 1; i <= _system.x_Size; i++)
                        {
                            for (int j = 1; j <= _system.y_Size; j++)
                            {
                                if (_system.Field[i][j].Mine)
                                {
                                    for (int t = 0; t < 8; t++)
                                        _system.Field[i+_system.Check[t].first][j+_system.Check[t].second].ValueOfMine++;
                                }
                            }
                        }
                        _system.Time.Begin = clock();
                        _system.FirstDig = false;
                    }
                    if (_system.Field[_system.x][_system.y].Mine && !_system.Field[_system.x][_system.y].Flag)
                    {
                        system("cls");
                        cout << "YOU LOSE!\n";
                        _system.End_Of_Game = true;

                        for (int i = 1; i <= _system.x_Size; i++)
                        {
                            for (int j = 1; j <= _system.y_Size; j++)
                                COUT(_system.Field[i][j], _system.End_Of_Game);
                            cout << "\n";
                        }

                        ChangeColor(colors::White);
                        cout << "Press any key to continue.";
                        ClearConsole();
                        continue;
                    }
                    if (_system.Field[_system.x][_system.y].Flag || _system.Field[_system.x][_system.y].DigOut)
                    {
                        _system.Skip_Cout = 1;
                        continue;
                    }
                    if (_system.Field[_system.x][_system.y].ValueOfMine == 0)
                    {
                        queue <pair <int, int> > q;
                        q.push({_system.x, _system.y});
                        _system.Field[_system.x][_system.y].DigOut = 1;
                        while (!q.empty())
                        {
                            int x1 = q.front().fr;
                            int yy1 = q.front().sc;
                            _system.Field[x1][yy1].DigOut = 1;
                            q.pop();
                            for (int i = 0; i < 8; i++)
                            {
                                int xx = _system.Check[i].fr;
                                int yy = _system.Check[i].sc;
                                if (_system.Field[x1+xx][yy1+yy].ValueOfMine >= 1 && x1 + xx > 0 && x1 + xx <= _system.x_Size && yy1 + yy > 0 && yy1 + yy <= _system.y_Size &&!_system.Field[x1+xx][yy1+yy].DigOut)
                                {
                                    _system.Field[x1+xx][yy1+yy].DigOut = 1;
                                    continue;
                                }
                                if (_system.Field[x1+xx][yy1+yy].ValueOfMine == 0 && x1 + xx > 0 && x1 + xx <= _system.x_Size && yy1 + yy > 0 && yy1 + yy <= _system.y_Size && !_system.Field[x1+xx][yy1+yy].DigOut)
                                {
                                    _system.Field[x1][yy1].DigOut = 1;
                                    q.push({x1+xx, yy1+yy});
                                    continue;
                                }
                            }
                        }
                        continue;
                    }
                    if (_system.Field[_system.x][_system.y].ValueOfMine > 0)
                    {
                        _system.Field[_system.x][_system.y].DigOut = 1;
                        continue;
                    }
                }
            }
        }
        else
        {
            system("cls");
            cout << "Unknown command! \2\n";
        }
    }
    cout << "Game created by SANESS.\nFor leaving, press any button.";

    ChangeColor(Black);

    return 0;
}
void ClearConsole()
{
    getch();
    system("cls");
}


