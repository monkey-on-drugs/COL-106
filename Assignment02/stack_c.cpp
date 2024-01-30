#include <iostream>
#include "stack_c.h"
using namespace std;

Stack_C ::Stack_C(){
    stk = new List();
}

Stack_C ::~Stack_C(){
    delete stk;
}

void Stack_C ::push(int data){
    stk->insert(data);
}

int Stack_C ::pop(){
    return stk->delete_tail();
}

int Stack_C ::get_element_from_top(int idx){

    if(idx < 0 || idx >= stk->get_size()){
        throw runtime_error("Index out of range");
    }

    Node* temp = stk->get_head(); int count = 0;

    while(count < (stk->get_size() - idx)){
        temp = temp->next;
        count++;
    }

    return temp->get_value();
}

int Stack_C ::get_element_from_bottom(int idx){

    if(idx < 0 || idx >= stk->get_size()){
        throw runtime_error("Index out of range");
    }

    Node* temp = stk->get_head(); int count = 0;

    while(count <= idx){
        temp = temp->next;
        count++;
    }

    return temp->get_value();
}

void Stack_C ::print_stack(bool top_or_bottom){
    if(top_or_bottom){
        Node* temp = stk->get_head();

        while(temp->next != nullptr){
            temp = temp->next;
        }
        temp = temp->prev;
        while(temp->prev != nullptr){
            cout << temp->get_value() << endl;
            temp = temp->prev;
        }
    }
    else{
        Node* temp = stk->get_head();
        temp = temp->next;
        while(temp->next != nullptr){
            cout << temp->get_value() << endl;
            temp = temp->next;
        }
    }
}

int Stack_C ::add(){
    if(stk->get_size() < 2){
        throw runtime_error("Not Enough Arguments");
    }
    int num1 = pop();
    int num2 = pop();
    int result = num1 + num2;
    push(result);
    return result;
}

int Stack_C ::subtract(){
    if(stk->get_size() < 2){
        throw runtime_error("Not Enough Arguments");
    }
    int num1 = pop();
    int num2 = pop();
    int result = num2 - num1;
    push(result);
    return result;
}

int Stack_C ::multiply(){
    if(stk->get_size() < 2){
        throw runtime_error("Not Enough Arguments");
    }
    int num1 = pop();
    int num2 = pop();
    int result = num1 * num2;
    push(result);
    return result;
}

int Stack_C ::divide(){
    if(stk->get_size() < 2){
        throw runtime_error("Not Enough Arguments");
    }
    float num1 = pop();
    float num2 = pop();
    if(num1 == 0){
        throw runtime_error("Divide by Zero Error");
    }

    float result = num2/num1;
    int final_result = 0;

    if(result < 0){
        final_result = (int)(result - 1);
    }
    else{
        final_result = (int)(result);
    }
    push(final_result);
    return final_result;
}

List* Stack_C ::get_stack(){
    return stk;
}

int Stack_C ::get_size(){
    return stk->get_size();
}