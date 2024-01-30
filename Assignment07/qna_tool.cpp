#include <assert.h>
#include <sstream>
#include "qna_tool.h"

using namespace std;

// Helper functions begins.
bool isSeparator(char ch){
    string separators = ".,-:!\"\'()?[];@ ";

    for(int i = 0; i < separators.size(); i++){
        if(ch == separators[i]){ return true; }
    }
    return false;
}

vector<string> splitSentence(string sentence){
    // This function splits a sentence into lowercase words
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
    return words;
}

long double QNA_tool::occurence_in_general_corpus(string& word) {
    // This function finds out the general count of the word in the corpus and returns it.
    return dict.okrnc(word)->gen_cnt;
}

void QNA_tool::get_para_score(string word, word_node* Word_Node, vector<vector<int>>& intermediate_result) {

    vector<vector<int>> word_occurences = Word_Node->origin;
    long long frequency = Word_Node->count;

    long long general_count = occurence_in_general_corpus(word)+1;

    for (auto occurence : word_occurences) {
        double word_score = double((frequency+1))/general_count;

        int book = occurence[0];
        int page = occurence[1];
        int para = occurence[2];
        int word_in_para = occurence[3];

        if(dict.pwc[book][page][para][1] == 0){
            intermediate_result.push_back({book, page, para});
        }

        dict.pwc[book][page][para][1] += word_score*word_in_para;
    }
}

double log10(double x) {    
    const double EULER_CONST = 2.718281828459045;
    const int ITERATIONS =  100;
    const double LN10 =  2.3025850929940456;
    const double LN2 =  0.6931471805599453;
    
    int max_power = 0;

    while (x > 1.0) {
        x /= EULER_CONST;
        max_power++;
    }

    x -= 1.0;
    double result = 0.0, negative_power = 1.0, temp_power = x;

    for (int k = 1 ; k <= ITERATIONS ; k++) {
        result += temp_power * negative_power / k;
        temp_power *= x;
        negative_power *= -1;
    }
    return (max_power + result)/LN2;
}

//Helper functions ends.

QNA_tool::QNA_tool(){

    std::ifstream file("unigram_freq.csv");
    int idx1, idx2;
    string line;

    while (getline(file, line)) {

        std::istringstream stream(line);
        string token;
        while (getline(stream, token, ',')) {
            string occurrence;
            if (getline(stream, occurrence, ',')) {
                if(isdigit(occurrence[0])) {
                    dict.insert_wrd(token,stol(occurrence));
                }
            }
        }
    }
    file.close();
}

QNA_tool::~QNA_tool(){
     
}

void QNA_tool::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    // This function inserts a sentence into the dictionary for book code, page, paragraph, and sentence number.
    dict.insert_sentence(book_code, page, paragraph, sentence_no, sentence);
    return;
}

Node* QNA_tool::get_top_k_para(string question, int k) {
    vector<string> words = splitSentence(question);
    vector<vector<int>> intermediate_result;

    for (string i : words) {
        word_node* wordNode = dict.okrnc(i);
        if(wordNode != nullptr){
            get_para_score(i, wordNode, intermediate_result);
        }
    }

    if(intermediate_result.empty()) return nullptr;

    vector<pair<double, vector<int>>> result;

    for(auto in : intermediate_result){
        int book = in[0];
        int page = in[1];
        int para = in[2];
        double para_score = dict.pwc[book][page][para][1];

        result.push_back({para_score, in});
        dict.pwc[book][page][para][1] = 0;
    }

    MaxHeap heap;

    for (auto i : result) { heap.insert(i); }

    Node* head = new Node();
    head->left = head->right = nullptr;
    Node* tail = head;

    vector<vector<int>> sorted_heap = heap.get_sorted(k);

    for(auto i : sorted_heap) {

        Node* temp = new Node();
        temp->book_code = i[0];
        temp->page = i[1];
        temp->paragraph = i[2];
        temp->left = tail; temp->right = nullptr; tail->right = temp; 
        tail = temp;
    }
    Node* to_return = head->right; 
    head->right = nullptr; head->left = nullptr; to_return->left = nullptr;
    delete head;
    return to_return;
}

