#include <iostream>
#include <vector>
using namespace std;

class SET {
    public:
    vector<vector<int>*> vector_of_pointers;

    ~SET(){
        for (int i = 0; i < vector_of_pointers.size(); i++){
            delete vector_of_pointers[i];
        }
        vector_of_pointers.clear();
    }

    int find_element(vector<int> set, int element){

        int start = 0; int end = set.size() - 1; 
        int mid;

        while(start <= end){
            mid = start + (end - start)/2;
            if(set[mid] == element){
                return mid;
            }
            else if(set[mid] < element){
                start = mid + 1;
            }
            else if (set[mid] > element){
                end = mid - 1;
            }
        }
        return -1;
    }

    int my_insert(int set_num, int data){ //O(n)

        if(vector_of_pointers.size() <= set_num){
            vector<int>* temp = new vector<int>; 
            vector_of_pointers.push_back(temp);
            (*temp).push_back(data);
            return (*temp).size();
        }

        vector<int> (*temp) = vector_of_pointers[set_num];

        if((*temp).size() == 0){
            (*temp).insert((*temp).begin(), data);
            return (*temp).size();
        }

        if(data < (*temp)[0]){
            (*temp).insert((*temp).begin(), data);
            return (*temp).size();
        }
        else if(data > (*temp)[(*temp).size() - 1]){
            (*temp).insert((*temp).begin() + (*temp).size(), data);
            return (*temp).size();
        }

        for(int i = 0; i < (*temp).size() - 1; i++){
            if(data > (*temp)[i] && data < (*temp)[i + 1]){
                (*temp).insert((*temp).begin() + i + 1, data);
                break;
            }
            else if((data == (*temp)[i] || data == (*temp)[i + 1])){
                break;
            }
        }
        return (*temp).size();
    }

    int my_delete(int set_num, int data){ //O(log(n))

        if (vector_of_pointers.size() <= set_num){
            return -1;
        }

        vector<int>* temp = vector_of_pointers[set_num];
        int to_delete = find_element((*temp), data);

        if(to_delete == -1){
            return (*temp).size();
        }
        else{
            (*temp).erase((*temp).begin() + to_delete);
            return (*temp).size();
        }
    }

    int my_belongs_to(int set_num, int data){ // O(log(n))

        if (vector_of_pointers.size() <= set_num){
            return -1;
        } 

        vector<int>* temp = vector_of_pointers[set_num];
        int to_delete = find_element((*temp), data);

        if(to_delete == -1){
            return 0;
        }
        else{
            return 1;
        }
    }

    int my_union(int set_num1, int set_num2){ // O(n)

        if (vector_of_pointers.size() <= set_num1){
            vector<int>* temp = new vector<int>; 
            vector_of_pointers.push_back(temp);
        }
        if (vector_of_pointers.size() <= set_num2){
            vector<int>* temp = new vector<int>; 
            vector_of_pointers.push_back(temp); 
        }

        vector<int>* temp1 = vector_of_pointers[set_num1];
        vector<int>* temp2 = vector_of_pointers[set_num2];

        if(set_num1 == set_num2){
            return (*temp1).size();
        }

        int i = 0; int j = 0; vector<int> result;
        while (i < (*temp1).size() && j < (*temp2).size()){
            if((*temp1)[i] < (*temp2)[j]){
                result.push_back((*temp1)[i++]); 
            }
            else if((*temp1)[i] > (*temp2)[j]){
                result.push_back((*temp2)[j++]);
            }else {
                result.push_back((*temp1)[i]);
                i++;
                j++;
            }
        }

        while(i < (*temp1).size()){
            result.push_back((*temp1)[i++]);
        }

        while(j < (*temp2).size()){
            result.push_back((*temp2)[j++]);
        }
        temp1->swap(result);
        return (*temp1).size();
    }

    int my_intersection(int set_num1, int set_num2){ //O(n)

        if (vector_of_pointers.size() <= set_num1){
            vector<int>* temp = new vector<int>; 
            vector_of_pointers.push_back(temp);
        }
        if (vector_of_pointers.size() <= set_num2){
            vector<int>* temp = new vector<int>; 
            vector_of_pointers.push_back(temp); 
        }

        vector<int>* temp1 = vector_of_pointers[set_num1];
        vector<int>* temp2 = vector_of_pointers[set_num2];

        if(set_num1 == set_num2){
            return (*temp1).size();
        }

        int i = 0; int j = 0; vector<int> result;
        while (i < (*temp1).size() && j < (*temp2).size()){
            if((*temp1)[i] < (*temp2)[j]){
                i++; 
            }
            else if((*temp1)[i] > (*temp2)[j]){
                j++;
            }else {
                result.push_back((*temp1)[i]);
                i++;
                j++;
            }
        }
        temp1->swap(result);

        return (*temp1).size();
    }

