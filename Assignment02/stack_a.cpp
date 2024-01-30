#include <iostream>
#include "./stack_a.h"
using namespace std;

Stack_A ::Stack_A() {
    size = 0;
}

void Stack_A ::push(int data){
    if(size == 1024){
        throw runtime_error("Stack Full");
    }
    stk[size++] = data;
}

int Stack_A ::pop(){
    if(size == 0){
        throw runtime_error("Empty Stack");
    }
    return stk[--size];
}

int Stack_A ::get_element_from_top(int idx){
    int val = size - 1 - idx;
    if(val < 0 || val >= size){
        throw runtime_error("Index out of range");
    }
    return stk[val];
}

int Stack_A ::get_element_from_bottom(int idx){
    if(idx < 0 || idx >= size){
        throw runtime_error("Index out of range");
    }
    return stk[idx];
}

void Stack_A ::print_stack(bool top_or_bottom){
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

int Stack_A ::add(){
    if(size < 2){
        throw runtime_error("Not Enough Arguments");
    }
    int num1 = pop();
    int num2 = pop();
    int result = num1 + num2;
    push(result);
    return result;
}

int Stack_A ::subtract(){
    if(size < 2){
        throw runtime_error("Not Enough Arguments");
    }
    int num1 = pop();
    int num2 = pop();
    int result = num2 - num1;
    push(result);
    return result;
}

int Stack_A ::multiply(){
    if(size < 2){
        throw runtime_error("Not Enough Arguments");
    }
    int num1 = pop();
    int num2 = pop();
    int result = num1 * num2;
    push(result);
    return result;
}

int Stack_A ::divide(){
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

int* Stack_A ::get_stack(){
    return stk;
}

int Stack_A ::get_size(){
    return size;
}