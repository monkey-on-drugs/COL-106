#include "search.h"

SearchEngine::SearchEngine(){
}

SearchEngine::~SearchEngine(){
}

string lower(string s) {
    string r = "";
    for (auto i = s.begin(); i != s.end(); i++) { r += tolower(*i); }
    return r;
}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    DB_Node node = DB_Node(book_code, page, paragraph, sentence_no, lower(sentence));
    db.push_back(node);
    return;
}

Node* SearchEngine::search(string pattern, int& n_matches){

    pattern = lower(pattern);
    Node* head = new Node();
    Node* node = head;

    const int prime = 1572869;
    bool found = false;

    Node* temp;

    for (int o = 0; o < db.size(); o++) {
        string text = db[o].sentence;

        int pattern_length = pattern.length();
        int text_length = text.length();
        int pattern_hash = 0;
        int text_hash = 0;
        int h = 1;

        for (int i = 0; i < pattern_length - 1; i++) { h = (h * 256) % prime; }

        for (int i = 0; i < pattern_length; i++) {
            pattern_hash = (256 * pattern_hash + pattern[i]) % prime;
            text_hash = (256 * text_hash + text[i]) % prime;
        }

        for (int i = 0; i <= text_length - pattern_length; i++) {

            bool match = true;
            for (int j = 0; j < pattern_length; j++) {
                if (pattern[j] != ' ' && text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }

            if (match) {
                
                found = true;
                n_matches++;

                temp = new Node();
                temp->book_code = db[o].book_code;
                temp->page = db[o].page;
                temp->paragraph = db[o].paragraph;
                temp->sentence_no = db[o].sentence_no;
                temp->offset = i;

                if (head->right == nullptr) {
                    head->right = temp; 
                    node = head->right;
                } 
                else {
                    node->right = temp; 
                    node = node->right;
                }
            }

            if (i < text_length - pattern_length) {
                text_hash = (256 * (text_hash - text[i] * h) + text[i + pattern_length]) % prime;
                if (text_hash < 0) { text_hash = (text_hash + prime); }
            }
        }
    }
    
    if (!found) {
        delete head;
        return nullptr;
    }

    temp = head->right;
    delete head;
    return temp;
}

