#include <iostream>
#include <string>

using namespace std;

class ImageInterface {
public:
    virtual void drawImage() = 0;
    virtual void showDimensions()  =0;
};

class ImageObject: public ImageInterface {
private:
    int width, height;
public:
    ImageObject(int width, int height): width(width), height(height) {}

    void drawImage()  {
        cout << "Image was been built.\n";
    }

    void showDimensions()  {
        cout << "(" << this->width << "," << this->height << ")\n";
    }
};

class ImageProxy {
private:
    string filename;
    ImageObject* img;

    ImageObject* loadImage() {
        if (!this->img) {
            this->img = new ImageObject(10,10);
        }

        return this->img;
    }
public:
    ImageProxy(string filename): filename(filename) {}

    void drawImage()  {
        this->loadImage()->drawImage();
    }

    void showDimensions()  {
        this->loadImage()->showDimensions();
    }

    ImageObject* operator -> () {
        return this->loadImage();
    }

    ~ImageProxy() {
        delete this->img;
    }
};

int main() {
    ImageProxy* img = new ImageProxy("file");

    img->drawImage();
    delete img;
    return 0;
}