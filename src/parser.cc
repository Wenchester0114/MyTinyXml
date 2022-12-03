#include <string>
#include <fstream>
#include <sstream>
#include "parser.h"

using namespace xml;
using namespace std;
Parser::Parser() : _string(""), _index(0) {

}
bool Parser::loadfile(const std::string& fileName) {
    
    std::ifstream fin(fileName);
    if (fin.fail()) {
        return false;
    }
    std::stringstream ss;
    ss << fin.rdbuf();
    _string = ss.str();
    _index = 0;
    return true;
}

XmlNode Parser::parse() {
    // // parse head
    // parseDeclaration();
    // //parse comment 
    // while (_string.compare(_index, 4, "<!--") == 0) {
    //     //parseComment();
    //     skipSpace();
    // }
    // //parse element 
    // parseElement();
}

XmlNode* Parser::parseElement() {
    XmlNode* node = new XmlNode;
    
    while (_string[_index] != '\0') {
        skipSpace();
        if (_string[_index] == '<' && (isalpha(_string[_index + 1]) || _string[_index + 1] == '_')) {
            //parse name
            _index++;
            int pos = _index;
            while (isalpha(_string[_index])    || 
                        _string[_index] == '-' || 
                        _string[_index] == '_') 
            {
                _index++;
            }
            //std::cout << _string.substr(pos, _index - pos) << std::endl;
            node->setName(_string.substr(pos, _index - pos));
            skipSpace();
        }
        //parse attr
        if (_string[_index] == '_' || isalpha(_string[_index])) {
            int pos = _index;
            while (_string[_index] != '=') {
                _index++;
            }
            std::string key = _string.substr(pos, _index - pos);
            _index += 2;
            pos = _index;
            while (_string[_index] != '"') {
                _index++;
            }
            
            std::string val = _string.substr(pos, _index - pos);
            node->setAttrs(key, val);
            _index++;
        }
        //parse text
        if (_string[_index] == '>') {
            skipSpace();
            int pos = _index;
            while (_string[_index] != '<') {
                _index++;
            }
            node->setText(_string.substr(pos + 1, _index - pos - 1));
            
        }
        //parse end of node 
        if (_string[_index] == '<' && _string[_index + 1] == '/') {
            _index++;
            int pos = _index;
            while (_string[_index] != '>') {
                _index++;
            }


            if (_string.compare(pos + 1, node->getNameSize(), node->getName()) != 0 || node->getNameSize() != _index - pos - 1) {
                throw std::logic_error("Parse error: The end of node name is diffent from node name.");
            }
        }
        else {
            node->addSubNode(parseElement());
        }
    }
    return node;
}

void Parser::skipSpace() {
    while (_string[_index] == ' '   || 
            _string[_index] == '\n' || 
            _string[_index] == '\r' ||
            _string[_index] == '\t') 
    { 
        _index++;
    }
}
bool Parser::parseDeclaration() {
    if (_string.compare(_index, 5, "<?xml") != 0) {
        return false;
    }//没找到
    _index += 5;
    size_t pos = _string.find("?>", _index);
    if (pos == std::string::npos) {
        return false;
    }
    _index = pos + 2;
    return true;


}
bool Parser::parseComment() {
    if (_string.compare(_index, 4, "<!--") != 0) {
        return false;
    }//没找到
    _index += 4;
    size_t pos = _string.find("-->", _index);
    if (pos == std::string::npos) {
        return false;
    }
    _index = pos + 3;
    return true;

}


std::string xml::Parser::parseElementName() {
    /*int pos = 0;
    if (_string[_index] == '<') {
        _index++;
        pos = _index;
        while (isalpha(_string[_index])) {
            _index++;
        }
    }
    return _string.substr(pos, _index - pos); */
    return "";
}
std::string Parser::parseElementText() {
    /* int pos = _index;
    if (_string[_index] == '>') {
        _index++;
        while (_string[_index] != '<') {
            _index++;
        }
    }
    return _string.substr(pos, _index - pos); */
    return "";
}
std::string Parser::parseElementNameAndAttrKey() {
    /* int pos = _index;
    while (isalpha(_string[_index])) {
        _index++;
    }
    return _string.substr(pos, _index - pos); */
    return "";
}
std::string Parser::parseElementAttrVal(){
    /* int pos = _index;
    if (_string[_index] == '"') {
        _index++;
        while (_string[_index] != '"') {
            _index++;
        }
    }
    return _string.substr(pos, _index - pos); */
    return "";
}



