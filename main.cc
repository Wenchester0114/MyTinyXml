#include <iostream>
#include "xml.h"
#include "parser.h"

using namespace std;
using namespace xml;

int main() {
    Parser p;
    p.loadfile("./test1.xml");
    XmlNode* x = p.parseElement();
    //cout << x->getName() << " "  << x->getAttrs("lang") << " " << x->getText() << endl;
    if (x->_child) {
        for (auto it = x->_child->begin(); it != x->_child->end(); it++) {
            cout << (*it)->getName() << " " << (*it)->getText() << endl;
        }
    }
    return 0;
} 