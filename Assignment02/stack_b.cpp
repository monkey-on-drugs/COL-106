#include <iostream>
#include "stack_b.h"
using namespace std;

Stack_B ::Stack_B(){
    capacity = 1024; size = 0;
    stk = new int [1024];
    try{
        stk = new int[1024];
    }
    catch (bad_alloc &ba){
        throw runtime_error("Out of Memory");
    }
}

Stack_B ::~Stack_B(){
    delete []stk;
}

void Stack_B ::push(int data){
    if(size == capacity){
        int* result = new int [2*capacity];
        for(int i = 0; i < size; i++){
            result[i] = stk[i];
        }
        delete []stk;
        stk = result;
        capacity *= 2;
    }
    stk[size++] = data;
}

int Stack_B ::pop(){
    if(size == 0){
        throw runtime_error("Empty Stack");
    }
    if(size <= capacity/4 && capacity > 1024){
        int* result = new int[capacity/2];
        for(int i = 0; i < size; i++){
            result[i] = stk[i];
        }
        delete []stk;
        stk = result;
        capacity /= 2;
    }
    return stk[--size];
}

int Stack_B ::get_element_from_top(int idx){
    int val = size - 1 - idx;
    if(val < 0 || val >= size){
        throw runtime_error("Index out of range");
    }
    return stk[val];
}

int Stack_B ::get_element_from_bottom(int idx){
    if(idx < 0 || idx >= size){
        throw runtime_error("Index out of range");
    }
    return stk[idx];
}

void Stack_B ::print_stack(bool top_or_bottom){
    if(top_or_bottom){
        for(int i = size - 1; i >= 0; i--){
            cout << stk[i] << endl;
        }
    }
    else{
        for(int i = 0; i < size; i++){
            cout << stk[i] << endl;
        } 
    }
}

int Stack_B ::add(){
    if(size < 2){
        throw runtime_error("Not Enough Arguments");
    }
    int num1 = pop();
    int num2 = pop();
    int result = num1 + num2;
    push(result);
    return result;
}

int Stack_B ::subtract(){
    if(size < 2){
        throw runtime_error("Not Enough Arguments");
    }
    int num1 = pop();
    int num2 = pop();
    int result = num2 - num1;
    push(result);
    return result;
}

int Stack_B ::multiply(){
    if(size < 2){
        throw runtime_error("Not Enough Arguments");
    }
    int num1 = pop();
    int num2 = pop();
    int result = num1 * num2;
    push(result);
    return result;
}

int Stack_B ::divide(){
    if(size < 2){
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

int* Stack_B ::get_stack(){
    return stk;
}

int Stack_B ::get_size(){
    return size;
}
