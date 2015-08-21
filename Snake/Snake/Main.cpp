#include <iostream>

using namespace std;

#define dim 20
// preprocessing step

void SnakeDraw()
{
	for (int i = 0;i < dim;i++)
	{
		for (int  j = 0; j < dim; j++)
		{
			// when to draw the boundary
			if (i == 0 || i == dim - 1 || j == 0 || j == dim - 1)
				cout << "#";
			else if (i == 9 && j == 8
				|| i == 9 && j == 9
				|| i == 9 && j == 10)
				cout << "*";
			else
				cout << " ";
		}
		cout << endl;
	}
}
int main()
{
	SnakeDraw();
	system("pause");
	return 0;
}