#include "parser.h"
#include <sstream>

using namespace xml;


XmlNode::XmlNode()
    : _name(nullptr)
    , _text(nullptr)
    , _attrs(nullptr)
    , _child(nullptr) {
}

XmlNode::XmlNode(const char* name)
    : _name(nullptr)
    , _text(nullptr)
    , _attrs(nullptr)
    , _child(nullptr) {
    _name = new std::string(name);
}

XmlNode::XmlNode(const std::string name)
    : _name(nullptr)
    , _text(nullptr)
    , _attrs(nullptr)
    , _child(nullptr) {
    _name = new std::string(name);
}

std::string XmlNode::getName() const {
    if (!_name) return "";
    return *_name; 
}

void XmlNode::setName(const std::string& str) {
    if (_name) delete _name; 
    _name = new std::string(str);
}

std::string XmlNode::getText() const {
    if (!_text) return "";
    return *_text; 
}

void XmlNode::setText(const std::string& str) {
    if (!_text) delete _text;
    _text = new std::string(str);
}

std::string XmlNode::getAttrs(const std::string& key) const {
    if (!_attrs) return "";
    return (*_attrs)[key];
}

void XmlNode::setAttrs(const std::string& key, const std::string& value) {
    if (!_attrs) _attrs = new std::map<std::string, std::string>(); 
    (*_attrs)[key] = value;
}

void XmlNode::addSubNode(XmlNode *child) {
        if (!_child) {
            _child = new std::list<XmlNode*>();
        }      
        _child->push_back(child);
}

std::string XmlNode::toStr() {
    if (!_name) throw std::logic_error("This is a empty node");
    std::ostringstream ss;
    ss << "<" << *_name;
    if (_attrs) {
        for (auto it = _attrs->begin(); it != _attrs->end(); it++) {
            ss << " " << it->first << "=\"" << it->second << "\"";  
        }
    }
    ss << ">";
    if (_text) ss << *_text; 
    if (_child) {
        
        for (auto it = _child->begin(); it != _child->end(); it++) {
            ss << (*it)->toStr();
        }
    } 
    ss << "</" << *_name << ">";
    return ss.str();
}

void XmlNode::remove(const std::string& name) {
    if (!_child) return;
    for (auto it = _child->begin(); it != _child->end(); it++) {
        if ((*it)->getName() == name) {
            it = _child->erase(it);
        } 
        else
        {
            it++;
        }   
    }
}

bool XmlNode::load(const std::string & filename)
{
    Parser p;
    if (!p.loadfile(filename))
    {
        return false;
    }
    *this = p.parse();
    return true;
}







