#include <SFML/Graphics.hpp>
#include <iostream>

// Интерфейс субъекта
class Subject {
public:
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void move(float x, float y) = 0;
    virtual void loadImage(const std::string& filename) = 0;
};

// Реальный субъект
class RealSubject : public Subject {
private:
    sf::Texture texture;
    sf::Sprite sprite;

public:
    void draw(sf::RenderWindow& window) override {
        window.draw(sprite);
    }

    void move(float x, float y) override {
        sprite.setPosition(x, y);
    }

    void loadImage(const std::string& filename) override {
        if (texture.loadFromFile(filename)) {
            sprite.setTexture(texture);
        }
    }
};

// Заместитель
class Proxy : public Subject {
private:
    RealSubject* realSubject;

public:
    Proxy() : realSubject(nullptr) {}

    ~Proxy() {
        if (realSubject) {
            delete realSubject;
        }
    }

    void draw(sf::RenderWindow& window) override {
        if (realSubject) {
            realSubject->draw(window);
        }
    }

    void move(float x, float y) override {
        if (realSubject) {
            realSubject->move(x, y);
        }
    }

    void loadImage(const std::string& filename) override {
        if (!realSubject) {
            realSubject = new RealSubject();
        }
        realSubject->loadImage(filename);
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Image Proxy Example");

    Proxy proxy;

    bool doubleClick = false;
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (clock.getElapsedTime().asMilliseconds() < 500) {
                    doubleClick = true;
                    clock.restart();
                }
                else {
                    doubleClick = false;
                    clock.restart();
                }
            }
        }

        if (doubleClick) {
            proxy.loadImage("C:\\Users\\vitrl\\Downloads\\fun-backpacker-german-shepherd-dog-cartoon-character.jpg");
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            proxy.move(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
        }

        window.clear();
        proxy.draw(window);
        window.display();
    }

    return 0;
}
