#include<iostream>

#include<soop.hpp>


int main()
{
	SOOP poos(10,10);

	poos.init();

	while(true)
        {
                if(getch()==27)
                        break;


	
		poos.put(5,5, 'x');

		poos.draw();
	}

	return 0;
}


