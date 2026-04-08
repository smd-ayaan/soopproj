//should be ncurses
#include<curses.h>
#include<cmath.h>


class SOOP
{
private:
	int width,height;
	WINDOW *rootWin, mainWin;
public:
	SOOP(int w, int h);

	clear();
	draw();

	put(int x, int y, char c);

	~SOOP();


};
