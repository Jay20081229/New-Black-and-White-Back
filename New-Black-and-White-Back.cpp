#include<iostream> 
#include<cstring>
#include<algorithm>
#include "time.h"
#include<stdlib.h>
using namespace std;
int ne[12];
int n, colour[12];
bool cannot;
int step[12] = {0};
int player[999999];
bool st[12];
int setl[12] = {0};
int N;
bool flag;
int sr[12],cnt[10];

void Start();
void GetResults();

int I, J, life, maxrand;
char c;
void Start() {
	I = 0;
	J = 0;
	life = 0;
	maxrand = 6;
	
	cout << "Select difficulty mode:\n"; // the user has to select a difficutly level
	cout << "1 : Easy (0-15)\n";
	cout << "2 : Medium (0-30)\n";
	cout << "3 : Difficult (0-50)\n";
	cout << "or type another key to quit\n";
	c = 30;

	cin >> c;                   // read the user's choice
	cout << "\n";

	switch (c) {
		case '1':
			maxrand = 15;  // the random number will be between 0 and maxrand
			break;
		case '2':
			maxrand = 30;
			break;
		case '3':
			maxrand = 50;
			break;
		default:
			exit(0);
		break;
	}

	life = 5;         // number of lifes of the player
	srand((unsigned)time(NULL)); // init Rand() function
	J = rand() % maxrand;  // j get a random value between 0 and maxrand
	
	GetResults();
}
void GetResults() {
	if (life <= 0) { // if player has no more life then he loses
		cout << "You lose !\n\n";
		Start();
	}

	cout << "Type a number: \n";
	cin >> I;
	
	if((I>maxrand) || (I<0)) { // if the user number isn't correct, restart
		cout << "Error: number not between 0 and \n" << maxrand;
		GetResults();
	}

	if(I == J) {
		cout << "YOU WIN!\n\n"; // the user found the secret number
		Start();
	} else if(I>J) {
		cout << "Too BIG\n";
		life = life - 1;
		cout << "Lives remaining: " << life << "\n\n";
		GetResults();
	} else if(I<J) {
		cout << "Too SMALL\n";
		life = life - 1;
		cout << "Lives remaining: " << life << "\n\n";
		GetResults();
	}
}

