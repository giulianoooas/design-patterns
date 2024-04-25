#include <string>
#include <iostream>

using namespace std;

class Product {
protected: 
    string name;
    int id;
public:
    Product(){
        this->id =0;
        this->name = "";
    }

    Product(int id, string name){
        this->id = id;
        this->name = name;
    }

    virtual void showProduct() const = 0;
};

class AnimalProduct : public Product{
public:
    AnimalProduct(): Product(1,"animal product") {}

    void showProduct() const {
        cout << "Animal product - name: " << this->name << ", id: " << this->id<< endl; 
    }
};

class VeganProduct : public Product{
public:
    VeganProduct(): Product(2,"vegan product") {}

    void showProduct() const {
        cout << "Vegan product - name: " << this->name << ", id: " << this->id<< endl; 
    }
};

enum ProductType {Animal, Vegan};

class ProductFactory {
private:
    ProductType productType;
public:
    ProductFactory(ProductType productType) {
        this->productType = productType;
    }

    Product* createProduct() const {
        switch (this->productType)
        {
            case Animal:
                return new AnimalProduct();
            case Vegan:
                return new VeganProduct();
            default:
                return 0;
        }
    }
};

int main() {
    ProductFactory productFactory(Animal);
    const Product* product = productFactory.createProduct();
    product -> showProduct();
    delete product;
    return 0;
}
