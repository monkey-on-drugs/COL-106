/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICITLY clarified on Piazza. */
#include "symtable.h"

//Write your code below this line

SymbolTable::SymbolTable(){
    size = 0;
    root = new SymNode();
}

int balance_factor(SymNode* node){

    int left_height, right_height;

    if(node->left != NULL){
        left_height = node->left->height;
    }
    else{
        left_height = -1;
    }

    if(node->right == NULL){
        right_height = -1;
    }
    else{
        right_height = node->right->height;
    }

    return (left_height - right_height);
}

int my_max_symtable(SymNode* left, SymNode* right){
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

void SymbolTable::insert(string k){

    if(size == 0){
        root->key = k; size++;
        return;
    }

    SymNode* new_node = new SymNode(k);
    SymNode* temp = root;

    while(true){
        if(temp->key < k){
            if(temp->right == NULL){
                temp->right = new_node; new_node->par = temp; temp->height++;
                break;
            }
            temp->height++; temp = temp->right;
        }
        else if(temp->key > k){
            if(temp->left == NULL){
                temp->left = new_node; new_node->par = temp; temp->height++;
                break;
            }
            temp->height++; temp = temp->left;
        }
        else{
            temp = temp->par;
            while(temp!= NULL){
                temp->height--;
                temp = temp->par;
            }
            return;
        }
    }
    temp = new_node;

    while(temp->par != NULL && (balance_factor(temp) != 2 && balance_factor(temp) != -2)){
        temp = temp->par;
    }

    if(balance_factor(temp) == 2){
        if(balance_factor(temp->left) == -1){ //RL
            temp = temp->RightLeftRotation();
        }
        else{ //RR
            temp = temp->RightRightRotation();
        }
    }
    else if(balance_factor(temp) == -2){
        if(balance_factor(temp->right) == 1){ //LR
            temp = temp->LeftRightRotation();
        }
        else{ //LL
            temp = temp->LeftLeftRotation();
        }
    }
    if(temp->par == NULL) root = temp;
    temp = temp->par;

    while(temp != NULL){
        temp->height = my_max_symtable(temp->left, temp->right) + 1;
        temp = temp->par;
    }

    size++;
}

SymNode* my_successor(SymNode* node){
    SymNode* temp = node->right;
    while(temp->left != NULL) temp = temp->left;
    return temp;
}

void SymbolTable::remove(string k){
    SymNode* temp = root;

    while(temp != NULL){
        if(temp->key < k){
            temp = temp->right;
        }
        else if(temp->key > k){
            temp = temp->left;
        }
        else{
            break;
        }
    }

    if(temp == NULL){
        return;
    }

    SymNode* temp_par = temp->par; //For height Balance

    if(temp_par == NULL){ //Root Deletion: temp == root: No height balance required in Case 1 and Case 2.
        if(temp->left == NULL && temp->right == NULL){ //Case 1: No Child
            root = NULL; delete temp; return;
        }
        if(temp->right == NULL){ //Case 2.a: Child on left side
            root = temp->left; root->par = NULL;
            delete temp; return;
        }
        if(temp->left == NULL){ //Case 2.b: Child on right side
            root = temp->right; root->par = NULL;
            delete temp; return;
        }
    }

    if(temp->left != NULL && temp->right != NULL){ //Case 3: Both child: Temp could be Root or Internal Node
        SymNode* successor = my_successor(temp); 
        SymNode* successor_par = successor->par;
        temp->key = successor->key;
        temp_par = successor_par; temp = successor;
    }

    if(temp->left == NULL && temp->right == NULL){ //Case 1: No child
        if(temp_par->left == temp){
            temp_par->left = NULL; delete temp;
        }
        else{
            temp_par->right = NULL; delete temp;
        }
    }
    else if(temp->left != NULL && temp->right == NULL){ //Case 2.a: Child on left side
        if(temp_par->left == temp){
            temp_par->left = temp->left; temp->left->par = temp_par; delete temp;
        }
        else{
            temp_par->right = temp->left; temp->left->par = temp_par; delete temp;
        }
    }
    else if(temp->left == NULL && temp->right != NULL){ //Case 2.b: Child on right side
        if(temp_par->left == temp){
            temp_par->left = temp->right; temp->right->par = temp_par; delete temp;
        }
        else{
            temp_par->right = temp->right; temp->right->par = temp_par; delete temp;
        }
    }

    //Now height balancing after removal
    while(temp_par != NULL){

        //First updating the height
        temp = temp_par;
        while(temp != NULL){
            temp->height = my_max_symtable(temp->left, temp->right) + 1;
            temp = temp->par;
        }

        //Then finding imbalance
        temp = temp_par;
        while(temp->par != NULL && (balance_factor(temp) != 2 && balance_factor(temp) != -2)){
            temp = temp->par;
        }
        SymNode* start_from = temp->par; //Storing the parent node of imbalance to check its imbalance in next iteration
        if(balance_factor(temp) == 2){
            if(balance_factor(temp->left) == -1){ //RL
                temp = temp->RightLeftRotation();
            }
            else{ //RR
                temp = temp->RightRightRotation();
            }
        }
        else if(balance_factor(temp) == -2){
            if(balance_factor(temp->right) == 1){ //LR
                temp = temp->LeftRightRotation();
            }
            else{ //LL
                temp = temp->LeftLeftRotation();
            }
        }
        if(temp->par == NULL) root = temp;
        temp_par = start_from;
    }
    size--;
}

int SymbolTable::search(string k){
    SymNode* temp = root;

    while(temp != NULL){
        if(temp->key < k){
            temp = temp->right;
        }
        else if(temp->key > k){
            temp = temp->left;
        }
        else{
            break;
        }
    }

    if(temp != NULL){
        return temp->address;
    }
    return -2;
}

void SymbolTable::assign_address(string k,int idx){
    SymNode* temp = root;

    while(temp != NULL){
        if(temp->key < k){
            temp = temp->right;
        }
        else if(temp->key > k){
            temp = temp->left;
        }
        else{
            break;
        }
    }

    if(temp != NULL){
        temp->address = idx;
        return;
    }
    temp->address = -1;
}

int SymbolTable::get_size(){
    return size;
}

SymNode* SymbolTable::get_root(){
    return root;
}

void postorder(SymNode* node){
    if(node == NULL) return;
    postorder(node->left);
    postorder(node->right);

    if(node->par != NULL){
        if(node->par->left == node){
            node->par->left = NULL; 
        }
        else if(node->par->right == node){
            node->par->right = NULL;
        }
    }
    delete node;
}

SymbolTable::~SymbolTable(){
    postorder(root);
}