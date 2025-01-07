#include <iostream>
#include <fstream>
#include <string>
#include <memory>

enum class LogMessageType {
    WARNING,
    ERROR,
    FATAL_ERROR,
    UNKNOWN
};

class LogMessage {
public:
    LogMessage(LogMessageType type, const std::string& message)
        : messageType(type), messageContent(message) {}

    LogMessageType type() const { return messageType; }
    const std::string& message() const { return messageContent; }

private:
    LogMessageType messageType;
    std::string messageContent;
};

class LogHandler {
protected:
    std::shared_ptr<LogHandler> nextHandler;

public:
    void setNext(std::shared_ptr<LogHandler> handler) {
        nextHandler = handler;
    }

    virtual void handle(const LogMessage& logMessage) {
        if (nextHandler) {
            nextHandler->handle(logMessage);
        }
    }
};

class FatalErrorHandler : public LogHandler {
public:
    void handle(const LogMessage& logMessage) override {
        if (logMessage.type() == LogMessageType::FATAL_ERROR) {
            throw std::runtime_error("Fatal Error: " + logMessage.message());
        }
        else {
            LogHandler::handle(logMessage);
        }
    }
};

class ErrorHandler : public LogHandler {
private:
    std::string filePath;

public:
    ErrorHandler(const std::string& path) : filePath(path) {}

    void handle(const LogMessage& logMessage) override {
        if (logMessage.type() == LogMessageType::ERROR) {
            std::ofstream outFile(filePath, std::ios::app);
            if (outFile.is_open()) {
                outFile << "Error: " << logMessage.message() << std::endl;
                outFile.close();
            }
            else {
                std::cerr << "Could not open file for logging errors." << std::endl;
            }
        }
        else {
            LogHandler::handle(logMessage);
        }
    }
};

class WarningHandler : public LogHandler {
public:
    void handle(const LogMessage& logMessage) override {
        if (logMessage.type() == LogMessageType::WARNING) {
            std::cout << "Warning: " << logMessage.message() << std::endl;
        }
        else {
            LogHandler::handle(logMessage);
        }
    }
};

class UnknownMessageHandler : public LogHandler {
public:
    void handle(const LogMessage& logMessage) override {
        if (logMessage.type() == LogMessageType::UNKNOWN) {
            throw std::runtime_error("Unknown log message: " + logMessage.message());
        }
        else {
            LogHandler::handle(logMessage);
        }
    }
};

int main() {
    auto fatalErrorHandler = std::make_shared<FatalErrorHandler>();
    auto errorHandler = std::make_shared<ErrorHandler>("error.log");
    auto warningHandler = std::make_shared<WarningHandler>();
    auto unknownMessageHandler = std::make_shared<UnknownMessageHandler>();

    fatalErrorHandler->setNext(errorHandler);
    errorHandler->setNext(warningHandler);
    warningHandler->setNext(unknownMessageHandler);

    LogMessage fatalError(LogMessageType::FATAL_ERROR, "A fatal error occurred!");
    LogMessage error(LogMessageType::ERROR, "An error occurred.");
    LogMessage warning(LogMessageType::WARNING, "This is a warning.");
    LogMessage unknown(LogMessageType::UNKNOWN, "This is an unknown message.");

    try {
        fatalErrorHandler->handle(fatalError); 
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    try
    {
    fatalErrorHandler->handle(error);

    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    try
    {
    fatalErrorHandler->handle(warning);

    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    try {
        fatalErrorHandler->handle(unknown);
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}