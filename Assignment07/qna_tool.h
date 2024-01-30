#pragma once
#include <iostream>
#include <fstream>
#include "Node.h"
#include "dict.h"
#include "search.h"

using namespace std;

class MaxHeap {

private:
    vector<pair< double, vector<int>>> heap;
    int size;

public:

    MaxHeap(){
        size = 0;
    }

    int getLeftChild(int index) {return 2*index + 1;}
    int getRightChild(int index) {return 2*index + 2;}
    int getParent(int index) {return (index - 1)/2;}

    void heapifyUP(int at){

        if(at == 0) return;

        int parIndex = getParent(at);
        auto current = heap[at];
        auto parent = heap[parIndex];

        if(current.first >= parent.first){
            swap(heap[at], heap[parIndex]);
            heapifyUP(parIndex);
        }
    }

    void insert(pair< double, vector<int>> to_insert){
        heap.push_back(to_insert);
        heapifyUP(size);
        size++;
    }

    void heapifyDOWN(int at){

        int leftChildIndex = getLeftChild(at);
        int rightChildIndex = getRightChild(at);

        if(leftChildIndex >= size) return;

        auto current = heap[at];
        auto leftChild = heap[leftChildIndex];

        if(rightChildIndex >= size){
            if(leftChild.first >= current.first){
                swap(heap[at], heap[leftChildIndex]);
                return;
            }
        }

        auto rightChild = heap[rightChildIndex];

        if(leftChild.first >= current.first && leftChild.first >= rightChild.first){
            swap(heap[at], heap[leftChildIndex]);
            heapifyDOWN(leftChildIndex);
        }
        else if(rightChild.first >= current.first && rightChild.first >= leftChild.first){
            swap(heap[at], heap[rightChildIndex]);
            heapifyDOWN(rightChildIndex);
        }
        return;
    }
    

    pair< double, vector<int>> deleteMax(){
        auto max = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        size--;
        heapifyDOWN(0);
        return max;
    }

    vector<vector<int>> get_sorted(int top_k){
        vector<vector<int>> answer(top_k);

        for(int i = 0; i < top_k && size > 0; i++){
            auto max = deleteMax();
            answer[i] = max.second;
        }
        return answer;
    }
};

class QNA_tool {

private:

    // You are free to change the implementation of this function
    void query_llm(string filename, Node* root, int k, string API_KEY, string question);
    // filename is the python file which will call ChatGPT API
    // root is the head of the linked list of paragraphs
    // k is the number of paragraphs (or the number of nodes in linked list)
    // API_KEY is the API key for ChatGPT
    // question is the question asked by the user

    // You can add attributes/helper functions here

public:

    /* Please do not touch the attributes and
    functions within the guard lines placed below  */
    /* ------------------------------------------- */

    Dict dict;
    
    QNA_tool(); // Constructor
    ~QNA_tool(); // Destructor
    
    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);
    // This function is similar to the functions in dict and search 
    // The corpus will be provided to you via this function
    // It will be called for each sentence in the corpus

    Node* get_top_k_para(string question, int k);
    // This function takes in a question, preprocess it
    // And returns a list of paragraphs which contain the question
    // In each Node, you must set: book_code, page, paragraph (other parameters won't be checked)

    std::string get_paragraph(int book_code, int page, int paragraph);
    // Given the book_code, page number, and the paragraph number, returns the string paragraph.
    // Searches through the corpus.

    void query(string question, string filename);
    // This function takes in a question and a filename.
    // It should write the final answer to the specified filename.

    /* -----------------------------------------*/
    /* Please do not touch the code above this line */
    
    // You can add attributes/helper functions here

    long double occurence_in_general_corpus(string& word);
    void get_para_score(string word, word_node* _word_node_, vector<vector<int>>& intermediate_result); 
    const int size1 = 24593;
    const int size2 = 1019;

    Node* LLM_get_top_k_para(string question, int k);
    void LLM_get_para_score(string word, word_node* _word_node_, vector<vector<int>>& intermediate_result); 
    void LLM_query(string filename, Node* root, int k, string question);

};