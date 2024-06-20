#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum EventTypes {COUNTER};

struct Event {
    Event(EventTypes type, void *value): type(type), value(value) {}

    EventTypes type;
    void * value;
};

class AbsObserver {
public:
    virtual void update(Event& event) = 0;
};

class Subject {
protected:
    vector<AbsObserver*> observers;

      void notify(Event& event) {
        for (AbsObserver* obs: this->observers) {
            obs->update(event);
        }
    }

public:
    
    void addObserver(AbsObserver* observer) {
        this->observers.push_back(observer);
    }

    void removeObserver(AbsObserver* observer) {
        vector<AbsObserver*> observers;

        for (AbsObserver* obs: this->observers) {
            if (obs != observer) {
                observers.push_back(obs);
            }
        }

        this->observers=observers;
    }
};

class Observer: public AbsObserver{
protected:
    Subject* subject;
    EventTypes type;
public:

    Observer(Subject* subject, EventTypes type): subject(subject), type(type) {
        this->subject->addObserver(this);
    }

    ~Observer() {
        this->subject->removeObserver(this);
    }

    virtual void update(Event& event) = 0;
};

class Counter: public Subject {
private:
    int _counter;

public:
    Counter(): _counter(0) {}

    void increaseCounter() {
        this->_counter ++;

        int * val = new int(this->_counter);
        Event counterIncrease(COUNTER, val);
        this->notify(counterIncrease);
        delete val;
    }

    int getCurrentCounter() const {
        return _counter;
    }
};

class Watch: public Observer {
private:
    int _counter;

public:
    Watch(Counter* subject): Observer((Subject*)subject,COUNTER) {
        this->_counter = subject->getCurrentCounter();
    }

    void update(Event& event) {
        if (event.type == this->type) {
            this->_counter = *((int*)event.value);
        }
    }

    void showCounter() const {
        cout << "Current counter state is " << this->_counter << endl;
    }
};

int main() {
    Counter counter;
    Watch w1(&counter), w2(&counter);

    w1.showCounter();
    w2.showCounter();
    counter.increaseCounter();
    w1.showCounter();
    w2.showCounter();
    counter.increaseCounter();
    w1.showCounter();
    w2.showCounter();
    return 0;
}