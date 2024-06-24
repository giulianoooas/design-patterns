#include <iostream>
#include <vector>

using namespace std;

// patterns used Visitor + Composite

class Visitor;

class Element {
public:
    virtual void addElement(Element * elem) = 0;
    virtual int getValue() const = 0;
    virtual void acceptVisitor(Visitor* v) = 0;
};

class SimpleElement;

class CompositeElement;

class Visitor {
private:
    int total;
public:
    Visitor(): total(0) {}

    void visitSimpleElement(Element* element) {
        this->total += element->getValue();
    }

    void visitComplexElement(Element* element) {
        this->total += 10;
    }

    void showTotal() const {
        cout << this->total << endl;
    }
};

class SimpleElement : public Element{
    int val;
public:
    SimpleElement(int val): val(val) {}

    void addElement(Element* elem) {
        return;
    } 

    int getValue() const {
        return this->val;
    }

    void acceptVisitor(Visitor* v) {
        v->visitSimpleElement(this);
    };
};

class CompositeElement: public Element {
private:
    vector<Element*> elems;

public:

    void addElement(Element* elem) {
        this->elems.push_back(elem);
    } 

    int getValue() const {
        int total = 0;

        for (Element* elem : this->elems) {
            total += elem->getValue();
        }

        return total;
    }

    int getSize() const {
        return this->elems.size();
    }

    void acceptVisitor(Visitor* v) {
        for (Element* elem : this->elems) {
            elem->acceptVisitor(v);
        }
        v->visitComplexElement(this);
    };
};


int main() {
    CompositeElement elem;
    SimpleElement s1(2), s2(3);
    elem.addElement(&s1);
    elem.addElement(&s2);

    Visitor v;

    elem.acceptVisitor(&v);
    v.showTotal();

    return 0;
}