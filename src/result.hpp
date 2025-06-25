#ifndef RESULT_HPP
#define RESULT_HPP

#include <memory>
#include <string>

struct Error {
    std::string message;
    inline Error(const std::string& message)
        : message(message) {}
};

template <typename T>
class Result {
private:
    std::shared_ptr<Error> error;
    std::shared_ptr<T> value;

public:
    inline Result(const Error& error) : error(std::make_shared<Error>(error)), value(nullptr) {}
    inline Result(const T& value) : error(nullptr), value(std::make_shared<T>(value)) {}
    inline bool is_error() const { return this->error != nullptr; }
    inline T& get_value() const { return *this->value; }
    inline Error& get_error() const { return *this->error; }
};

#endif