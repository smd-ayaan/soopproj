//should be ncurses
#include<curses.h>
#include<cmath>


class SOOP
{
private:
	int width,height;
	WINDOW *rootWin, *mainWin;
	char **buffer;
public:
	SOOP(int w, int h);

	int init();

	void clear();
	void draw();

	void put(int x, int y, char c);

	~SOOP();


};
