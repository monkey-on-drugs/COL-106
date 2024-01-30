/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICITLY clarified on Piazza. */
#include "exprtreenode.h"

ExprTreeNode::ExprTreeNode(){
    left = nullptr; right = nullptr;
    type = "equals";
    val = nullptr; evaluated_value = nullptr;
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedInt *v){
    left = nullptr; right = nullptr;
    val = nullptr; evaluated_value = nullptr;
    if(t == "+") type = "ADD";
    else if(t == "-") type = "SUB";
    else if(t == "*") type = "MUL";
    else if(t == "/") type = "DIV";
    else if (t == "%") type = "MOD";
    else if(t[0] == '-' || isdigit(t[0])){
        type = "VAL";
        UnlimitedInt* one = new UnlimitedInt(1);
        val = new UnlimitedRational(v, one); 
        evaluated_value = new UnlimitedRational(v, one);
        delete one;
    }
    else{
        type = "VAR"; id = t;
    }
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedRational *v){
    left = nullptr; right = nullptr;
    val = nullptr; evaluated_value = nullptr;
    if(t == "+") type = "ADD";
    else if(t == "-") type = "SUB";
    else if(t == "*") type = "MUL";
    else if(t == "/") type = "DIV";
    else if (t == "%") type = "MOD";
    else if(t[0] == '-' || isdigit(t[0])){
        type = "VAL";
        val = new UnlimitedRational(v->get_p(), v->get_q());
        evaluated_value = new UnlimitedRational(v->get_p(), v->get_q());
    }
    else{
        type = "VAR"; id = t;
        val = new UnlimitedRational(v->get_p(), v->get_q());
        evaluated_value = new UnlimitedRational(v->get_p(), v->get_q());
    }
}

ExprTreeNode::~ExprTreeNode(){
    if(val != nullptr){
        delete val;
        val = nullptr;
    }
    if(evaluated_value != nullptr){
        delete evaluated_value;
        evaluated_value = nullptr;
    }

}
