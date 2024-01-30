#include "CubicProbing.h"

CubicProbing::CubicProbing(){
    bankStorage1d.resize(100019);
    size = 0;
}

void CubicProbing::createAccount(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    int hash_index = hash(id);
    Account acc;
    acc.id = id; acc.balance = count;
    int i = 1; int start_index = hash_index; int j = 1;

    do{
        if(bankStorage1d[hash_index].id == ""){
            bankStorage1d[hash_index] = acc; size++; return;
        }
        hash_index = (hash_index + i*i*i) % bankStorage1d.size(); i++;

        if(i >= bankStorage1d.size()){
            hash_index = (start_index + (j++)) % bankStorage1d.size();
            i = 1;
        }
    }
    while (hash_index != start_index);
}

std::vector<int> CubicProbing::getTopK(int k) {
    // IMPLEMENT YOUR CODE HERE
    std::vector<int> balances;

    for(int i = 0; i < bankStorage1d.size(); i++){
        if(bankStorage1d[i].id != ""){
            balances.push_back((bankStorage1d[i]).balance);
        }
    }

    merge_sort(balances, 0, balances.size() - 1);

    if(k >= balances.size()){
        return balances;
    }
    else{
        std::vector<int> result(balances.begin(), balances.begin() + k);
        return result;
    }
}

int CubicProbing::getBalance(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int hash_index = hash(id);
    int index = find(hash_index, id);

    if(index == -1){
        return -1;
    }
    return bankStorage1d[index].balance; // Placeholder return value
}

void CubicProbing::addTransaction(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    int hash_index = hash(id);
    int index = find(hash_index, id);
    if(index == -1){
        createAccount(id, count);
        return;
    }
    bankStorage1d[index].balance += count;
    return;
}

bool CubicProbing::doesExist(std::string id) {
    // IMPLEMENT YOUR CODE HERE

    int hash_index = hash(id);
    int index = find(hash_index, id);

    if(index == -1){
        return false;
    }
    return true; // Placeholder return value
}

bool CubicProbing::deleteAccount(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int hash_index = hash(id);

    int index = find(hash_index, id);

    if(index == -1){
        return false;
    }
    bankStorage1d[index].id = ""; size--;
    return true; // Placeholder return value
}
int CubicProbing::databaseSize() {
    // IMPLEMENT YOUR CODE HERE
    return size; // Placeholder return value
}

int CubicProbing::hash(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int hash_code = 0;

    for(int i = 0; i < id.size(); i++){
        hash_code += id[i]*((int)power(1.7, i));
    }

    int hashed_value = (hash_code % bankStorage1d.size());

    return hashed_value; // Placeholder return value
}

int CubicProbing::find(int hashed_index, std::string id){
    int i = 1; int start_index = hashed_index; int j = 1;
    do{
        if(bankStorage1d[hashed_index].id == id){
            return hashed_index;
        }
        hashed_index = (hashed_index + i*i*i) % bankStorage1d.size(); i++;

        if(i >= bankStorage1d.size()){
            hashed_index = (start_index + (j++)) % bankStorage1d.size();
            i = 1;
        }
    }
    while (hashed_index != start_index);
    return -1;
}

float CubicProbing::power(float x, int n){

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

void CubicProbing::merge(std::vector<int>& vector, int start, int middle, int end){

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

void CubicProbing::merge_sort(std::vector<int>& vector, int left, int right){
    if(left < right){
        int middle = left + (right - left) / 2;

        merge_sort(vector, left, middle);
        merge_sort(vector, middle + 1, right);
        merge(vector, left, middle, right);
    }
}