#include <iostream>
#include <vector>

using namespace std;

// patterns used Visitor + Composite

class SimpleElement;
class CompositeElement;

class Visitor {
protected:
    int total;
public:
    Visitor(): total(0) {}

    virtual void visitSimpleElement(SimpleElement* element) = 0; 
    virtual void visitComplexElement(CompositeElement* element) = 0;

    void showTotal() const {
        cout << this->total << endl;
    }
};
class Element {
public:
    virtual void addElement(Element * elem) = 0;
    virtual int getValue() const = 0;
    virtual void acceptVisitor(Visitor* v) = 0;
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

class ConcreteVisitor: public Visitor{
public:
    void visitSimpleElement(SimpleElement* element) {
        this->total += element->getValue();
    }

    void visitComplexElement(CompositeElement* element) {
        this->total += element->getSize();
    }
};


int main() {
    CompositeElement elem;
    SimpleElement s1(2), s2(3);
    elem.addElement(&s1);
    elem.addElement(&s2);

    ConcreteVisitor v;

    elem.acceptVisitor(&v);
    v.showTotal();

    return 0;
}