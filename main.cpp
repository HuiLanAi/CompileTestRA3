#include "iostream"
#include "GetNumSymbol.h"
#include "Partition.h"
#include "FuncGroup.h"
using namespace std;

int main()
{
    char targetString[200] = { 0 };
    cin >> targetString;
    int frontPoint = 0, backPoint = 0;
    char seg[200] = { 0 };//用于保存当前带处理的字符串片段
    int arrayOfKind[100] = { 0 };//用于记录当前语句中每个片段的类型
    int lengthOfArray = 0;//用于记录当前数组长度

    vector <string> attrList;

    while(targetString[backPoint] != 0)
    {
        diminishVacant(targetString, &frontPoint, &backPoint);
        for(int i = 0; i < backPoint - frontPoint; i++)
        {
            seg[i] = targetString[frontPoint + i];
        }
        //backPoint = backPoint = 0 ? 1 : backPoint;
        if(frontPoint == 0)
		{
			frontPoint = backPoint;
		}
        
        /* **************生成新的片段**************** */
        
		// cout << seg << " " << frontPoint << " " << backPoint << endl;
        
        arrayOfKind[lengthOfArray] = getNumSymbol(seg, backPoint - frontPoint);

        // cout << arrayOfKind[lengthOfArray] << endl;

        string temp = string(seg);
		attrList.push_back(temp);
		//cout << seg << endl;
		for(int i = 0; i < 200; i++)
			seg[i] = 0;
		//将得到的字符串或属性值压栈
     
        if(!arrayOfKind[lengthOfArray])
        {
            cout << "Invaild Synx!" << endl;
			system("pause");
            return 1;
        }
        /* *************非法标识符************ */
        lengthOfArray++;
        //记录类型和长度
    }
    /* 已经完成了词法分析的全部流程 */

    inHonorOfRedAlart3(arrayOfKind, lengthOfArray, attrList);

	system("pause");
	return 0;
}


