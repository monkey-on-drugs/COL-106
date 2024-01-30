// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;



class word_node {
    public:
        string word;
        long long count=0;
        long long gen_cnt = 0;
        vector<vector<int>> origin; //each vector in the 2d vector will represent a single occurance.
                                    /*[x][0] => book no
                                      [x][1] => page no
                                      [x][2] => para no
                                      [x][3] => count*/

                              
        word_node(long long& general_count, string& wrd) 
        {
            gen_cnt = general_count;    
            word =wrd;
        }
        word_node(int book_code, int page, int paragraph, string& wrd) {
                vector<int> temp={book_code, page, paragraph, 1};
                origin.push_back(temp);
                count = 1;
                word = wrd;
        }
        void insert(int book_code, int page, int paragraph)
        {
            count++;
            if(!origin.empty()) //well this case is not needeed, but just for precautionary purpose
            {
                vector<int> temp = origin.back();
                if(temp[2] == paragraph  && temp[1] == page)    //if the word has occured inthe para recently, then we just incre,ment the last entry
                {
                    origin.back()[3]= origin.back()[3]+1;
                }
                else    //if not then we create a new entry
                {
                    vector<int> new_ntry={book_code, page, paragraph, 1};
                    origin.push_back(new_ntry);
                }
            }
            else    // this will never occur.................
            {
                vector<int> temp={book_code, page, paragraph, 1};
                origin.push_back(temp);
            }
        }

};


class Dict {
private:
    // You can add attributes/helper functions here
    vector<vector<word_node*>> lib;
    int hash1(string word);
    int hash2(string word);
    //long long max_hash=0;
    const int size1 = 116911;
    const int size2 = 33;
    int l_para=0;
    int lb=0,lpg=-1,lpa=-1;
    vector<vector<long long>> WordLoc;
    
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
    long long tot_words=0,tot_para=1,unique_wrds=0;
    vector<vector<vector<vector<float>>>> pwc;
    void para_w_c(int book_code, int page, int paragraph);
    int get_word_count_of_para(int book_code, int page, int paragraph);
    word_node* okrnc (string word);
    void insert_wrd(string& wrd, long long freq);  
};