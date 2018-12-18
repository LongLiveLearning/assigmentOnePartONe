#include <stdlib.h>
#include <iostream>
#include <utility>
#include <sstream>

#include "TextTester.h"
#include "Text.h"

using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::string;
using std::map;

const string TextTester::DEL_WORD = "DELETE";
const string NEW_WORD = "NEW_WORD";

TextTester::TextTester() : error_(false), funcname_("") {
    unsigned int val(time(0)*rand());
    srand(val);
}

TextTester::~TextTester() {
}

void TextTester::testResize(){
    funcname_ = "testResize";

    //increase capacity empty text
    string* text = nullptr;
    unsigned int length{0};
    unsigned int capacity{0};

    unsigned int new_capacity=rand()%SMALL_CAPACITY+1;
    resize(text,length,capacity,new_capacity);
    if(capacity!=new_capacity)
        errorOut_("Capacity not increased correctly.",1);

    // new capacity equal to old
    if(text!=nullptr)
        delete [] text;
    text = nullptr;
    length=0;
    capacity=0;
    vector<string> text_vector;
    text = generateText_(text_vector,length,capacity);
    unsigned int capacity_copy = capacity;
    resize(text, length, capacity, capacity);
    if(capacity!=capacity_copy)
        errorOut_("Modified capacity when new capacity equal to old.",2);

    if(!checkText_(text,text_vector,length))
        errorOut_("Modified contents.",3);

    //new capacity greater than old
    if(text!=nullptr)
        delete [] text;
    text = nullptr;
    length=0;
    capacity=0;
    text = generateText_(text_vector,length,capacity);
    capacity_copy=capacity;
    unsigned int larger = capacity + rand()%SMALL_CAPACITY +1;
    resize(text, length, capacity, larger);
    if(capacity!=larger)
        errorOut_("Capacity not increased correctly.",4);
    if(!checkText_(text,text_vector,length))
        errorOut_("Modified contents.",5);

    //new capacity smaller than old
    if(text!=nullptr)
        delete [] text;
    text = nullptr;
    length=0;
    capacity=0;
    text = generateText_(text_vector,length,capacity);
    capacity_copy=capacity;
    unsigned int smaller = capacity - (rand()%capacity +1);
    resize(text, length, capacity, smaller);
    if(capacity!=capacity_copy)
        errorOut_("Modified capacity when new capacity smaller than old.",6);
    if(!checkText_(text,text_vector,length))
        errorOut_("Modified contents.",7);

    if(text!=nullptr)
        delete [] text;
    text = nullptr;

    passOut_("Tested the resizing.");
}

void TextTester::testReadText(){
    funcname_ = "testReadText";

    unsigned int length_gen{SMALL_CAPACITY};
    unsigned int capacity_gen{2*SMALL_CAPACITY};
    vector<string> text_vector;
    string* tmp = generateText_(text_vector,length_gen,capacity_gen);
    if(tmp!=nullptr)
        delete [] tmp;
    tmp=nullptr;

    string whitespace [3] = {" ","\t","\n"};
    std::stringstream sstream;
    for(int i=0;i<text_vector.size();++i){
        sstream<< text_vector[i]<<whitespace[rand()%3];
    }
    sstream<<END_OF_TEXT;

    unsigned int length{0};
    unsigned int capacity{0};
    string* text = readText(sstream, length, capacity);
    if(length!=length_gen){
        errorOut_("Text has wrong length.",1);
    }
    if(length > capacity){
        errorOut_("Length larger than capacity.",2);
    }
    if(!checkText_(text,text_vector,length))
        errorOut_("Wrong text contents.",3);

    if(text!=nullptr)
        delete [] text;
    text=nullptr;

    passOut_("Tested reading a text from an input stream.");
}

