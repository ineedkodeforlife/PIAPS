#include <iostream>
#include <string>
#include <vector>

// Класс для водителя
class Driver {
private:
    std::string category;
public:
    Driver(std::string cat) : category(cat) {}
    std::string getCategory() const {
        return category;
    }
};

// Класс для пассажиров
class Passenger {
private:
    std::string type;
    float ticketPrice;
public:
    Passenger(std::string t, float price) : type(t), ticketPrice(price) {}
    std::string getType() const {
        return type;
    }
    float getTicketPrice() const {
        return ticketPrice;
    }
};

// Класс для детского кресла
class ChildSeat {
    // В данной задаче оставим его пустым
};

// Класс для билета
class Ticket {
private:
    float price;
public:
    Ticket(float p) : price(p) {}
    float getPrice() const {
        return price;
    }
};

// Класс для транспортного средства
class Vehicle {
private:
    Driver* driver;
    std::vector<Passenger*> passengers;
    int capacity;
    ChildSeat* childSeat;
public:
    void setDriver(Driver* d) {
        driver = d;
    }
    void addPassenger(Passenger* p) {
        passengers.push_back(p);
    }
    void setCapacity(int cap) {
        capacity = cap;
    }
    void setChildSeat(ChildSeat* cs) {
        childSeat = cs;
    }
    bool isReadyToDepart() const {
        return (driver != nullptr && passengers.size() > 0);
    }
};

// Интерфейс строителя
class VehicleBuilder {
public:
    virtual void buildDriver(std::string category) = 0;
    virtual void buildPassengers(std::vector<Passenger*> passengers) = 0;
    virtual void buildCapacity(int capacity) = 0;
    virtual void buildChildSeat() = 0;
    virtual Vehicle* getResult() = 0;
};

// Конкретный строитель для автобуса
class BusBuilder : public VehicleBuilder {
private:
    Vehicle* bus;
public:
    BusBuilder() {
        bus = new Vehicle();
    }
    void buildDriver(std::string category) override {
        bus->setDriver(new Driver(category));
    }
    void buildPassengers(std::vector<Passenger*> passengers) override {
        for (Passenger* p : passengers) {
            bus->addPassenger(p);
        }
    }
    void buildCapacity(int capacity) override {
        bus->setCapacity(capacity);
    }
    void buildChildSeat() override {
        // В автобусе нет необходимости в детском кресле
    }
    Vehicle* getResult() override {
        std::cout << "Bus is loaded and go to drive\n";
        return bus;
    }
};

// Конкретный строитель для такси
class TaxiBuilder : public VehicleBuilder {
private:
    Vehicle* taxi;
public:
    TaxiBuilder() {
        taxi = new Vehicle();
    }
    void buildDriver(std::string category) override {
        taxi->setDriver(new Driver(category));
    }
    void buildPassengers(std::vector<Passenger*> passengers) override {
        for (Passenger* p : passengers) {
            taxi->addPassenger(p);
        }
    }
    void buildCapacity(int capacity) override {
        taxi->setCapacity(capacity);
    }
    void buildChildSeat() override {
        taxi->setChildSeat(new ChildSeat());
    }
    Vehicle* getResult() override {
        std::cout << "Taxi is loaded and go to drive\n";
        return taxi;
    }
};

// Директор
class VehicleDirector {
private:
    VehicleBuilder* builder;
public:
    VehicleDirector(VehicleBuilder* b) : builder(b) {}
    void construct(std::string category, std::vector<Passenger*> passengers, int capacity) {
        builder->buildDriver(category);
        builder->buildPassengers(passengers);
        builder->buildCapacity(capacity);
        builder->buildChildSeat();
    }
};

int main() {
    // Использование паттерна "Строитель"
    BusBuilder busBuilder;
    TaxiBuilder taxiBuilder;

    VehicleDirector busDirector(&busBuilder);
    VehicleDirector taxiDirector(&taxiBuilder);

    std::vector<Passenger*> busPassengers = { new Passenger("adult", 10.0),
        new Passenger("concession", 5.0),
        new Passenger("child", 3.0) };
    std::vector<Passenger*> taxiPassengers = { new Passenger("adult", 15.0),
        new Passenger("child", 7.0) };

    busDirector.construct("category1", busPassengers, 30);
    taxiDirector.construct("category2", taxiPassengers, 4);

    Vehicle* bus = busBuilder.getResult();
    Vehicle* taxi = taxiBuilder.getResult();
    

    delete bus;
    delete taxi;

    return 0;
}
