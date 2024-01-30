/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICITLY clarified on Piazza. */
#include "symnode.h"

//Write your code below this line

SymNode::SymNode(){
    left = NULL; right = NULL; par = NULL;
    height = 0; address = -1;
}

SymNode::SymNode(string k){
    left = NULL; right = NULL; par = NULL;
    height = 0; key = k; address = -1;
}

int my_max_symnode(SymNode* left, SymNode* right){
    int left_h, right_h;
    if(left == NULL){
        left_h = -1;
    }
    else{
        left_h = left->height;
    }

    if(right == NULL){
        right_h = -1;
    }
    else{
        right_h = right->height;
    }

    if(left_h > right_h) return left_h;
    else return right_h;
}

SymNode* SymNode::LeftLeftRotation(){
    SymNode* temp = this->right; temp->par = this->par;
    this->right = temp->left; 
    if(temp->left != NULL) temp->left->par = this;
    temp->left = this; this->par = temp;

    if(temp->par != NULL){
        if(temp->par->left == this){
            temp->par->left = temp;
        }
        else if(temp->par->right == this){
            temp->par->right = temp;
        }
    }

    this->height = my_max_symnode(this->left, this->right) + 1;
    temp->height = my_max_symnode(temp->left, temp->right) + 1;

    return temp;
}

SymNode* SymNode::RightRightRotation(){
    SymNode* temp = this->left; temp->par = this->par;
    this->left = temp->right; 
    if(temp->right != NULL) temp->right->par = this;
    temp->right = this; this->par = temp;

    if(temp->par != NULL){
        if(temp->par->left == this){
            temp->par->left = temp;
        }
        else if(temp->par->right == this){
            temp->par->right = temp;
        }
    }

    this->height = my_max_symnode(this->left, this->right) + 1;
    temp->height = my_max_symnode(temp->left, temp->right) + 1;

    return temp;
}

SymNode* SymNode::LeftRightRotation(){
    SymNode* temp = this->right->RightRightRotation();
    temp = this->LeftLeftRotation();
    return temp;
}

SymNode* SymNode::RightLeftRotation(){
    SymNode* temp = this->left->LeftLeftRotation();
    temp = this->RightRightRotation();
    return temp;
}

SymNode::~SymNode(){

}