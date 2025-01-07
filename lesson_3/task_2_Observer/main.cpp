#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

class Observer {
public:
    virtual ~Observer() = default; 
    virtual void onWarning(const std::string& message) {}
    virtual void onError(const std::string& message) {}
    virtual void onFatalError(const std::string& message) {}
};

class WarningObserver : public Observer {
public:
    void onWarning(const std::string& message) override {
        std::cout << "Warning: " << message << std::endl;
    }
};

class ErrorObserver : public Observer {
private:
    std::string filePath;
public:
    ErrorObserver(const std::string& path) : filePath(path) {}

    void onError(const std::string& message) override {
        std::ofstream outFile(filePath, std::ios::app);
        if (outFile.is_open()) {
            outFile << "Error: " << message << std::endl;
            outFile.close();
        }
        else {
            std::cerr << "Error: Could not open file for writing." << std::endl;
        }
    }
};

class FatalErrorObserver : public Observer {
private:
    std::string filePath;
public:
    FatalErrorObserver(const std::string& path) : filePath(path) {}

    void onFatalError(const std::string& message) override {
        std::cout << "Fatal Error: " << message << std::endl;

        std::ofstream outFile(filePath, std::ios::app);
        if (outFile.is_open()) {
            outFile << "Fatal Error: " << message << std::endl;
            outFile.close();
        }
        else {
            std::cerr << "Error: Could not open file for writing." << std::endl;
        }
    }
};

class Observed {
private:
    std::vector<Observer*> observers; 
public:
    ~Observed() {}

    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void notifyWarning(const std::string& message) const {
        for (Observer* observer : observers) {
            observer->onWarning(message);
        }
    }

    void notifyError(const std::string& message) const {
        for (Observer* observer : observers) {
            observer->onError(message);
        }
    }

    void notifyFatalError(const std::string& message) const {
        for (Observer* observer : observers) {
            observer->onFatalError(message);
        }
    }

    void warning(const std::string& message) const {
        notifyWarning(message);
    }

    void error(const std::string& message) const {
        notifyError(message);
    }

    void fatalError(const std::string& message) const {
        notifyFatalError(message);
    }
};

int main() {
    Observed observed;

    WarningObserver warnObserver;
    ErrorObserver errorObserver("error.log");
    FatalErrorObserver fatalObserver("fatal_error.log");

    observed.addObserver(&warnObserver);
    observed.addObserver(&errorObserver);
    observed.addObserver(&fatalObserver);

    observed.warning("This is a warning message.");
    observed.error("This is an error message.");
    observed.fatalError("This is a fatal error message.");

    return 0;
}