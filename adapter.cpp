#include <string>
#include <iostream>

using namespace std;

class Poz{
private:
    int x,y;
public:
    Poz(int x, int y) {
        this->x=x;
        this->y=y;
    }

    int* getPoz() const {
        int * poz = new int[2];
        poz[0] = this->x;
        poz[1] = this->y;
        return poz;
    }
};

class TextBox {
private:
    string text;
    Poz* poz;
public: 
    
    TextBox(int x, int y, string text) {
        this->poz = new Poz(x,y);
        this->text = text;
    }

    ~TextBox() {
        delete this->poz;
    }

    Poz *getPoz() const {
        return this->poz;
    }

    string getText() const {
        return this -> text;
    }
};

class Shape {
public:
    virtual void writeShape() const= 0;
private:
    virtual int* getDim() const = 0;
};

class TextShapeInheritance: public Shape, private TextBox{
public:
    TextShapeInheritance(int x, int y, string text) : TextBox(x,y,text) {}

    void writeShape() const {
        int * dim = this->getDim();
        cout << dim[0] << " ," << dim[1] << endl;
        delete[] dim;
    }
private:
    int* getDim() const {
        Poz* poz = TextBox::getPoz();
        int *dim = poz->getPoz();
        dim[1] += TextBox::getText().length();
        return dim;
    }
};

class TextShapeComposition: public Shape {
private:
    TextBox* textBox;
public:
    TextShapeComposition(TextBox* textBox) {
        this->textBox = textBox;
    }

    void writeShape() const {
        int * dim = this->getDim();
        cout << dim[0] << " ," << dim[1] << endl;
        delete[] dim;
    }

private:
    int* getDim() const {
        Poz* poz = this->textBox->getPoz();
        int *dim = poz->getPoz();
        dim[1] += this->textBox->getText().length();
        return dim;
    }
};

int main() {
    TextBox textBox(1,1,"example 1");
    TextShapeComposition textShapeComposition(&textBox);
    TextShapeInheritance textShapeInheritance(2,1,"example 2");
    textShapeComposition.writeShape();
    textShapeInheritance.writeShape();
    return 0;
}