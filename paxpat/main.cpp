#include <iostream>
#include <fstream>
#include "Expat.hpp"

using namespace std;
using namespace paxpat;

int main(int argc, const char * argv[]) {
    
    Expat e;
    
    e.elementHandler("author", [](Expat& a) -> void {
        cout << "author name: " << a.text() << endl;
    });
    e.elementHandler("title", [](Expat& a) -> void {
        cout << "title name: " << a.text() << endl;
    });
    e.elementHandler("genre", [](Expat& a) -> void {
        cout << "genre name: " << a.text() << endl;
    });
    e.parseFile("books.xml");
    
    
    return 0;
}
