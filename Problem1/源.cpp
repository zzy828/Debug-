#include<vector>
#include<iostream>
#include<cstdlib>
#include<algorithm>
#include<map>
#include<numeric>
using namespace std;

int main()
{
	int num = 0;
	int totday = 0;
	int word;
	int use_day[100] = { 0 };
	int number[100] = { 0 };
	cin >> num >> totday;
	cin.clear();
	int f = 0;
	while (f < num)
	{
		cin >> use_day[f];
		number[f] = f + 1;
		f++;
	}
	

	int all = 0;
	for (int j = 0; j < num; j++)
	{
		all += use_day[j];
	}
	if (totday >= all)
	{
		cout << num << endl;
		for (int i = 0; i < num; i++)
		{
			cout << number[i]<<' ';	
		}
		return 0;
	}
	else


	{
		for (int i = 0; i < num - 1; i++)
		{
			for (int j = 0; j < num - i - 1; j++)
			{
				if (use_day[j] > use_day[j + 1])
				{
					int temp = use_day[j];
					use_day[j] = use_day[j + 1];
					use_day[j + 1] = temp;
					int temp_1 = number[j];
					number[j] = number[j + 1];
					number[j + 1] = temp_1;
				}
			}
		}


		int add = 0;
		int z = -1;
		int all_num = -1;
		while(add<=totday)
		{
			z++;
			add += use_day[z];
			
			all_num++;
		}
		
		cout << all_num << endl;
		for (int l = 0; l < z; l++)
			cout << number[l]<<' ';
	}
	system("pause");
	return 0;
}