#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Subject {
private:
    const string type;
    const int importance;
public:
    
    Subject(string type, int importance): type(type), importance(importance) {}

    void writeSubject() const {
        cout << "Subject type: " << type << " and importance: " << importance << endl;
    }

    bool isEqual(string type, int importance) const {
        return type == this->type && importance == this->importance;
    }
};

class SubjectFactory{
private:
    static SubjectFactory* instance;
    vector<Subject*> subjects;

    SubjectFactory() {
        subjects.resize(0);
    }

public:

    static SubjectFactory* getInstance() {
        if (!instance) {
            instance = new SubjectFactory();
        }

        return instance;
    }

    static void deleteInstance() {
        if (instance) {
            delete instance;
        }
    }

    Subject* getSubject(string type, int importance)  {
        for (Subject* subject : this->subjects) {
            if (subject->isEqual(type,importance)) {
                return subject;
            }
        }

        Subject* subject = new Subject(type,importance);
        this->subjects.push_back(subject);
        return subject;
    }

    void  eraseSubject() {
        for (Subject* sub: subjects) {
            delete sub;
        }
    }
};

SubjectFactory* SubjectFactory::instance = 0;

int main() {
    SubjectFactory* factory = SubjectFactory::getInstance();
    Subject *sub1 = factory->getSubject("example",1);
    Subject *sub2 = factory->getSubject("example",2);
    Subject *sub3 = factory->getSubject("example",1);
    sub1->writeSubject();
    sub2->writeSubject();
    cout << (sub1 == sub3) << endl;
    factory->eraseSubject();
    SubjectFactory::deleteInstance();
    return 0;
}