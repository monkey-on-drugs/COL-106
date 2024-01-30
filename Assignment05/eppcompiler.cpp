/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICITLY clarified on Piazza. */
#include "eppcompiler.h"

//Write your code below this line

EPPCompiler::EPPCompiler(){ //Constructor 01
}

EPPCompiler::EPPCompiler(string out_file,int mem_limit){ //Constructor 02
    output_file = out_file; memory_size = mem_limit;
    mem_loc.resize(memory_size);
    for(int i = 0; i < memory_size; i++){
        mem_loc.push_back(i);
    }
}

void postorder_R(ExprTreeNode* node, vector<string>& ans, Parser& target){
    if(node == NULL) return;
    postorder_R(node->right, ans, target);
    postorder_R(node->left, ans, target);

    string s;
    if(node->type == "VAL"){
        s = "PUSH " + to_string(node->num);
    }
    else if(node->type == "VAR"){
        int adr = target.symtable->search(node->id);
        if(adr == -2){
            s = "PUSH mem[" + to_string(target.last_deleted) + "]";
        }
        else{
            s = "PUSH mem[" + to_string(adr) + "]";
        }
    }
    else if(node->type == "ADD") s = "ADD";
    else if(node->type == "SUB") s = "SUB";
    else if(node->type == "MUL") s = "MUL";
    else if(node->type == "DIV") s = "DIV";

    ans.push_back(s);
}

void EPPCompiler::compile(vector<vector<string>> code){
    ofstream myfile; myfile.open(output_file); myfile.close();

    for(long unsigned int i = 0; i < code.size(); i++){

        targ.parse(code[i]); //Parse tree made
        
        if(targ.expr_trees.back()->left->type == "VAR"){ //Assigning the memory
            int current_address = targ.symtable->search(targ.expr_trees.back()->left->id);
            if(current_address == -1){
                int address = mem_loc.back(); mem_loc.pop_back();
                targ.symtable->assign_address(targ.expr_trees.back()->left->id, address);
            }
        }
        if(targ.expr_trees.back()->left->type == "DEL"){ 
            mem_loc.push_back(targ.last_deleted);
        }
        vector<string> answer;
        postorder_R(targ.expr_trees.back()->right, answer, targ); //Generating the target code

        string s;
        if(targ.expr_trees.back()->left->type == "DEL"){
            s = "DEL = mem[" + to_string(targ.last_deleted) + "]";
        }
        else if(targ.expr_trees.back()->left->type == "RET"){
            s = "RET = POP";
        }
        else if(targ.expr_trees.back()->left->type == "VAR"){
            s = "mem[" + to_string(targ.symtable->search(targ.expr_trees.back()->left->id)) + "] = POP";
        }
        answer.push_back(s);

        write_to_file(answer);

    }
    return;

}

vector<string> EPPCompiler::generate_targ_commands(){
}

void EPPCompiler::write_to_file(vector<string> commands){
    ofstream myfile; myfile.open(output_file, ios::app);
    if(myfile.is_open()){
        for(long unsigned int i = 0; i < commands.size(); i++){
            myfile << commands[i] << "\n";
        }
    }
    myfile.close();
}

EPPCompiler::~EPPCompiler(){
}
