#include <iostream>
#include <vector>
#include <unordered_map>

#define vExp vector<Exp*>
#define pb push_back

using namespace std;

// literals are letters from a to z
// resolve operation like + and  -

enum Operation {ADD, SUB, NONE};
enum Literal {q,w,e,r,t,y,u,i,o,p,a,s,d,f,g,h,j,k,l,z,x,c,v,b,n,m};

struct ContextDataMap {
    Literal letter;
    int value;

    ContextDataMap(Literal letter, int value) : letter(letter), value(value) {}
};

class Context {
private:
    unordered_map<Literal,int> contextMap;
public:
    Context(unordered_map<Literal,int> contextMap): contextMap(contextMap) {}

    void setContext(vector<ContextDataMap> contextMap) {
        for (ContextDataMap data : contextMap) {
            this->contextMap.insert({data.letter,data.value});
        }
    }

    int getValueFor(Literal letter) const {
        if (this->contextMap.find(letter) != this->contextMap.end()) {
            return this->contextMap.at(letter);
        }

        return -1;
    }

};

class Exp {
protected:
    vExp children;
    bool hasChildren;
    Operation op;
public:
    Exp(Operation op, bool hasChildren):op(op),  hasChildren(hasChildren) {}

    void addChildren(Exp* child) {
        if (!hasChildren) {
            return;
        }
        this->children.pb(child);
    }

    virtual int interpret(Context & context) const {
        int res = 0;

        for (Exp * child : this->children) {
            switch (this->op)
            {
            case ADD:
                res += child -> interpret(context);
                break;
            
            default:
                res -= child -> interpret(context);
                break;
            }
        }

        return res;
    }
};

class LiteralExp : public Exp {
private:
    Literal letter;
public:
    LiteralExp(Literal letter):letter(letter), Exp(NONE, false) {}

    virtual int interpret(Context & context) const {
        return context.getValueFor(this->letter);
    }
};


class AddExp: public Exp {
public:
    AddExp(): Exp(ADD, true) {}
};

class SubExp: public Exp {
public:
    SubExp(): Exp(SUB, true) {}
};

int main() {
    unordered_map<Literal,int> map;
    Context context(map);
    vector<ContextDataMap> contextMap;
    contextMap.pb(ContextDataMap(a,10));
    contextMap.pb(ContextDataMap(b,-21));
    context.setContext(contextMap);

    // solve a + ((a + b) - b)
    Exp* lit1 = new LiteralExp(a);
    Exp* lit2 = new LiteralExp(b);

    Exp* op1 = new AddExp();
    Exp* op2 = new SubExp();
    Exp* op3 = new AddExp();
  
    op1->addChildren(lit1);
    op1->addChildren(op2);

    op2->addChildren(op3);
    op2->addChildren(lit2);
    
    op3->addChildren(lit1);
    op3->addChildren(lit2);
    

    cout << op1->interpret(context) << endl;

    delete op1;
    delete op2;
    delete op3;
    delete lit1;
    delete lit2;
    return 0;
}