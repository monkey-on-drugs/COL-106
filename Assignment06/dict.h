// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

struct TriNode{
    TriNode* links[256];
    long long int count_ends = 0;

    void put(char ch, TriNode* node){
        links[ch] = node;
    }

    bool doesContain(char ch){
        return (links[ch] != nullptr);
    }

    TriNode* get(char ch){
        return links[ch];
    }

    void increaseCountEnd(){ count_ends++;}
    long long int getCountEnd(){return count_ends;}
    bool isEnd(){return count_ends != 0;}
};

class Trie{

private:
    TriNode* root;

public:

    Trie(){
        root = new TriNode();
    }

    void destroy(TriNode* node){
        if(node == NULL){
            return;
        }
        for(int i = 32; i < 256; i++){
            destroy(node->links[i]);
        }
        delete node;
    }

    ~Trie(){
        destroy(root);
    }

    void insert(const string& word){
        TriNode* temp = root;

        for(int i = 0; i < word.size(); i++){
            if(!temp->doesContain(word[i])){
                temp->put(word[i], new TriNode());
            }
            temp = temp->get(word[i]);
        }
        temp->increaseCountEnd();
    }

    int search(string& word){
        TriNode* temp = root;

        for(int i = 0; i < word.size(); i++){
            if(temp->doesContain(word[i])){
                temp = temp->get(word[i]);
            }
            else{
                return -1;
            }
        }
        return temp->getCountEnd();
    }

    TriNode* getRoot(){return root;}

    void traverse(string& prefix, TriNode* node, vector<string>& ans){
        if(node->getCountEnd() > 0){
            ans.push_back(prefix + ", " + to_string(node->getCountEnd()));
        }

        for(int i = 32; i < 256; i++){
            char w = i;
            TriNode* child = node->links[i];
            if(child != nullptr){
                prefix.push_back(w);
                traverse(prefix, child, ans);
                prefix.pop_back();
            }
        }

    }

    vector<string> print(){
        vector<string> answer;
        string s = "";
        traverse(s, root, answer);
        return answer;
    }
};

class Dict {
private:
    // You can add attributes/helper functions here
    Trie trie;

public: 
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    Dict();

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    int get_word_count(string word);

    void dump_dictionary(string filename);

    /* -----------------------------------------*/
};