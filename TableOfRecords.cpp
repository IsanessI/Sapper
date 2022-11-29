#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <fstream>
#include <cstring>
#include <set>

using namespace std;

void ChangeSizeOfWindow(const int& x_Size, const int& y_Size);
int AnalyseOfInfo(char *info, const bool& End_Of_Game, const int& Time);

int TableOfRecords(const int& Time,const bool& End_Of_Game, char& difficult)
{
    system("cls");
    ChangeSizeOfWindow(400, -100);

    ifstream savein("save.txt");
    ofstream saveout;
    char infoE[1000], infoN[1000], infoH[1000], infoC[1000];

    if (!savein.is_open())
    {
        cout << "Can't find save file. Creating new.\n";
        Sleep(1000);

        saveout.open("save.txt");
        saveout << '\n' << '\n' << '\n';
        saveout.close();
        savein.open("save.txt");
    }

    savein.getline(infoE, 1000);
    savein.getline(infoN, 1000);
    savein.getline(infoH, 1000);
    savein.getline(infoC, 1000);

    savein.close();

    switch (difficult)
    {
    case 'E':
        AnalyseOfInfo(infoE, End_Of_Game, Time);
        saveout << '\n' << infoN << '\n' << infoH << '\n' << infoC;
        break;
    case 'N':
        saveout << infoE << '\n';
        AnalyseOfInfo(infoN, End_Of_Game, Time);
        saveout << '\n' << infoH << '\n' << infoC;
        break;
    case 'H':
        saveout << infoE << '\n' << infoN << '\n';
        AnalyseOfInfo(infoH, End_Of_Game, Time);
        saveout << '\n' << infoC;
        break;
    case 'C':
        saveout << infoE << '\n' << infoN << '\n' << infoH << '\n';
        AnalyseOfInfo(infoC, End_Of_Game, Time);
        break;
    }
    return 0;
}
int AnalyseOfInfo(char *info, const bool& End_Of_Game, const int& Time)
{
    multiset <pair <int, string> > table_of_records;
    multiset <pair <int, string> > :: iterator it;
    string name, bName = "";
    ofstream saveout("save.txt");
    int bTime = 0;

    if (info == "")
    {
        if (End_Of_Game)
        {
            cout << "Congrats! You reached new record. Enter your name type XXXX:\n";
            cin >> name;
            while (name.size() != 4)
            {
                cout << "Error. Please, try again: ";
                cin >> name;
            }
            bTime = Time > 5999 ? 5999 : Time;
            saveout << name;
            if (bTime % 10 == bTime)
                saveout << 0 << 0 << 0 << bTime;
            else if (bTime % 100 == bTime)
                saveout << 0 << 0 << bTime;
            else if (bTime % 1000 == bTime)
                saveout << 0 << bTime;
            else saveout << bTime;

            return 0;
        }
        else
        {
            cout << "Can't find records. Back to the menu...";
            getch();
            system("cls");
            return 0;
        }
    }
    else
    {
        for (int i = 0; i < strlen(info); i++)
        {
            if (info[i] == ' ')
            {
                for (int j = bName.size()-1, t = 0; j >= bName.size()-4; j--, t++)
                    bTime += (bName[j] - '0') * pow(10, t);
                for (int j = 0; j < bName.size()-4; j++)
                    name += bName[j];
                table_of_records.insert({bTime, name});
                bName = "";
                name = "";
                bTime = 0;
                continue;
            }
            bName += info[i];
        }

        if (End_Of_Game)
        {
            if (table_of_records.size() < 10)
            {
                cout << "Congrats! You reached new record. Enter your name type XXXX:\n";
                cin >> name;
                while (name.size() != 4)
                {
                    cout << "Error. Please, try again: ";
                    cin >> name;
                }

                bTime = Time > 5999 ? 5999 : Time;
                table_of_records.insert({Time, name});
                for (it = table_of_records.begin(); it != table_of_records.end(); it++)
                {
                    saveout << (*it).second;
                    if ((*it).first % 10 == (*it).first)
                    {
                        saveout << "000" << (*it).first << ' ';
                        continue;
                    }
                    else if ((*it).first % 100 == (*it).first)
                    {
                        saveout << "00" << (*it).first << ' ';
                        continue;
                    }
                    else if ((*it).first % 1000 == (*it).first)
                    {
                        saveout << 0 << (*it).first << ' ';
                        continue;
                    }
                    else
                    {
                        saveout << (*it).first << ' ';
                        continue;
                    }
                }
                return 0;
            }
            else
            {
                it = table_of_records.end();
                it--;
                if (Time < (*it).first)
                {
                    table_of_records.erase(it, table_of_records.end());
                    cout << "Congrats! You reached new record. Enter your name type XXXX:\n";
                    cin >> name;
                    while (name.size() != 4)
                    {
                        cout << "Error. Please, try again: ";
                        cin >> name;
                    }

                    bTime = Time > 5999 ? 5999 : Time;
                    for (it = table_of_records.begin(); it != table_of_records.end(); it++)
                    {
                        saveout << (*it).second;
                        if ((*it).first % 10 == (*it).first)
                        {
                            saveout << "000" << (*it).first << ' ';
                            continue;
                        }
                        else if ((*it).first % 100 == (*it).first)
                        {
                            saveout << "00" << (*it).first << ' ';
                            continue;
                        }
                        else if ((*it).first % 1000 == (*it).first)
                        {
                            saveout << 0 << (*it).first << ' ';
                            continue;
                        }
                        else
                        {
                            saveout << (*it).first << ' ';
                            continue;
                        }
                    }
                }
                return 0;
            }
        }
        else
        {
            cout << "Name Time\n";
            for (auto i: table_of_records)
            {
                bTime = i.first;
                cout << i.second << ' ';
                if (bTime / 60 < 10) cout << 0 << bTime / 60 << ':';
                else cout << bTime / 60 << ':';
                int x = bTime - (bTime / 60) * 60;
                if (x % 10 == x) cout << 0;
                cout << x;
                cout << endl;
            }
            saveout << info;
            getch();
            system("cls");
            return 0;
        }
    }
}
void ChangeSizeOfWindow(const int& x_Size, const int& y_Size)
{
    HWND hwnd;
    char Title[1024];
    GetConsoleTitle(Title, 1024); // Узнаем имя окна
    hwnd = FindWindow(NULL, Title); // Узнаем hwnd окна
    int x = x_Size +300;
    int y = y_Size +300;
    MoveWindow(hwnd,450,200,x,y,TRUE);//xnew,ynew,wnew,hnew -новые положение x,y, ширина и высота
}
