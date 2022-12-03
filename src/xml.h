#pragma once

//#ifdef __XML_H__
//#define __XML_H__


#include <iostream>
#include <string>
#include <map>
#include <list>

class Xml {
    
};

class XmlNode {
public:
    XmlNode();
    XmlNode(const char* name);
    XmlNode(const std::string name);
    std::string getName() const;
    void setName(const std::string& name);
    std::string getText() const;
    void setText(const std::string& text);
    std::string getAttrs(const std::string& attrs) const;
    void setAttrs(const std::string& key, const std::string& value);
    void addSubNode(XmlNode *child);


    std::string toStr();
    void remove(const std::string& name);
    bool load(const std::string & filename);

    size_t getNameSize() {
        return _name->size();
    }
//private:
    std::string *_name;
    std::string *_text;
    std::map<std::string, std::string> *_attrs;
    std::list<XmlNode*> *_child;
    
};



//#endif __XML_H__