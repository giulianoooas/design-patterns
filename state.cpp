#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum StateEnum {SQUARE, CUBE};

class GarbageCollector {
public:
    static GarbageCollector* getInstance() {
        if (!instance) {
            instance = new GarbageCollector();
        }

        return instance;
    }

    void addPointer(void* pointer) {
        this->pointers.push_back(pointer);
    }   

    ~GarbageCollector() {
        cout << "------- free memory -------\n";
        for (auto pointer: this->pointers) {
            cout << "Free memory for " << pointer << endl;
            free(pointer);
        }
    }

private:
    GarbageCollector() {
        this->pointers.resize(0);
    }

    static GarbageCollector* instance;
    vector <void*> pointers;
    
};

GarbageCollector* GarbageCollector::instance = 0;

class BaseClass {
public:
    BaseClass() {
        GarbageCollector::getInstance()->addPointer(this);
    }    
};


class State: public BaseClass {
public:
    virtual void showPanel() = 0;
};

class SquareState : public State{
public:
    void showPanel() {
        cout << "Square state\n";
    }
};

class CubeState : public State{
public:
    void showPanel() {
        cout << "Cube state\n";
    }
};

class StateFactory{
public:
    static State* getState(StateEnum type) {
        switch (type)
        {
        case SQUARE:
            return new SquareState();        
        default:
            return new CubeState();
        }
    }
};

class Context: public BaseClass {
private:
    State* state;
public:

    void showPanel() {
        this->state->showPanel();
    }

    void setState(StateEnum type) {
        this->state = StateFactory::getState(type);
    }
};

int main() {
    Context* context = new Context();
    context->setState(SQUARE);
    context->showPanel();
    context->setState(CUBE);
    context->showPanel();
    delete GarbageCollector::getInstance();
    return 0;
}