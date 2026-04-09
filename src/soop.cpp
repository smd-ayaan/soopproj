#include <soop.hpp>


SOOP::SOOP(int w, int h){



	width=w;height=h;

	buffer = new char*[h];

	for(int i=0;i<h;i++)
	{
		buffer[i] = new char[w];
	}

	clear();


    
}

int SOOP::init()
{

	rootWin = initscr();


	int win_x, win_y;
	getmaxyx(rootWin, win_y, win_x);

	if (!(width<=win_x && height<=win_y))
		return -1;


	mainWin = subwin(rootWin, height, width, (win_y-height)/2, (win_x-width)/2);

	noecho();
	nodelay(rootWin, TRUE);
	keypad(rootWin, TRUE);

	return 0;

}

void SOOP::put(int x, int y,char c){
	if(x>width || y>height)
		return;

    buffer[y][x]=c;
}

void SOOP::clear(){

	for (int i=0;i<height;i++)
	{
		for (int j=0;j<width;j++)
		{
			buffer[i][j]=' ';
		}
	}

}
void SOOP::draw(){
    for (int i=0;i<height;i++)
    {
        for (int j=0;j<width;j++)
        {
            mvwaddch(mainWin, i, j,buffer[i][j]);
        }
    }
    wrefresh(mainWin);
}


SOOP::~SOOP(){
    for(int i=0;i<height;i++){
        delete[] buffer[i];
    }
    delete[] buffer;
    delwin(mainWin);
	endwin();
}

