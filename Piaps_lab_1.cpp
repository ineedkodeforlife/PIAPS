#include <iostream>

class Singleton {
private:
    // Приватный статический член класса, который хранит единственный экземпляр класса
    static Singleton* instance;

    // Приватный конструктор, чтобы предотвратить создание экземпляров класса извне
    Singleton() {}

public:
    // Статический метод, который возвращает экземпляр класса
    static Singleton* getInstance() {
        // Если экземпляр еще не был создан, создаем его
        if (instance == nullptr) {
            instance = new Singleton();
            // Устанавливаем функцию, которая будет вызвана при завершении программы для удаления экземпляра
            std::atexit([]() {
                delete instance;
                });
        }
        // Возвращаем единственный экземпляр класса
        return instance;
    }

    // Метод для демонстрации работы экземпляра класса
    void showMessage() {
        std::cout << "Hello I'm Singleton" << std::endl;
    }
};

// Инициализация статического члена класса
Singleton* Singleton::instance = nullptr;

//int main() {
//    // Получаем единственный экземпляр класса Singleton
//    Singleton* singletonInstance = Singleton::getInstance();
//
//    // Демонстрация работы экземпляра
//    singletonInstance->showMessage();
//
//    return 0;
//}
