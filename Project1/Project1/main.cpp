// zion_solution.cpp

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

#include "Game.h"
#include "Game.h"
#include "Arena.h"
#include "Arena.h"
#include "Previous.h"
#include "Previous.h"
#include "Player.h"
#include "Player.h"
#include "Robot.h"
#include "Robot.h"
#include "globals.h"
#include "globals.h"

// zion_solution.cpp

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;


//#include "Arena.h"
// #include "Player.h"
// #include "Previous.h"
// #include "globals.h"
// int main()
// {
// Arena a(2, 2);
// a.addPlayer(1, 1);
// a.player()->move(RIGHT);
// a.player()->stand();
// a.player()->move(DOWN);
// a.thePrevious().showPreviousMoves();
// }

int main()
{
      // Initialize the random number generator.  (You don't need to
      // understand how this works.)
    srand(static_cast<unsigned int>(time(0)));

      // Create a game
      // Use this instead to create a mini-game:   Game g(3, 3, 2);
    Game g(15, 18, 80);

      // Play the game
    g.play();
}
