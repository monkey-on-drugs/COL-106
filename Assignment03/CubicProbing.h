#ifndef CUBICPROBING_H
#define CUBICPROBING_H

#include "BaseClass.h"
#include <iostream>

class CubicProbing : public BaseClass {
public:
    CubicProbing();
    int find(int hashed_index, std::string id);
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    float power(float x, int n);
    void merge(std::vector<int>& vector, int start, int middle, int end);
    void merge_sort(std::vector<int>& vector, int left, int right);
    
private:
    int size;
    // Other data members and functions specific to Quadratic Probing
};

#endif // CUBICPROBING_H
