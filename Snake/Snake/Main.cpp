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
			if (i == 0)
				cout << "a";
			else if (i == dim - 1)
				cout << "b";
			else if(j == 0)
				cout << "c";
			else if (j == dim - 1)
				cout << "d";
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