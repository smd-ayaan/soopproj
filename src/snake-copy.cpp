#include<iostream>
#include<unistd.h>
#include<ncurses.h>
#include<random>


#include"RingBuffer.hpp"

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

	int win_y, win_x;
	
	WINDOW* main_win = initscr();
	WINDOW* win = subwin(main_win, HEIGHT, WIDTH, 0, 0);
	
	getmaxyx(win, win_y, win_x);

	if (WIDTH<=win_x && HEIGHT<=win_y)
	{
		box(win, 0, 0);
		noecho();
		nodelay(main_win, TRUE);
		keypad(main_win, TRUE);
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

		wclear(win);
		box(main_win, 0, 0);

		//render here
		int size = snake.getSize();
		for (int i=0;i<size;i++)
		{
			mvwaddch(win, snake.at(i).y+1, snake.at(i).x+1, '#');
			mvwaddch(win, apple.y+1, apple.x+1, '@');
		}
		
		
		
		
		refresh();

		//if size =1716----win!!


		if(game_over)
		{
			//do game over stuff
			running = false;
		}
		
		
		
		//maybe should handle input before
		//handle input
		int key_pressed = getch();
		if (key_pressed==27) running=false;
		if ((key_pressed==KEY_UP) && (dir!=Direction::DOWN)) dir = Direction::UP;
		if ((key_pressed==KEY_DOWN) && (dir!=Direction::UP)) dir = Direction::DOWN;
		if ((key_pressed==KEY_RIGHT) && (dir!=Direction::LEFT)) dir = Direction::RIGHT;
		if ((key_pressed==KEY_LEFT) && (dir!=Direction::RIGHT)) dir = Direction::LEFT;

		usleep(FRAME_TIME);

	}

	delwin(win);
	delwin(main_win);
	endwin();
	return 0;
}
