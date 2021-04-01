#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
	int ok = 0;
	while (1) //一直迴圈，直到找到不一樣的資料
	{
		system("test_data_gen.py > test.in");
		system("2.exe < test.in > 2.in");
		double begin = clock();
		system("insert.py < test.in > insert.in");
		double end = clock();
		double t = (end - begin);
		if (system("fc 2.in insert.in")) //當 fc 返回1時，說明這時資料不一樣
			break;						 //不一樣就跳出迴圈
		else if (t > 1000)				 //1秒
		{
			printf("time cost  %.0lfms\n", t);
			ok++;
		}
		else
		{
			printf(" time cost %.0lfms\n", t);
			ok++; //AC數量+1
		}

		printf("correct %d\n", ok);
	}
	return 0;
}