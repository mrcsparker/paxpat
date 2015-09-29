#include <iostream>
#include <map>
#include <expat.h>

using namespace std;

namespace paxpat {
    class Expat {
    public:

        Expat() {
            parser = XML_ParserCreate(NULL);
            if (!parser) {
                throw std::bad_alloc();
            }

            // pass ref from Expat(class) to the expat parser
            XML_SetUserData(parser, this);

            // callbacks for the elements handlers
            XML_SetElementHandler(parser, &Expat::startElement, &Expat::endElement);
        }

        ~Expat() {
            XML_ParserFree(parser);
        }

        long line() {
            return XML_GetCurrentLineNumber(parser);
        }

        long column() {
            return XML_GetCurrentColumnNumber(parser);
        }

        void parseString(string s) {
            int len = static_cast<int>(strlen(s.c_str()));
            XML_Parse(parser, s.c_str(), len, 1);
        }

        void elementHandler(string elementName, function<void(Expat& a)> call) {
            elementCallbacks[elementName] = call;
        }

    private:

        XML_Parser parser;

        static void startElement(void *data, const char *name, const char **atts) {

            if (static_cast<Expat *>(data)->elementCallbacks.find(name) !=
                    static_cast<Expat *>(data)->elementCallbacks.end()) {
                static_cast<Expat *>(data)->elementCallbacks.find(name)->second(*static_cast<Expat *>(data));
            }
        }

        static void endElement(void *data, const char *name) {

        }

        map<string, function<void(Expat& a)>> elementCallbacks;
    };
}