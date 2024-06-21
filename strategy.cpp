#include <iostream>
#include <vector>

using namespace std;

// patterns used: Flyweight, Singleton, Strategy, Factory method


// Strategy 

class SortingAlg {
public:
    virtual void sort(vector<int> &vec) = 0;
};

class BubbleSortingAlg: public SortingAlg {
public:
    void sort(vector<int> &vec) {
        cout << "For sorting is used bubble sort\n";

        for (int i = 0; i < vec.size(); i ++) {
            for (int j = i + 1; j < vec.size(); j ++) {
                if (vec[j] < vec[i]) {
                    swap(vec[i], vec[j]);
                }
            }
        }
    }
};

class MergeSortingAlg: public SortingAlg {
private:
    void merge(vector<int> & vec, int i, int j) {
        int mij = (j + i) / 2, idx = 0;
        vector<int> res(j - i + 1);

        int x = i, y = mij;

        while (x < mij && y < j) {
            if (vec[x] < vec[y]) {
                res[idx] = vec[x];
                idx ++;
                x ++;
            } else {
                res[idx] = vec[y];
                idx ++;
                y ++;
            }   
        }

        while (x < mij) {
            res[idx] = vec[x];
            idx ++;
            x ++;
        }

        while (y < j) {
            res[idx] = vec[y];
            idx ++;
            y ++;
        }

        for (int i1 = 0; i1 < idx; i1 ++) {
            vec[i + i1] = res[i1];
        }
    }

    void mergesort(vector<int> & vec, int i, int j) {
        if (j - i > 1) {
            int mij = (j + i) / 2;

            this->mergesort(vec,i,mij);
            this->mergesort(vec,mij,j);
            this->merge(vec,i,j);
        }
    }

public:
    void sort(vector<int> &vec) {
        cout << "For sorting is used mergesort\n";
        this->mergesort(vec,0,vec.size());
    }
};

// Flyweight + Singleton + Factory method

enum SortType {MERGE, BUBBLE};

struct SortingAlgStruct{
    SortingAlgStruct() {}

    SortingAlgStruct(SortType type, SortingAlg* sortingAlg): type(type), sortingAlg(sortingAlg) {}

    SortingAlgStruct(const SortingAlgStruct & c) {
        this->sortingAlg = c.sortingAlg;
        this->type = c.type;
    }

    SortType type;
    SortingAlg* sortingAlg;
};

class SortingAlgFactory {
private:
    vector<SortingAlgStruct> sortingAlgs;

    static SortingAlgFactory* instance;

    SortingAlgFactory() {
        this->sortingAlgs.resize(0);
    }

public:

    static SortingAlgFactory* getInstance() {
        if (!instance) {
            instance = new SortingAlgFactory();
        }

        return instance;
    }

    SortingAlg* getSortingAlg(SortType type) {
        for (auto alg: this->sortingAlgs) {
            if (type == alg.type) {
                return alg.sortingAlg;
            }
        }

        SortingAlg* alg;
        switch (type)
        {
        case MERGE:
            alg = new MergeSortingAlg();
            break;
        
        default:
            alg = new BubbleSortingAlg();
            break;
        }
        this->sortingAlgs.push_back(SortingAlgStruct(type, alg));
        return alg;
    }

    ~SortingAlgFactory() {
        for (auto sortingAlg: this->sortingAlgs) {
            cout << "Free memory for "<< sortingAlg.sortingAlg << endl;
            delete sortingAlg.sortingAlg;
        }
    }
};

SortingAlgFactory* SortingAlgFactory::instance = 0;

class List {
private:
    vector<int> vec;
    SortingAlg* sortingAlg;
public:
    List() {
        sortingAlg = 0;
        vec.resize(0);
    }

    void add(int elem) {
        this->vec.push_back(elem);
    }

    void setSortingAlg(SortType type) {
        this->sortingAlg = SortingAlgFactory::getInstance()->getSortingAlg(type);
    }

    void sort() {
        if (!this->sortingAlg) {
            cout << "First set sorting alg!\n";
            return;
        }

        this->sortingAlg->sort(this->vec);
    }

    void showElems() const {
        for (auto elem : this->vec) {
            cout << elem << " ";
        }
        cout << endl;
    }
};

int main() {
    List a,b,c;

    for (int i = 10; i > 0; i --) {
        a.add(i);
        b.add(i);
        c.add(i);
    }

    a.setSortingAlg(BUBBLE);
    b.setSortingAlg(MERGE);

    a.sort();
    b.sort();
    c.sort();

    a.showElems();
    b.showElems();
    c.showElems();

    delete SortingAlgFactory::getInstance();
    return 0;
}