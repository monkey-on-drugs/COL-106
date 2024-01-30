#ifndef COMP_H
#define COMP_H

#include "BaseClass.h"
#include <iostream>
#include <vector>

class Comp : public BaseClass {
public:
    Comp();
    int find(int hashed_index, int second_hashed_index, std::string id);
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    int hash2(std::string id);
    float power(float x, int n);
    void merge(std::vector<int>& vector, int start, int middle, int end);
    void merge_sort(std::vector<int>& vector, int left, int right);
    void increase_size();
    void decrease_size();
    
private:
    int size;
    float alpha = 0.7;
    // Other data members and functions specific to Your implementation
};

#endif // COMP_H
