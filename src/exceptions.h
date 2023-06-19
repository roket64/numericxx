#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include "exception"

namespace integer {
namespace exceptions {
class DividedByZeroException : public std::exception {
   public:
    DividedByZeroException(const char *msg) : message(msg){};
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
}  // namespace exceptions
}  // namespace integer

#endif