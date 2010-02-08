
/* Simple program:  Create a blank window, wait for keypress, quit.

   Please see the SDL documentation for details on using the SDL API:
   /Developer/Documentation/SDL/docs.html
*/
   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "game.h"

int main(int argc, char *argv[])
{	
	Game game;
	
	bool done = false;
	while(!done) {
		done = game.updateGame();
	}
	
	return(0);
}
