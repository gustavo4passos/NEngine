#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "src/Game.h"

const int WINDOW_WIDTH = 1366;
const int WINDOW_HEIGHT = 768;

int main(int argc, char** args)
{
  srand(time(NULL));
  Game game("NEngine", WINDOW_WIDTH, WINDOW_HEIGHT, 3, 2, false, true);
  game.run();
  return 0;
}
