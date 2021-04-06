#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print(char *f, double t)
{
	if (t > 1000) //1秒
		printf("%s time cost  %.0lfms\n", f, t);
	else
		printf("%s time cost  %.0lfms\n", f, t);
}

int main()
{
	int ok = 0, main = 0, standard = 0, brute_force = 0;
	while (ok < 5000) //一直迴圈，直到找到不一樣的資料
	{
		ok++; //AC數量+1
		system("python3 ./test_data_gen.py > test.in ");
		double begin = clock();
		system("./a < test.in > a.out");
		double end = clock();
		main += end - begin;
		print("main        ", end - begin);

		begin = clock();
		system("python3 ./standard.py < test.in > standard.out");
		end = clock();
		standard += end - begin;
		print("standard    ", end - begin);

		begin = clock();
		system("./brute_force < test.in > brute_force.out");
		end = clock();
		brute_force += end - begin;
		print("brute_force ", end - begin);
		// double t = (end - begin);
		printf("\n");
		if (ok % 5 == 0)
		{
			printf("\n\n-------------Average--------------\n");
			print("main        ", main / ok);
			print("standard    ", standard / ok);
			print("brute_force ", brute_force / ok);
			printf("------------------------------------\n\n\n");
		}

		if (system("diff a.out standard.out"))			 //當 fc 返回1時，說明這時資料不一樣
			break;									 //不一樣就跳出迴圈
		// if (system("fc brute_force.in standard.in")) //當 fc 返回1時，說明這時資料不一樣
		// 	break;									 //不一樣就跳出迴圈

		printf("correct %d\n", ok);
	}

	printf("Find difference!\n");
	return 0;
}