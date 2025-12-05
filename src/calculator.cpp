#include "calculator.h"
#include "config.h"
#include "io.h"
#include "exceptions.h"

using BigNumber = calculator::BigArithmetic::BigNumber;

char calculator::SmallArithmetic::plus1(char c)
{
    for (int i = 0; i < MAX_DIGITS; i++)
    {
        if (rule[i].first == c)
            return rule[i].second;
    }
    return '\0';
}

char calculator::SmallArithmetic::minus1(char c)
{
    for (int i = 0; i < MAX_DIGITS; i++)
    {
        if (rule[i].second == c)
            return rule[i].first;
    }
    return '\0';
}

char calculator::SmallArithmetic::add(char x, char y)
{
    char result = x;
    char current = ZERO; // 'a'

    while (current != y)
    {
        result = plus1(result);
        current = plus1(current);
    }
    return result;
}

char calculator::SmallArithmetic::sub(char x, char y)
{
    char result = x;
    char current = ZERO; // 'a'

    while (current != y)
    {
        result = minus1(result);
        current = plus1(current);
    }

    return result;
}

char calculator::SmallArithmetic::mul(char x, char y)
{
    char result = ZERO;  // 'a'
    char current = ZERO; // 'a'

    while (current != y)
    {
        result = add(result, x);
        current = plus1(current);
    }
    return result;
}

char calculator::SmallArithmetic::div(char x, char y)
{
    char k = ZERO;

    do
    {
        if (mul(y, k) == x)
            return k;
        k = plus1(k);
    } while (k != ZERO);

    throw std::runtime_error("Деление не определено");
}

int calculator::SmallArithmetic::compare(char x, char y)
{
    if (x == y)
        return 0;

    char current = x;
    for (int i = 0; i < MAX_DIGITS; i++)
    {
        if (current == y)
            return -1;
        current = plus1(current);
        if (current == ZERO)
            break;
    }
    return 1;
}

vector<vector<char>> calculator::SmallArithmetic::addition_table()
{
    vector<vector<char>> a_table(MAX_DIGITS, vector<char>(MAX_DIGITS));

    for (int i = 0; i < MAX_DIGITS; i++)
    {
        for (int j = 0; j < MAX_DIGITS; j++)
        {
            a_table[i][j] = add(elems[i], elems[j]);
        }
    }
    return a_table;
}

vector<vector<char>> calculator::SmallArithmetic::multiplication_table()
{
    vector<vector<char>> m_table(MAX_DIGITS, vector<char>(MAX_DIGITS));

    for (int i = 0; i < MAX_DIGITS; i++)
    {
        for (int j = 0; j < MAX_DIGITS; j++)
        {
            m_table[i][j] = mul(elems[i], elems[j]);
        }
    }
    return m_table;
}

vector<vector<char>> calculator::SmallArithmetic::carry_table()
{
    vector<vector<char>> c_table(MAX_DIGITS, vector<char>(MAX_DIGITS));

    for (int i = 0; i < MAX_DIGITS; i++)
    {
        for (int j = 0; j < MAX_DIGITS; j++)
        {
            char x = elems[i];
            char y = elems[j];

            bool carry = false;

            char current = ZERO; // 'a'

            while (current != y)
            {
                x = plus1(x);
                if (x == ZERO)
                {
                    carry = true;
                    break;
                }
                current = plus1(current);
            }

            c_table[i][j] = carry ? '+' : '-';
        }
    }
    return c_table;
}

calculator::BigArithmetic::BigNumber::BigNumber(const string &s)
{
    if (s.empty())
        throw BigNumberException("Пустой ввод");

    size_t pos = 0;
    if (s[0] == '-')
    {
        negative = true;
        pos = 1;
    }
    for (; pos < s.size(); ++pos)
    {
        char c = s[pos];
        bool ok = false;
        for (char e : elems)
            if (e == c)
            {
                ok = true;
                break;
            }
        if (!ok)
        {
            string error = "Символа '" + string(1, c) + string("' не существует в данной арифметики");
            throw BigNumberException(error);
        }

        digits.push_back(c);
    }

    while (digits.size() > 1 && digits.front() == ZERO)
        digits.erase(digits.begin());

    if (digits.size() == 1 && digits[0] == ZERO)
        negative = false;

    if (digits.size() > MAX_DIGITS)
    {
        throw BigNumberException("Переполнение при разборе числа");
    }
}

