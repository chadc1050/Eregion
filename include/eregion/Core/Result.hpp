#pragma once

#include <stdexcept>
#include <string>
#include <variant>

namespace eregion {

template <typename T> struct Success {
    T value;
};

// Specialize Success<void> to handle void success cases
template <> struct Success<void> {};

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
    std::string getError() const;

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

template <typename T> std::string Result<T>::getError() const {
    if (this->isSuccess()) {
        throw std::runtime_error("Invalid access of Result!");
    }
    return std::get<Error>(result).message;
}

// Specialization for Result<void> to handle functions that don't return values
template <> class Result<void> {
  public:
    Result();
    Result(const Error& error);

    bool isSuccess() const;
    bool isError() const;
    std::string getError() const;

  private:
    std::variant<Success<void>, Error> result;
};

inline Result<void>::Result() : result(Success<void>{}) {}

inline Result<void>::Result(const Error& error) : result(error) {}

inline bool Result<void>::isSuccess() const { return std::holds_alternative<Success<void>>(result); }

inline bool Result<void>::isError() const { return std::holds_alternative<Error>(result); }

inline std::string Result<void>::getError() const {
    if (this->isSuccess()) {
        throw std::runtime_error("Invalid access of Result!");
    }
    return std::get<Error>(result).message;
}

} // namespace eregion