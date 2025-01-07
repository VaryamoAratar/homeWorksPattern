#include <fstream>
#include <memory>
#include <stdexcept>

class Formatter
{
public:
    virtual ~Formatter() = default;
    virtual std::string format(const std::string& data) const = 0;
};

class TextFormatter : public Formatter
{
public:
    std::string format(const std::string& data) const override
    {
        return data;
    }
};

class HTMLFormatter : public Formatter
{
public:
    std::string format(const std::string& data) const override
    {
        return "<html>" + data + "</html>";
    }
};

class JSONFormatter : public Formatter
{
public:
    std::string format(const std::string& data) const override
    {
        return "{ \"data\": \"" + data + "\"}";
    }
};

class Data
{
public:
    Data(std::string data) : data_(std::move(data)) {}

    const std::string& getData() const { return data_; }

private:
    std::string data_;
};

class DataSaver
{
public:
    void saveTo(std::ofstream& file, const Data& data, const Formatter& formatter)
    {
        file << formatter.format(data.getData());
    }
};

// Функции для сохранения данных в различных форматах
void saveToAsHTML(std::ofstream& file, const Data& data)
{
    HTMLFormatter htmlFormatter;
    DataSaver saver;
    saver.saveTo(file, data, htmlFormatter);
}

void saveToAsJSON(std::ofstream& file, const Data& data)
{
    JSONFormatter jsonFormatter;
    DataSaver saver;
    saver.saveTo(file, data, jsonFormatter);
}

void saveToAsText(std::ofstream& file, const Data& data)
{
    TextFormatter textFormatter;
    DataSaver saver;
    saver.saveTo(file, data, textFormatter);
}