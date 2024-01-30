// Do NOT add any other includes
#include "dict.h"
using namespace std;
Dict::Dict(){
    // Implement your function here 
    lib.resize(size1);   
    pwc.push_back({{{{}}}});
}


Dict::~Dict(){
    // Implement your function here 
    for(auto i : WordLoc)
    {
        delete lib[i[0]][i[1]];
    }
}

void Dict::para_w_c(int book_code, int page, int paragraph)
         {
            if(pwc.size()>book_code)    
        {
            if(pwc[book_code].size()>page)
            {
                if(pwc[book_code][page].size()>paragraph)
                {
                    if(pwc[book_code][page][paragraph].size())
                    {
                        pwc[book_code][page][paragraph][0]+=1;
                    }
                    else
                    {
                        pwc[book_code][page][paragraph] = {1,0};
                    }
                }
                else
                {
                    pwc[book_code][page].resize(paragraph+1);
                    pwc[book_code][page][paragraph] = {1,0};
                }
            }
            else
            {
                pwc[book_code].resize(page+1);
                pwc[book_code][page].resize(paragraph+1);
                pwc[book_code][page][paragraph] = {1,0};
            }
        }
        else
        {
            pwc.resize(book_code+1);
            pwc[book_code].resize(page+1);
            pwc[book_code][page].resize(paragraph+1);
            pwc[book_code][page][paragraph] = {1,0};
        }
        }

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    // Implement your function here 
    
    int idx1,idx2,sze(sentence.size());
    if(l_para != paragraph) 
    {
        tot_para++;
        l_para = paragraph;
    }
    
    
    std::string word("");
    for(int i=0;i<=sze;i++)
    {
        if(sentence[i]!=' ' && sentence[i]!='.' && sentence[i]!=',' && sentence[i]!='-' && sentence[i]!=':' && sentence[i]!='!' && sentence[i]!='\"' && sentence[i]!='\'' && sentence[i]!='(' &&sentence[i]!=')' && sentence[i]!='?' && sentence[i]!='[' && sentence[i]!=']' && sentence[i]!=';' && sentence[i]!='@' && sentence[i]!=';'  && i!=sze && sentence[i]!='\r')    //implies we are still reading a word
        {
            if(isalpha(sentence[i]))    word+=tolower(sentence[i]);
            else word+=sentence[i];
        }
        else    //word has finished or two consecutive spaces
        {
            if(word!="")
            {
                
                para_w_c(book_code,page,paragraph);
                tot_words++;
                //compute the idx using the hash function
                idx1 = hash1(word);
                idx2 = hash2(word);
                if(lib.size()>idx1) // key index exists
                {
                    if(lib[idx1].size()!=0) //vector already exists
                    {
                        if(lib[idx1].size()>idx2)   //vector can accomodate the new key
                        {
                        int size2 = lib[idx1].size();
                        if(lib[idx1][idx2]!=nullptr)   //if the some key already exists
                            {
                                if(lib[idx1][idx2]->word==word) //if the required key exists
                                {
                                    lib[idx1][idx2]->insert(book_code,page,paragraph);
                                }
                                else //collision
                                { 
                                    bool exists(false);
                                    while(idx2<size2)
                                    {
                                        if(lib[idx1][idx2] != 0)
                                        {
                                            if(lib[idx1][idx2]->word == word ) 
                                            {
                                              exists=true;
                                              break;  
                                            } 
                                        }
                                        else break;
                                        idx2++;
                                    }
                                    if(idx2==size2) //we need to resize
                                    {
                                        lib[idx1].resize(2*size2);
                                    }
                                    if(!exists)
                                    {
                                        unique_wrds++;
                                        WordLoc.push_back({idx1,idx2});
                                        lib[idx1][idx2] = new word_node(book_code , page , paragraph, word);
                                    }
                                    else
                                    {
                                        lib[idx1][idx2]->insert(book_code,page,paragraph);
                                    }
                                }
                            }
                            else
                            {
                                unique_wrds++;
                                WordLoc.push_back({idx1,idx2});
                                lib[idx1][idx2] = new word_node(book_code , page , paragraph, word);  
                            }
                        }
                        else    //vector cannot accomodate
                        {
                            unique_wrds++;
                            lib[idx1].resize(idx2+1);
                            WordLoc.push_back({idx1,idx2});
                            lib[idx1][idx2] = new word_node(book_code , page , paragraph, word);
                        }

                    }
                    else    //when 2nd vector DNe
                    {
                        unique_wrds++;
                        vector<word_node*> temp(idx2+1,nullptr);
                        WordLoc.push_back({idx1,idx2});
                        temp[idx2] = new word_node(book_code , page , paragraph, word);
                        lib[idx1]=temp;
                    }
                }
                word="";    //clear the variable for next word to be read
            }
        }
    }
    return;
}

