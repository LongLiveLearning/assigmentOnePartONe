#include <iostream>
#include <string>

#include "Text.h"

using std::string;
using std::ostream;


/**
 *  Increases the size of the array of strings text
 to size new_capacity. Resizing has no effect on
 the contents of the array.
 The parameter length is the number of words stored
 in the array, and capacity is the number of allocated
 elements.
 If new_capacity is smaller or equal than capacity,
 does nothing, leaving text and capacity unchanged.
 Otherwise, increases the reserved space and updates
 the reference pointer text to point to the new array.
 Deallocates memory for which there will be no pointer
 after updating the reference pointer text.
 Sets the capacity passed by reference to the new capacity.
 * @param text is an array of string we want to resize passed by reference
 * @param length number of strings in array text
 * @param capacity is the size of text array
 * @param new_capacity the new size of the text array
 */
void resize(string*& text, uint length, uint& capacity, uint new_capacity){
    string* temp;
    if (new_capacity > capacity) {
        temp = new string[new_capacity];
        for (int i=0; i<capacity; i++) {
            temp[i] = text[i];
        }
        capacity = new_capacity;
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
