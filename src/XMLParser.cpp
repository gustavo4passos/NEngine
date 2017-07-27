#include "XMLparser.h"
#include <stdio.h>
#include "../tinyxml/tinyxml.h"
#include "../tinyxml/tinystr.h"

// Declares only instance
XMLParser* XMLParser::_instance = 0;

void XMLParser::getAttributes(std::string file, std::string elementName, std::vector<std::string> attributes, std::vector<int>* data)
{
  // Open XML file
  TiXmlDocument xmlFile(file.c_str());
  // Checks if it opened successfully
  bool success = xmlFile.LoadFile();
  if(!success)
  {
    printf("XML PARSER ERROR: Unable to load XML file ('%s'). Error: %s\n", xmlFile.ErrorDesc());
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
      printf("XML PARSER ERROR: Unable to find element('%s').", elementName);
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
