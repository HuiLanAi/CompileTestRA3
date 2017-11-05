#pragma once

#define LEFT 5
#define RIGHT 6
#define ADD 3
#define MINUS 7
#define DIV 8
#define MULT 4
#define NUMBER 2
#define SYNX 1
#define ERROR 0

#include "iostream"
#include "vector"
#include "string"
using namespace std;

bool discernE(int curUnit, int* eleArray, int *start, int end, vector<string> attrList, vector<string>* simu, vector<string>* resu);
bool discernT(int curUnit, int* eleArray, int *start, int end, vector<string> attrList, vector<string>* simu, vector<string>* resu);
bool discernE1(int curUnit, int* eleArray, int *start, int end, vector<string> attrList, vector<string>* simu, vector<string>* resu);
bool discernF(int curUnit, int* eleArray, int *start, int end, vector<string> attrList, vector<string>* simu, vector<string>* resu);
int discernW0(int curUnit, int* eleArray, int *start, int end, vector<string> attrList, vector<string>* simu, vector<string>* resu);
bool discernNull(int curUnit, int* eleArray, int *start, int end, vector<string> attrList, vector<string>* simu, vector<string>* resu);
bool discernT1(int curUnit, int* eleArray, int *start, int end, vector<string> attrList, vector<string>* simu, vector<string>* resu);
bool discernL(int curUnit, int* eleArray, int *start, int end, vector<string> attrList, vector<string>* simu, vector<string>* resu);
int discernW1(int curUnit, int* eleArray, int *start, int end, vector<string> attrList, vector<string>* simu, vector<string>* resu);
void handleStake(vector<string>* resu);


void inHonorOfRedAlart3(int* eleArray, int end, vector<string> attrList)
/* 生成四元式的主功能函数 */
/* 致敬夕阳中的红色警戒3！2017.11.1 */
{
    vector<string> simu, resu;
    int start = 0;
    if(discernE(0, eleArray, &start, end, attrList, &simu, &resu))
    {
        cout << "Valid Lanauage!" << endl;
        handleStake(&resu);
    }
    else
    {
        cout << "Invalid Lanauage!" << endl;
    }
}

bool discernE(int curUnit, int* eleArray, int *start, int end, 
    vector<string> attrList, vector<string>* simu, vector<string>* resu)
{
    curUnit = eleArray[*start];  
    //读取下一个字符
    if(!discernT(curUnit, eleArray, start, end, attrList, simu, resu))
    {
        // cout << "E ->T" << endl;
        return false;
    }
    else
    {
        //为读取下一个字符做准备
        if(discernE1(curUnit, eleArray, start, end, attrList, simu, resu))
        {
            return true;
        }
        else
        {
            // cout << "E ->TE1" << endl;
            return false;
        }
    }

    if(*start == end - 1)
    {
        return true;
    }
    /* 读取到最后的一个字符 */

    return true;
}

bool discernE1(int curUnit, int* eleArray, int *start, int end, 
    vector<string> attrList, vector<string>* simu, vector<string>* resu)
{
	 
    curUnit = eleArray[*start]; 

    int temp = discernW0(curUnit, eleArray, start, end, attrList, simu, resu);
    
    if(!temp)
    {
        discernNull(curUnit, eleArray, start, end, attrList, simu, resu);
        /* 进入空产生式函数*/
        return true;
    }
    else
    {
        if(discernT(curUnit, eleArray, start, end, attrList, simu, resu))
        {
            if(temp == ADD)
            {
                (*resu).push_back("+");
            }
            if(temp == MINUS)
            {
                (*resu).push_back("-");
            }
            /* 语义动作压栈 */

            if(discernE1(curUnit, eleArray, start, end, attrList, simu, resu))
            {
                *(start) ++;
                return true;
            }
            else
            {
                // cout << "E1 ->W0TE1" << endl;
                return false;
            }
        }
        else
        {
            // cout << "E1 ->W0T" << endl;
            return false;
        }
    }
}

bool discernT(int curUnit, int* eleArray, int *start, int end, 
    vector<string> attrList, vector<string>* simu, vector<string>* resu)
{
    curUnit = eleArray[*start];  
    if(!discernF(curUnit, eleArray, start, end, attrList, simu, resu))
    {
        // cout << "T->F" << endl;
        return false;
    }
    else
    {
        if(discernT1(curUnit, eleArray, start, end, attrList, simu, resu))
        {
            return true;
        }
        else{
            return false;
        }
    }
}