void TextTester::testAppendText(){
    funcname_ = "testAppendText";

    unsigned int length_gen1{SMALL_CAPACITY};
    unsigned int capacity_gen1{SMALL_CAPACITY};
    vector<string> text_vector1;
    string* text1 = generateText_(text_vector1,length_gen1,capacity_gen1);
    unsigned int length1 = length_gen1;
    unsigned int capacity1 = capacity_gen1;

    unsigned int length_gen2{0};
    unsigned int capacity_gen2{0};
    vector<string> text_vector2;
    string* text2 = generateText_(text_vector2,length_gen2,capacity_gen2);
    unsigned int length2 = length_gen2;
    unsigned int capacity2 = capacity_gen2;

    text_vector1.insert(text_vector1.end(), text_vector2.begin(), text_vector2.end());

    appendText(text1, length1, capacity1, text2, length2);

    if(length1!=length_gen1+length_gen2){
        errorOut_("Result has wrong length.",1);
    }
    if(length1 > capacity1){
        errorOut_("Length of result is larger than its capacity.",2);
    }
    if(!checkText_(text1,text_vector1,length1))
        errorOut_("Wrong text contents.",3);

    if(text1!=nullptr)
        delete [] text1;
    text1=nullptr;

    if(text2!=nullptr)
        delete [] text2;
    text2=nullptr;

    passOut_("Tested appending texts.");
}

void TextTester::testDeleteWordAll(){
    funcname_ = "testDeleteWordAll";

    unsigned int length_gen{6};
    unsigned int capacity_gen{6};
    vector<string> text_vector;
    string* text = generateText_(text_vector,length_gen,capacity_gen);
    unsigned int length = length_gen;
    unsigned int capacity = capacity_gen;

    unsigned int mid = length/2;
    unsigned int numDel = 0;
    if(length >= 1){
        text[0] = DEL_WORD;
        text_vector.erase(text_vector.begin());
        numDel=1;
        if(length >= 2){
            text[length-1] = DEL_WORD;
            text_vector.erase(text_vector.end()-1);
            numDel=2;
            if(length >= 3){
                text[mid] = DEL_WORD;
                text_vector.erase(text_vector.begin()+(mid - 1));
                numDel=3;
            }
        }
    }

    deleteWordAll(text, length, DEL_WORD);

    if(length != length_gen - numDel){
        errorOut_("Result has wrong length.",1);
    }
    if(length > capacity){
        errorOut_("Length of result is larger than its capacity.",2);
    }
    if(!checkText_(text,text_vector,length))
        errorOut_("Wrong text contents.",3);

    deleteWordAll(text, length, DEL_WORD);

    if(length != length_gen - numDel){
        errorOut_("Changed length when word not present.",4);
    }
    if(length > capacity){
        errorOut_("Length is larger than capacity.",5);
    }
    if(!checkText_(text,text_vector,length))
        errorOut_("Wrong text contents.",6);

    if(text!=nullptr)
        delete [] text;
    text=nullptr;

    passOut_("Tested deleting a word.");
}

void TextTester::testGetWords(){
    funcname_ = "testGetWords";
    vector<string> unique;
    unsigned int number{0};
    generateUniqueWords_(unique,number);

    unsigned int length{3*number};
    unsigned int capacity{4*number};

    map<string,bool> used;
    string* text = generateTextFromWords_(unique,length,capacity,used);

    unsigned int number_unique=0;
    unsigned int capacity_unique=0;
    string* unique_words = getWords(text, length, number_unique, capacity_unique);

    if(number_unique != used.size()){
        errorOut_("Wrong number of words returned.",1);
    }
    if(!checkWords_(unique_words,number_unique,used)){
        errorOut_("Wrong set of words returned.",2);
    }

    if(text != nullptr)
        delete [] text;
    if(unique_words != nullptr)
        delete [] unique_words;

    passOut_("Tested getWords.");

}

