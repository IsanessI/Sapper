#include "functions.h"

using namespace std;

int Generation(bool& Mine, int& ValueOfMine, const int& x_Size, const int& y_Size, const int& x, const int& y, int& AmountOfMines, int& i, int& j)
{
    const pair <int, int> Check[8] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    if (AmountOfMines == 0)
        return 0;
    if (i == x && j == y) return 1;
    if (x_Size > 4 && y_Size > 4)
    {
        bool f1 = 0; //для того, чтобы возле курсора не появились мины
        for (int t = 0; t < 8; t++)
            if (i == x+Check[t].first && j == y+Check[t].second)
            {
                f1 = 1;
                break;
            }
        if (f1) return 1;
    }
    if (Mine)
        return 1;
    int xx = rand() % (x_Size*y_Size);
    if (xx == rand() % x_Size*x_Size)
    {
        Mine = 1;
        ValueOfMine = 0;
        AmountOfMines--;
    }
    return 1;
}