bool discernT1(int curUnit, int* eleArray, int *start, int end, 
    vector<string> attrList, vector<string>* simu, vector<string>* resu)
{
    curUnit = eleArray[*start]; 
    
    int temp = discernW1(curUnit, eleArray, start, end, attrList, simu, resu);
    
    if(!temp)
    {
        discernNull(curUnit, eleArray, start, end, attrList, simu, resu);
        return true;
    }
    else
    {
        if(discernF(curUnit, eleArray, start, end, attrList, simu, resu))
        {
            if(temp == MULT)
            {
                (*resu).push_back("*");
            }
            if(temp == DIV)
            {
                (*resu).push_back("/");
            }
            /* 语义动作压栈 */
            if(discernT1(curUnit, eleArray, start, end, attrList, simu, resu))
            {
                *(start) ++;
        
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
}

bool discernF(int curUnit, int* eleArray, int *start, int end, 
    vector<string> attrList, vector<string>* simu, vector<string>* resu)
{
    curUnit = eleArray[*start];  
    
    if(!discernL(curUnit, eleArray, start, end, attrList, simu, resu))
    {
        if(curUnit == LEFT)
        {
            (*start) ++;

            if(discernE(curUnit, eleArray, start, end, attrList, simu, resu))
            {
                curUnit = eleArray[*start];  
                if(curUnit == RIGHT)
                {
                    *(start) ++;
        
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
        /* 是（E）的情况 */
    }
    else
    {
       *(start) ++;
       
       return true;
    }
}

bool discernL(int curUnit, int* eleArray, int *start, int end, 
    vector<string> attrList, vector<string>* simu, vector<string>* resu)
{
    curUnit = eleArray[*start];  
    
    if(curUnit == SYNX || curUnit == NUMBER)
    {
        (*resu).push_back(attrList.at(*start));
        (*start) ++;
        
        return true;
    }
    else
    {
        return false;
    }
}


int discernW0(int curUnit, int* eleArray, int *start, int end, 
    vector<string> attrList, vector<string>* simu, vector<string>* resu)
{
    curUnit = eleArray[*start];  
    
    if(curUnit == ADD || curUnit == MINUS)
    {
        if(curUnit == ADD)
        {
            (*start) ++;
            return ADD;
        }
        else
        {
            (*start) ++;
            return MINUS;
        }
    }
    else
    {
        return false;
    }
}

int discernW1(int curUnit, int* eleArray, int *start, int end, 
    vector<string> attrList, vector<string>* simu, vector<string>* resu)
{
    curUnit = eleArray[*start];  
    
    if(curUnit == MULT || curUnit == DIV)
    {
        if(curUnit == MULT)
        {
            (*start) ++;
            return MULT;
        }
        else
        {
            (*start) ++;
            return DIV;
        }
    }
    else
    {
        return false;
    }
}

bool discernNull(int curUnit, int* eleArray, int *start, int end, 
    vector<string> attrList, vector<string>* simu, vector<string>* resu)
{
     
    *start = *start;
    return true;
}

void handleStake(vector<string>* resu)
{
    int synxCount = 0;
    vector<string> stake;
	vector<string>::iterator itr = (*resu).begin();
    stake.push_back((*resu).front());
    (*resu).erase(itr);
	itr = (*resu).begin();
    while(!(*resu).empty())
    {
        stake.push_back((*resu).front());
        (*resu).erase(itr);
		itr = (*resu).begin();
        //压入一个元素
        if(stake.back().compare("+") == 0 ||
            stake.back().compare("-") == 0 ||
            stake.back().compare("*") == 0 ||
            stake.back().compare("/") == 0)
        {
            cout << stake.back() << " ";
            stake.pop_back();
            //弹出符号
            string temp1 = stake.back();
            stake.pop_back();
            //弹出第一个元素
            string temp2 =  stake.back();
            stake.pop_back();
            //弹出第二个元素
			cout << temp2 << " " << temp1 << " ";
            stake.push_back("t");
			char temp[2] = { 0 };
			temp[0] = char(synxCount + 48);
			synxCount++;
            stake.back().append(temp);
            cout << stake.back() << endl;
        }
    }
}