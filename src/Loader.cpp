#include "Loader.h"
#include <stdio.h>
#include <stdlib.h>
#include "../tinyxml/tinyxml.h"
#include "../tinyxml/tinystr.h"
#include "Background.h"
#include "GraphicEngine.h"
#include "Player.h"
#include "Layer.h"
#include "Shader.h"
#include "Tileset.h"
#include "World.h"

// Starts static instance as 0 so the singleton can be instantiated later
Loader* Loader::_instance = 0;

void Loader::loadConfig(const char* file, std::string elementName, std::vector<std::string> attributes, std::vector<int>* data)
{
  // Open XML file
  TiXmlDocument xmlFile(file);
  // Checks if it opened successfully
  bool success = xmlFile.LoadFile();
  if(!success)
  {
    printf("LOADER ERROR: Unable to load XML file ('%s'). Error: %s\n", xmlFile.ErrorDesc());
  }
  else
  {
    TiXmlElement* root = xmlFile.RootElement();
    TiXmlElement* elementImLookingFor = NULL;
    for(TiXmlElement* e = root->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
      if(e->Value() == elementName)
      {
        elementImLookingFor = e;
        break;
      }
    }

    if(elementImLookingFor == NULL)
    {
      printf("LOADER ERROR: Unable to find element('%s').", elementName);
    }

    else
      {
      TiXmlElement* dataElement = elementImLookingFor->FirstChildElement();
      for(int i = 0; i < attributes.size(); i++)
      {
        int value;
        dataElement->Attribute(attributes[i], &value);
        data->push_back(value);
      }
    }
  }
}

Player* Loader::loadPlayer(const char* file)
{
  TiXmlDocument doc(file);
  bool success = doc.LoadFile();
  if(!success)
  {
    printf("LOADER ERROR: Unable to open XML file ('%s'). Erorr: %s\n", file, doc.ErrorDesc());
    return NULL;
  }
  else
  {
    TiXmlElement* root = doc.RootElement();
    TiXmlElement* playerElement = NULL;
    for(TiXmlElement* e = root->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
      if(e->Value() == std::string("HERO"))
      {
        playerElement = e;
        break;
      }
    }

    // Gets the data element
    TiXmlElement* data = playerElement->FirstChildElement();

    // Retrieve data
    const char* sprite = data->Attribute("sprite");
    int x, y, width, height, framesx, framesy;
    float speed;
    data->Attribute("x", &x);
    data->Attribute("y", &y);
    data->Attribute("width", &width);
    data->Attribute("height", &height);
    data->QueryFloatAttribute("speed", &speed);
    data->Attribute("framesx", &framesx);
    data->Attribute("framesy", &framesy);

    // Creates and return player based on data
    Player* player = new Player(sprite, x, y, width, height, speed, framesx, framesy);
    return player;
  }
}

