/************************************************************************/
/* 
*  经计算64人中 至少有两人在同日生的概率几乎为1 特此测试
*
*/
/************************************************************************/

#include <iostream>
#include <time.h>

#define Max 70


void Sort(int* array, int len)
{
	for (int i = 0; i < len - 1; i++)
	{
		for (int j = 0; j < len - i - 1; j++)
		{
			if (array[j] > array[j + 1])
			{
				array[j] ^=		array[j + 1];
				array[j + 1] ^= array[j];
				array[j] ^=		array[j + 1];
			}
		}
	}

}

bool hasIdentical(int* array, int len, int* tmp)
{
	for (int i = 0; i < len - 1; i++)
	{
		if (array[i] == array[i + 1])
		{
			*tmp = array[i];
			return true;
		}
	}

	return false;
}

int main(int agv, char *agvs[])
{
	int p = 0;
	
	srand((unsigned int)time(NULL));
	while (p < 1000000)
	{
		int brithDays[Max];
		
		for (int i = 0; i < Max; ++i)
		{
			brithDays[i] = rand() % 365 + 1;
		}
		int num;

		Sort(brithDays, Max);

		if (hasIdentical(brithDays, Max, &num))
		{
			printf("有相同的为 %d\n\n\n", num);
		}
		else
		{
			printf("没有相同的\n\n\n\n");
		}
		p++;
	}
// 	for (int i = 0; i < 64; ++i)
// 	{
// 		std::cout << brithDays[i] << "  ";
// 	}



	//std::cout << "hello..." << std::endl;

	return 0;
}

