#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <algorithm>

class Database; // Forward declaration

// Observer interface
class IObserver {
public:
    virtual void Update(std::map<std::string, int> report) = 0;
};

// Observable interface
class IObservable {
public:
    virtual void RegisterObserver(IObserver* observer) = 0;
    virtual void RemoveObserver(IObserver* observer) = 0;
    virtual void NotifyObservers() = 0;
};

// Concrete Observer class
class Deanery : public IObserver {
private:
    Database* database;

public:
    Deanery(Database* db);

    void Update(std::map<std::string, int> report) override {
        for (const auto& pair : report) {
            if (pair.second == 0) {
                std::cout << "Деканат: " << pair.first << " не создал отчет вовремя!" << std::endl;
            }
        }
    }
};

// Teacher class
class Teacher {
private:
    Database* database;
    std::string name;

public:
    Teacher(const std::string& name, Database* database);

    std::string GetName() const {
        return name;
    }

    int WriteReport() {
        // Simulating whether the report is created in time or not
        return rand() % 2;
    }
};

// Concrete Observable class
class Database : public IObservable {
private:
    std::vector<IObserver*> observers;
    std::vector<Teacher*> teachers;
    std::map<std::string, int> report_;

public:
    void RegisterObserver(IObserver* observer) override {
        observers.push_back(observer);
    }

    void RemoveObserver(IObserver* observer) override {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void NotifyObservers() override {
        for (auto observer : observers) {
            observer->Update(report_);
        }
    }

    void RegisterTeacher(Teacher* teacher) {
        teachers.push_back(teacher);
    }

    void EndOfWeek() {
        for (auto teacher : teachers) {
            report_[teacher->GetName()] = teacher->WriteReport();
        }
        NotifyObservers();
    }
};

// Implementations of Deanery and Teacher constructors
Deanery::Deanery(Database* db) : database(db) {
    database->RegisterObserver(this);
}

Teacher::Teacher(const std::string& name, Database* database) : name(name), database(database) {
    database->RegisterTeacher(this);
}

int main() {
    srand(time(nullptr));

    Database database;
    Deanery deanery(&database);

    // Registering teachers
    Teacher teacher1("Teacher1", &database);
    Teacher teacher2("Teacher2", &database);
    Teacher teacher3("Teacher3", &database);

    // Simulating end of the week
    database.EndOfWeek();

    return 0;
}
