#include <iostream>
#include <string>

using namespace std;

class BasicComponent{
public:
    virtual void write() const =0;
};

class TextComponent:public BasicComponent {
private:
    string text;

public:
    TextComponent(string text): text(text), BasicComponent() {}

    void write() const {
        cout << text << endl;
    }
};

class Decorator: public BasicComponent {
private:
    BasicComponent* component;
public:
    Decorator(BasicComponent* component): component(component) {}

    void write() const {
        this->component->write();
    }
};

class ScrollBarDecorator: public Decorator {
public:
    ScrollBarDecorator(BasicComponent* component): Decorator(component) {}

    void write() const {
        cout << "(Scroll bar)" << endl;
        Decorator::write();
    }
};

class BorderDecorator: public Decorator {
public:
    BorderDecorator(BasicComponent* component): Decorator(component) {}

    void write() const {
        cout << "-----------------------------" << endl;
        Decorator::write();
        cout << "-----------------------------" << endl;
    }
};

int main() {
    BasicComponent * comp = new TextComponent("example");
    BasicComponent * borderedComp = new BorderDecorator(comp);
    BasicComponent * scrolledBorderComp = new ScrollBarDecorator(borderedComp);

    scrolledBorderComp->write();
    cout << endl;
    comp->write();
    cout << endl;
    borderedComp->write();

    delete scrolledBorderComp;
    delete borderedComp;
    delete comp;
    return 0;
}