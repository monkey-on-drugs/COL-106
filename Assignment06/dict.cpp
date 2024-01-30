// Do NOT add any other includes
#include "dict.h"

Dict::Dict(){
    // Implement your function here
}

Dict::~Dict(){
    // Implement your function here 
}

bool isSeparator(char ch){
    string separators = ".,-:!\"\'()?[];@ ";
    for(int i = 0; i < separators.size(); i++){
        if(ch == separators[i]){
            return true;
        }
    }
    return false;
}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    // Implement your function here 

    //Step: 01: separate the sentence into words and store also convert capital letters into small letters first
    vector<string> words;
    string s = "";
    for(int i = 0; i < sentence.size(); i++){
        if(isSeparator(sentence[i]) || sentence[i] == 13){
            if(s != ""){
                words.push_back(s);
                s = "";
            }
        }
        else{
            if(65 <= sentence[i] && sentence[i] <= 90){
                s += (sentence[i] + 32);
            }
            else{
                s += sentence[i];
            }
        }
    }
    if(s != ""){
        words.push_back(s);
    }

    //Step: 02: insert all the words into the tries
    for(int i = 0; i < words.size(); i++){
        trie.insert(words[i]);
    }

    return;
}

int Dict::get_word_count(string word){
    // Implement your function here

    return (trie.search(word));
}

void Dict::dump_dictionary(string filename){
    // Implement your function here
    vector<string> answer = trie.print();
    ofstream myfile;
    myfile.open(filename);//Creates automatically if doesn't exist
    if(myfile.is_open()){
        for(long unsigned int i = 0; i < answer.size(); i++){
            myfile << answer[i] << "\n";
        }
    }
    myfile.close();

    return;
}