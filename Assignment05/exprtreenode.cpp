/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICITLY clarified on Piazza. */
#include "exprtreenode.h"

//Write your code below this line

ExprTreeNode::ExprTreeNode(){
    left = right = NULL;
    type = "equals";
}

ExprTreeNode::ExprTreeNode(string t,int v){
    left = right = NULL;
    if(t == "+") type = "ADD";
    else if(t == "-") type = "SUB";
    else if(t == "*") type = "MUL";
    else if(t == "/") type = "DIV";   
    else if(t[0] == '-' || isdigit(t[0])){
        type = "VAL"; num = v;
    }
    else if(t == "del") type = "DEL";
    else if(t == "ret") type = "RET";
    else{
        type = "VAR"; id = t;
    }
}

ExprTreeNode::~ExprTreeNode(){
    
}

