#include <iostream>
#include <conio.h>
#include <math.h>

using namespace std;

#define dim 20



enum Direction { left = 0, right = 1,up = 2,down = 3 };
#define LEFT Direction::left 
#define RIGHT Direction::right 
#define UP Direction::up 
#define DOWN Direction::down 

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

struct Food
{
	int x;
	int y;
	int timelefttodisappear;
};

struct World
{
	Snake snake;
	Food food[5];
	int foodcount;
	int score;
	bool gameover;
	char world[dim][dim];
};



void InitializeSnake(Snake & snk);

void SnakeDraw();

void InitializeWorldOfSnake(World & wofsnk);

void AddSnakeToTheWorld(World & wofsnk);

bool GeneratedOnSnake(Snake sn, int x, int y);
void InitializeWorld(char world[dim][dim]);

void DrawWorld(World w);

void MoveSnakeToTheRight(Snake & snake);

bool MoveSnake(Snake & snake,Direction direction);

void MoveNode(Node & node, Direction dir);

bool AreThereAnyCollisions(Snake snake);

void AddFoodToTheWorld(World & w);


Direction GetDirection(char choice)
{


	if (choice == 'a')
		return LEFT;
	else if(choice == 's')
		return DOWN;
	else if (choice == 'd')
		return RIGHT;
	else if (choice == 'w')
		return UP;
}

void MoveNodeNormally(Node & node);

void InitializeFood(World &w);

bool SnakeEatFood(World &w);
int main()
{
	World w;
	char choice = 's';
	InitializeSnake(w.snake);
	InitializeFood(w);
	bool gameover = false;
	while (!gameover)
	{
		system("cls");
		InitializeWorldOfSnake(w);
		DrawWorld(w);
		cout << endl << endl << "Enter a,s,d,w to move left,down,right,up respectively"<<endl;
		choice = _getch();
		while (choice != 'a' && choice != 's'
			&& choice != 'w' && choice != 'd')
		{
			cout << endl << "Not Valid Direction, Please Enter a,s,d,w only" << endl;
		}
		gameover = MoveSnake(w.snake,GetDirection(choice));
		if (SnakeEatFood(w))
			w.snake.size++;
	}
	system("pause");
	return 0;
}

bool SnakeEatFood(World &w)
{
	int headx = w.snake.nodes[0].x;
	int heady = w.snake.nodes[0].y;
	for (int i = 0; i < w.foodcount; i++)
	{
		if (headx == w.food[i].x
			&& heady == w.food[i].y)
		{
			
			w.food[i].timelefttodisappear = 1;
			w.score += 100;
			return true;
		}
	}
	return false;
}


void InitializeFood(World & w)
{
	w.foodcount = 0;
	w.score = 0;
}

void MoveNode(Node & node, Direction dir)
{
	node.dir = dir;
	MoveNodeNormally(node);
}

void MoveNodeNormally(Node & node)
{
	Direction dir = node.dir;
	if (dir == UP)
		node.x--;
	else if (dir == DOWN)
		node.x++;
	else if (dir == RIGHT)
		node.y++;
	else if (dir == LEFT)
		node.y--;
	// adjust node coordinates if it's on the wall
	if (node.x == 0)
		node.x = dim - 2;
	else if (node.x == dim - 1)
		node.x = 1;
	if (node.y == 0)
		node.y = dim - 2;
	else if (node.y == dim - 1)
		node.y = 1;
}

bool IsMovingInItsDirection(Direction input, Direction state)
{
	if (input == state
		|| input == UP && state == DOWN
		|| input == DOWN && state == UP
		|| input == RIGHT && state == LEFT
		|| input == LEFT && state == RIGHT)
		return true;
	else
		return false;
}

bool MoveSnake(Snake & snake, Direction direction)
{
	Direction HeadDirection = snake.nodes[0].dir;
	bool ShouldMoveNormally = IsMovingInItsDirection(direction, HeadDirection);
	int snakesize = snake.size;
	for (int i = snakesize;i > 0 ;i--)
	{
		// snake was     : ***>
		// snake will be :  ***>
		// moving each node from the tail to the node next to it in the snake
		snake.nodes[i].x = snake.nodes[i - 1].x;
		snake.nodes[i].y = snake.nodes[i - 1].y;
		snake.nodes[i].dir = snake.nodes[i - 1].dir;
	}
	if (ShouldMoveNormally)
	{
		// the head node will continue to move in its original direction
		MoveNodeNormally(snake.nodes[0]);
	}
	else
	{
		MoveNode(snake.nodes[0],direction);
	}

	return AreThereAnyCollisions(snake);
}

