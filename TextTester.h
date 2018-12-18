#ifndef TEXTTESTER_H_
#define TEXTTESTER_H_

#include <string>
#include <vector>
#include <map>

class TextTester {
public:
    TextTester();
    ~TextTester();

    void testResize();
    void testReadText();
    void testAppendText();
    void testDeleteWordAll();
    void testGetWords();
    void testReplacePhraseFirst();
    void testContainsWord();
    void testWordCount();
    void testReplaceWordAll();

private:
    std::string* generateText_(std::vector<std::string>& text_vector, unsigned int& length, unsigned int& capacity);
    void generateUniqueWords_(std::vector<std::string>& unique, unsigned int& number);
    std::string* generateTextFromWords_(std::vector<std::string>& words, unsigned int& length, unsigned int& capacity,std::map<std::string,bool>& used);
    void generateWord_(std::string& word, unsigned int length);
    bool checkText_(std::string* text, std::vector<std::string>& text_vector, unsigned int length);
    bool checkWords_(std::string* words1, unsigned int length,const std::map<std::string,bool>& words2);
    void resetText_(std::string*& text,std::vector<std::string>& text_vector, unsigned int& length, unsigned int& capacity);


    void errorOut_(const std::string& errMsg, unsigned int errBit);
    void passOut_(const std::string& passMsg);

    char error_;
    std::string funcname_;

    static const unsigned int SMALL_LENGHT = 100;
    static const unsigned int SMALL_CAPACITY = 100;
    static const unsigned int WORD_LENGTH = 20;
    static const std::string DEL_WORD;
    static const unsigned int REPEAT = 3;
};

#endif /* TEXTTESTER_H_ */