std::string QNA_tool::get_paragraph(int book_code, int page, int paragraph){

    cout << "Book_code: " << book_code << " Page: " << page << " Paragraph: " << paragraph << endl;
    
    std::string filename = "mahatma-gandhi-collected-works-volume-";
    filename += to_string(book_code);
    filename += ".txt";

    std::ifstream inputFile(filename);

    std::string tuple;
    std::string sentence;

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the input file " << filename << "." << std::endl;
        exit(1);
    }

    std::string res = "";

    while (std::getline(inputFile, tuple, ')') && std::getline(inputFile, sentence)) {
        // Get a line in the sentence
        tuple += ')';

        int metadata[5];
        std::istringstream iss(tuple);

        // Temporary variables for parsing
        std::string token;

        // Ignore the first character (the opening parenthesis)
        iss.ignore(1);

        // Parse and convert the elements to integers
        int idx = 0;
        while (std::getline(iss, token, ',')) {
            // Trim leading and trailing white spaces
            size_t start = token.find_first_not_of(" ");
            size_t end = token.find_last_not_of(" ");
            if (start != std::string::npos && end != std::string::npos) {
                token = token.substr(start, end - start + 1);
            }
            
            // Check if the element is a number or a string
            if (token[0] == '\'') {
                // Remove the single quotes and convert to integer
                int num = std::stoi(token.substr(1, token.length() - 2));
                metadata[idx] = num;
            } else {
                // Convert the element to integer
                int num = std::stoi(token);
                metadata[idx] = num;
            }
            idx++;
        }

        if(
            (metadata[0] == book_code) &&
            (metadata[1] == page) &&
            (metadata[2] == paragraph)
        ){
            res += sentence;
        }
    }

    inputFile.close();
    return res;
}


//---------------- LLM Functions ----------------//


double LLM_word_score(int total_words , int words , int paras , long total_para) {
    double TD = (double(total_words+1)/double(words));
    double IDF = log10(double(total_para)/double(paras+1));

    return TD*IDF;
}

void QNA_tool::LLM_get_para_score(string word, word_node* Word_Node, vector<vector<int>>& intermediate_result) {

    vector<vector<int>> word_occurences = Word_Node->origin;
    long long frequency = Word_Node->count;

    for (auto occurence : word_occurences) {

        int total_words = dict.get_word_count_of_para(occurence[0],occurence[1],occurence[2]);
        double word_score = LLM_word_score(total_words , occurence[3], word_occurences.size() , dict.tot_para);
        int book = occurence[0];
        int page = occurence[1];
        int para = occurence[2];
        int word_in_para = occurence[3];

        if(dict.pwc[book][page][para][1] == 0){ intermediate_result.push_back({book, page, para}); }

        dict.pwc[book][page][para][1] += word_score*word_in_para;        
    }
}

