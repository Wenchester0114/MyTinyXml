#pragma once

#include "xml.h"
#include <string>


namespace xml {
class Parser {
public:
    Parser();
    bool loadfile(const std::string& fileName);
    XmlNode* parse();  
    std::string getString();

    void skipSpace();
    bool parseDeclaration();
    bool parseComment();
    XmlNode* parseElement();

private:
    std::string _string;
    size_t _index;

};
}
