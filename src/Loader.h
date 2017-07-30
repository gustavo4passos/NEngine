#ifndef LOADER_H
#define LOADER_H

#include <string>
#include <vector>

class Background;
class Hero;
class Layer;
class Shader;
class Tileset;
class TiXmlElement;
class World;

class Loader
{
public:
  static Loader* instance()
  {
    if(_instance == 0)
    {
        _instance = new Loader();
    }
  }

  Loader(){}

  // Load config data from a XML file using attributes in a string vector, and stores into a vector<int>
  // The position of the data inside the final vector will be relative to the attributes vector
  // Ex: If the string vector position [2] is "width", the vector<int> data[2] will store the attribute
  void loadConfig(const char* file, std::string elementName, std::vector<std::string> attributes, std::vector<int>* data);

  // Load a hero object from a xml file
  Hero* loadHero(const char* file, Shader* shader);

  // Load a Background image from a xml file
  Background* loadBackground(const char* file, Shader* shader);

  // Load World
  Tileset* loadTileset(const char* tsxFile);
  Layer* loadLayer(TiXmlElement* layerElement, Tileset* tileset, Shader* shader);
  World* loadWorld(const char* tmxFile, Shader* shader);

private:
  static Loader* _instance;
};

#endif
