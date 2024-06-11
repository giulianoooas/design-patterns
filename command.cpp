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
        if (!prevCommand) {
            return;
        }
        this->text = prevCommand->text;
    }

    void showState() const {
        cout << "State is " << this->text << endl;
    }
};

class AddACommand: public Command{
    public:
        AddACommand(Command * prevCommand): Command(prevCommand) {}

        void execute() {
            this->text += "A";
        }
};

class AddBCommand: public Command{
    public:
        AddBCommand(Command * prevCommand): Command(prevCommand) {}

        void execute() {
            this->text += "B";
        }
};

int main() {
    Command* aCommand = new AddACommand(0);
    Command* bCommand = new AddBCommand(aCommand);
    bCommand->showState();
    bCommand->undo();
    bCommand->showState();
    delete aCommand;
    delete bCommand;
    return 0;
}