    int get_size(int set_num){ //O(1)

        if(vector_of_pointers.size() <= set_num){
            vector<int>* temp = new vector<int>; 
            vector_of_pointers.push_back(temp);
            return (*temp).size();
        }
        vector<int>* temp = vector_of_pointers[set_num];
        return (*temp).size();
    }

    int my_difference(int set_num1, int set_num2){ //O(n)

        if (vector_of_pointers.size() <= set_num1){

            vector<int>* temp = new vector<int>; 
            vector_of_pointers.push_back(temp);
        }
        if (vector_of_pointers.size() <= set_num2){
            vector<int>* temp = new vector<int>; 
            vector_of_pointers.push_back(temp); 
        }

        vector<int>* temp1 = vector_of_pointers[set_num1];
        vector<int>* temp2 = vector_of_pointers[set_num2];

        if(set_num1 == set_num2){
            (*temp1).clear();
            return (*temp1).size();
        }

        int i = 0; int j = 0; vector<int> result;
        while (i < (*temp1).size() && j < (*temp2).size()){
            if((*temp1)[i] < (*temp2)[j]){
                result.push_back((*temp1)[i++]); 
            }
            else if((*temp1)[i] > (*temp2)[j]){
                j++;
            }
            else {
                i++;
                j++;
            }
        }

        while(i < (*temp1).size()){
            result.push_back((*temp1)[i++]);
        }
        temp1->swap(result);

        return (*temp1).size();
    }

    int my_symmetric_difference(int set_num1, int set_num2){//O(n)

        if (vector_of_pointers.size() <= set_num1){

            vector<int>* temp = new vector<int>; 
            vector_of_pointers.push_back(temp);
        }
        if (vector_of_pointers.size() <= set_num2){
            vector<int>* temp = new vector<int>; 
            vector_of_pointers.push_back(temp); 
        }

        vector<int> *temp1 = vector_of_pointers[set_num1];
        vector<int> *temp2 = vector_of_pointers[set_num2];

        if(set_num1 == set_num2){
            (*temp1).clear();
            return (*temp1).size();
        }

        int i = 0; int j = 0; vector<int> result;
        while (i < (*temp1).size() && j < (*temp2).size()){
            if((*temp1)[i] < (*temp2)[j]){
                result.push_back((*temp1)[i++]); 
            }
            else if((*temp1)[i] > (*temp2)[j]){
                result.push_back((*temp2)[j++]);
            }else {
                i++;
                j++;
            }
        }

        while(i < (*temp1).size()){
            result.push_back((*temp1)[i++]);
        }

        while(j < (*temp2).size()){
            result.push_back((*temp2)[j++]);
        }
        temp1->swap(result);
        return (*temp1).size();
    }

    void my_print(int set_num){ //O(n)

        if (vector_of_pointers.size() <= set_num){
            cout << endl; return;
        }

        vector<int> temp = *vector_of_pointers[set_num];
        for (int i = 0; i < temp.size(); i++){          
            if(i == temp.size() - 1){
            cout << temp[temp.size() - 1];
            }
            else{
                cout << temp[i] << ",";
            }
        }
        cout << endl;
    }
};

void perform_operation(int operation_num, SET& newset){
    int set_num; int data;
    int set_num1; int set_num2;

    switch(operation_num){

        case (1):
            cin >> set_num >> data;
            cout << newset.my_insert(set_num, data) << endl;
            break;

        case (2):
            cin >> set_num >> data;
            cout << newset.my_delete(set_num, data) << endl;
            break;

        case (3):
            cin >> set_num >> data;
            cout << newset.my_belongs_to(set_num, data) << endl;
            break;

        case (4):
            cin >> set_num1 >> set_num2;
            cout << newset.my_union(set_num1, set_num2) << endl;
            break;

        case (5):
            cin >> set_num1 >> set_num2;
            cout << newset.my_intersection(set_num1, set_num2) << endl;
            break;

        case (6):
            cin >> set_num;
            cout << newset.get_size(set_num) << endl;
            break;

        case (7):
            cin >> set_num1 >> set_num2;
            cout << newset.my_difference(set_num1, set_num2) << endl;
            break;

        case (8):
            cin >> set_num1 >> set_num2;
            cout << newset.my_symmetric_difference(set_num1, set_num2) << endl;
            break;

        case (9):
            cin >> set_num;
            newset.my_print(set_num);
            break;

        default:
            break;

    }
}

int main(){

    SET newset;

    int operation_num;

    while(cin >> operation_num){
        perform_operation(operation_num, newset);
    }
    return 0;
}