void TextTester::testReplacePhraseFirst(){
    funcname_ = "testReplacePhraseFirst";

    unsigned int rest_length = rand()%SMALL_CAPACITY+1;
    unsigned int phrase_length = rand()%10+1;
    unsigned int new_phrase_length =rand()%10+1;

    vector<string> unique;
    unsigned int number_unique = rest_length+phrase_length+new_phrase_length;
    generateUniqueWords_(unique,number_unique);

    std::vector<string> rest_v(unique.begin(), unique.begin()+rest_length);
    std::vector<string> phrase_v(unique.begin()+rest_length, unique.begin()+rest_length+phrase_length);
    std::vector<string> new_phrase_v(unique.begin()+rest_length+phrase_length, unique.end());

    string* phrase=new string[phrase_length];
    for(int i =0; i < phrase_length; ++i){
        phrase[i]= phrase_v[i];
    }

    string* new_phrase= new string[new_phrase_length];
    for(int i =0; i < new_phrase_length; ++i){
        new_phrase[i]= new_phrase_v[i];
    }

    unsigned int length0{rest_length};
    unsigned int capacity0{length0*2};
    string* text0 = new string[capacity0];
    // fill text0, phrase does not appear
    for(int i=0; i < length0; i++){
        text0[i] = rest_v[i];
    }

    unsigned int lengthb{rest_length+phrase_length};
    unsigned int capacityb{lengthb*2};
    string* textb = new string[capacityb];
    // fill textb, phrase in the beginning
    for(int i=0; i < lengthb; i++){
        if(i < phrase_length){
            textb[i]=phrase_v[i];
        }
        else{
            textb[i]=rest_v[i-phrase_length];
        }
    }
    unsigned int lengthm{rest_length+phrase_length};
    unsigned int capacitym{lengthm*2};
    string* textm = new string[capacitym];
    // fill textm, phrase in the middle
    unsigned int mid = rest_length/2;
    for(int i=0; i < mid; i++){
        textm[i] = rest_v[i];
    }
    for(int i=mid; i < mid+phrase_length; i++){
        textm[i] = phrase_v[i-mid];
    }
    for(int i=mid+phrase_length; i < lengthm; i++){
        textm[i] = rest_v[i-phrase_length];
    }

    unsigned int lengthe{rest_length+phrase_length};
    unsigned int capacitye{lengthe*2};
    string* texte = new string[capacitye];
    // fill texte, phrase in the end
    for(int i=0; i < lengthe; i++){
        if(i < rest_length){
            texte[i]=rest_v[i];
        }
        else{
            texte[i]=phrase_v[i-rest_length];
        }
    }

    replacePhraseFirst(text0, length0, capacity0, phrase, phrase_length,new_phrase,new_phrase_length);
    if(length0 != rest_length || !checkText_(text0, rest_v, length0))
        errorOut_("Replaced phrase that does not exist.",1);

    replacePhraseFirst(textb, lengthb, capacityb, phrase, phrase_length,new_phrase,new_phrase_length);
    vector<string> newb(new_phrase_v);
    newb.insert(newb.end(),rest_v.begin(), rest_v.end());
    if(lengthb != rest_length+new_phrase_length || !checkText_(textb, newb, lengthb)){
        errorOut_("Error replacing phrase at the beginning.",2);

    }

    replacePhraseFirst(textm, lengthm, capacitym, phrase, phrase_length,new_phrase,new_phrase_length);
    vector<string> newm(rest_v.begin(),rest_v.begin()+mid);
    newm.insert(newm.end(),new_phrase_v.begin(), new_phrase_v.end());
    newm.insert(newm.end(),rest_v.begin()+mid, rest_v.end());
    if(lengthm != rest_length+new_phrase_length || !checkText_(textm, newm, lengthm)){
        errorOut_("Error replacing phrase in the middle.",3);

    }


    replacePhraseFirst(texte, lengthe, capacitye, phrase, phrase_length,new_phrase,new_phrase_length);
    vector<string> newe(rest_v);
    newe.insert(newe.end(),new_phrase_v.begin(), new_phrase_v.end());
    if(lengthe != rest_length+new_phrase_length || !checkText_(texte, newe, lengthe)){
        errorOut_("Error replacing phrase at the end.",2);

    }

    if(phrase != nullptr)
        delete [] phrase;
    if(new_phrase != nullptr)
        delete [] new_phrase;
    if(text0 != nullptr)
        delete [] text0;
    if(textb != nullptr)
        delete [] textb;
    if(textm != nullptr)
        delete [] textm;
    if(texte != nullptr)
        delete [] texte;

    passOut_("Tested replacePhraseFirst.");
}

