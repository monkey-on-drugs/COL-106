#include <string> 
#include <vector>
#include <iostream>
#include "Node.h"
using namespace std;

class DB_Node {
public:
    string sentence;
    int book_code;
    int page;
    int paragraph;
    int sentence_no;
    DB_Node* next;

    DB_Node(int book_code, int page, int paragraph, int sentence_no, string sentence) {
        this->book_code = book_code;
        this->page = page;
        this->paragraph = paragraph;
        this->sentence_no = sentence_no;
        this->sentence = sentence;
        this->next = nullptr;
    }
};

class SearchEngine {
private:
    vector<DB_Node> db;

public: 
    SearchEngine();
    ~SearchEngine();
    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);
    Node* search(string pattern, int& n_matches);
};