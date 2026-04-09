#include<iostream>
#include<unistd.h>
#include<ncurses.h>
#include<random>

#include<soop.hpp>

#include"RingBuffer/RingBuffer.hpp"

#define WIDTH 80
#define HEIGHT 24

#define FRAME_TIME 100000

struct pos
{
	int x,y;
};

bool operator==(pos a, pos b)
{
	if((a.x==b.x)&&(a.y==b.y))return true;
	else return false;
}






enum class Direction
{
	LEFT, RIGHT, UP, DOWN
};


int main()
{
	bool running, game_over;

	SOOP soop(WIDTH, HEIGHT);
	if(soop.init()>=0)
	{
		running = true;
		game_over = false;
	}
	else running = false;

	RingBuffer<pos> snake = RingBuffer<pos>(1716);

	snake.push({0, 0});
	snake.push({1, 0});
	snake.push({2, 0});

	pos apple = {WIDTH/2, HEIGHT/2};

	Direction dir = Direction::RIGHT;


	while(running)
	{
		pos head = snake.at(snake.getSize()-1);
		//pos head = snake.head();

		//move snake here
		switch (dir)
		{

			case Direction::RIGHT:
				head.x = head.x+1;
				if(head.x>=WIDTH-2) game_over = true;
				break;
			case Direction::LEFT:
				head.x = head.x-1;
				if (head.x<0) game_over = true;
				break;
			case Direction::UP:
				head.y = head.y-1;
				if (head.y<0) game_over = true;
				break;
			case Direction::DOWN:
				head.y = head.y+1;
				if (head.y>=HEIGHT-2) game_over = true;
				break;


		}

		for(int i=0;i<snake.getSize();i++)
		{
			if(snake.at(i)==head) game_over=true;
		}

		if(head==apple)
		{
			//generate new apple

			//seed
			std::random_device rd;
			//generator
			std::mt19937 gen(rd());

			std::uniform_int_distribution dist_a(0, WIDTH-3);
			std::uniform_int_distribution dist_b(0, HEIGHT-3);

			bool check;
			do {
				apple.x = dist_a(gen);
				apple.y = dist_b(gen);


				//check if apple is not in snake
				for(int i=0;i<snake.getSize();i++)
				{
					if(snake.at(i)==apple) check=false;
					else check = true;
				}


			}
			while(!check);

			snake.push(head);
		}


		snake.push(head);
		snake.pop();

		soop.clear();
		soop.draw();


		//render here
		int size = snake.getSize();
		for (int i=0;i<size;i++)
		{
			soop.put(snake.at(i).x+1, snake.at(i).y+1, '#');
		}
		soop.put( apple.x+1, apple.y+1, '@');




		soop.draw();

		//if size =1716----win!!


		if(game_over)
		{
			//do game over stuff
			running = false;
		}



		int key_pressed = getch();
		if (key_pressed==27) running=false;
		if ((key_pressed==KEY_UP) && (dir!=Direction::DOWN)) dir = Direction::UP;
		if ((key_pressed==KEY_DOWN) && (dir!=Direction::UP)) dir = Direction::DOWN;
		if ((key_pressed==KEY_RIGHT) && (dir!=Direction::LEFT)) dir = Direction::RIGHT;
		if ((key_pressed==KEY_LEFT) && (dir!=Direction::RIGHT)) dir = Direction::LEFT;

		usleep(FRAME_TIME);

	}


	return 0;
}
