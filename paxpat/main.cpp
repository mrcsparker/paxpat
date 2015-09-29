#include <iostream>
#include <fstream>
#include "Expat.hpp"

using namespace std;
using namespace paxpat;

int main(int argc, const char * argv[]) {
    
    string xml = "<?xml version=\"1.0\"?><catalog><book id=\"bk101\"><author>Gambardella, Matthew</author><title>XML Developer's Guide</title></book></catalog>";
    
    Expat e;
    
    e.elementHandler("catalog", [](Expat& a) -> void {
        cout << "found catalog on line " << a.line() << endl;
    });
    e.elementHandler("author", [](Expat& a) -> void {
        cout << "found author on column " << a.column() << endl;
    });
    e.parseFile("books.xml");
    
    
    return 0;
}
