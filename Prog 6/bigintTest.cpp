// Citlally Vasquez
// CECS 325-01
//  Prog 6 -  BigInt class (arbitrarily large integers)
//  Due (05/08/24)
//
//  I certify that this program is my own original work. I did not copy any part of this program from any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <climits>
#include <cmath>

using namespace std;

// -- Bigint Header (outline given) --
class BigInt {
private:
    vector<char> v; // Vector stores digits

    // Helper function for Fibonacci calculation
    static BigInt fiboHelper(BigInt n, BigInt a = 0, BigInt b = 1) {
    BigInt i = 2;
    while (i <= n) {
        BigInt c = a + b;
        a = b;
        b = c;
        ++i;
    }
    return b;
}

public:
    // Constructors
    BigInt() {}

    // Converts integer into strings and places digits in vector
    BigInt(int num) {
        while (num > 0) {
            v.insert(v.begin(), num % 10);
            num /= 10;
        }
    }

    BigInt(string str) {
        // Converts char to digit
        for (size_t i = 0; i < str.size(); ++i) {
            v.push_back(str[i] - '0');
        }
    }

    // -- Operator Overloading --

    // Addition operator
    BigInt operator+(const BigInt& other) const {
        BigInt result;
        int carry = 0;
        int i = v.size() - 1, j = other.v.size() - 1;
        while (i >= 0 || j >= 0 || carry) {
            if (i >= 0) carry += v[i--];
            if (j >= 0) carry += other.v[j--];
            result.v.insert(result.v.begin(), carry % 10);
            carry /= 10;
        }
        return result;
    }

    // Subtraction operator
    BigInt operator-(const BigInt& other) const {
        BigInt result;
        int borrow = 0;
        for (int i = v.size() - 1, j = other.v.size() - 1; i >= 0; --i, --j) {
            int diff = v[i] - borrow;
            if (j >= 0) diff -= other.v[j];
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result.v.insert(result.v.begin(), diff);
        }
        // Removes leading zeros
        while (!result.v.empty() && result.v.front() == 0) {
            result.v.erase(result.v.begin());
        }
        return result;
    }
    
    // Decrement operator
    BigInt operator--(int) {
        BigInt temp(*this);
        *this = *this - BigInt(1);
        return temp;
}
    // Mutliplication operator
    BigInt operator*(const BigInt& other) const {
        BigInt result;
        result.v.resize(v.size() + other.v.size(), 0);
        for (int i = v.size() - 1; i >= 0; --i) {
            int carry = 0;
            for (int j = other.v.size() - 1; j >= 0; --j) {
                int product = v[i] * other.v[j] + result.v[i + j + 1] + carry;
                result.v[i + j + 1] = product % 10;
                carry = product / 10;
            }
            result.v[i] += carry;
        }
        // Removes leading zeros
        while (!result.v.empty() && result.v.front() == 0) {
            result.v.erase(result.v.begin());
        }
        return result;
    }

    // Division operator
    BigInt operator/(const BigInt& other) const {
        BigInt quotient;
        BigInt remainder = *this;
        BigInt divisor = other;
        while (remainder >= divisor) {
            int quotientDigit = 0;
            while (remainder >= divisor * (BigInt(quotientDigit + 1))) {
                ++quotientDigit;
            }
            quotient = quotient * 10 + quotientDigit;
            remainder = remainder - divisor * quotientDigit;
        }
        return quotient;
    }

    // Modulo operator
    BigInt operator%(const BigInt& other) const {
        BigInt quotient;
        BigInt remainder = *this;
        BigInt divisor = other;
        while (remainder >= divisor) {
            int quotientDigit = 0;
            while (remainder >= divisor * (BigInt(quotientDigit + 1))) {
                ++quotientDigit;
            }
            quotient = quotient * 10 + quotientDigit;
            remainder = remainder - divisor * quotientDigit;
        }
        return remainder;
    }

    // Increment operator
    BigInt operator++() {
        *this = *this + 1;
        return *this;
    }

    BigInt operator++(int) {
        BigInt temp(*this);
        *this = *this + 1;
        return temp;
    }
    
