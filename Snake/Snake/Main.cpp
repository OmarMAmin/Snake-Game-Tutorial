#include <iostream>

using namespace std;

#define dim 20
// preprocessing step

enum Direction { left = 0, right = 1,up = 2,down = 3 };

struct Node
{
	int x;
	int y;
	Direction dir;
};

struct Snake
{
	Node nodes[400];
	int size;
};

struct WorldOfSnake
{
	Snake snake;
	bool gameover;
	char world[dim][dim];
};



void InitializeSnake(Snake & snk);

void SnakeDraw();

void InitializeWorldOfSnake(WorldOfSnake & wofsnk);

void AddSnakeToTheWorld(WorldOfSnake & wofsnk);


void InitializeWorld(char world[dim][dim]);

void DrawWorld(WorldOfSnake w);

void MoveSnakeToTheRight(Snake & snake);

int main()
{
	WorldOfSnake w;
	char choice = 's';
	InitializeSnake(w.snake);
	while (choice == 's')
	{
		system("cls");
		cin.clear();
		InitializeWorldOfSnake(w);
		DrawWorld(w);
		cout << endl << endl << "Enter s to move anything else to exit"<<endl;
		cin >> choice;
		MoveSnakeToTheRight(w.snake);
	}
	system("pause");
	return 0;
}


void MoveSnakeToTheRight(Snake & snake)
{
	for (size_t i = 0; i < snake.size; i++)
	{
		snake.nodes[i].y++;
		// if snake moved to the right wall
		if (snake.nodes[i].y == dim - 1)
			// make it the first 
			snake.nodes[i].y = 1;
	}
}


void InitializeWorldOfSnake(WorldOfSnake & wofsnk)
{
	InitializeWorld(wofsnk.world);
	AddSnakeToTheWorld(wofsnk);
}

void AddSnakeToTheWorld(WorldOfSnake & wofsnk)
{
	int size = wofsnk.snake.size;
	for (int i = 0; i < size; i++)
	{
		int x = wofsnk.snake.nodes[i].x;
		int y = wofsnk.snake.nodes[i].y;
		wofsnk.world[x][y] = '*';
	}
}

void DrawWorld(WorldOfSnake w)
{
	for (size_t i = 0; i < dim; i++)
	{
		for (size_t j = 0; j < dim; j++)
		{
			cout << w.world[i][j];
		}
		cout << endl;
	}
}

void InitializeWorld(char world[dim][dim])
{
	for (int i = 0;i < dim;i++)
	{
		for (int j = 0; j < dim; j++)
		{

			// when to draw boundary
			if (i == 0 || i == dim - 1 || j == 0 || j == dim - 1)
				world[i][j] = '#';
			// when to draw space 
			else
				world[i][j] = ' ';
		}
		
	}
}

void InitializeSnake(Snake & snk)
{
	snk.size = 3;
	int initial_y = 8;
	for (size_t i = 0; i < snk.size; i++)
	{
		snk.nodes[i].x = 9;
		snk.nodes[i].y = initial_y++;
	}
}

void SnakeDraw()
{
	for (int i = 0;i < dim;i++)
	{
		for (int j = 0; j < dim; j++)
		{

			// when to draw boundary
			if (i == 0 || i == dim - 1 || j == 0 || j == dim - 1)
				cout << "#";
			// when to draw snake
			else if (i == 9 && j == 8
				|| i == 9 && j == 9
				|| i == 9 && j == 10)
				cout << "*";
			// when to draw empty 
			else
				cout << " ";
		}
		cout << endl;
	}
}