void TextTester::testContainsWord(){
    funcname_ = "testContainsWord";

    unsigned int length_gen{0};
    unsigned int capacity_gen{0};
    vector<string> text_vector;
    string* text = generateText_(text_vector,length_gen,capacity_gen);
    unsigned int length = length_gen;
    unsigned int capacity = capacity_gen;

    unsigned int mid = length/2;

    if(containsWord(text,length,DEL_WORD)){
        errorOut_("Found non-existing word.",1);
    }

    if(length >= 1){
        string tmp = text[0];
        text[0] = DEL_WORD;
        if(!containsWord(text,length,DEL_WORD))
            errorOut_("Did not find word at the start.",2);
        text[0]= tmp;
    }
    if(length >= 2){
        string tmp = text[length-1];
        text[length-1] = DEL_WORD;
        if(!containsWord(text,length,DEL_WORD))
            errorOut_("Did not find word at the end.",3);
        text[length-1]=tmp;
    }
    if(length >= 3){
        text[mid] = DEL_WORD;
        if(!containsWord(text,length,DEL_WORD))
            errorOut_("Did not find word in the middle.",4);
    }

    if(length >= 1){
        text[0] = DEL_WORD;
    }
    if(length >= 2){
        text[length-1] = DEL_WORD;
    }

    if(length >=1 && !containsWord(text,length,DEL_WORD))
        errorOut_("Error when word occurs multiple times.",5);
    if(text!=nullptr)
        delete [] text;
    text=nullptr;

    passOut_("Tested conatainment of a word.");
}

void TextTester::testWordCount(){
    funcname_ = "testWordCount";

    unsigned int length_gen{0};
    unsigned int capacity_gen{0};
    vector<string> text_vector;
    string* text = generateText_(text_vector,length_gen,capacity_gen);
    unsigned int length = length_gen;
    unsigned int capacity = capacity_gen;

    unsigned int mid = length/2;

    if(wordCount(text,length,DEL_WORD)>0){
        errorOut_("Positive count for non-existing word.",1);
    }

    if(length >= 1){
        string tmp = text[0];
        text[0] = DEL_WORD;
        if(wordCount(text,length,DEL_WORD)!=1)
            errorOut_("Did not count word at the start.",2);
        text[0]= tmp;
    }
    if(length >= 2){
        string tmp = text[length-1];
        text[length-1] = DEL_WORD;
        if(wordCount(text,length,DEL_WORD)!=1)
            errorOut_("Did not count word at the end.",3);
        text[length-1]=tmp;
    }
    if(length >= 3){
        string tmp = text[mid];
        text[mid] = DEL_WORD;
        if(wordCount(text,length,DEL_WORD)!=1)
            errorOut_("Did not count word in the middle.",4);
        text[mid] = tmp;
    }

    unsigned int count=0;
    for(int i =0; i < length; ++i){
        if(rand()%2){
            text[i]=DEL_WORD;
            count++;
        }
    }
    if(wordCount(text,length,DEL_WORD)!=count)
        errorOut_("Retrurned wrong count.",5);

    if(text!=nullptr)
        delete [] text;
    text=nullptr;

    passOut_("Tested counting the occurrences of a word.");
}

void TextTester::testReplaceWordAll(){
    funcname_ = "testReplaceWordAll";

    unsigned int length_gen{0};
    unsigned int capacity_gen{0};
    vector<string> text_vector;
    string* text = generateText_(text_vector,length_gen,capacity_gen);
    unsigned int length = length_gen;
    unsigned int capacity = capacity_gen;

    unsigned int mid = length/2;

    replaceWordAll(text,length,DEL_WORD, NEW_WORD);
    if(!checkText_(text,text_vector,length))
        errorOut_("Replaced non-existing word.",1);

    resetText_(text,text_vector,length,capacity_gen);

    if(length >= 1){
        string tmp = text_vector[0];
        text[0] = DEL_WORD;
        text_vector[0] = NEW_WORD;
        replaceWordAll(text,length,DEL_WORD, NEW_WORD);
        if(!checkText_(text,text_vector,length))
            errorOut_("Did not replace correctly word at the start.",2);
        text_vector[0]= tmp;
        resetText_(text,text_vector,length,capacity_gen);
    }
    if(length >= 2){
        string tmp = text_vector[length-1];
        text[length-1] = DEL_WORD;
        text_vector[length-1] = NEW_WORD;
        replaceWordAll(text,length,DEL_WORD, NEW_WORD);
        if(!checkText_(text,text_vector,length))
            errorOut_("Did not replce correctly word at the end.",3);
        text_vector[length-1]=tmp;
        resetText_(text,text_vector,length,capacity_gen);
    }
    if(length >= 3){
        string tmp = text_vector[mid];
        text[mid] = DEL_WORD;
        text_vector[mid] = NEW_WORD;
        replaceWordAll(text,length,DEL_WORD, NEW_WORD);
        if(!checkText_(text,text_vector,length))
            errorOut_("Did not replace correctly word in the middle.",4);
        text_vector[mid] = tmp;
        resetText_(text,text_vector,length,capacity_gen);
    }

    for(int i =0; i < length; ++i){
        if(rand()%2){
            text[i]=DEL_WORD;
            text_vector[i] = NEW_WORD;
        }
    }
    replaceWordAll(text,length,DEL_WORD, NEW_WORD);
    if(!checkText_(text,text_vector,length))
        errorOut_("Wrong result of replacement.",5);

    if(text!=nullptr)
        delete [] text;
    text=nullptr;

    passOut_("Tested replacement of a word.");
}

