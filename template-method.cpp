#include <iostream>
#include <vector>

using namespace std;

class SortAlg {
protected:
    virtual bool doComparaison(int nr1, int nr2) const = 0;

public:
    void sort(vector<int> & vec) const {
        for (int i = 0; i < vec.size(); i ++) {
            for (int j = i + 1; j < vec.size(); j ++) {
                if (!this->doComparaison(vec[i],vec[j])) {
                    swap(vec[i],vec[j]);
                }
            }
        }
    }
};

class AscSortAlg: public SortAlg {
protected:
    bool doComparaison(int nr1, int nr2) const {
        return nr1 <= nr2;
    }
};

class DescSortAlg: public SortAlg {
protected:
    bool doComparaison(int nr1, int nr2) const {
        return nr1 >= nr2;
    }
};

void showVec(vector<int> &vec) {
    for (int i = 0; i < vec.size(); i ++) {
        cout << vec[i] << " ";
    }

    cout << endl;
}

int main() {
    SortAlg *sortAlg1 = new AscSortAlg();
    SortAlg *sortAlg2 = new DescSortAlg();

    vector<int> vec;

    for (int i = 0; i < 10; i ++) {
        vec.push_back(i);
    }

    sortAlg2->sort(vec);
    showVec(vec);

    sortAlg1->sort(vec);
    showVec(vec);

    delete sortAlg1, sortAlg2;
    return 0;
}