#include <iostream>

using namespace std;

void PrintMatrixClockwisely(int **numbers, int columns, int rows)
{
	int x = 0;
	int y = 0;
	
	while(1)
	{
		for(int i=0;i<columns;i++)
			cout<<numbers[y][x++]<<" ";
		rows--;
		x--;
		y++;
		if(rows<=0)
			break;
		
		for(int i=0;i<rows;i++)
			cout<<numbers[y++][x]<<" ";
		columns--;
		y--;
		x--;
		if(columns<=0)
			break;
		
		for(int i=0;i<columns;i++)
			cout<<numbers[y][x--]<<" ";
		rows--;
		x++;;
		y--;
		if(rows<=0)
			break;
		
		for(int i=0;i<rows;i++)
			cout<<numbers[y--][x]<<" ";
		columns--;
		y++;
		x++;
		if(columns<=0)
			break;
	}
}