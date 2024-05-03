#include <string>
#include <iostream>

using namespace std;

enum TextType {B,N};

class TextWriter {
public:
    virtual void writeText(string text) = 0;
};

class BeautifulTextWriter: public TextWriter {
public:
    void writeText(string text) {
        cout << "You used a beautiful tet writer for: " << text << endl;;
    };
};

class NormalTextWriter: public TextWriter {
public:
    void writeText(string text) {
        cout << "You used a normal tet writer for: " << text << endl;;
    }; 
};

class TextFactory {
private:
    TextFactory() {}
    static TextFactory* instance;
public:
    static TextFactory* getInstance() {
        if (instance == 0) {
            instance = new TextFactory();
        }

        return instance;
    }

    static void deleteInstance() {
        if (instance == 0) {
            delete instance;
        }
    }

    TextWriter* getTextWriter(TextType type) const { 
        switch (type)
        {
        case B:
            return new BeautifulTextWriter();
        case N:
            return new NormalTextWriter();
        default:
            return 0;
        }
    }
};

TextFactory* TextFactory::instance = 0;

class TextBox {
private:
    string text;
    TextWriter* textWriter;
public:
    TextBox() {
        this->text = "";
        this->textWriter = 0;
    }

    ~TextBox() {
        if (textWriter) {
            delete textWriter;
        }
    }

    void setTextWriter(TextType type) {
        if (textWriter) {
            delete textWriter;
        }

        textWriter = TextFactory::getInstance()->getTextWriter(type);
    }

    void setText(string text) {
        this->text=text;
    }

    void writeText() {
        if (this->textWriter) {
            this->textWriter->writeText(this->text);
        }
    }
};

int main() {
    TextBox textBox;
    textBox.setText("example");
    textBox.setTextWriter(N);
    textBox.writeText();
    textBox.setTextWriter(B);
    textBox.writeText();
    TextFactory::deleteInstance();
    return 0;
}