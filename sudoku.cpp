#include <bits/stdc++.h>
using namespace std;
#define UNASSIGNED 0
#define N 9

/* Searches the grid to find an entry that is still unassigned. If found, the reference parameters row, col will be set the location that is unassigned, and true is returned. If no unassigned entries remain, false is returned. */
bool FindUnassignedLocation(int grid[N][N], int& row, int& col)
{
	for (row = 0; row < N; row++)
		for (col = 0; col < N; col++)
			if (grid[row][col] == UNASSIGNED)
				return true;
	return false;
}

// Checks whether it will be legal to assign num to the given row, col
bool isSafe(int grid[N][N], int row, int col, int num);

bool SolveSudoku(int grid[N][N])
{
	int row, col;
	if (!FindUnassignedLocation(grid, row, col))
		return true;
	for (int num = 1; num <= N; num++) 
	{
		if (isSafe(grid, row, col, num)) 
		{
			grid[row][col] = num;
			if (SolveSudoku(grid))
				return true;
			grid[row][col] = UNASSIGNED;
		}
	}
	// This triggers backtracking
	return false;
}

/* Returns a boolean which indicates whether an assigned entry in the specified row matches the given number. */
bool UsedInRow(int grid[N][N], int row, int num)
{
	for (int col = 0; col < N; col++)
		if (grid[row][col] == num)
			return true;
	return false;
}

/* Returns a boolean which indicates whether an assigned entry in the specified column matches the given number. */
bool UsedInCol(int grid[N][N], int col, int num)
{
	for (int row = 0; row < N; row++)
		if (grid[row][col] == num)
			return true;
	return false;
}

/* Returns a boolean which indicates whether an assigned entry within the specified 3x3 box matches the given number. */
bool UsedInBox(int grid[N][N], int boxStartRow, int boxStartCol, int num)
{
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			if (grid[row + boxStartRow][col + boxStartCol] == num)
				return true;
	return false;
}

/* Returns a boolean which indicates whether it will be legal to assign num to the given row, col location. */
bool isSafe(int grid[N][N], int row, int col, int num)
{
	return !UsedInRow(grid, row, num) && !UsedInCol(grid, col, num) && !UsedInBox(grid, row - row % 3, col - col % 3, num) && grid[row][col] == UNASSIGNED;
}

void printGrid(int grid[N][N])
{
	cout << "The solution is: " << endl;
	for (int row = 0; row < N; row++) 
	{
		for (int col = 0; col < N; col++)
        {
			cout << grid[row][col] << " ";
            if((col+1)%3==0 && col!=8)
            {
                cout << "| ";
            }
        }
		cout << endl;
        if((row+1)%3==0 && row!=8)
        {
            cout << "-----------------";
        }
        cout << endl;
	}
}

int main()
{
    cout << "Enter the elements of the sudoku row-wise: ";
	cout << endl;
	int grid[N][N];
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            cin >> grid[i][j];
        }
    }
	if (SolveSudoku(grid) == true)
		printGrid(grid);
	else
		cout << "No solution exists";
	return 0;
}