Background* Loader::loadBackground(const char* file, Shader* shader)
{
    TiXmlDocument doc(file);
    bool success = doc.LoadFile();
    if(!success)
    {
      printf("LOADER ERROR: Unable to open XML file ('%s'). Erorr: %s\n", file, doc.ErrorDesc());
      return NULL;
    }
    else
    {
      TiXmlElement* root = doc.RootElement();
      TiXmlElement* bgElement = NULL;
      for(TiXmlElement* e = root->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
      {
        if(e->Value() == std::string("BACKGROUND"))
        {
          bgElement = e;
          break;
        }
      }

      if(bgElement == NULL)
      {
        printf("LOADER ERROR: Unable to find BACKGROUND element in %s. Returning NULL.\n", file);
        return NULL;
      }

      // Gets the data element
      TiXmlElement* data = bgElement->FirstChildElement();

      // Retrieve data
      const char* file = data->Attribute("file");
      int width, height;
      data->Attribute("width", &width);
      data->Attribute("height", &height);

      // Creates and return player based on data
      Background* background = new Background(file, shader, width, height);
      return background;
    }
}

Tileset* Loader::loadTileset(const char* tsxFile)
{
  TiXmlDocument doc(tsxFile);
  bool success = doc.LoadFile();
  if(!success)
  {
    printf("LOADER ERROR: Unable to load tileset from tmx file. Path: %s\nError: %s\n", tsxFile, doc.ErrorDesc());
    return NULL;
  }
  else
  {
    TiXmlElement* root = doc.RootElement();

    std::string name;
    int tileWidth, tileHeight, columns;

    root->QueryStringAttribute("name", &name);
    root->QueryIntAttribute("tilewidth", &tileWidth);
    root->QueryIntAttribute("tileheight", &tileHeight);
    root->QueryIntAttribute("columns", &columns);

    std::string source;
    int width, height;

    TiXmlElement* imageElement = root->FirstChildElement();

    imageElement->QueryStringAttribute("source", &source);
    imageElement->QueryIntAttribute("width", &width);
    imageElement->QueryIntAttribute("height", &height);

    return new Tileset(source.c_str(), name.c_str(), width, height, tileWidth, tileHeight, columns);
  }
}

Layer* Loader::loadLayer(TiXmlElement* layerElement, Tileset* tileset)
{
  std::string layerName;
  int width;
  int height;

  // Retrieve layer attributes
  layerElement->QueryStringAttribute("name", &layerName);
  layerElement->QueryIntAttribute("width", &width);
  layerElement->QueryIntAttribute("height", &height);

  // Search for the layer data in a string
  TiXmlNode* dataNode;
  for(TiXmlElement* e = layerElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
  {
    if(e->Value() == std::string("data"))
    {
      dataNode = e->FirstChild();
      break;
    }
  }
  TiXmlText* dataNodeText = dataNode->ToText();
  std::string data = dataNodeText->Value();

  // Stores position of the character in the string
  std::size_t foundAt = 0;
  std::size_t previous = 0;

  std::vector<GLfloat> vbodata;
  std::vector<GLuint> ebodata;

  // Reference for ebo
  int index = 0;

  for(int i = 0; i < height; i++)
  {
    for(int j = 0; j < width  ; j++)
    {
      previous = foundAt;
      foundAt = data.find(",", foundAt + 1);
      std::string id("");

      if(int(previous == 0))
      {
        id = data.substr(previous, foundAt - previous);
      }
      else if(int(foundAt) < 0)
      {
        id = data.substr(previous + 1, data.size() - previous);
      }
      else
      {
        id = data.substr(previous + 1, foundAt - previous - 1);
      }

      int tile = atoi(id.c_str());

      // Empty tile
      if(tile == 0)
      {
        continue;
      }

      // Position of the tile in the tileset
      float tilex, tiley;
      tilex = (tile - 1) % tileset->columns(); // We subtract because the first index is 1
      tiley = (tile - 1) / tileset->columns();
      // Helps find the tex coordinate of the tile
      float stridex, stridey;
      stridex = 1.f / tileset->columns();
      stridey = 1.f / tileset->rows();

      // Decides the position of the vertex based on the tileset and layer information
      GLfloat vertices[] =
      {
        tileset->tileWidth() * j                         , tileset->tileHeight() * i                             , stridex * tilex            , stridey * tiley,
        (tileset->tileWidth() * j) + tileset->tileWidth(), tileset->tileHeight() * i                             , (stridex * tilex) + stridex, stridey * tiley,
        (tileset->tileWidth() * j) + tileset->tileWidth(), (tileset->tileHeight() * i) + tileset->tileHeight()   , (stridex * tilex) + stridex, (stridey * tiley) + stridey,
        tileset->tileWidth() * j                         , (tileset->tileHeight() * i) + tileset->tileHeight()   , stridex * tilex            , (stridey * tiley) + stridey
      };

      // Create index data (4 indices per tile)
      GLuint indices[] = { index, index + 1, index + 2, index + 2, index + 3, index };
      index += 4;

      // Insert tile data into the end of the array
      vbodata.insert(vbodata.end(), vertices, vertices + 16);
      ebodata.insert(ebodata.end(), indices, indices + 6);
    }
  }

  // Upload the data to the ebo and vbo
  GLuint vao, vbo, ebo;
  vao = GraphicEngine::instance()->loadVao();
  vbo = GraphicEngine::instance()->loadToVbo(&vbodata[0], sizeof(GLfloat) * vbodata.size());
  ebo = GraphicEngine::instance()->loadToEbo(&ebodata[0], sizeof(GLuint) * ebodata.size());

  // Enable vertex array attribs
  GraphicEngine::instance()->staticShader()->vertexAttribPointer("position", 2, 4, 0);
  GraphicEngine::instance()->staticShader()->vertexAttribPointer("texcoord", 2, 4, 2);

  // Return freshly created layer
  Layer* layer = new Layer(width, height, layerName.c_str(), vao, vbo, ebo, ebodata.size());
  return layer;
}

void Loader::loadCollisionLayer(TiXmlElement* objectGroupElement, World* world)
{
  for(TiXmlElement* e = objectGroupElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
  {
    float id, x, y, width, height;
    e->QueryFloatAttribute("id", &id);
    e->QueryFloatAttribute("x", &x);
    e->QueryFloatAttribute("y", &y);
    e->QueryFloatAttribute("width", &width);
    e->QueryFloatAttribute("height", &height);

    Box box = { id, x, y, x + width, y + height, width, height };
    world->addCollisionBox(box);
  }
}

World* Loader::loadWorld(const char* loadFile)
{

  TiXmlDocument loadFileDoc(loadFile);
  bool loadFileLoaded = loadFileDoc.LoadFile();
  if(!loadFileLoaded)
  {
    printf("LOADER ERROR: Unable to load world config file. File: %s Error: %s\n", loadFile, loadFileDoc.ErrorDesc());
    return NULL;
  }
  else
  {
    TiXmlElement* configRoot = loadFileDoc.RootElement();
    TiXmlElement* mapElement = NULL;

    for(TiXmlElement* e = configRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("MAP"))
        {
          mapElement = e;
          break;
        }
    }

    // If the Map element wasn't found, return NULL
    if(mapElement == NULL)
    {
      printf("LOADER ERROR: Unable to find map element on config file. File: %s\n", loadFile);
      return NULL;
    }
    else
    {
      TiXmlElement* mapFileData = mapElement->FirstChildElement();
      std::string tmxFile;
      mapFileData->QueryStringAttribute("file", &tmxFile);

      // If the string is empty, the path of the tmx file could not be found
      if(tmxFile == "")
      {
        printf("LOADER ERROR: Unable to find map file path in xml config file! File: %s\n", tmxFile);
        return NULL;
      }
      else
        {
        TiXmlDocument doc(tmxFile);
        bool success = doc.LoadFile();

        if(!success)
        {
          printf("LOADER ERROR: Unable to load world. File: %s Error: %s\n", tmxFile.c_str(), doc.ErrorDesc());
          return NULL;
        }
        else
        {
          TiXmlElement* root = doc.RootElement();

          Tileset* tileset;
          World* world;
          std::string tilesetFile;

          // Gather map info
          int width, height, tileWidth, tileHeight;
          root->QueryIntAttribute("width", &width);
          root->QueryIntAttribute("height", &height);
          root->QueryIntAttribute("tilewidth", &tileWidth);
          root->QueryIntAttribute("tileheight", &tileHeight);

          // Search for the tileset source on the tmx file
          for(TiXmlElement* e = root->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
          {
            if(e->Value() == std::string("tileset"))
            {
              e->QueryStringAttribute("source", &tilesetFile);
            }
          }

          // Load tileset from tsx file
          tileset = loadTileset(tilesetFile.c_str());

          // Use the tileset to create world
          world = new World(tileset, width, height, tileWidth, tileHeight);

          // Load and add layers
          for(TiXmlElement* e = root->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
          {
            if(e->Value() == std::string("layer"))
            {
              // Check if the layer has any properties
              if(e->FirstChildElement()->Value() == std::string("properties"))
              {
                TiXmlElement* layerProperties = e->FirstChildElement();
                for(TiXmlElement* properties = layerProperties->FirstChildElement(); properties != NULL; properties = properties->NextSiblingElement())
                {
                  if(properties->Attribute("value") == std::string("overlay"))
                  {
                    world->addOverlayLayer(loadLayer(e, tileset));
                  }
                }
              }
              else
              {
                world->addLayer(loadLayer(e, tileset));
              }
            }
            else if(e->Value() == std::string("objectgroup"))
            {
              std::string checkAttribute;
              e->QueryStringAttribute("name", &checkAttribute);
              if(checkAttribute == "Collision layer")
              {
                loadCollisionLayer(e, world);
              }
            }
          }

          // Return freshly build world
          return world;
        }
      }
    }
  }
}
