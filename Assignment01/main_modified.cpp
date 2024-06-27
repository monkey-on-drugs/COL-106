#include <iostream>
#include <vector>
using namespace std;

class Set {
public:
    vector<vector<int>*> sets;

    ~Set() {
        for (auto& setPtr : sets) {
            delete setPtr;
        }
        sets.clear();
    }

    int findElement(const vector<int>& set, int element) {
        int start = 0;
        int end = set.size() - 1;

        while (start <= end) {
            int mid = start + (end - start) / 2;
            if (set[mid] == element) {
                return mid;
            }
            if (set[mid] < element) {
                start = mid + 1;
            } else {
                end = mid - 1;
            }
        }
        return -1;
    }

    int insert(int setIndex, int data) {
        if (sets.size() <= setIndex) {
            sets.push_back(new vector<int>{data});
            return sets[setIndex]->size();
        }

        vector<int>& set = *sets[setIndex];

        if (set.empty() || data < set.front()) {
            set.insert(set.begin(), data);
        } else if (data > set.back()) {
            set.push_back(data);
        } else {
            for (auto it = set.begin(); it != set.end() - 1; ++it) {
                if (data > *it && data < *(it + 1)) {
                    set.insert(it + 1, data);
                    break;
                }
            }
        }
        return set.size();
    }

    int remove(int setIndex, int data) {
        if (sets.size() <= setIndex) {
            return -1;
        }

        vector<int>& set = *sets[setIndex];
        int pos = findElement(set, data);

        if (pos != -1) {
            set.erase(set.begin() + pos);
        }
        return set.size();
    }

    int contains(int setIndex, int data) {
        if (sets.size() <= setIndex) {
            return -1;
        }

        vector<int>& set = *sets[setIndex];
        return findElement(set, data) != -1 ? 1 : 0;
    }

    int unionSets(int setIndex1, int setIndex2) {
        if (sets.size() <= setIndex1 || sets.size() <= setIndex2) {
            return -1;
        }

        vector<int>& set1 = *sets[setIndex1];
        vector<int>& set2 = *sets[setIndex2];
        vector<int> result;

        size_t i = 0, j = 0;
        while (i < set1.size() && j < set2.size()) {
            if (set1[i] < set2[j]) {
                result.push_back(set1[i++]);
            } else if (set1[i] > set2[j]) {
                result.push_back(set2[j++]);
            } else {
                result.push_back(set1[i]);
                i++;
                j++;
            }
        }

        while (i < set1.size()) {
            result.push_back(set1[i++]);
        }

        while (j < set2.size()) {
            result.push_back(set2[j++]);
        }

        set1 = result;
        return set1.size();
    }

    int intersectSets(int setIndex1, int setIndex2) {
        if (sets.size() <= setIndex1 || sets.size() <= setIndex2) {
            return -1;
        }

        vector<int>& set1 = *sets[setIndex1];
        vector<int>& set2 = *sets[setIndex2];
        vector<int> result;

        size_t i = 0, j = 0;
        while (i < set1.size() && j < set2.size()) {
            if (set1[i] < set2[j]) {
                i++;
            } else if (set1[i] > set2[j]) {
                j++;
            } else {
                result.push_back(set1[i]);
                i++;
                j++;
            }
        }

        set1 = result;
        return set1.size();
    }

    int differenceSets(int setIndex1, int setIndex2) {
        if (sets.size() <= setIndex1 || sets.size() <= setIndex2) {
            return -1;
        }

        vector<int>& set1 = *sets[setIndex1];
        vector<int>& set2 = *sets[setIndex2];
        vector<int> result;

        size_t i = 0, j = 0;
        while (i < set1.size() && j < set2.size()) {
            if (set1[i] < set2[j]) {
                result.push_back(set1[i++]);
            } else if (set1[i] > set2[j]) {
                j++;
            } else {
                i++;
                j++;
            }
        }

        while (i < set1.size()) {
            result.push_back(set1[i++]);
        }

        set1 = result;
        return set1.size();
    }

    int symmetricDifferenceSets(int setIndex1, int setIndex2) {
        if (sets.size() <= setIndex1 || sets.size() <= setIndex2) {
            return -1;
        }

        vector<int>& set1 = *sets[setIndex1];
        vector<int>& set2 = *sets[setIndex2];
        vector<int> result;

        size_t i = 0, j = 0;
        while (i < set1.size() && j < set2.size()) {
            if (set1[i] < set2[j]) {
                result.push_back(set1[i++]);
            } else if (set1[i] > set2[j]) {
                result.push_back(set2[j++]);
            } else {
                i++;
                j++;
            }
        }

        while (i < set1.size()) {
            result.push_back(set1[i++]);
        }

        while (j < set2.size()) {
            result.push_back(set2[j++]);
        }

        set1 = result;
        return set1.size();
    }

    void printSet(int setIndex) const {
        if (sets.size() <= setIndex) {
            cout << endl;
            return;
        }

        const vector<int>& set = *sets[setIndex];
        for (size_t i = 0; i < set.size(); ++i) {
            cout << set[i];
            if (i < set.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }

    int getSize(int setIndex) const {
        if (sets.size() <= setIndex) {
            return 0;
        }
        return sets[setIndex]->size();
    }
};

void performOperation(int operationNum, Set& setCollection) {
    int setIndex, data, setIndex1, setIndex2;

    switch (operationNum) {
    case 1:
        cin >> setIndex >> data;
        cout << setCollection.insert(setIndex, data) << endl;
        break;
    case 2:
        cin >> setIndex >> data;
        cout << setCollection.remove(setIndex, data) << endl;
        break;
    case 3:
        cin >> setIndex >> data;
        cout << setCollection.contains(setIndex, data) << endl;
        break;
    case 4:
        cin >> setIndex1 >> setIndex2;
        cout << setCollection.unionSets(setIndex1, setIndex2) << endl;
        break;
    case 5:
        cin >> setIndex1 >> setIndex2;
        cout << setCollection.intersectSets(setIndex1, setIndex2) << endl;
        break;
    case 6:
        cin >> setIndex;
        cout << setCollection.getSize(setIndex) << endl;
        break;
    case 7:
        cin >> setIndex1 >> setIndex2;
        cout << setCollection.differenceSets(setIndex1, setIndex2) << endl;
        break;
    case 8:
        cin >> setIndex1 >> setIndex2;
        cout << setCollection.symmetricDifferenceSets(setIndex1, setIndex2) << endl;
        break;
    case 9:
        cin >> setIndex;
        setCollection.printSet(setIndex);
        break;
    default:
        break;
    }
}

int main() {
    Set setCollection;
    int operationNum;

    while (cin >> operationNum) {
        performOperation(operationNum, setCollection);
    }
    return 0;
}
