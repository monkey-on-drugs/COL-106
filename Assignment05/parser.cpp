/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICITLY clarified on Piazza. */
#include "parser.h"

//Write your code below this line

Parser::Parser(){
    symtable= new SymbolTable();
}

void Parser::parse(vector<string> expression){
    ExprTreeNode* root = new ExprTreeNode();
    ExprTreeNode* LHS = new ExprTreeNode(expression[0], 0000);
    ExprTreeNode* RHS = new ExprTreeNode();
    root->left = LHS; root->right = RHS;

    ExprTreeNode* temp = RHS;
    vector<ExprTreeNode*> parents;
    parents.push_back(root);

    for(long unsigned int i = 2; i < expression.size(); i++){
        if(expression[i] == "("){
            ExprTreeNode* left_new_node = new ExprTreeNode();
            temp->left = left_new_node; parents.push_back(temp);
            temp = left_new_node;
        }
        else if(expression[i] == ")"){
            temp = parents.back(); parents.pop_back();
        }
        else if(expression[i] == "+" || expression[i] == "-" || expression[i] == "*" || expression[i] == "/"){
            ExprTreeNode* right_new_node = new ExprTreeNode(expression[i], 0000);
            right_new_node->left = temp->left;
            ExprTreeNode* parent = parents.back();
            if(parent->right == temp){
                parent->right = right_new_node;
            }
            else{
                parent->left = right_new_node;
            }
            temp->left = NULL; temp->right = NULL;
            right_new_node->right = temp;
            parents.push_back(right_new_node);
        }
        else if(expression[i][0] == '-' || isdigit(expression[i][0])){
            ExprTreeNode* value = new ExprTreeNode("1", stoi(expression[i]));
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
            ExprTreeNode* value = new ExprTreeNode(expression[i], 0000);
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

    //Making changes in SymTable
    if(LHS->type == "VAR"){ //Inserting on variable assignment
        symtable->insert(LHS->id);
    }
    else if(LHS->type == "DEL"){ //Deleting on del
        last_deleted = symtable->search(expression[2]);
        symtable->remove(expression[2]);
    }
    //None on return
}

void postorder_parser_del(ExprTreeNode* node){
    if(node != NULL){
        postorder_parser_del(node->left);
        postorder_parser_del(node->right);
        delete node; node = NULL;
    }
}

Parser::~Parser(){
    for (long unsigned int i = 0; i < expr_trees.size(); i++){
        postorder_parser_del(expr_trees[i]);
    }
    delete symtable;
}