Node* QNA_tool::LLM_get_top_k_para(string question, int k) {

    ifstream outfile("Lemmatized_query.txt");
    string line;
    string cmbnd;
    while ((getline(outfile,line))) { cmbnd+=line; }
    outfile.close();

    vector<string> words = splitSentence(cmbnd);
    vector<string> stop_words = {"i", "me", "my", "myself", "we", "our", "ours", "ourselves", "you", "your", "yours", "yourself", "yourselves", "he", "him", "his", "himself", "she", "her", "hers", "herself", "it", "its", "itself", "they", "them", "their", "theirs", "themselves", "what", "which", "who", "whom", "this", "that", "these", "those", "am", "is", "are", "was", "were", "be", "been", "being", "have", "has", "had", "having", "do", "does", "did", "doing", "a", "an", "the", "and", "but", "if", "or", "because", "as", "until", "while", "of", "at", "by", "for", "with", "about", "against", "between", "into", "through", "during", "before", "after", "above", "below", "to", "from", "up", "down", "in", "out", "on", "off", "over", "under", "again", "further", "then", "once", "here", "there", "when", "where", "why", "how",  "no", "nor", "not", "only","than", "too", "very", "s", "t", "can", "will", "just",  "should"};

    vector<vector<int>> intermediate_result;

    for (string i : words) {
        bool common_word = false;
        for(string j : stop_words){
            if(i == j){
                common_word = true;
                break;
            }
        }
        if (!common_word) {
            word_node* wordNode = dict.okrnc(i);

            if(wordNode != nullptr){
                LLM_get_para_score(i, wordNode, intermediate_result);
            }
        }
    }

    if(intermediate_result.empty()){
        return nullptr;
    }

    vector<pair<double, vector<int>>> result;

    for(auto in : intermediate_result){
        int book = in[0];
        int page = in[1];
        int para = in[2];
        double para_score = dict.pwc[book][page][para][1];
        result.push_back({para_score, in});
    }

    MaxHeap heap;
    for (auto i : result) { 
        heap.insert(i);
    }

    Node* head = new Node();
    head->left = head->right = nullptr;
    Node* tail = head;

    vector<vector<int>> sorted_heap = heap.get_sorted(k);

    for(auto i : sorted_heap) {

        Node* temp = new Node();
        temp->book_code = i[0];
        temp->page = i[1];
        temp->paragraph = i[2];
        temp->left = tail; temp->right = nullptr; tail->right = temp; 
        tail = temp;
    }
    Node* to_return = head->right; 
    head->right = nullptr; head->left = nullptr; to_return->left = nullptr;
    delete head;
    return to_return;
}

void QNA_tool::query(string question, string filename){
    Node* queries_paragraph = LLM_get_top_k_para(question, 5);
    LLM_query(filename, queries_paragraph, 5, question);
    return;
}

void QNA_tool::LLM_query(string filename, Node* root, int k, string question){
    Node* traverse = root;
    int num_paragraph = 0;

    while(num_paragraph < k){
        assert(traverse != nullptr);
        string p_file = "paragraph_";
        p_file += to_string(num_paragraph);
        p_file += ".txt";
        remove(p_file.c_str());
        ofstream outfile(p_file);
        string paragraph = get_paragraph(traverse->book_code, traverse->page, traverse->paragraph);
        assert(paragraph != "$I$N$V$A$L$I$D$");
        outfile << paragraph;
        outfile.close();
        traverse = traverse->right;
        num_paragraph++;
    }

    ofstream outfile("query.txt");
    outfile << "According to only the information in the document sources provided within the context above, " ;
    outfile << question;
    outfile.close();
 
    cout << '\n';
    string command = "python3 ";
    command += filename;
    command += " ";
    command += to_string(k);
    command += " ";
    command += "query.txt";

    system(command.c_str());
    return;
}

void QNA_tool::query_llm(string filename, Node* root, int k, string API_KEY, string question){

    // first write the k paragraphs into different files

    Node* traverse = root;
    int num_paragraph = 0;

    while(num_paragraph < k){
        assert(traverse != nullptr);
        string p_file = "paragraph_";
        p_file += to_string(num_paragraph);
        p_file += ".txt";
        // delete the file if it exists
        remove(p_file.c_str());
        ofstream outfile(p_file);
        string paragraph = get_paragraph(traverse->book_code, traverse->page, traverse->paragraph);
        assert(paragraph != "$I$N$V$A$L$I$D$");
        outfile << paragraph;
        outfile.close();
        traverse = traverse->right;
        num_paragraph++;
    }

    // write the query to query.txt
    ofstream outfile("query.txt");
    outfile << "These are the excerpts from Mahatma Gandhi's books.\nOn the basis of this, ";
    outfile << question;
    // You can add anything here - show all your creativity and skills of using ChatGPT
    outfile.close();
 
    // you do not need to necessarily provide k paragraphs - can configure yourself

    // python3 <filename> API_KEY num_paragraphs query.txt
    string command = "python3 ";
    command += filename;
    command += " ";
    command += API_KEY;
    command += " ";
    command += to_string(k);
    command += " ";
    command += "query.txt";

    system(command.c_str());
    return;
}