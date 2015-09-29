#include <iostream>
#include <fstream>
#include "Expat.hpp"

using namespace std;
using namespace paxpat;

int main(int argc, const char * argv[]) {
    
    Expat e;
    
    e.elementHandler("author", [](Expat& a) -> void {
        cout << "author name: " << a.text() << endl;
        cout << "column number: " << a.column() << endl;
    }).elementHandler("title", [](Expat& a) -> void {
        cout << "title name: " << a.text() << endl;
    }).elementHandler("genre", [](Expat& a) -> void {
        cout << "genre name: " << a.text() << endl;
    }).parseFile("books.xml");
    
    
    return 0;
}
