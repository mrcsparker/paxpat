#pragma once

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
        
        void parseFile(const std::string& filename) {
            const size_t BUFFER_SIZE = 255;
            
            FILE* fd = fopen(filename.c_str(), "r");
            if (fd == NULL) {
                throw std::runtime_error("File does not exist");
            }
            
            for (;;) {
                void *buffer = XML_GetBuffer(parser, BUFFER_SIZE);
                if (buffer == NULL) {
                    throw std::runtime_error("out of memory");
                }
                
                int bytes_read = static_cast<int>(fread(buffer, 1, BUFFER_SIZE, fd));
                if (bytes_read < 0) {
                    throw std::runtime_error("error reading file");
                }
                
                if (!XML_ParseBuffer(parser, bytes_read, bytes_read == 0)) {
                    throw std::runtime_error("could not parse buffer");
                }
                
                if (bytes_read == 0) {
                    break;
                }
            }
            fclose(fd);
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