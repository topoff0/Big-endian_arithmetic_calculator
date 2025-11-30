#include <stdexcept>
#include <string>

class BigNumberException : public std::runtime_error
{
public:
    explicit BigNumberException(const string &msg)
        : std::runtime_error(msg) {}
};

class BigNumberDivisionException : public BigNumberException
{
public:
    explicit BigNumberDivisionException(const string &msg)
        : BigNumberException(msg) {}
};