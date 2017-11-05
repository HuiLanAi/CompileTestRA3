#pragma once
#include "iostream"
using namespace std;

void diminishVacant(char targetS[], int *front, int *back)
//用于消除空格和更改两个哨兵的值
{
    int key = 0;
    if (*front == 0) //如果是最初的情况
    {
        /****************消除开头的空格字符*******************/
        while (targetS[*front] == 32 || targetS[*front] == '\t' || targetS[*front] == '\n')
        {
            (*front)++;
            (*back)++;
        }
        /******************消除分隔的情况**********************/
        while (((targetS[*back] >= '0' && targetS[*back] <= '9') 
                || (targetS[*back] >= 'A' && targetS[*back] <= 'Z') 
                || (targetS[*back] >= 'a' && targetS[*back] <= 'z') 
                || targetS[*back] == '_') &&
               ((targetS[(*back) + 1] >= '0' && targetS[(*back) + 1] <= '9') 
               || (targetS[(*back) + 1] >= 'A' && targetS[(*back) + 1] <= 'Z') 
               || (targetS[(*back) + 1] >= 'a' && targetS[(*back) + 1] <= 'z') 
               || targetS[(*back) + 1] == '_')) //判断分隔的情况
        {
        //第一个有效字符和第二个有效字符不构成标识符->只有第一个有效字符构成标识符或符号开头
            (*back)++; //back指向当前片段最后一个字符
            key = 1;
        }

        if(key)
        {
            (*back) ++;
            return;
        }

        if((targetS[*back] >= '0' && targetS[*back] <= '9') 
        || (targetS[*back] >= 'A' && targetS[*back] <= 'Z') 
        || (targetS[*back] >= 'a' && targetS[*back] <= 'z'))
        {
            (*back) ++;
            return;
            //第一个有效字符独自构成标识符
        }

        /* ****************确定普通字符的分隔********************* */
        /* *******************符号的分隔************** */
        if(targetS[*back] == '(' || targetS[*back] == ')' || targetS[*back] == '+'
            || targetS[*back] == '-' || targetS[*back] == '*' || targetS[*back] == '/')
        {
            *front = *back;
            (*back) ++;
        }
    }
    else
    {
        *front = *back;
        while (targetS[*front] == 32 || targetS[*front] == '\t' || targetS[*front] == '\n')
        {
            (*front)++;
            (*back)++;
        }
        /******************消除分隔的情况**********************/
        while (((targetS[*back] >= '0' && targetS[*back] <= '9') 
                || (targetS[*back] >= 'A' && targetS[*back] <= 'Z') 
                || (targetS[*back] >= 'a' && targetS[*back] <= 'z') 
                || targetS[*back] == '_') &&
               ((targetS[(*back) + 1] >= '0' && targetS[(*back) + 1] <= '9') 
               || (targetS[(*back) + 1] >= 'A' && targetS[(*back) + 1] <= 'Z') 
               || (targetS[(*back) + 1] >= 'a' && targetS[(*back) + 1] <= 'z') 
               || targetS[(*back) + 1] == '_')) //判断分隔的情况
        {
            (*back)++; //back指向当前片段最后一个字符
            key = 1;
        }
        if(key)
        {
            (*back) ++;
            return;
        }
        
        if((targetS[*back] >= '0' && targetS[*back] <= '9') 
        || (targetS[*back] >= 'A' && targetS[*back] <= 'Z') 
        || (targetS[*back] >= 'a' && targetS[*back] <= 'z'))
        {
            (*back) ++;
            return;
            //第一个有效字符独自构成标识符
        }

        /* *******************符号的分隔************** */
        if(targetS[*back] == '(' || targetS[*back] == ')' || targetS[*back] == '+'
           || targetS[*back] == '-' || targetS[*back] == '*' || targetS[*back] == '/')
            {
                *front = *back ;
                (*back) ++;
            }
    }
}