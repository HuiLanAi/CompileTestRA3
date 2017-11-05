#define LEFT 5
#define RIGHT 6
#define ADD 20
#define MINUS 21
#define MULT 22
#define DIV 23
#define NUMBER 2
#define SYNX 1
#define ERROR 0

int judgeNum(char targetSeg[], int length);
int judgeSynx(char targetSeg[], int length);

int getNumSymbol(char targetSeg[], int length)//返回当前词的属性
{
	int cur = 0;
	if (targetSeg[cur] == '+' || targetSeg[cur] == '-')
	{
		if(targetSeg[cur] == '+')
			return ADD;
		else
			return MINUS;
	}
	else if (targetSeg[cur] == '*' || targetSeg[cur] == '/')
	{
		if (targetSeg[cur] == '*')
			return MULT;
		if (targetSeg[cur] == '/')
			return DIV;
	}
	else if (targetSeg[cur] == '(')
	{
		return LEFT;
	}
	else if (targetSeg[cur] == ')')
	{
		return RIGHT;
	}
	else
	{
		if (targetSeg[cur] >= '0' && targetSeg[cur] <= '9')
			return judgeNum(targetSeg, length);
		else if ((targetSeg[cur] >= 'A' && targetSeg[cur] <= 'Z')
			|| (targetSeg[cur] >= 'a' && targetSeg[cur] <= 'z')
			|| targetSeg[cur] == '_')
			return judgeSynx(targetSeg, length);
		else return ERROR;
	}
}

int judgeNum(char targetSeg[], int length)
{
	int floatPresent = 0;//小数标志位
	if (targetSeg[0] == '0' && targetSeg[1] != '.' && length > 1)//数字以0开头的非法情况
	{
		return ERROR;
	}
	for (int i = 1; i < length; i++)
	{
		if ((targetSeg[i] >= '0' && targetSeg[i] <= '9')
			|| (targetSeg[i] == '.' && floatPresent == 0))//如果是数字则继续 小数点只能出现一次
		{
			if (targetSeg[i] == '.')
			{
				floatPresent = 1;//置小数标志位
			}
			continue;
		}
		else
			return ERROR;
	}
	return NUMBER;
}

int judgeSynx(char targetSeg[], int length)
{
	for (int cur = 1; cur < length; cur++)
	{
		if ((targetSeg[cur] >= 'A' && targetSeg[cur] <= 'Z')
			|| (targetSeg[cur] >= 'a' && targetSeg[cur] <= 'z')
			|| targetSeg[cur] == '_'
			|| (targetSeg[cur] >= '0' && targetSeg[cur] <= '9'))//如果出现的都是合法字符 则继续
			continue;
		else
			return ERROR;
	}
	return SYNX;
}