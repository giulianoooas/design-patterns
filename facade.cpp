#include <iostream>

using namespace std;

class CompilerBuilder {
private:
    CompilerBuilder() {}

    static CompilerBuilder* instance;
public:
    void build() {
        cout << "App is building\n";
    }

    static CompilerBuilder *getInstance() {
        if (instance == 0) {
            instance = new CompilerBuilder();
        }

        return instance;
    }

    static void deleteInstance() {
        if (instance != 0) {
            delete instance;
        }
    }
};

CompilerBuilder* CompilerBuilder::instance = 0;

class CompilerRunner {
private:
    CompilerRunner() {}

    static CompilerRunner* instance;
public:
    void run() {
        cout << "App is running\n";
    }

    static CompilerRunner *getInstance() {
        if (instance == 0) {
            instance = new CompilerRunner();
        }

        return instance;
    }

    static void deleteInstance() {
        if (instance != 0) {
            delete instance;
        }
    }
};

CompilerRunner* CompilerRunner::instance = 0;

class CompilerFacade {
private:
    CompilerFacade() {}

    static CompilerFacade* instance;
public:
    void start() {
        CompilerBuilder::getInstance()->build();
        CompilerRunner::getInstance()->run();
    }

    static CompilerFacade *getInstance() {
        if (instance == 0) {
            instance = new CompilerFacade();
        }

        return instance;
    }

    static void deleteInstance() {
        if (instance != 0) {
            delete instance;
        }
        CompilerBuilder::deleteInstance();
        CompilerRunner::deleteInstance();
    }
};

CompilerFacade* CompilerFacade::instance = 0;

int main() {
    CompilerFacade::getInstance()->start();
    CompilerFacade::deleteInstance();
    return 0;
}