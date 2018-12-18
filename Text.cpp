#include <iostream>
#include <string>

#include "Text.h"

using std::string;
using std::ostream;


void resize(string*& text, uint length, uint& capacity, uint new_capacity){

    text = new string[capacity];
    length = 0;
    string* temp;
    if (new_capacity >= capacity) {
        temp = new string[new_capacity];
        for (int i=0; i<capacity; i++) {
            temp[i] = text[i];
        }
        capacity *= 2;
        delete [] text;
        text = temp;
    }

}

string* readText(istream& in, uint& length, uint& capacity){
    // IMPLEMENT ME
    string* removeMe=nullptr;
    return removeMe;
}


void outputText(ostream& out, const string* text, uint length){
    // IMPLEMENT ME
}

void appendText(string*& text, uint& length, uint& capacity,
                const string * const other, uint length_other){
    // IMPLEMENT ME
}


bool containsWord(const string *text, uint length, const string& word){
    // IMPLEMENT ME
    bool removeMe=false;
    return removeMe;
}

uint wordCount(const string *text, uint length, const string& word){
    // IMPLEMENT ME
    uint removeMe=0;
    return removeMe;
}

string* getWords(const string *text, uint length, uint& number_unique, uint& capacity_unique){
    // IMPLEMENT ME
    string* removeMe=nullptr;
    return removeMe;
}

void replaceWordAll(string*& text, uint length, const string& word, const string& new_word){
    // IMPLEMENT ME
}

void deleteWordAll(string*& text, uint& length, const string& word){
    // IMPLEMENT ME
}

void replacePhraseFirst(string*& text, uint& length, uint& capacity,
                        const string *phrase, uint phrase_length,
                        const string *new_phrase, uint new_phrase_length){
    // IMPLEMENT ME
}
