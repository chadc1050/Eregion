#ifndef EREGION_RESULT_H
#define EREGION_RESULT_H

#include <stdexcept>
#include <string>
#include <variant>

namespace eregion {

template <typename T> struct Success {
    T value;
};

struct Error {
    std::string message;
};

template <typename T> class Result {
  public:
    Result(const Success<T>& success);
    Result(const Error& error);

    bool isSuccess() const;
    bool isError() const;
    T getValue() const;

  private:
    std::variant<Success<T>, Error> result;
};

template <typename T> Result<T>::Result(const Success<T>& success) : result(success) {}

template <typename T> Result<T>::Result(const Error& error) : result(error) {}

template <typename T> bool Result<T>::isSuccess() const { return std::holds_alternative<Success<T>>(result); }

template <typename T> bool Result<T>::isError() const { return std::holds_alternative<Error>(result); }

template <typename T> T Result<T>::getValue() const {
    if (this->isError()) {
        throw std::runtime_error("Invalid access of Result!");
    }

    return std::get<Success<T>>(result).value;
}

} // namespace eregion

#endif