#include <soop.hpp>


SOOP::SOOP(int w, int h){
    buffer = new char*[w];

    for(int i=0;i<w;i++){
        buffer[i] = new char[h];
    }


    clear();
	rootWin = initscr();
	getmaxyx(rootWin, y, x);
	noecho();
	nodelay(rootWin, TRUE);
	keypad(rootWin, TRUE);
	mainWin = subwin(rootWin,height , width, (y-height)/2, (x-width)/2);
    
}

SOOP::put(int x, int y,char c){
    screen_buffer[y][x]=c;
}
SOOP::clear(){

	for (int i=0;i<height;i++)
	{
		for (int j=0;j<width;j++)
		{
			screen_buffer[i][j]=' ';
		}
	}

}
SOOP::draw(){
    for (int i=0;i<height;i++)
    {
        for (int j=0;j<width;j++)
        {
            mvwaddch(mainWin, i, j,buffer[i][j]);
        }
    }
    wrefresh(mainWin);
}


SOOP:~SOOP(){
    for(int i=0;i<w;i++){
        delete[] buffer[i];
    } delete[] buffer;
    endwin();
}

