#include <iostream>
#include <vector>
#define MAX_SIZE 100

using namespace std;

enum IteratorType {NORMAL, DOUBLE_INCREMENT};

class AbsList{
public:
    virtual int getElem(int poz) const = 0;
    virtual int getSize() const = 0;
};



class Iterator {
protected:
    AbsList *list;
    int poz;
public:
    Iterator(AbsList * list): list(list), poz(0) {}

    Iterator(Iterator * &itr):  poz(0) {
        this->list = itr->list;
    }

    Iterator() : poz(0), list(0) {}

    virtual void first() {
        this->poz = 0;
    }

    virtual void next() = 0;
    
    virtual int getCurrent() const {
        return this->list->getElem(this->poz);
    }

    virtual bool isEnd() const {
        return this->poz >= this->list->getSize();
    }
};

class IteratorProxy: public Iterator {
private:
    Iterator* itr;
public:
    IteratorProxy(Iterator* &itr): itr(itr) , Iterator(itr) {} 
    
    IteratorProxy(const IteratorProxy & _itr) {
        this->itr = _itr.itr;
    }

    ~IteratorProxy() {
        delete this->itr;
    }

    void first() {
        this->itr->first();
    }

    void next() {
        this->itr -> next();
    }

    int getCurrent() const {
        return this->itr->getCurrent();
    }

    bool isEnd() const {
        return this->itr->isEnd();
    }

};

class NormalIterator: public Iterator {
public:
    NormalIterator(AbsList * list): Iterator( list) {}

    void next () {
        this->poz++;
    }
};

class DoubleIterator: public Iterator {
public:
    DoubleIterator(AbsList * list): Iterator( list) {}

    void next () {
        this->poz+= 2;
    }
};

class List: public AbsList{
private:
    unsigned int arr[MAX_SIZE];
    int n;
public:
    List(): n(0) {}

    void add(int val) {
        if (this->n < MAX_SIZE) {
            this->arr[this->n] = val;
            this->n ++;
        }

    }

    void remove() {
        if (this->n > 0) {
            this->n --;
        }
    }

    int getElem(int poz) const {
        if (poz < 0 || poz >= this->n) {
            return -1;
        }

        return this->arr[poz];
    }

    int getSize() const {
        return this->n;
    }

    IteratorProxy getIterator(IteratorType type) const {
        Iterator * itr;
        switch (type)
        {
        case NORMAL:
            itr = new NormalIterator((List*)this);
            break;
        default:
            itr = new DoubleIterator((List*)this);
            break;
        }

        return IteratorProxy(itr);
    }
};

void testIterator(List &lst, IteratorType type) {
    IteratorProxy itr = lst.getIterator(type);

    for (itr.first();!itr.isEnd(); itr.next()) {
        cout << itr.getCurrent() << " ";
    }

    cout << endl;
}

int main() {
    List lst;
    for (int i = 0; i < 10; i ++) {
        lst.add(i);
    }

    testIterator(lst, NORMAL);
    testIterator(lst,DOUBLE_INCREMENT);

    return 0;
};