bool AreThereAnyCollisions(Snake snake)
{
	// collision happens only when the head hits anyother node
	int snakeheadX = snake.nodes[0].x;
	int snakeheady = snake.nodes[0].y;
	for (size_t i = 1; i < snake.size; i++)
	{
		if (snake.nodes[i].x == snakeheadX
			&& snake.nodes[i].y == snakeheady)
			return true;
	}
	// if no node collided with the snake head
	// then there're no collisions
	return false;
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

void AdjustFoodTime(World &w)
{
	// just simpler name
	int count = w.foodcount;


	for (int i = 0; i < count; i++)
	{
		w.food[i].timelefttodisappear--;
		if (w.food[i].timelefttodisappear == 0)
		{
			// remove it
			for (int j = i;j < count;j++)
			{
				// move the rest backword one step starting from i to the end;
				w.food[j].x = w.food[j + 1].x;
				w.food[j].y = w.food[j + 1].y;
				w.food[j].timelefttodisappear = w.food[j + 1].timelefttodisappear;
			}
			// you've deleted one item, so update the counters
			count--;
			// go back one food item as afte the iteration i++ will be executed and you don't want
			// to skip any items
			i--;
		}
	}
	w.foodcount = count;
}

void InitializeWorldOfSnake(World & wofsnk)
{
	InitializeWorld(wofsnk.world);
	AdjustFoodTime(wofsnk);
	AddSnakeToTheWorld(wofsnk);
	AddFoodToTheWorld(wofsnk);
}

void AddSnakeToTheWorld(World & wofsnk)
{
	int size = wofsnk.snake.size;
	for (int i = 0; i < size; i++)
	{
		int x = wofsnk.snake.nodes[i].x;
		int y = wofsnk.snake.nodes[i].y;
		wofsnk.world[x][y] = '*';
	}
}

void DrawWorld(World w)
{
	for (size_t i = 0; i < dim; i++)
	{
		for (size_t j = 0; j < dim; j++)
		{
			cout << w.world[i][j];
		}
		cout << endl;
	}
	cout << endl;
	cout << "\t\t\t Score : " << w.score;
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
	int initial_y = 10;
	for (size_t i = 0; i < snk.size; i++)
	{
		snk.nodes[i].x = 9;
		snk.nodes[i].y = initial_y--;
		snk.nodes[i].dir = RIGHT;
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

bool GeneratedOnSnake(Snake sn, int x, int y)
{
	for (size_t i = 0; i < sn.size; i++)
	{
		if (sn.nodes[i].x == x
			&& sn.nodes[i].y == y)
		{
			return true;
		}
	}
	return false;
}

void AddFoodToTheWorld(World &w)
{
	// Do we need to generate food ?
	int foodcount = w.foodcount;
	if (foodcount == 4)
		return;
	bool Generate = ((4 - foodcount) * (rand() % 10)) > 26; 
	if(Generate)
	{
		// rand() % (dim - 2) + 1   ==== random number between 1 and dim-1 (inside the world)
		int x = rand() % (dim - 2) + 1;
		int y = rand() % (dim - 2) + 1;
		// check if the generated food isn't part of the snake
		while (GeneratedOnSnake(w.snake, x, y))
		{
			x = rand() % (dim - 2) + 1;
			y = rand() % (dim - 2) + 1;
		}
		int headx = w.snake.nodes[0].x; // getting head x position
		int heady = w.snake.nodes[0].y; // getting head y position
		int distance = abs(headx-x) + abs(heady-y);
		
		int timetodisappear = distance + 1 + rand() % 5;  // rand()%5 to give space for any mistake on the way
		// accumelate on other food objects
		w.food[foodcount].x = x;
		w.food[foodcount].y = y;
		w.food[foodcount].timelefttodisappear = timetodisappear;
		w.foodcount++;
	}

	for (size_t i = 0; i < w.foodcount; i++)
	{
		int x = w.food[i].x;
		int y = w.food[i].y;
		w.world[x][y] = '$';
	}
}