/*
    When is a complex system that has a lot of many-to-many relations and 
    it needs to prevent complexity problem.
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class BaseMediator{
public:
    virtual void notify(string name, string message) const = 0;
};

class Component {
private:
    string name;
    BaseMediator * mediator;
public:
    Component(string name): name(name) {} 

    void notify(string message) {
        if (this->mediator) {
            this->mediator->notify(this->name,message);
        }   
    }

    void showMessage(string name, string message) {
        cout << "(Comp ~ " << this->name << " ): " << name << " " << message << endl; 
    }

    void setMediator(BaseMediator* mediator) {
        this->mediator = mediator;
    }
};

class Mediator:public  BaseMediator {
private:
    vector<Component*> components;
public:
    Mediator() {
        this->components.resize(0);
    }

    void addComponent(Component& comp) {
        this->components.push_back(&comp);
        comp.setMediator(this);
    }

    void notify(string name, string message) const {
        for (Component* comp : this->components) {
            comp->showMessage(name, message);
        }
    }

    void notify(string message) const {
        for (Component* comp : this->components) {
            comp->showMessage("mediator", message);
        }
    }
 };

int main(){
    Mediator mediator;
    Component c1("c1"), c2("c2");

    mediator.addComponent(c1);
    mediator.addComponent(c2);

    c1.notify("message1");
    mediator.notify("message2");

    return 0;
}