void Dict::insert_wrd(string& word, long long freq)
{
    tot_words++;
    int idx1 = hash1(word);
    int idx2 = hash2(word);
    if(lib.size()>idx1) // key index exists
    {
    if(lib[idx1].size()!=0) //vector already exists
    {
        if(lib[idx1].size()>idx2)   //vector can accomodate the new key
        {
        int size2 = lib[idx1].size();
        if(lib[idx1][idx2]!=nullptr)   //if the some key already exists
        {
            if(lib[idx1][idx2]->word==word) //if the required key exists
            {
                lib[idx1][idx2]->gen_cnt = freq;
            }
            else //collision
            { 
                bool exists(false);
                while(idx2<size2)
                {
                    if(lib[idx1][idx2] != 0)
                    {
                        if(lib[idx1][idx2]->word == word ) 
                        {
                          exists=true;
                          break;  
                        } 
                    }
                    else break;
                    idx2++;
                }
                if(idx2==size2) //we need to resize
                {
                    lib[idx1].resize(2*size2);
                }
                if(!exists)
                {
                    unique_wrds++;
                    WordLoc.push_back({idx1,idx2});
                    lib[idx1][idx2] = new word_node(freq,word);
                }
                else
                {
                    lib[idx1][idx2]->gen_cnt = freq;
                }
                }
        }
            else
            {
                unique_wrds++;
                WordLoc.push_back({idx1,idx2});
                lib[idx1][idx2] = new word_node(freq,word);   
            }
        }
        else    //vector cannot accomodate
        {
            lib[idx1].resize(idx2+1);
            WordLoc.push_back({idx1,idx2});
            lib[idx1][idx2] = new word_node(freq,word);
            unique_wrds++;
    
        }
    }
    else    //when 2nd vector DNe
    {
        vector<word_node*> temp(idx2+1,nullptr);
        WordLoc.push_back({idx1,idx2});
        temp[idx2] = new word_node(freq,word);
        lib[idx1]=temp;
        unique_wrds++;
    }
    }
}

word_node* Dict::okrnc(string word)
{
    long long idx1= hash1(word);
    long long idx2 = hash2(word);
    if(lib[idx1].size() <= idx2) return nullptr;
    if(lib[idx1][idx2]){
        if(lib[idx1][idx2]->word==word){
            return lib[idx1][idx2];
        }
        long long length2= lib[idx1].size();
        while(idx2<length2){
            if(lib[idx1][idx2]){
                if(lib[idx1][idx2]->word==word){
                    return lib[idx1][idx2];
                }
            }
            idx2++;
        }
        return nullptr;

    }
    else {
        return nullptr;
    }
}

void Dict::dump_dictionary(string filename){
    // Implement your function here
    return;
}

int Dict::get_word_count_of_para(int book_code, int page, int paragraph)    //error detection not implemented
{
    return pwc[book_code][page][paragraph][0];
}

int Dict::hash1(string word)
{
    int index(0); 
    int sze = word.size();
    for(int i=0;i<sze;i++)
    {
    
       index += (((int(word[i])*8)+((i*i)-1))*(int(word[i])));
    }
    //max_hash+=index;
    return (index % size1);
}
int Dict::hash2(string word)
{
    int index(0); 
    int sze = word.size();
    for(int i=0;i<sze;i++)
    {
        index += (int(word[i])+i+1)*(1+i);
    }
    return (index % size2);
}