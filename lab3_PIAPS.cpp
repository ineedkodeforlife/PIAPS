#include <iostream>
#include <vector>
#include <string>

class PassengerComponent {
public:
    virtual void addPassenger(PassengerComponent* passenger) = 0;
    virtual void removePassenger(PassengerComponent* passenger) = 0;
    virtual int getTotalBaggageWeight() = 0;
    virtual void printPassengerInfo() = 0;
    virtual ~PassengerComponent() {}
};

class Passenger : public PassengerComponent {
private:
    std::string name;
    int baggageWeight;
public:
    Passenger(std::string name, int baggageWeight) : name(name), baggageWeight(baggageWeight) {}

    void addPassenger(PassengerComponent* passenger) override {
        throw std::runtime_error("Cannot add passenger to leaf node.");
    }

    void removePassenger(PassengerComponent* passenger) override {
        throw std::runtime_error("Cannot remove passenger from leaf node.");
    }

    int getTotalBaggageWeight() override {
        return baggageWeight;
    }

    void printPassengerInfo() override {
        std::cout << "Passenger: " << name << ", Baggage weight: " << baggageWeight << "kg" << std::endl;
    }
};

class Aircraft : public PassengerComponent {
private:
    int maxBaggageWeight;
    std::vector<PassengerComponent*> passengers;
public:
    Aircraft(int maxBaggageWeight) : maxBaggageWeight(maxBaggageWeight) {}

    void addPassenger(PassengerComponent* passenger) override {
        passengers.push_back(passenger);
    }

    void removePassenger(PassengerComponent* passenger) override {
        passengers.erase(std::remove(passengers.begin(), passengers.end(), passenger), passengers.end());
        delete passenger;
    }

    int getTotalBaggageWeight() override {
        int totalWeight = 0;
        for (auto passenger : passengers) {
            totalWeight += passenger->getTotalBaggageWeight();
        }
        return totalWeight;
    }

    void printPassengerInfo() override {
        for (auto passenger : passengers) {
            passenger->printPassengerInfo();
        }
    }

    void checkBaggageWeight() {
        int totalWeight = getTotalBaggageWeight();
        if (totalWeight > maxBaggageWeight) {
            std::cout << "Excess baggage detected. Removing baggage from economy class passengers." << std::endl;
            removeExcessBaggage();
        }
    }

    void removeExcessBaggage() {
        for (auto passenger : passengers) {
            Passenger* economyPassenger = dynamic_cast<Passenger*>(passenger);
            if (economyPassenger) {
                // У эконом-пассажиров удаляем лишний багаж
                if (economyPassenger->getTotalBaggageWeight() > 20) {
                    std::cout << "Removing excess baggage from economy class passenger: " << economyPassenger->getName() << std::endl;
                    economyPassenger->removeExcessBaggage();
                }
            }
        }
    }
};

int main() {
    PassengerComponent* aircraft = new Aircraft(5000); // Максимальный вес багажа 5000 кг

    PassengerComponent* passenger1 = new Passenger("John", 25); // Первый класс, 25 кг багажа
    PassengerComponent* passenger2 = new Passenger("Alice", 15); // Бизнес класс, 15 кг багажа
    PassengerComponent* passenger3 = new Passenger("Bob", 30); // Эконом класс, 30 кг багажа

    aircraft->addPassenger(passenger1);
    aircraft->addPassenger(passenger2);
    aircraft->addPassenger(passenger3);

    aircraft->printPassengerInfo();
    static_cast<Aircraft*>(aircraft)->checkBaggageWeight(); // Проверка веса багажа

    // Освобождение памяти
    delete aircraft;

    return 0;
}
