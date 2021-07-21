#include <iostream>
#include <vector>
#include <tuple>
#include <list>
#include <cmath>
#include <algorithm>

using namespace std;
int value[9][9];
list<tuple<int, int>> nearbys[9][9];
list<tuple<int, int>> guessPosition;
list<int> guessLen;
list<tuple<int, int>> getNearby(int row, int column);

void init_nearbys(void)
{
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            nearbys[i][j] = getNearby(i, j);
            value[i][j] =0;
        }
    }
}

bool checkAllowable(int row, int column, int num)
        {
            list<tuple<int, int>> result;
            list<tuple<int, int>> nearby1 = nearbys[row][column];
            auto it = nearby1.begin();
            for(int i = 0; i<nearby1.size(); i++)
            {
                    tuple<int,int> nearby= *it;
                    if (abs(value[get<0>(nearby)][get<1>(nearby)]) == num)
                        result.push_back(nearby);

                    it++;
            }

            if (result.size() == 0)
                return true;
            else
                return false;
        }

list<int> getAllowableNumber(int row, int column)
        {
            list<int> list;
            for (int i = 1; i <= 9; i++)
            {
                if (checkAllowable(row, column, i))
                {
                    list.push_back(i);
                }
            }
            return list;
        }
bool isAllFill(void)
{
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            if (value[i][j] == 0)
                return false;
        }
    }
    return true;
}

list<tuple<int, int>> getNearby(int row, int column)
{
    list<tuple<int, int>> result;

    for (int i = 0; i < 9; i++)
    {
        if(i!=column)
            result.push_back(tuple<int, int>(row, i));
        if(i!=row)
            result.push_back(tuple<int, int>(i, column));
    }
    for (int i = row - row % 3; i < row - row % 3 + 3; i++)
    {
        for (int j = column - column % 3; j < column - column % 3 + 3; j++)
        {
            if(i!=row && j!=column)
                result.push_back(tuple<int, int>(i, j));
        }
    }

    return result;
}
bool infer(void)
{
    list<int> allowableNumberArray[9][9];
    bool isChanged;
    int nextRow, nextColumn, lenNow, minLen;


    do
    {
        isChanged = false;
        nextRow = -1; nextColumn = -1; minLen = 0;

        //由允许位置直接推理
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (value[i][j] == 0)
                {
                    list<int> allowableNumber = getAllowableNumber(i, j);
                    if (allowableNumber.size() == 1)
                    {
                        guessPosition.push_back(tuple<int, int>(i, j));
                        value[i][j] = -allowableNumber.front();
                        isChanged = true;
                    }
                }
            }
        }
        //更新allowableNumberArray
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (value[i][j] == 0)
                {
                    allowableNumberArray[i][j] = getAllowableNumber(i, j);
                    lenNow = allowableNumberArray[i][j].size();

                    if (lenNow == 0)
                        return false;   //存在某格数字全部冲突

                    if (minLen == 0 || lenNow < minLen)
                    {
                        nextRow = i;
                        nextColumn = j;
                        minLen = lenNow;
                    }
                }
            }
        }
        //由可能位置直接推理
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (value[i][j] == 0)
                {
                    list<int> allowableNumber;
                    for (int k = 1; k <= 9; k++)
                        allowableNumber.push_back(k);

                    list<tuple<int, int>> nearby1 = getNearby(i,j);
                    auto it = nearby1.begin();
                    for(int i = 0; i<nearby1.size(); i++)
                    {
                        tuple<int,int> nearby = *it;
                        if (value[get<0>(nearby)][get<1>(nearby)] == 0)
                        {
                            list<int> nearby2 = allowableNumberArray[i][j];
                            auto it2 = nearby2.begin();
                            int index=0;
                            for(int j = 0; j<nearby2.size(); j++)
                            {   
                                allowableNumber.remove(*it2);
//                                auto index = find(allowableNumber.begin(),allowableNumber.begin(),*it2);
//                                if (index != allowableNumber.end())
//                                    allowableNumber.Remove(*it2);
                                it2++;
                            }
                        }
                        else
                        {
                            allowableNumber.remove(abs(value[get<0>(nearby)][get<1>(nearby)]));
                        }
                        it++;
                    }
                    if (allowableNumber.size() == 1)
                    {
                        guessPosition.push_back(tuple<int, int>(i, j));
                        value[i][j] = -allowableNumber.front();
                        isChanged = true;
                    }
                }
            }
        }
    } while (isChanged);

    //无法由当前棋盘判断确定数字
    if (isAllFill())
    {
        return true;
    }
    else
    {
        //由允许数字猜测
        list<int> nums = allowableNumberArray[nextRow][nextColumn];
        auto it3 = nums.begin();
        for(int i = 0; i<nums.size(); i++)
        {
            list<int> n = getAllowableNumber(nextRow, nextColumn);
            
            if (find(n.begin(),n.end(),*it3) != n.end())  //判断变动后该数字是否仍被允许
            {
                guessPosition.push_back(tuple<int, int>(nextRow, nextColumn));
                value[nextRow][nextColumn] = -*it3;
                guessLen.push_back(guessPosition.size());
                if (infer())
                {
                    guessPosition.clear();
                    guessLen.clear();
                    return true;
                }
                else
                {
                    guessLen.pop_back();

                    int len = guessLen.size() == 0 ? 0 : guessLen.back();
                    while (guessPosition.size() > len)
                    {
                        value[get<0>(guessPosition.back())][get<1>(guessPosition.back())] = 0;
                        guessPosition.pop_back();
                    }
                }
            }
        }

        //未填满，且存在某格数字全部冲突
        return false;
    }
}


int main(){

    init_nearbys();
    infer();
    return 0;
}