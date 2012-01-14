#include <stdlib.h>
#include <stdio.h>


#include <sys/types.h>
#include <unistd.h>

#include <curses.h>

//#include "player.h"
//#include "map.h"




int main(void) {
	
	pid_t pid;
	           
//	int ch;
	
	initscr();    // Start curses mode
	cbreak();		        // Line buffering disabled
	keypad(stdscr, TRUE);
	noecho(); 

	
	
	
	
	    /* Attempt to fork and check for errors */
	   
    if( (pid=fork()) == -1){
        fprintf(stderr,"Fork error. Exiting.\n");  // something went wrong 
        exit(1);
    }
	
	
	
	if(fork())
	{
	
		//pareant
		
		while(1)
		{
			//get_status();
			//fill_map();
		}
		
		//mvaddch(20, 20,'2');
		
		
   		//exit(1);
		//getch();	
		//exit(1);
    
    }
    else
    {
    	//child
    	/*
    	while((ch = getch()) != 113) //reads key's
		{	
			switch(ch)
			{	
				case KEY_LEFT:
					//call function 
					break;
				case KEY_RIGHT:
					//call function 
					break;
				case KEY_DOWN:
					//call function 
					break;
				case KEY_UP:
				//call function 
					break;
			}
		}
		*/
		
	
		
		
    	//refresh();			/* Print it on to the real screen */
		//getch();			/* Wait for user input */
		//endwin();			/* End curses mode		  */
    	//exit(1);
	}
	
	refresh();			/* Print it on to the real screen */
	endwin();			/* End curses mode		  */
    
    return (0);
}
