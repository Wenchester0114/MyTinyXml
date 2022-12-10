#include <iostream>
#include "xml.h"
#include "parser.h"

using namespace std;
using namespace xml;

int main() {
    XmlNode root;
    root.load("./test.xml");
    cout << root.toStr();
    return 0;
} 