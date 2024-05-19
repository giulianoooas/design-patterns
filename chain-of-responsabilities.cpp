#include <iostream>
#include <string>

using namespace std;

enum EventType {
    NUMERIC, CHARACTER
};

struct Event{
    EventType type;
    int priority;
};

class EventHandler {
protected:
    EventHandler * parent;
public:
    virtual void handleEvent(Event & event) const {
        if (parent) {
            parent->handleEvent(event);
        } else {
            cout << "Event could not be handled.\n";
        }
    }

    EventHandler(): parent(0) {}

    EventHandler(EventHandler* &parent): parent(parent) {}
};

class NumericHandler: public EventHandler {
public:
    NumericHandler() {}

    NumericHandler(EventHandler* parent): EventHandler(parent) {}

    void handleEvent(Event & event) const {
        if (event.type == NUMERIC) {
            cout << "This event is numeric with prio " << event.priority << endl;
        } else if (parent) {
            parent->handleEvent(event);
        }
    }
};

class CharHandler: public EventHandler {
public:
    CharHandler() {}

    CharHandler(EventHandler* parent): EventHandler(parent) {}

    void handleEvent(Event & event) const {
        if (event.type == CHARACTER) {
            cout << "This event is char with prio " << event.priority << endl;
        } else if (parent) {
            parent->handleEvent(event);
        }
    }
};

int main() {
    EventHandler baseHandler;
    NumericHandler numHandler(&baseHandler);
    CharHandler charHandler1(&baseHandler);
    CharHandler charHandler2(&numHandler);

    Event event;
    event.priority = 10;
    event.type = NUMERIC;
    charHandler1.handleEvent(event);
    cout << endl;
    charHandler2.handleEvent(event);

    return 0;
}