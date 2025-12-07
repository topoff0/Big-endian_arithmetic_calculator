#include <map>
#include <vector>
#include <string>

using std::map;
using std::pair;
using std::string;
using std::vector;

struct calculator
{
public:
    struct SmallArithmetic
    {
    public:
        static inline map<char, char> plus1_map;
        static inline map<char, char> minus1_map;

        static char plus1(char c);
        static char minus1(char c);

        static char add(char x, char y);
        static char sub(char x, char y);
        static char mul(char x, char y);
        static char div(char x, char y);
        static int compare(char x, char y);

        static vector<vector<char>> addition_table();
        static vector<vector<char>> multiplication_table();
        static vector<vector<char>> carry_table();
        static vector<vector<char>> carry_addition_table();
        static vector<vector<char>> carry_mult_table();
    };

    struct BigArithmetic
    {
    public:
        class BigNumber
        {
        private:
            bool negative = false;
            string digits;

        public:
            BigNumber() = default;
            BigNumber(const string &s);
            BigNumber(const bool neg, const string &dig);

            bool is_negative() const;

            size_t size() const;
            string get_digits() const;
            string str() const;

            const char &operator[](const size_t index) const;
            bool operator==(const BigNumber &other) const;
            bool operator!=(const BigNumber &other) const;
            bool operator<(const BigNumber &other) const;
            bool operator<=(const BigNumber &other) const;
            bool operator>(const BigNumber &other) const;
            bool operator>=(const BigNumber &other) const;
        };

        static BigNumber add(const BigNumber &A, const BigNumber &B);
        static BigNumber sub(const BigNumber &A, const BigNumber &B);
        static BigNumber mul(const BigNumber &A, const BigNumber &B);
        static pair<BigNumber, BigNumber> div(const BigNumber &A, const BigNumber &B);
        static BigNumber exp(const BigNumber &A, const BigNumber &B);
        static pair<char, char> mult_digits(const char &a, const char &b);

    private:
        static int compare_abs(const BigNumber &A, const BigNumber &B);
        static bool is_zero(const BigNumber &A);
        static bool causes_carry(const char &a, const char &b);
    };
};
