#include <iostream>
#include <string>

using namespace std;

string context = "base ";

class Command {
protected:
    Command* prevCommand;
    string text;
public:
    Command(Command * prevCommand) : prevCommand(prevCommand) {
        this->text = context;
    }

    virtual void execute() = 0;

    void undo() {
        context = text;
    }

    void showState() const {
        cout << "State is " << context << endl;
    }
};

class AddACommand: public Command{
    public:
        AddACommand(Command * prevCommand): Command(prevCommand) {}

        void execute() {
            text = context;
            context += "A";
        }
};

class AddBCommand: public Command{
    public:
        AddBCommand(Command * prevCommand): Command(prevCommand) {}

        void execute() {
            context += "B";
        }
};

int main() {
    Command* aCommand = new AddACommand(0);
    Command* bCommand = new AddBCommand(aCommand);
    bCommand->showState();
    aCommand->execute();
    bCommand->execute();
    bCommand->undo();
    bCommand->showState();
    delete aCommand;
    delete bCommand;
    return 0;
}