calculator::BigArithmetic::BigNumber::BigNumber(const bool neg, const string &dig) : negative(neg)
{
    for (char c : dig)
    {
        bool ok = false;
        for (char e : elems)
            if (e == c)
            {
                ok = true;
                break;
            }
        if (!ok)
        {
            string error = "Символа '" + string(1, c) + string("' не существует в данной арифметики");
            throw BigNumberException(error);
        }

        digits.push_back(c);
    }

    while (digits.size() > 1 && digits.front() == ZERO)
        digits.erase(digits.begin());

    if (digits.size() == 1 && digits[0] == ZERO)
        negative = false;

    if (digits.size() > MAX_DIGITS)
    {
        throw BigNumberException("Переполнение при разборе числа");
    }
}

bool calculator::BigArithmetic::BigNumber::is_negative() const
{
    return negative;
}

size_t calculator::BigArithmetic::BigNumber::size() const
{
    return digits.size();
}

string calculator::BigArithmetic::BigNumber::get_digits() const
{
    return digits;
}

string calculator::BigArithmetic::BigNumber::str() const
{
    if (!negative)
        return digits;
    return '-' + digits;
}

const char &calculator::BigArithmetic::BigNumber::operator[](const size_t index) const
{
    if (index >= digits.size())
        throw std::out_of_range("Неверный индекс");
    return digits[index];
}

bool calculator::BigArithmetic::BigNumber::operator==(const BigNumber &other) const
{
    if (negative != other.negative)
        return false;
    if (digits.size() != other.digits.size())
        return false;
    for (size_t i = 0; i < digits.size(); ++i)
    {
        if (digits[i] != other.digits[i])
            return false;
    }
    return true;
}

bool calculator::BigArithmetic::BigNumber::operator!=(const BigNumber &other) const
{
    return !(*this == other);
}

bool calculator::BigArithmetic::BigNumber::operator<(const BigNumber &other) const
{
    if (negative && !other.negative)
        return true;
    if (!negative && other.negative)
        return false;

    int cmp = BigArithmetic::compare_abs(*this, other);

    if (!negative)
        return cmp < 0;
    else
        return cmp > 0;
}

bool calculator::BigArithmetic::BigNumber::operator<=(const BigNumber &other) const
{
    return (*this < other) || (*this == other);
}

bool calculator::BigArithmetic::BigNumber::operator>(const BigNumber &other) const
{
    return !(*this <= other);
}

bool calculator::BigArithmetic::BigNumber::operator>=(const BigNumber &other) const
{
    return !(*this < other);
}

BigNumber calculator::BigArithmetic::add(const BigNumber &A, const BigNumber &B)
{
    if (is_zero(A))
        return B;
    if (is_zero(B))
        return A;
    if (A.size() > MAX_DIGITS)
        throw BigNumberException("Переполнение в числе А (слишком много разрядов)");
    if (B.size() > MAX_DIGITS)
        throw BigNumberException("Переполнение в числе B (слишком много разрядов)");
    string res_digits;
    BigNumber R;
    if (A.is_negative() == B.is_negative())
    {
        int ia = (int)A.size() - 1;
        int ib = (int)B.size() - 1;
        char carry = ZERO;
        while (ia >= 0 || ib >= 0 || carry != ZERO)
        {
            char xa = ia >= 0 ? A[ia] : ZERO;
            char xb = ib >= 0 ? B[ib] : ZERO;

            char r = SmallArithmetic::add(SmallArithmetic::add(xa, xb), carry);

            bool new_carry = causes_carry(xa, xb) || causes_carry(SmallArithmetic::add(xa, xb), carry);
            carry = new_carry ? SmallArithmetic::plus1(ZERO) : ZERO;

            res_digits.insert(res_digits.begin(), r);
            ia--;
            ib--;
        }
        R = BigNumber(A.is_negative(), res_digits);
    }
    else
    {
        BigNumber max_number;
        BigNumber min_number;
        if (A <= B)
        {
            max_number = B;
            min_number = A;
        }
        else
        {
            max_number = A;
            min_number = B;
        }

        int imax = (int)max_number.size() - 1;
        int imin = (int)min_number.size() - 1;
        char carry = ZERO;
        while (imax >= 0 || imin >= 0 || carry != ZERO)
        {
            char xmax = imax >= 0 ? max_number[imax] : ZERO;
            char xmin = imin >= 0 ? min_number[imin] : ZERO;

            char r = SmallArithmetic::sub(SmallArithmetic::sub(xmax, xmin), carry);

            bool new_carry = causes_carry(r, xmin) || causes_carry(SmallArithmetic::add(r, xmin), carry);
            carry = new_carry ? SmallArithmetic::plus1(ZERO) : ZERO;

            res_digits.insert(res_digits.begin(), r);

            imax--;
            imin--;
        }
        R = BigNumber(max_number.is_negative(), res_digits);
    }
    return R;
}

