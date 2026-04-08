#include <iostream>
#include <cmath>
#include <curses.h>

const int HEIGHT = 20;
const int WIDTH = 80;

char screen_buffer[HEIGHT][WIDTH];

WINDOW *win, *mainWin;

struct vec2
{
	float x, y;
};

void clear_buffer();
void draw_buffer();
vec2 getCoords(vec2 ndc);

int main()
{
	int x, y;
	clear_buffer();
	win = initscr();
	getmaxyx(win, y, x);
	noecho();
	nodelay(win, TRUE);
	keypad(win, TRUE);
	mainWin = subwin(win, HEIGHT, WIDTH, (y-HEIGHT)/2, (x-WIDTH)/2);

	while(true)
	{
		if(getch()==27)
			break;

		const float radius = 0.5f;
		const float small_radius = 0.2f;
		vec2 centre = {0.0f, 0.0f};
		//vec2 light_source = {};

		for(int i = 1;i<361;i++)
		{
			float sinv = sin(i);
			float cosv = cos(i);
			vec2 pointOnCircle = {(sinv*radius)+centre.x, (cosv*radius)+centre.y};
			vec2 small_centre = pointOnCircle;

			//val in sys = max/2 * (NDC+1)

			for(int j = 1;j<361;j++)
			{
				float sinv = sin(j);
				float cosv = cos(j);
			
				vec2 small_pointOnCircle = {(sinv*small_radius)+small_centre.x, (cosv*small_radius)+small_centre.y}; 
				screen_buffer[(int)getCoords(small_pointOnCircle).y][(int)getCoords(small_pointOnCircle).x] = '*';
			}
		}



		draw_buffer();
	}
	endwin();
	return 0;
}

void clear_buffer()
{
	for (int i=0;i<HEIGHT;i++)
	{
		for (int j=0;j<WIDTH;j++)
		{
			screen_buffer[i][j]=' ';
		}
	}
}

void draw_buffer()
{
	for (int i=0;i<HEIGHT;i++)
	{
		for (int j=0;j<WIDTH;j++)
		{
			mvwaddch(mainWin, i, j, screen_buffer[i][j]);
		}
	}
	wrefresh(mainWin);
}

vec2 getCoords(vec2 ndc)
{
	vec2 coords = {(WIDTH/2)*(ndc.x+1), (HEIGHT/2)*(ndc.y+1)};
	return coords;
}