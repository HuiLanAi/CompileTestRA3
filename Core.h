#pragma once
#include "iostream"
#include "string"
#include "vector"
using namespace std;

#define E 100
#define E1 101
#define T 102
#define T1 103
#define F 104
#define L 105
#define w0 106
#define w1 107

#define LEFT 5
#define RIGHT 6
#define ADD 20
#define MINUS 21
#define MULT 22
#define DIV 23
#define NUMBER 2
#define SYNX 1
#define ERROR 0
#define END 7

int judgePath(int stack, int ele, int* anaStack, int* topStack, int* topArray, vector<string>* simu, vector<string>* resu, vector<string>attrList);
int analyseTable(int array[], int length);
void judgeBeforePop(vector<string>* resu, vector<string>* simu);
void handleStake(vector<string>* resu);

int analyseTable(int* array, int length, vector<string> attrList)
{

	vector<string> simu;//模拟栈
	simu.push_back("E");
	vector<string> resu;//结果栈

	array[length] = END;
    //在输入数组最后加上结束符
    int* anaStack = new int [200];
    anaStack[0] = END;
    anaStack[1] = E;
    int topStack = 2;
    int eleStack = E;
    //分析栈的初始化

    int topArray = 0;
    int eleArray = array[0];
    do{
        int path = judgePath(eleStack, eleArray, anaStack, &topStack, &topArray, &simu, &resu, attrList);
		// cout << path << endl;
        if(path == 0)
        {
            cout << "Invaild lanauage!" << endl;
            return 0;
        }
        eleStack = anaStack[topStack - 1];
        eleArray = array[topArray];
	   // for (int i = 0; i < simu.size(); i++)
		//  cout << simu.at(i) << endl;
		//cout << "***************************" << endl;
    }
	while(topStack != 1);
    handleStake(&resu);
	if (topArray == length)
		return 1;
	else
		return 0;
}




int judgePath(int stack, int ele, int* anaStack, int* topStack, int* topArray, 
                vector<string>* simu, vector<string>* resu, vector<string> attrList)
{
    if(stack == E)
    {
        if(ele == NUMBER || ele == SYNX || ele == LEFT)
        {
			judgeBeforePop(resu, simu);
			(*simu).pop_back();
			(*simu).push_back("E1");
			(*simu).push_back("T");

            anaStack[*topStack - 1] = E1;
            anaStack[*topStack] = T;
            *topStack = *topStack + 1;
            return 1;
        }
        else return ERROR;
    }

    if(stack == E1)
    {
        if(ele == ADD || ele == MINUS)
        {
			judgeBeforePop(resu, simu);
			(*simu).pop_back();
            (*simu).push_back("E1");
			if(ele == ADD)
			{
				(*simu).push_back("+");
			}
			else{
				(*simu).push_back("-");
            }            
			(*simu).push_back("T");
            (*simu).push_back("W0");
            // uwadhsdjlaw
            // 这里w0和语义动作有问题 晚上没写完 参照txt
            anaStack[*topStack - 1] = E1;
            anaStack[*topStack] = T;
            anaStack[(*topStack) + 1] = w0;
            *topStack = *topStack + 2;
            return 2;
        }
        else if(ele == RIGHT || ele == END || ele == 0)
        {
            judgeBeforePop(resu, simu);
            judgeBeforePop(resu, simu);
			(*simu).pop_back();

            *topStack = *topStack - 1;
            return 3;
        }
        else return 0;
    }

    if(stack == T)
    {
        if(ele == NUMBER ||ele == SYNX || ele == LEFT)
        {
			judgeBeforePop(resu, simu);
			(*simu).pop_back();
			(*simu).push_back("T1");
			(*simu).push_back("F");

            anaStack[*topStack - 1] = T1;
            anaStack[*topStack] = F;
            *topStack = *topStack + 1;
            return 4;   
        }
        else return 0;
    }

    if(stack == T1)
    {
        if(ele == MULT || ele == DIV)
        {
            judgeBeforePop(resu, simu);
			(*simu).pop_back();
            (*simu).push_back("T1");
            if(ele == MULT)
            {
                (*simu).push_back("*");
            }
            else 
            {
                (*simu).push_back("/");
            }
            (*simu).push_back("F");
            (*simu).push_back("W1");
            
            anaStack[*topStack - 1] = T1;
            anaStack[*topStack] = F;
            anaStack[*topStack + 1] = w1;
            *topStack = *topStack + 2;
            return 5;
        }
        else if(ele == ADD || ele == MINUS || ele == RIGHT || ele == END || ele == 0)
        {
            judgeBeforePop(resu, simu);
            judgeBeforePop(resu, simu);
            (*simu).pop_back();
            
            *topStack = *topStack - 1;
            return 6;
        }
        else return 0;
    }

    if(stack == F)
    {
        if(ele == NUMBER || ele == SYNX)
        {
            judgeBeforePop(resu, simu);
            (*simu).pop_back();
            (*simu).push_back(attrList.at(*topArray));

            *topStack = *topStack - 1;
            *topArray = *topArray + 1;
            return 7;
        }
        else if(ele == LEFT)
        {
            judgeBeforePop(resu, simu);
            (*simu).pop_back();
            (*simu).push_back(")");
            (*simu).push_back("E");
            (*simu).push_back("(");

            anaStack[*topStack - 1] = RIGHT;
            anaStack[*topStack] = E;
            anaStack[*topStack + 1] = LEFT;
            *topStack = *topStack + 2;
            return 8;
        }
        else return 0;
    }

    if(stack == w0)
    {
        if(ele == ADD || ele == MINUS)
        {
            judgeBeforePop(resu, simu);
            (*simu).pop_back();

            *topStack = *topStack - 1;
            *topArray = *topArray + 1;
            return w0;
        }
        else return 0;
    }

    if(stack == w1)
    {
        if(ele == MULT || ele == DIV)
        {
            judgeBeforePop(resu, simu);
            (*simu).pop_back();

            *topStack = *topStack - 1;
            *topArray = *topArray + 1;
            return w1;
        }
        else return 0;
    }

    if(stack == LEFT)
    {
        if(ele == LEFT)
        {
            judgeBeforePop(resu, simu);
            (*simu).pop_back();

            *topStack = *topStack - 1;
            *topArray = *topArray + 1;
            return LEFT;
        }
        else return 0;
    }

    if(stack == RIGHT)
    {
        if(ele == RIGHT)
        {
            judgeBeforePop(resu, simu);
            (*simu).pop_back();

            *topStack = *topStack - 1;
            *topArray = *topArray + 1;
            return RIGHT;
        }
        else return 0;
    }
  
}

void judgeBeforePop(vector<string>* resu, vector<string>* simu)
{
	if((*simu).back().compare("E") != 0 &&
        (*simu).back().compare("E1") != 0 &&
        (*simu).back().compare("T") != 0 &&
    	(*simu).back().compare("T1") != 0 &&
        (*simu).back().compare("W0") != 0 &&
        (*simu).back().compare("F") != 0 &&
        (*simu).back().compare("W1") != 0 &&
        (*simu).back().compare("(") != 0 &&
        (*simu).back().compare(")") != 0  )
	{
		(*resu).push_back((*simu).back());
		(*simu).pop_back();
	}	
	
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

