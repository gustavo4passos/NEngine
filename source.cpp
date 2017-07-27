#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "src/texture.h"
#include "src/Game.h"
#include "src/XMLParser.h"
#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"

using namespace std;

int main(int argc, char** args)
{
  SDL_Surface* test = IMG_Load("../resources/sprites/jumper.png");
  printf("Value: %i and SDL_PIXELFORMAT_RGBA32 is %i\n", test->format->format, SDL_PIXELFORMAT_RGBA32);
  vector<string> attributes;
  attributes.push_back(string("width"));
  attributes.push_back(string("height"));
  attributes.push_back(string("major_version"));
  attributes.push_back(string("minor_version"));
  attributes.push_back(string("fullscreen"));
  attributes.push_back(string("vsync"));
  vector<int> data;
  XMLParser::instance()->getAttributes("../data/config.xml", "CONFIG", attributes, &data);
  if(!data.size())
  {
    printf("Unable to load config file. Exiting.\n");
    return -1;
  }

  // Avoid resolutions higher than 1920x1080 or < 0
  data[0] = (data[0] > 1920 || data[0] < 1) ? 1366 : data[0];
  data[1] = (data[1] > 1920 || data[1] < 1) ? 768 : data[1];


  srand(time(NULL));
  Game game("NEngine", data[0], data[1], data[2], data[3], data[4], data[5]);
  game.run();
  return 0;
}
