#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Абстрактный класс для наблюдателя
class Observer {
public:
    virtual void update(bool success) = 0;
};

// Конкретный наблюдатель - кафедра
class Department : public Observer {
public:
    void update(bool success) override {
        if (success) {
            cout << "Успеваемость создана вовремя. Кафедра уведомлена." << endl;
        }
        else {
            cout << "Успеваемость не создана вовремя! Кафедра оповещена." << endl;
        }
    }
};

// Абстрактный класс для субъекта
class Subject {
public:
    virtual void attach(Observer* observer) = 0;
    virtual void detach(Observer* observer) = 0;
    virtual void notifyObservers(bool success) = 0;
};

// Конкретный субъект - деканат
class DeanOffice : public Subject {
private:
    vector<Observer*> observers;
    bool success;

public:
    void attach(Observer* observer) override {
        observers.push_back(observer);
    }

    void detach(Observer* observer) override {
        // Метод detach можно также реализовать для удаления наблюдателей
        // из списка наблюдателей (observers), но для этого примера не нужен.
    }

    void notifyObservers(bool success) override {
        for (Observer* observer : observers) {
            observer->update(success);
        }
    }

    void createProgress(bool success) {
        this->success = success;
        notifyObservers(success);
    }
};

int main() {
    // Создаем объекты кафедры и деканата
    Department department;
    DeanOffice deanOffice;

    // Подписываем кафедру на уведомления деканата
    deanOffice.attach(&department);

    // Преподаватель создает текущую успеваемость
    bool success = false; // предположим, что успеваемость создана успешно

    // Деканат получает информацию о создании успеваемости и оповещает кафедру
    deanOffice.createProgress(success);

    return 0;
}
