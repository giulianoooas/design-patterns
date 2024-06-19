#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Memento Garbage collector

class GarbageCollector {
private:
    vector<void*> objects;
public:
    GarbageCollector() {
        objects = vector<void*>(0);
    }

    void addPointer(void* obj) {
        objects.push_back(obj);
    }

    ~GarbageCollector() {
        for (auto obj : objects) {
            if (!obj) {
                continue;
            }
            cout << "Memory free for " << obj << endl;
            free(obj);
        }
    }
} collector;

// Memento pattern

class AbstractState {
public:
    virtual string getState() const = 0;
};

class Memento {
private:
    string text;

public:
    Memento() {
        collector.addPointer(this);
    }

    virtual void setState(AbstractState* state) {
        this->text = state->getState();
    }

    string getState() {
        return this->text;
    }
};

class State: public AbstractState {
private:
    string text;
public:
    State() {
        this->text = "initial state ";
    }

    State(const State & state) {
        this->text = text;
    }

    Memento* createMemento() const {
        Memento* memento =  new Memento();
        memento->setState((AbstractState*)this);
        return memento;
    }

   void resetState(Memento* memento) {
        this->text = memento->getState();
   }

   string getState() const {
        return this->text;
   }

   void addToState(string add) {
        this->text = this->text + add;
   }
};


// command pattern

class Command {
protected:
    State* state;
public:
    Command(State* state): state(state) {
        collector.addPointer(this);
    }

    virtual void execute() = 0;
    virtual void undo() = 0;

    string getState() const {
        return this->state->getState();
    }
};

class AddCommand: public Command {
private:
    Memento* memento;
public:
    AddCommand(State* state): Command(state) {}

    void execute() {
        this->memento = this->state->createMemento();
        this->state->addToState(" - new command -");
    }

    void undo() {
        if (this->memento) {
            this->state->resetState(this->memento);
            this->memento = this->state->createMemento();
        }
    }

};

int main() {

    State state;
    Command* command = new AddCommand(&state);
    cout << command->getState() << endl;
    command->execute();
    cout << command->getState() << endl;
    command->execute();
    cout << command->getState() << endl;
    command->undo();
    cout << command->getState() << endl;
    command->undo();
    cout << command->getState() << endl;

    return 0;
}