    // Operators for comparison
    bool operator<(const BigInt& other) const {
        if (v.size() != other.v.size()) return v.size() < other.v.size();
        for (int i = 0; i < v.size(); ++i) {
            if (v[i] != other.v[i]) return v[i] < other.v[i];
        }
        return false;
    }

    bool operator<=(const BigInt& other) const {
        return *this < other || *this == other;
    }

    bool operator>(const BigInt& other) const {
        return !(*this <= other);
    }

    bool operator>=(const BigInt& other) const {
        return !(*this < other);
    }

    bool operator==(const BigInt& other) const {
        return v == other.v;
    }

    bool operator!=(const BigInt& other) const {
        return !(*this == other);
    }

    // Index operator
    char operator[](int index) const {
        return v[index];
    }

    // -- Utility Functions --
    // Displays BigInt
    void print() const {
        for (size_t i = 0; i < v.size(); ++i) {
            cout << static_cast<int>(v[i]);
        }
    }

    // Size function returns # of digits within BigInt
    int size() const {
        return v.size();
    }

    // Fibo function
    BigInt fibo() const {
        return fiboHelper(*this);
    }

    // Factorial
    BigInt fact() const {
        BigInt result(1), current(*this);
        while (current > 1) {
            result = result * current;
            current = current - BigInt(1);
        }
    return result;
}

    // Friend functions
    friend ostream& operator<<(ostream& os, const BigInt& num);
    friend BigInt operator+(int num, const BigInt& bigint);
};

// Friend function for overloading
ostream& operator<<(ostream& os, const BigInt& num) {
    if (num.size() <= 12) {
        for (size_t i = 0; i < num.v.size(); ++i) {
            os << static_cast<int>(num.v[i]);
        }
    } else {
        string str = to_string(num.v[0]);
        str += '.';
        for (size_t i = 1; i < num.v.size(); ++i) {
            str += to_string(num.v[i]);
        }
        os << str.substr(0, 1) << str.substr(1, 6) << "e" << (num.size() - 1);
    }
    return os;
}

// Friend function adds integer and BigInt value
BigInt operator+(int num, const BigInt& bigint) {
    return BigInt(num) + bigint;
}

// -- Test unit function (given) --
void testUnit() {
    int space = 10;
    cout << "\a\nTestUnit:\n" << flush;
    system("whoami");
    system("date");
    // initialize variables
    BigInt n1(25);
    BigInt s1("25");
    BigInt n2(1234);
    BigInt s2("1234");
    BigInt n3(n2);
    BigInt fibo(12345);
    BigInt fact(50);
    BigInt imax = INT_MAX;
    BigInt big("9223372036854775807");
    // display variables
    cout << "n1(int) :" << setw(space) << n1 << endl;
    cout << "s1(str) :" << setw(space) << s1 << endl;
    cout << "n2(int) :" << setw(space) << n2 << endl;
    cout << "s2(str) :" << setw(space) << s2 << endl;
    cout << "n3(n2) :" << setw(space) << n3 << endl;
    cout << "fibo(12345):" << setw(space) << fibo << endl;
    cout << "fact(50) :" << setw(space) << fact << endl;
    cout << "imax :" << setw(space) << imax << endl;
    cout << "big :" << setw(space) << big << endl;
    cout << "big.print(): "; big.print(); cout << endl;
    cout << n2 << "/" << n1 << " = " << n2 / n1 << " rem " << n2 % n1 << endl;
    cout << "fibo(" << fibo << ") = " << fibo.fibo() << endl;
    cout << "fact(" << fact << ") = " << fact.fact() << endl;
    cout << "10 + n1 = " << 10 + n1 << endl;
    cout << "n1 + 10 = " << n1 + 10 << endl;
    cout << "(n1 == s1)? --> " << ((n1 == s1) ? "true" : "false") << endl;
    cout << "n1++ = ? --> before:" << n1++ << " after:" << n1 << endl;
    cout << "++s1 = ? --> before:" << ++s1 << " after:" << s1 << endl;
    cout << "s2 * big = ? --> " << s2 * big << endl;
    cout << "big * s2 = ? --> " << big * s2 << endl;
}

// -- Main function calls for test unit --
int main() {
    testUnit();
    return 0;
}
