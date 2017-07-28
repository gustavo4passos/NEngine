#include "Loader.h"
#include <stdio.h>
#include "../tinyxml/tinyxml.h"
#include "../tinyxml/tinystr.h"
#include "Shader.h"
#include "Hero.h"

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

Hero* Loader::loadHero(const char* file, Shader* shader)
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
    TiXmlElement* heroElement = NULL;
    for(TiXmlElement* e = root->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
      if(e->Value() == std::string("HERO"))
      {
        heroElement = e;
        break;
      }
    }

    // Gets the data element
    TiXmlElement* data = heroElement->FirstChildElement();

    // Retrieve data
    const char* sprite = data->Attribute("sprite");
    int x, y, width, height, speed, framesx, framesy;
    data->Attribute("x", &x);
    data->Attribute("y", &y);
    data->Attribute("width", &width);
    data->Attribute("height", &height);
    data->Attribute("speed", &speed);
    data->Attribute("framesx", &framesx);
    data->Attribute("framesy", &framesy);

    // Creates and return hero based on data
    Hero* hero = new Hero(sprite, x, y, width, height, speed, shader, framesx, framesy);
    return hero;
  }
}
