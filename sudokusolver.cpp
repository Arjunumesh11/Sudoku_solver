#include<iostream>
#include<fstream>
int spacecal();
int sudoku(int n, int x, int y);
int check(int num, int x, int y);
using namespace std;
int box[9][9] = { 0 };
int ans[9][9] = { 0 };
int main()
{
	ifstream fp("sudoku.txt");
	if (!fp) {
		cout << "Error, file couldn't be opened" << endl;
		return 1;
	}
	for (int row = 0; row < 9; row++) {  // stop loops if nothing to read
		for (int column = 0; column < 9; column++) {
			fp >> box[row][column];
			ans[row][column]= box[row][column];
			if (!fp) {
				cout << "Error reading file for element " << row << "," << column << endl;
				return 1;
			}
		}
	}
	int t = 0;
	int num = spacecal();
	//cout <<box[0][2] << "\n";
	//t = check(2, 5, 5);
	//cout << num<<"\n";
	t = sudoku(num, 0, 0);
	 //cout <<"\n"<< t << "\n";
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cout << box[i][j] << " ";
		}
		cout << "\n";
	}
	fp.close();
	return 0;
}
int spacecal()
{
	int count = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (box[i][j] == 0)
			{
				count++;
			}
		}
	}
	return count;
}
int check(int num, int x, int y)
{
	int r = 0, c = 0;
	r = x - x % 3;
	c = y - y % 3;

	//cout << "\nrow:" << r;
	//cout << "\ncol:" << c;

	for (int i = 0; i < 9; i++)            //row
	{
		if (num == box[x][i])
			return 0;
	}

	for (int i = 0; i < 9; i++)            //col
	{
		if (num == box[i][y])
			return 0;
	}
	int k = 0, j = 0;
	for (int i = 0; i < 9; i++)            //_box:
	{
		j = c + (i / 3);
		k = r + (i % 3);
		//cout <<"\n"<< box[k][j]<<" ";
		if (num == box[k][j])
			return 0;
	}
	return 1;
}
int sudoku(int n, int x, int y)
{
	if (n == 0)
		return 0;
	int k = 0,x_1=0,y_1=0;
	x_1 = x;
	y_1 = y;
	if (box[x][y] == 0)
	{
		for (int i = 1; i < 10; i++)
		{
			
			k = check(i, x, y);
			if (k == 1)
			{
				x_1 = x;
				y_1 = y;
				box[x][y] = i;
				if (x < 8)
				{
					x_1++;
				}
				else if ((x == 8) && (y < 8))
				{
					x_1 = 0;
					y_1++;
				}
				else if ((x == 8) && (y == 8))
				{
					return 0;
				}
				//cout << "::" << n;
				//cout << "**" << x_1 <<" "<< y_1;
				n = sudoku(n - 1, x_1, y_1);
			}
			if (n == 0)
			{
				return 0;
			}
		}
		box[x][y] = 0;
		return (n + 1);
	}
	else
	{
		if (x < 8)
			x_1++;
		else if ((x == 8) && (y < 8))
		{
			x_1 = 0;
			y_1++;
		}
		else if ((x == 8) && (y == 8))
			return 0;
		n = sudoku(n, x_1, y_1);
		return n;
	}
}