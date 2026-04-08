#include <soop.hpp>
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