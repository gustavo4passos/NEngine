#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <vector>
#include <string>

class XMLParser
{
public:
  static XMLParser* instance()
  {
    if(_instance == 0)
    {
      _instance = new XMLParser;
    }
    return _instance;
  }
  void getAttributes(std::string file, std::string elementName, std::vector<std::string> attributes, std::vector<int>* data);
  
private:
  static XMLParser* _instance;
};

#endif
