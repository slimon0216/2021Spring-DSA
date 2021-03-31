#include <stdio.h>
#include <stdlib.h>
int main()
{
    while(1) //一直迴圈，直到找到不一樣的資料
	{
		system("test_data_gen.py > test.in");
		system("insert.py < test.in > insert.in");
		system("2.exe < test.in > 2.in");
		if(system("fc 2.in insert.in")) //當 fc 返回1時，說明這時資料不一樣
			break; //不一樣就跳出迴圈
		printf("correct\n");
	}
	return 0;
}