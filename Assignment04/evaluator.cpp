/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICITLY clarified on Piazza. */
#include "evaluator.h"

Evaluator::Evaluator(){
    symtable = new SymbolTable();
}

void post_order_delete(ExprTreeNode* node){
    if(node != nullptr){
        post_order_delete(node->left);
        post_order_delete(node->right);
        delete node; node = nullptr;
    }
}

Evaluator::~Evaluator(){
    for(int i = expr_trees.size() - 1; i >= 0; i--){
        post_order_delete(expr_trees[i]);
    }
    delete symtable;
}

void Evaluator::parse(vector<string> code){

    ExprTreeNode* root = new ExprTreeNode();
    
    ExprTreeNode* LHS = new ExprTreeNode();
    LHS->id = code[0]; LHS->type = "VAR";
    root->left = LHS;
    
    ExprTreeNode* RHS = new ExprTreeNode();
    root->right = RHS;
    
    ExprTreeNode* temp = RHS;
    
    vector<ExprTreeNode*> parents;
    parents.push_back(root);
    
    for(long unsigned int i = 2; i < code.size(); i++){
        if(code[i] == "("){
            ExprTreeNode* left_new_node = new ExprTreeNode();
            temp->left = left_new_node; 
            parents.push_back(temp);
            temp = left_new_node;
        }
        else if(code[i] == "+" || code[i] == "-" || code[i] == "*" || code[i] == "/" || code[i] == "%"){
            ExprTreeNode* right_new_node = new ExprTreeNode(code[i], new UnlimitedInt(1));
            right_new_node->left = temp->left;
            ExprTreeNode* parent = parents.back();
            if(parent->right == temp){
                parent->right = right_new_node;
            }
            else{
                parent->left = right_new_node;
            }
            temp->left = nullptr; temp->right = nullptr;
            right_new_node->right = temp;
            parents.push_back(right_new_node);
        }
        else if(code[i] == ")"){
            temp = parents.back();
            parents.pop_back();
        }
        else if(code[i][0] == '-' || isdigit(code[i][0])){
            UnlimitedInt* num = new UnlimitedInt(code[i]);
            UnlimitedInt* one = new UnlimitedInt(1);
            UnlimitedRational* v = new UnlimitedRational(num, one);
            ExprTreeNode* value = new ExprTreeNode(code[i], v);
            delete num; delete one;
            ExprTreeNode* parent = parents.back();
            if(parent->right == temp){
                parent->right = value;
            }
            else{
                parent->left = value;
            }
            temp = parents.back();
            parents.pop_back();
        }
        else{
            UnlimitedRational* variable = symtable->search(code[i]);
            ExprTreeNode* value = new ExprTreeNode(code[i], variable);
            ExprTreeNode* parent = parents.back();
            if(parent->right == temp){
                parent->right = value;
            }
            else{
                parent->left = value;
            }
            temp = parents.back();
            parents.pop_back();
        }
    }
    expr_trees.push_back(root);
}

UnlimitedRational* postorder(ExprTreeNode* node) {
    if (node->left == nullptr || node->right == nullptr) return node->val;

    if(node->left != nullptr && node->right != nullptr){
        UnlimitedRational* left = postorder(node->left);
        UnlimitedRational* right = postorder(node->right);
        if(node->type == "ADD"){
            node->evaluated_value = UnlimitedRational::add(left, right);
        }
        else if(node->type == "SUB"){
            node->evaluated_value = UnlimitedRational::sub(left, right);
        }
        else if(node->type == "MUL"){
            node->evaluated_value = UnlimitedRational::mul(left, right);
        }
        else if(node->type == "DIV"){
            node->evaluated_value = UnlimitedRational::div(left, right);
        }
        return node->evaluated_value;
    }
}

void Evaluator::eval(){
    ExprTreeNode* root = expr_trees.back();
    string LHS = root->left->id;
    UnlimitedRational* RHS = postorder(root->right);
    symtable->insert(LHS, RHS);
}