BigNumber calculator::BigArithmetic::sub(const BigNumber &A, const BigNumber &B)
{
    BigNumber nB(!B.is_negative(), B.get_digits());
    return add(A, nB);
}

BigNumber calculator::BigArithmetic::mul(const BigNumber &A, const BigNumber &B)
{
    if (is_zero(A) || is_zero(B))
        return BigNumber(string(1, ZERO));

    bool neg = A.is_negative() ^ B.is_negative();

    int n = (int)A.size();
    int m = (int)B.size();

    vector<char> result(n + m, ZERO);

    for (int i = m - 1; i >= 0; --i)
    {
        for (int j = n - 1; j >= 0; --j)
        {
            auto pr = mult_digits(B[i], A[j]);
            char low = pr.first;
            char carry_char = pr.second;
            io::print("low = " + string(1, low) + ", carry_char = " + string(1, carry_char), YELLOW);

            int pos_low = i + j + 1;
            int pos_high = i + j;

            char old = result[pos_low];
            char summed = SmallArithmetic::add(old, low);
            result[pos_low] = summed;

            if (causes_carry(old, low))
            {
                int k = pos_high;
                while (k >= 0)
                {
                    char oldk = result[k];
                    char newk = SmallArithmetic::plus1(oldk);
                    result[k] = newk;

                    if (newk != ZERO)
                        break;

                    --k;
                }
                if (k < 0)
                {
                    throw BigNumberException("Переполнение: результат умножения слишком длинный");
                }
            }

            if (carry_char != ZERO)
            {
                char old = result[pos_high];
                char summed = SmallArithmetic::add(old, carry_char);
                result[pos_high] = summed;

                if (causes_carry(old, carry_char))
                {
                    int k = pos_high - 1;
                    while (k >= 0)
                    {
                        char oldk = result[k];
                        char newk = SmallArithmetic::plus1(oldk);
                        result[k] = newk;
                        if (newk != ZERO)
                            break;
                        --k;
                    }
                    if (k < 0)
                    {
                        throw BigNumberException("Переполнение: результат умножения слишком длинный");
                    }
                }
            }
            io::print("result[" + std::to_string(pos_low) + "] = " + string(1, result[pos_low]) + ", result[" + std::to_string(pos_high) + "] = " + string(1, result[pos_high]));
        }
    }

    string res_digits;
    bool leading = true;
    for (char c : result)
    {
        if (leading && c == ZERO)
            continue;
        leading = false;
        res_digits.push_back(c);
    }
    if (res_digits.empty())
        res_digits = string(1, ZERO);

    if (res_digits.size() > MAX_DIGITS)
        throw BigNumberException("Переполнение: результат умножения слишком длинный");

    return BigNumber(neg, res_digits);
}

