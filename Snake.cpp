#include <iostream>
#include<conio.h>
#include <string>
#include<ctime>
#include<windows.h>
using namespace std;

//setup //draw //input //logic

bool gameover;
const int width = 20;
const int height = 20;
int x, y, fruitx, fruity, score;
short dir;//1=right;2=left;3=up;4=down;0=stop;
int tailx[100], taily[100];
int ntail;


void setup()
{

	gameover = false;
	dir = 0;
	x = width / 2;
	y = height / 2;
	srand(time(0));
	fruitx = rand() % width;
	fruity = rand() % height;
	score = 0;
}


void draw()
{
	system("cls"); //system("clear");
	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "O";
			else if (i == fruity && j == fruitx)
				cout << "F";
			else
			{
				bool print = false;
				for (int k = 0; k < ntail; k++)
				{
					if (tailx[k] == j && taily[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}


			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;
	cout << endl;
	cout << "\t\tScore:" << score << endl;
}



void input()
{
	if (_kbhit()) //return 1 or zero 
	{//one when a key is pressed
		switch (_getch())//return the asci value of the pressed key
		{
		case'a':
			dir = 2;
			break;
		case'd':
			dir = 1;
			break;
		case'w':
			dir = 3;
			break;
		case's':
			dir = 4;
			break;
		case'x':
			gameover = true;
			break;


		}
	}
}


void logic()
{
	int prevx = tailx[0];
	int prevy = taily[0];
	int prev2x, prev2y;
	tailx[0] = x;
	taily[0] = y;
	for (int i = 1; i < ntail; i++)
	{
		prev2x = tailx[i];
		prev2y = taily[i];
		tailx[i] = prevx;
		taily[i] = prevy;
		prevx = prev2x;
		prevy = prev2y;
	}
	//x & y are like a forth quarter but with both have positive signs
	switch (dir)
	{
	case 2://left
		x--;
		break;
	case 1://right
		x++;
		break;
	case 3://up
		y--;
		break;
	case 4://down
		y++;
		break;
	default:
		break;
	}
	//to end game when u hit the wall
/*	if (x > width || x<0 || y>height || y < 0)
	{
		gameover = true;
	}
	*/
	//to move through walls
	if (x >= width)x = 0; else if (x < 0)x = width - 1;
	if (y >= height)y = 0; else if (y < 0)y = height - 1;

	//to end game when u hit your tail
	for (int i = 0; i < ntail; i++)
	{
		if (tailx[i] == x && taily[i] == y)
		{
			//not working for some reason so I commented it

			/*short n;
			cout << "Play again??\n";
			cout << "1\ Yes            2\ No\n";
			cin >> n;
			if (n == 1)
			{
				setup();
				while (!gameover)
				{
					draw();
					input();
					logic();
					Sleep(100);
				}
			}
			else*/
				gameover = true;
		}
	}
	if (x == fruitx && y == fruity)
	{
		score += 10;
		fruitx = rand() % width;
		fruity = rand() % height;
		ntail += 3;
	}

}

int main()
{
	
	setup();
	while (!gameover)
	{
		draw();
		input();
		logic();
		Sleep(100);
	}

	return 0;
}
