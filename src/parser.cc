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

XmlNode* Parser::parse() {
    parseDeclaration();
    parseDeclaration();
    return parseElement();
}

XmlNode* Parser::parseElement() {
    XmlNode* node = new XmlNode;

    skipSpace();
    if (_string[_index] == '<' && (isalnum(_string[_index + 1]) || _string[_index + 1] == '_')) {
        //parse name
        _index++;
        int pos = _index;
        while (isalnum(_string[_index]) ||
            _string[_index] == '-' ||
            _string[_index] == '_')
        {
            _index++;
        }
        std::string str = _string.substr(pos, _index - pos);
        node->setName(str);
        skipSpace();
    }
    //parse attr
    if (_string[_index] == '_' || isalnum(_string[_index])) {
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
        _index++;
        skipSpace();
        int pos = _index;
        while (_string[_index] != '<') {
            _index++;
        }
        std::string str = _string.substr(pos, _index - pos);
        node->setText(str);
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
        _index++;

    }
    else {
        while (_string[_index + 1] != '/') {
            node->addSubNode(parseElement());
            skipSpace();
        }
        if (_string[_index + 1] == '/') {
            _index++;
            while (_string[_index] != '\0' && _string[_index] != '>') {
                _index++;
            }
            _index++;
        }
        skipSpace();
    }
    return node;
}

void Parser::skipSpace() {
    while (_string[_index] != '\0' && (_string[_index] == ' ' ||
        _string[_index] == '\n' ||
        _string[_index] == '\r' ||
        _string[_index] == '\t'))
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