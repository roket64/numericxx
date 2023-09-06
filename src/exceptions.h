#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include "exception"

namespace numericxx {
namespace exceptions {
class DividedByZeroException : public std::exception {
   public:
    DividedByZeroException(const char *msg) : message_(msg){};
    const char *what() const noexcept override { return message_; };

   private:
    const char *message_;
};

class OverFlowException : public std::exception {
   public:
    OverFlowException(const char *msg) : message_(msg){};
    const char *what() const noexcept override { return message_; };

   private:
    const char *message_;
};

class InvalidSolutionException : public std::exception {
   public:
    InvalidSolutionException(const char *msg) : message_(msg){};
    const char *what() const noexcept override { return message_; }

   private:
    const char *message_;
};
}  // namespace exceptions
}  // namespace integer

#endif