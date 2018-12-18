
#include <iostream>
#include <string>

#include "TextTester.h"


using std::cout;
using std::endl;


int main(int argc, char* argv[]) {

    while (argc > 1) {
        switch (argv[--argc][0]) {
            case 'a':
            {
                TextTester t;
                t.testResize();
            }
                break;
            case 'b':
            {
                TextTester t;
                t.testReadText();
            }
                break;
            case 'c':
            {
                TextTester t;
                t.testAppendText();
            }
                break;
            case 'd':
            {
                TextTester t;
                t.testDeleteWordAll();
            }
                break;
            case 'e':
            {
                TextTester t;
                t.testGetWords();
            }
                break;
            case 'f':
            {
                TextTester t;
                t.testReplacePhraseFirst();
            }
                break;
            case 'g':
            {
                TextTester t;
                t.testContainsWord();
            }
                break;
            case 'h':
            {
                TextTester t;
                t.testWordCount();
            }
                break;
            case 'i':
            {
                TextTester t;
                t.testReplaceWordAll();
            }
                break;
            default:
            {
                cout<<"Options are a -- i."<<endl;
            }
                break;
        }
    }

    return 0;
}