pair<BigNumber, BigNumber> calculator::BigArithmetic::div(const BigNumber &A, const BigNumber &B)
{
    if (is_zero(B))
    {
        if (is_zero(A))
        {
            string max_digits(MAX_DIGITS, MAX_VALUE);
            string msg = "[-" + max_digits + "; " + max_digits + "]";
            throw BigNumberDivisionException(msg);
        }
        throw BigNumberDivisionException("Ø");
    }

    BigNumber zero(false, string(1, ZERO));
    if (is_zero(A))
    {
        return {zero, zero};
    }

    BigNumber absA = A.is_negative() ? BigNumber(false, A.get_digits()) : A;
    BigNumber absB = B.is_negative() ? BigNumber(false, B.get_digits()) : B;

    if (absA < absB)
    {
        return {zero, A};
    }

    char one_char = SmallArithmetic::plus1(ZERO);
    BigNumber one(false, string(1, one_char));

    BigNumber rem = absA;
    BigNumber quotient(false, string(1, ZERO));

    while (compare_abs(rem, absB) >= 0)
    {
        // io::print("rem = " + rem.str() + ", absB = " + absB.str());
        rem = sub(rem, absB);
        quotient = add(quotient, one); // quotient = quotient + 1
        if (quotient.size() > MAX_DIGITS)
            throw BigNumberException("Переполнение при делении");
    }

    bool signAneg = A.is_negative();
    bool signBneg = B.is_negative();

    BigNumber Q = quotient;
    BigNumber R = rem;

    // A-, B+
    if (signAneg && !signBneg)
    {
        if (!is_zero(R))
        {
            Q = add(Q, one); // Q = Q + 1
            R = sub(absB, R);

            if (Q.size() > MAX_DIGITS)
                throw BigNumberException("Переполнение при делении");
        }

        Q = BigNumber(true, Q.get_digits());
        R = BigNumber(false, R.get_digits());
    }
    // A+, B-
    else if (!signAneg && signBneg)
    {
        Q = BigNumber(true, Q.get_digits());
        R = BigNumber(false, R.get_digits());
    }
    // A-, B- | A+, B+
    else
    {
        Q = BigNumber(false, Q.get_digits());
        R = BigNumber(false, R.get_digits());
    }

    return {Q, R};
}

BigNumber calculator::BigArithmetic::exp(const BigNumber &A, const BigNumber &B)
{
    return BigNumber();
}

int calculator::BigArithmetic::compare_abs(const BigNumber &A, const BigNumber &B)
{
    if (A.size() > B.size())
        return 1;
    if (A.size() < B.size())
        return -1;

    for (size_t i = 0; i < A.size(); i++)
    {
        int cmp = SmallArithmetic::compare(A[i], B[i]);
        if (cmp != 0)
            return cmp;
    }
    return 0;
}

bool calculator::BigArithmetic::is_zero(const BigNumber &A)
{
    return (A.size() == 1 && A[0] == ZERO);
}

pair<char, char> calculator::BigArithmetic::mult_digits(const char &a, const char &b)
{
    pair<char, char> result(ZERO, ZERO);
    io::print("times:" + string(1, b));

    char current = ZERO; // 'a'

    while (current != b)
    {
        char old = result.first;
        char newResult = SmallArithmetic::add(old, a);

        bool carry = causes_carry(old, a);
        io::print("'" + string(1, old) + "' + '" + string(1, a) + "' causes_carry = " + std::to_string(carry));

        if (carry)
            result.second = SmallArithmetic::plus1(result.second);

        result.first = newResult;
        current = SmallArithmetic::plus1(current);
    }
    return result;
}

bool calculator::BigArithmetic::causes_carry(const char &a, const char &b)
{
    static const auto carry = SmallArithmetic::carry_table();

    for (int i = 0; i < carry.size(); i++)
    {
        for (int j = 0; j < carry[i].size(); j++)
        {
            if (elems[i] == a && elems[j] == b)
            {
                // io::print(string(1, elems[i]) + " and " + string(1, elems[j]) + " is_carry: " + string(1, carry[i][j]), PURPLE);
                return carry[i][j] == '+';
            }
        }
    }
    string error_msg = "Символов '" + string(1, a) + "' и '" + string(1, b) + "' не существует в таблице переноса";
    throw std::runtime_error(error_msg);
}
