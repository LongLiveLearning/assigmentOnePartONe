#ifndef TEXT_H_
#define TEXT_H_


#include <iostream>
#include <string>

using std::istream;
using std::ostream;
using std::string;

typedef unsigned int uint;

const string END_OF_TEXT = "EOT";


/*
* In this exercise you will implement several functions
* for manipulating dynamic arrays of strings.
* Each of the elements of the array represents a word
* (an arbitrary string without whitespaces).
* Some of the functions will be allocating memory for
* the array. The code using the functions will be
* responsible for deallocating the array's memory.
* A null pointer is interpreted as an empty sequence
* of words with length and capacity equal to 0.
*/

// Increases the size of the array of strings text
// to size new_capacity. Resizing has no effect on
// the contents of the array.
// The parameter length is the number of words stored
// in the array, and capacity is the number of allocated
// elements.
// If new_capacity is smaller or equal than capacity,
// does nothing, leaving text and capacity unchanged.
// Otherwise, increases the reserved space and updates
// the reference pointer text to point to the new array.
// Deallocates memory for which there will be no pointer
// after updating the reference pointer text.
// Sets the capacity passed by reference to the new capacity.
void resize(string*& text, uint length, uint& capacity, uint new_capacity);

// Reads from the input stream in a sequence of words
// (strings separated by whitespaces) until a sentinel,
// which is the string EOT is read.
// Returns an array of strings containing the sequence
// of read words (without the sentinel).
// Sets the length passed by reference to the number of
// words that were read (excluding the sentinel).
// Sets the capacity passed by reference to the capacity
// of the returned array. If an empty sequence is read,
// length should be set to 0.
string* readText(istream& in, uint& length, uint& capacity);

// Writes the sequence of strings stored in the array
// text to the given output stream.
// The parameter length is the number of words (strings)
// in the array text.
void outputText(ostream& out, const string *text, uint length);

// Appends the contents of the array other to the end of
// array text. The result is stored in the array text.
// The parameter length is the number of words in text.
// The parameter capacity is the capacity of the array text.
// The parameter length_other is the number of words
// stored in the array other.
// Increases the capacity of the array text as necessary.
// Updates the length passed by reference with the new
// number of strings in the array text. Updates the capacity
// passed by reference with the new capacity of the array text.
void appendText(string*& text, uint& length, uint& capacity, const string * const other, uint length_other);

// Returns true if the array text contains an entry
// equal to the string word, and false otherwise.
// The parameter length is the number of strings
// in the array text.
bool containsWord(const string *text, uint length, const string& word);

// Returns the number of entries of the array text
// that are equal to the string word.
// The parameter length is the number of strings
// in the array text.
uint wordCount(const string *text, uint length, const string& word);

// Returns a dynamic array for the different (i.e., unique)
// strings that are contained in the array text.
// Sets the integer passed by reference number_unique to the
// new number of unique strings in the array text.
// Sets the integer passed by reference capacity_unique to the
// capacity of the returned array.
// The parameter length is the number of strings
// in the array text.
string* getWords(const string *text, uint length, uint& number_unique, uint& capacity_unique);

// Replaces all entries of the array text that are
// equal to the string word with the string new_word.
// The parameter length is the number of strings
// in the array text.
void replaceWordAll(string*& text, uint length, const string& word, const string& new_word);

// Removes all entries of the array text equal to the string word.
// The length passed by reference is updated with the new
// number of strings in the array.
// Has no effect on the capacity (reserved space) of the array.
void deleteWordAll(string*& text, uint& length, const string& word);

// Replaces the first occurrence of a sequence of entries
// of the array text that is equal to the sequence of strings
// stored in the array phrase. If either of text or phrase is
// empty, does nothing, and leaves text, length and capacity unchanged.
// Otherwise, the sequence of strings phrase is replaced with
// the sequence of strings given in the array new_phrase.
// phrase_length is the number of strings in the array phrase.
// new_phrase_length is the number of strings in array new_phrase.
// The length passed by reference is updated with the new
// number of strings in the array text.
// The capacity passed by reference is updated with the new
// capacity of the array text.
void replacePhraseFirst(string*& text, uint& length, uint& capacity,
                        const string* phrase, uint phrase_length,
                        const string* new_phrase, uint new_phrase_length);


#endif /* TEXT_H_ */
