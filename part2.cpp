#include <iostream>
#include <vector>

// Abstract classes for driver and passenger
class Driver {
public:
    virtual ~Driver() {}
    virtual void drive() const = 0;
};

class Passenger {
public:
    virtual ~Passenger() {}
    virtual void sit() const = 0;
};

// Concrete implementation of a bus driver
class BusDriver : public Driver {
private:
    BusDriver() {} // Private constructor to prevent external instantiation

public:
    static BusDriver& getInstance() {
        static BusDriver instance;
        return instance;
    }

    void drive() const override {
        std::cout << "Bus started moving." << std::endl;
    }
};

// Concrete implementation of a BoardTaxi driver
class TaxiDriver : public Driver {
private:
    TaxiDriver() {} // Private constructor to prevent external instantiation

public:
    static TaxiDriver& getInstance() {
        static TaxiDriver instance;
        return instance;
    }

    void drive() const override {
        std::cout << "BoardTaxi started moving." << std::endl;
    }
};

// Concrete implementation of a passenger
class PassengerImpl : public Passenger {
public:
    void sit() const override {
        std::cout << "Passenger sat in the BoardAnyCar." << std::endl;
    }
};

// Abstract class for BoardAnyCar
class BoardAnyCar {
public:
    virtual ~BoardAnyCar() {}
    virtual void BoardPassanger(const std::vector<Passenger*>& passengers) = 0;
    virtual void BoardDriver(Driver& driver) = 0;
};

// Concrete implementation of a bus
class BoardBus : public 
    BoardAnyCar {
private:
    std::vector<Passenger*> passengers;
    const int capacity = 30; // Load limit
    Driver* driver = nullptr;

public:
    void BoardPassanger(const std::vector<Passenger*>& passengers) override {
        if (passengers.size() > capacity) {
            std::cout << "Bus load limit exceeded." << std::endl;
            return;
        }

        this->passengers = passengers;
        std::cout << "Bus loaded." << std::endl;
    }

    void BoardDriver(Driver& driver){
        if (this->driver != nullptr) {
            std::cout << "Bus already has a driver." << std::endl;
            return;
        }
        this->driver = &driver;
        std::cout << "Driver set for the bus. And bus moving" << std::endl;
    }

    void setBusDriver(BusDriver& busDriver) {
        BoardDriver(busDriver);
    }
};

// Concrete implementation of a BoardTaxi
class BoardTaxi : public BoardAnyCar {
private:
    std::vector<Passenger*> passengers;
    const int capacity = 4; // Load limit
    Driver* driver = nullptr;

public:
    void BoardPassanger(const std::vector<Passenger*>& passengers) override {
        if (passengers.size() > capacity) {
            std::cout << "BoardTaxi load limit exceeded." << std::endl;
            return;
        }

        this->passengers = passengers;
        std::cout << "BoardTaxi loaded." << std::endl;
    }

    void BoardDriver(Driver& driver) {
        if (this->driver != nullptr) {
            std::cout << "Bus already has a driver." << std::endl;
            return;
        }
        this->driver = &driver;
        std::cout << "Driver set for the taxi. And taxi moving" << std::endl;
    }

    void setTaxiDriver(BusDriver& busDriver) {
        BoardDriver(busDriver);
    }
};

// Abstract factory for creating BoardAnyCars
class TransportFactory {
public:
    virtual ~TransportFactory() {}
    virtual BoardAnyCar* createBoardAnyCar() const = 0;
};

// Concrete factory for creating buses
class BusFactory : public TransportFactory {
public:
    BoardAnyCar* createBoardAnyCar() const override {
        return new BoardBus();
    }
};

// Concrete factory for creating BoardTaxis
class BoardTaxiFactory : public TransportFactory {
public:
    BoardAnyCar* createBoardAnyCar() const override {
        return new BoardTaxi();
    }
};

int main() {
    // Creating factories for buses and BoardTaxis
    BusFactory busFactory;
    BoardTaxiFactory BoardTaxiFactory;

    // Creating a bus and loading passengers and setting driver
    BoardAnyCar* bus = busFactory.createBoardAnyCar();
    std::vector<Passenger*> busPassengers = { new PassengerImpl(), new PassengerImpl() };
    bus->BoardPassanger(busPassengers);
    bus->BoardDriver(BusDriver::getInstance());

    // Creating a BoardTaxi and loading passengers and setting driver
    BoardAnyCar* BoardTaxi = BoardTaxiFactory.createBoardAnyCar();
    std::vector<Passenger*> BoardTaxiPassengers = { new PassengerImpl() };
    BoardTaxi->BoardPassanger(BoardTaxiPassengers);
    BoardTaxi->BoardDriver(TaxiDriver::getInstance());

    // Freeing memory
    delete bus;
    delete BoardTaxi;

    for (Passenger* passenger : busPassengers) {
        delete passenger;
    }

    for (Passenger* passenger : BoardTaxiPassengers) {
        delete passenger;
    }

    return 0;
}
