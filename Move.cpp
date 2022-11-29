#include <windows.h>
#include <conio.h>

using namespace std;

char Key(char& symbol);
char ReChange(char& symbol);
bool Move(COORD& pt, char& symbol, const int& x_Size, const int& y_Size)
{
    HANDLE stdcon = GetStdHandle(STD_OUTPUT_HANDLE);
    symbol = Key(symbol);
    if (symbol == -32) // признак escape последовательности, означает что был введён не символ а спец клавиша, код которой будет прочтён следующим _getch()
    {
        symbol = Key(symbol);
        if (symbol == 75) // влево
        {
            if (pt.X)
                pt.X--;
        }
        else if (symbol == 72)  // вверх
        {
            if (pt.Y)
                pt.Y--;
        }
        else if (symbol == 77) // вправо
        {
            if (pt.X < y_Size - 1)
                pt.X++;
        }
        else if (symbol == 80) // вниз
        {
            if (pt.Y < x_Size - 1)
                pt.Y++;
        }
        SetConsoleCursorPosition(stdcon, pt);
        return true;
    }
    symbol = ReChange(symbol);
    if (symbol == 13 || symbol == 'F' || symbol == VK_ESCAPE)
        return false;
}
char Key(char& symbol)
{
    symbol = _getch();
    return symbol;
}
char ReChange(char& symbol)
{
    if (symbol >= 'a' && symbol <= 'z') symbol += 'A' - 'a';
    return symbol;
}

