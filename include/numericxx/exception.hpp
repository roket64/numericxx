#ifndef NUMERICXX_EXCEPTION_HPP_
#define NUMERICXX_EXCEPTION_HPP_

#include <exception>

namespace numericxx {
namespace exceptions {
class DividedByZeroException : public std::exception {
public:
  DividedByZeroException(const char *msg) : message(msg){};
  const char *what() const noexcept override { return message; };

private:
  const char *message;
};

class OverFlowException : public std::exception {
public:
  OverFlowException(const char *msg) : message(msg){};
  const char *what() const noexcept override { return message; };

private:
  const char *message;
};

class InvalidSolutionException : public std::exception {
public:
  InvalidSolutionException(const char *msg) : message(msg){};
  const char *what() const noexcept override { return message; }

private:
  const char *message;
};

class InvalidArgumentException : public std::exception {
public:
  InvalidArgumentException(const char *msg) : message(msg){};
  const char *what() const noexcept override { return message; }

private:
  const char *message;
};
} // namespace exceptions
} // namespace numericxx

#endif