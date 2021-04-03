#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print(char * f, double t)
{
	if (t > 1000)				   //1秒
		printf("%s time cost  %.0lfms\n", f, t);
	else
		printf("%s time cost  %.0lfms\n", f, t);
}

int main()
{
	int ok = 0;
	while (1) //一直迴圈，直到找到不一樣的資料
	{
		system("test_data_gen.py > test.in");
		double begin = clock();
		system("a.exe < test.in > a.in");
		double end = clock();
		print("main        ", end-begin);

		begin = clock();
		system("standard.py < test.in > standard.in");
		end = clock();
		print("standard    ", end-begin);

		begin = clock();
		system("brute_force.exe < test.in > brute_force.in");
		end = clock();
		print("brute_force ", end-begin);
		// double t = (end - begin);
		


		
		if (system("fc a.in standard.in")) //當 fc 返回1時，說明這時資料不一樣
			break;						   //不一樣就跳出迴圈
	

		ok++; //AC數量+1
		printf("correct %d\n", ok);
	}

	printf("Fine difference!");
	return 0;
}