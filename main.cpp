#include <iostream>
#include <string>

#include "Text.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::ostream;

int main(){
    // read text from standard input
    uint length1 = 0;
    uint capacity1 = 0;
    cout << "Enter a sequence of words separated by white spaces and terminated by " << END_OF_TEXT << endl;
    string* text1 = readText(cin, length1,capacity1);
    cout<<"Read a text of length "<<length1<<endl;
    outputText(cout,text1,length1);

    uint length2 = 0;
    uint capacity2 = 0;
    cout << "Enter a sequence of words separated by white spaces and terminated by " << END_OF_TEXT << endl;
    string* text2 = readText(cin, length2,capacity2);
    cout<<"Read a text of length "<<length2<<endl;
    outputText(cout,text2,length2);

    // append text1 and text2, result stored in text1
    appendText(text1,length1,capacity1,text2,length2);
    cout<<"Result of append:"<<endl;
    outputText(cout,text1,length1);

    // unique words
    string* unique_words=nullptr;
    uint number_unique=0;
    uint capacity_unique=0;
    unique_words = getWords(text1,length1,number_unique,capacity_unique);
    cout<<"Unique words "<<endl;
    outputText(cout,unique_words,number_unique);

    if(unique_words!=nullptr)
        delete [] unique_words;
    number_unique=0;
    capacity_unique=0;

    string word = "";
    cout<<"Enter a word"<<endl;
    cin>>word;

    // word occurrences
    if(containsWord(text1,length1,word)){
        cout<<"The text contains "<<word<<endl;
    }
    else{
        cout<<"The text does not contain "<<word<<endl;
    }
    cout<<"Number of occurrences of "<<word<<" is "<<wordCount(text1,length1,word)<<endl;

    // word replacement
    replaceWordAll(text1,length1,word,word+"_new");
    cout<<"Result of replacing "<<word<<" by "<<word+"_new is"<<endl;
    outputText(cout,text1,length1);

    // word delition
    deleteWordAll(text1,length1,word+"_new");
    cout<<"Result of deleting "<<word+"_new is"<<endl;
    outputText(cout,text1,length1);

    // phrase replacement
    uint phrase_length=4;
    string phrase[4]={"1","2","1","2"};
    uint new_phrase_length=3;
    string new_phrase[3] = {"3","4","5"};
    replacePhraseFirst(text1,length1,capacity1,phrase,phrase_length,new_phrase,new_phrase_length);
    cout<<"Result of replacing first occurrence of the phrase is"<<endl;
    outputText(cout,text1,length1);

    if(text1!=nullptr)
        delete [] text1;
    if(text2!=nullptr)
        delete [] text2;

    return 0;
}