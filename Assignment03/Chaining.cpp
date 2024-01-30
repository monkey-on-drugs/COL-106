#include "Chaining.h"

Chaining::Chaining(){
    bankStorage2d.resize(100000);   
    size = 0; 
}

void Chaining::createAccount(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    int hash_index = hash(id);
    Account acc;
    acc.id = id; acc.balance = count;
    bankStorage2d[hash_index].push_back(acc); size++; return;
}

std::vector<int> Chaining::getTopK(int k) {
    // IMPLEMENT YOUR CODE HERE
    std::vector<int> balances;

    for(int i = 0; i < bankStorage2d.size(); i++){
        for(int j = 0; j < bankStorage2d[i].size(); j++){
            balances.push_back((bankStorage2d[i][j]).balance);
        }
    }

    merge_sort(balances, 0, balances.size() - 1);

    if(k >= balances.size()){
        return balances;
    }
    else{
        std::vector<int> result (balances.begin(), balances.begin() + k);
        return result;
    }
}

int Chaining::getBalance(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int hash_index = hash(id);
    int index = find(hash_index, id);

    if(index == -1){
        return -1;
    }
    return bankStorage2d[hash_index][index].balance; // Placeholder return value
}

void Chaining::addTransaction(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    int hash_index = hash(id);
    int index = find(hash_index, id);
    if(index == -1){
        createAccount(id, count);
        return;
    }
    bankStorage2d[hash_index][index].balance += count;
    return;
} 

bool Chaining::doesExist(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int hash_index = hash(id);
    int index = find(hash_index, id);

    if(index == -1){
        return false;
    }
    return true; // Placeholder return value
}

bool Chaining::deleteAccount(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int hash_index = hash(id);

    int index = find(hash_index, id);

    if(index == -1){
        return false;
    }
    bankStorage2d[hash_index].erase(bankStorage2d[hash_index].begin() + index); size--;
    return true; // Placeholder return value
}

int Chaining::databaseSize() {
    // IMPLEMENT YOUR CODE HERE
    return size; // Placeholder return value
}

int Chaining::hash(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int hash_code = 0;

    for(int i = 0; i < id.size(); i++){
        hash_code += id[i]*((int)power(1.7, i));
    }

    int hashed_value = (hash_code % 100000);

    return hashed_value; // Placeholder return value
}

int Chaining::find(int hashed_index, std::string id){

    for(int i = 0; i < bankStorage2d[hashed_index].size(); i++){
        Account temp = bankStorage2d[hashed_index][i];
        if (temp.id == id){
            return i;
        }
    }
    return -1;
}

float Chaining::power(float x, int n){

    if(n == 0){
        return 1;
    }
    else{
        float y = power(x, n/2);
        if(n % 2 == 0){
            return y*y;
        }
        else{
            return y*y*x;
        }
    }
}

void Chaining::merge(std::vector<int>& vector, int start, int middle, int end){

    int n1 = middle - start + 1;
    int n2 = end - middle;

    std::vector<int> left_array(vector.begin() + start, vector.begin() + start + n1);
    std::vector<int> right_array(vector.begin() + middle + 1, vector.end());

    int i = 0;
    int j = 0;
    int k = start;

    while (i < n1 && j < n2) {
        if (left_array[i] >= right_array[j]) {
            vector[k] = left_array[i++];
        } else {
            vector[k] = right_array[j++];
        }
        k++;
    }

    while (i < n1) {
        vector[k++] = left_array[i++];
    }

    while (j < n2) {
        vector[k++] = right_array[j++];
    }
}

void Chaining::merge_sort(std::vector<int>& vector, int left, int right){
    if(left < right){
        int middle = left + (right - left) / 2;

        merge_sort(vector, left, middle);
        merge_sort(vector, middle + 1, right);
        merge(vector, left, middle, right);
    }
}