int res;
void computer()
{
	if (st[1])
	{
		for (int k = 1;k <= N - 1;k++)
	    {
	    	
		    srand((unsigned)time(NULL)); 
		    if (st[k])
				colour[k + 1] = rand() % 2;
		}
	}
	else 
	{
		for (int k = 1;k <= N;k++)
		{
			srand((unsigned)time(NULL)); 
			if (st[k])
				colour[k] = rand() % 2;
		}
	}
	
}
void judge()
{
	int n0 = 0,n1 = 0;
	for (int j = 1;j <= N;j++)
	{
		if (colour[j] == 0 && st[j])
		{
			n0++;
		}
		else
		{
			if (st[j])
				n1++;
		}
	}
	if (n1 == 0 || n0 == 0)
	{
		res = 2;
	}
	else
	{
		if((n - 1) / 2 >= n0) 
		{
			res = 0;
		}
		else 
		{
			if ((n - 1) / 2 >= n1)
			{
				res = 1;
			}
			if (n1 == n0)
			{
				res = 2;
			}
		}
	}	
}
void exi(int ex)
{
	st[ex] = false;
} 
void compare(int xx,int yy)
{
    if (xx == yy)
    {
		return;
	}
	else
	{
		if (xx + yy == 5)
		{
			if (xx < yy)
			{
				step[1]++;
				sr[1] = 1;
			}
			else
			{
				step[2]++;
				sr[2] = 1;
		    }
		}
		else
		{
			if (xx > yy)
			{
				step[1]++;
		    	sr[1] = 1;
			}
			else
	    	{
				step[2]++;
				sr[2] = 1;
			}
		}
	}
	if (step[1] + step[2] == 8)
	{
	    if (sr[1] == 1)
		{
			cout << "Player win!";
		}
		else
    	{
    		cout << "Computer" << st[2] << " win!";
		}
    }
}
int main()
{
	
	flag = true;
	cin >> n;
	N = n;
	memset(st,true,sizeof(st));
	if (n == 1)
	{
		cout << "** Jackpot game **\n";
		cout << "The goal of this game is to guess a number.\n";
		cout << "Jackpot will tell you if the number is too big or too\n";
		cout << "small compared to the secret number to find.\n\n";
		Start();
		return 0;
	}
	while (n > 2)
	{
		memset(colour,-1,sizeof(colour));
		cout << endl << "Black and white back, boys and girls back, back, left back right back together!" << endl;
		//黑白背，男生女生背，左背右背，大家一起背！ 
		if (st[1]) cin >> colour[1];
		computer();
		for (int i = 1;i <= N;i++) 
		{
			cout << colour[i];
		}
		judge();
		if (res < 2)
		{
			memset(sr,0,sizeof(sr));
			for (int i = 1;i <= N;i++)
			{
				if (st[i])
				{
					if (colour[i] == res)
					{
						if (step[i] == 4)
						{
							if (i == 1 && st[i])
							{
								cout << "Direction?" << endl;
								cannot = false;
								while (cannot)
								{
									cin >> setl[1];
									cannot = true;
									for (int l = 2;l <= N;l++)
									{
										if (setl[1] == setl[l] || !st[setl[1]])
										{
											cannot = false;
											break;
										}
									}
								}
							}
							else
							{
								cannot = false;
								while (cannot)
								{
									srand((unsigned)time(NULL));
									setl[i] = rand() % n;
									for (int l = 1;l <= N;l++)
									{
										if (i != l)
										{
											if (setl[i] == setl[l] || !st[setl[i]])
											{
												cannot = false;
												break;
											}
										}
										
									}
								}							
							}
						}
						step[i]++;
						sr[i] = 1;
					}
				}
				
			}
			for(int i = 1;i <= N;i++)
			{
				if (st[i])
				{
					cnt[step[i]]++;
				}
			}
			if (cnt[4] > 1)
			{
				for (int i = 1;i <= N;i++)
				{
					if (step[i] == 4 && st[i]) 
					{
						exi(i);
					}
				}
			}
			for (int i = 1;i <= N;i++)	
			{
				if (st[i])
				{
					flag = false;
					int cn = 1;
					for (int l = 1;l <= N;l++)
					{
						if (st[i] == false)
						{
							continue;
						}
						if (i == setl[l])
						{
							flag = true;
							break;
						}
						cn++;
					}
					if(flag == false) 
					{
						cn = 0;
					}
					if (cn > 0 || setl[cn] == i)
					{
						if (st[i])
						{
							if(setl[cn] == i) 
							{
								if (cn + i >= 8)
								{
									if (sr[cn] == 1 && sr[i] == 1)
									{
										exi(cn);
										exi(i);
									}
									else
									{
										if (sr[cn] == 1)
										{
											exi(i);
										}
										if (sr[i] == 1)
										{
											exi(cn);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	int m = 0,tmp,ai;
	int list1[3] = {0,2,5};
	if (st[1] && n == 2)
	{
		while(n > 1)
		{
			cout << endl << "Stone scissors cloth!" << endl;
			cin >> tmp;
			memset(cnt,0,sizeof(cnt));
			memset(sr,0,sizeof(sr));
			//石头剪刀布！
			for (int i = 1;i <= m;i++)
			{
				cnt[player[i]]++;
			}
			m++;
			player[m] = tmp;
			if (player[m] != 0 && player[m] != 2 && player[m] != 5) 
				continue;
			if (cnt[2] > cnt[0] && cnt[2] > cnt[5])
			{
				ai = 5;
			}
			else
			{
				if (cnt[5] > cnt[0] && cnt[5] > cnt[2])
				{
					ai = 0;
				}
				else
				{
					ai = 2;
				}
			}
			compare(player[m],ai);
		}
	}
	else
	{
		if (n == 2)
		{
			int comput1,comput2;
			while (n > 1)
			{
				memset(sr,0,sizeof(sr));
				cout << endl << "Stone scissors cloth!" << endl;
				srand((unsigned)time(NULL)); 
				comput1 = list1[rand() % 3];
				srand((unsigned)time(NULL)); 
				comput2 = list1[rand() % 3];
				compare(comput1,comput2);
			}
		}
	}	
}
