#include <string>
#include <iostream>

using namespace std;

class ProductPrototype {
private:
    static ProductPrototype* instance;

    int id;
    string name;

     ProductPrototype() {
        this->id = 0;
        this->name  = "default product";
    }

    ProductPrototype(const ProductPrototype & product) {
        this->id = product.id;
        this->name = product.name;
    }
public:
    static ProductPrototype* getInstance() {
        if (instance == 0) {
            instance = new ProductPrototype();
        }

        return instance;
    }

    ProductPrototype* setId(const int id) {
        this->id = id;
        return this;
    }

    int getId() const {
        return this->id;
    }

    ProductPrototype* setName(string name) {
        this->name = name;
        return this;
    }

    string getName() const {
        return this->name;
    }

    ProductPrototype* clone() const {
        return new ProductPrototype(*this);
    } 
};

ProductPrototype* ProductPrototype::instance = 0;

int main() {
    const ProductPrototype* defaultProduct = ProductPrototype::getInstance();
    ProductPrototype* product1 = defaultProduct -> clone();

    product1 -> setId(1) -> setName("Ana");

    cout << product1 -> getName() << " " << defaultProduct -> getName() << endl;

    delete product1;
    delete defaultProduct;

    return 0;
}