string* TextTester::generateText_(vector<string>& text_vector, unsigned int& length, unsigned int& capacity){
    if (capacity==0) {
        capacity = rand()%SMALL_CAPACITY+1;
        length = rand()%capacity;
    }
    else if(length > capacity){
        length = rand()%capacity;
    }

    string* text = new string[capacity];
    text_vector.clear();
    for(int i =0; i < length; ++i){
        string w = "";
        generateWord_(w,rand() % WORD_LENGTH+1);
        text_vector.push_back(w);
        text[i] = w;
    }

    return text;
}

void TextTester::generateUniqueWords_(vector<string>& unique, unsigned int& number){
    if (number==0) {
        number = rand()%SMALL_CAPACITY+1;
    }

    map<string,bool> generated;

    unique.clear();
    for(int i =0; i < number; ++i){
        string w = "";
        generateWord_(w,rand() % WORD_LENGTH+1);
        while(generated.count(w)>0){
            w = "";
            generateWord_(w,rand() % WORD_LENGTH+1);
        }
        unique.push_back(w);
        generated.insert(std::pair<string, int>(w,1));
    }
}

string* TextTester::generateTextFromWords_(vector<string>& words, unsigned int& length, unsigned int& capacity, map<string,bool>& used){
    if (capacity==0) {
        capacity = rand()%SMALL_CAPACITY+1;
        length = rand()%capacity;
    }
    else if(length > capacity){
        length = rand()%capacity;
    }

    string* text = new string[capacity];
    used.clear();
    for(int i =0; i < length; ++i){
        unsigned int index = rand() % words.size();
        string w = words[index];
        text[i] = words[index];
        used.insert(std::pair<string,bool>(w,1));
    }

    return text;
}

void TextTester::generateWord_(string& word, const unsigned int length) {
    static const char alphanum[] =
            "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    do{
        word = "";
        for (int i = 0; i < length; ++i)
            word += alphanum[rand() % (sizeof(alphanum) - 1)];
    } while(word==DEL_WORD);
}

bool TextTester::checkText_(string* text, vector<string>& text_vector, unsigned int length){
    if((text == nullptr || length == 0) && text_vector.size()>0){
        return false;
    }

    for(int i =0; i < text_vector.size(); ++i){
        if(text_vector[i]!=text[i]){
            return false;
        }
    }
    return true;
}
bool TextTester::checkWords_(string* words1, unsigned int length,const map<string,bool>& words2){
    if((words1 == nullptr || length == 0) && words2.size()>0)
        return false;
    if(length != words2.size())
        return false;

    for(int i =0; i < length; ++i){
        if(words2.count(words1[i])==0)
            return false;
    }

    return true;
}

void TextTester::resetText_(string*& text,vector<string>& text_vector, unsigned int& length, unsigned int& capacity){
    if (text!=nullptr) {
        delete [] text;
    }

    text = new string[capacity];
    length= text_vector.size();
    for(int i =0; i < length; ++i){
        text[i] = text_vector[i];
    }

}

void TextTester::errorOut_(const string& errMsg, unsigned int errBit) {
    cerr << funcname_ << " " << "(fail";
    if (errBit)
        cerr << errBit;
    cerr << "): " << errMsg << endl;
    error_|=(1<<errBit);
}

void TextTester::passOut_(const string& passMsg) {
    if (!error_) {
        cerr << funcname_ << " " << "(pass): " << passMsg << endl;
    }
}