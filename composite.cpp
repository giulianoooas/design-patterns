#include <iostream>
#include <vector>
using namespace std;

class Member {
protected:
    vector<Member*> children;
    Member* parent;

    virtual bool isComposite() const {
        return false;
    }
public:
    Member() {
        this->parent = 0;
    }

    void addChild(Member *child) {
        if (this->isComposite() && child) {
            child->parent = this;
            this->children.push_back(child);
        } 
    }

    virtual int solve() const = 0;
};

class NumberMember: public Member {
private:
    int number;
public:
    NumberMember(int number): number(number), Member() {}

    int solve() const {
        return this->number;
    }
};

enum Op {ADD,SUB};

class OperationMember: public Member {
private:
    Op op;

    bool isComposite() const {
        return true;
    }

public:
    OperationMember(Op op): op(op) , Member() {}

    ~OperationMember() {
        for (int idx = 0; idx < children.size(); idx ++) {
            delete children[idx];
        }
    }

    int solve()  const {
        int res = 0;
        bool first = true;
        for (Member* child: this->children) {
            if (first) {
                res = child -> solve();
                first = false;
            } else {
                switch (this->op)
                {
                case ADD:
                    res += child->solve();
                    break;
                
                default:
                    res -= child->solve();
                    break;
                }
            }
        }

        return res;
    }
};


int main() {
    // op => (2 + 4) - (3 + 10) => -7
    
    Member* bigOp = new OperationMember(SUB);
    Member * firstPar = new OperationMember(ADD);
    Member *secondPar = new OperationMember(ADD);
    bigOp->addChild(firstPar);
    bigOp->addChild(secondPar);
    firstPar->addChild(new NumberMember(2));
    firstPar->addChild(new NumberMember(4));
    secondPar->addChild(new NumberMember(3));
    secondPar->addChild(new NumberMember(10));
    cout << bigOp->solve() << endl;

    // 2 + 4 + 10
    firstPar -> addChild(new NumberMember(10));
    cout << bigOp->solve() <<" "<< firstPar->solve() << endl;

    delete bigOp;
    return 0;
}
