#include <iostream>
#include "list.h"
using namespace std;

List ::List(){
    size = 0;
    sentinel_head = new Node(true);
    sentinel_tail = new Node(true);
    sentinel_head->next = sentinel_tail;
    sentinel_tail->prev = sentinel_head;
}

List ::~List(){
    Node* temp1 = sentinel_head;
    while(temp1 != nullptr){
        Node* temp2 = temp1->next;
        delete temp1;
        temp1 = temp2;
    }
}

void List ::insert(int v){
    Node* temp = new Node(v, nullptr, nullptr);
    temp->prev = sentinel_tail->prev;
    temp->next = sentinel_tail;
    sentinel_tail->prev->next = temp;
    sentinel_tail->prev = temp;
    size++;
}

int List ::delete_tail(){
    if(size == 0){
        throw runtime_error("Empty Stack");
    }
    Node* temp = sentinel_tail->prev;
    sentinel_tail->prev = sentinel_tail->prev->prev;
    sentinel_tail->prev->next = sentinel_tail;
    int ans = temp->get_value();
    delete temp;
    size--;
    return ans;
}

int List ::get_size(){
    return size;
} 

Node* List ::get_head(){
    return sentinel_head;
}