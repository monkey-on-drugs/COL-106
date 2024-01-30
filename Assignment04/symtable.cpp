/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICITLY clarified on Piazza. */
#include "symtable.h"

void postorder(SymEntry* node) {
    if(node != nullptr){
        postorder(node->left);
        postorder(node->right);
        delete node; node = nullptr;
    }
}

SymbolTable::SymbolTable(){
    root = nullptr; size = 0;
}

SymbolTable::~SymbolTable(){
    postorder(root);
}

void SymbolTable::insert(string k, UnlimitedRational *v){
    SymEntry *new_entry = new SymEntry(k, v);
    if(root == nullptr){
        root = new_entry;
    }
    else{
        SymEntry *temp = root;
        while(temp != nullptr){
            if(k < temp->key){
                if(temp->left == nullptr){
                    temp->left = new_entry;
                    break;
                }
                else{
                    temp = temp->left;
                }
            }
            else if(k > temp->key){
                if(temp->right == nullptr){
                    temp->right = new_entry;
                    break;
                }
                else{
                    temp = temp->right;
                }
            }
            else{
                delete new_entry;
                return;
            }
        }
    }
    size++;
}

SymEntry* my_min(SymEntry* node) {
    while (node->left)
        node = node->left;
    return node;
}

SymEntry* my_delete(SymEntry* head, string k) {
    if (head == nullptr) return nullptr;
    
    if (head->key == k) {
        if (head->left == nullptr) return head->right;
        if (head->right == nullptr) return head->left;
        
        SymEntry* minNode = my_min(head->right);
        SymEntry* parent = head;
        while (parent->left != minNode && parent->right != minNode) {
            if (minNode->key < parent->key) {
                parent = parent->left;
            } else {
                parent = parent->right;
            }
        }
        head->key = minNode->key;
        head->val = minNode->val;
        if (parent->left == minNode) {
            parent->left = minNode->right;
        } else {
            parent->right = minNode->right;
        }
        delete minNode;
    } 
    else if (head->key < k) head->right = my_delete(head->right, k);
    else head->left = my_delete(head->left, k);
    return head;
}

void SymbolTable::remove(string k){
        SymEntry* new_root = my_delete(root, k);
        root = new_root;
        size--;
}

UnlimitedRational *SymbolTable::search(string k){
    SymEntry *temp = root;
    while(temp != nullptr){
        if(k < temp->key){
            temp = temp->left;
        }
        else if(k > temp->key){
            temp = temp->right;
        }
        else{
            return temp->val;
        }
    }
    return nullptr;
}

int SymbolTable::get_size(){
    return size;
}

SymEntry *SymbolTable::get_root(){
    return root;
}
