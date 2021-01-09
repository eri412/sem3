#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <string>

#define OPER_BUFFER 2

class TransNumber {
public:
    TransNumber(float a, float b) {
        a_ = a;
        b_ = b;
    }
    TransNumber operator+(const TransNumber& other) const {
        return TransNumber(a_ + other.a_, b_ + other.b_);
    }
    TransNumber operator-(const TransNumber& other) const {
        return TransNumber(a_ - other.a_, b_ - other.b_);
    }
    TransNumber operator*(const TransNumber& other) const {
        return TransNumber(a_*other.a_ + b_*other.b_*2, a_*other.b_ + b_*other.a_);
    }
    TransNumber operator/(const TransNumber& other) const {
        return TransNumber((a_*other.a_ - 2*b_*other.b_)/(pow(other.a_, 2) - 2*pow(other.b_, 2)),
                           (b_*other.a_ - a_*other.b_)/(pow(other.a_, 2) - 2*pow(other.b_, 2)));
    }
    TransNumber& operator+=(const TransNumber& other) {
        return *this = *this + other;
    }
    TransNumber& operator-=(const TransNumber& other) {
        return *this = *this - other;
    }
    TransNumber& operator*=(const TransNumber& other) {
        return *this = *this * other;
    }
    TransNumber& operator/=(const TransNumber& other) {
        return *this = *this / other;
    }
    bool operator>(const TransNumber& other) const {
        return a_ + b_*sqrt(2) > other.a_ + other.b_*sqrt(2);
    }
    bool operator<(const TransNumber& other) const {
        return a_ + b_*sqrt(2) < other.a_ + other.b_*sqrt(2);
    }
    bool operator==(const TransNumber& other) const {
        return a_ + b_*sqrt(2) == other.a_ + other.b_*sqrt(2);
    }
    bool operator>=(const TransNumber& other) const {
        return *this > other || *this == other;
    }
    bool operator<=(const TransNumber& other) const {
        return *this < other || *this == other;
    }
    bool operator!=(const TransNumber& other) const {
        return !(*this == other);
    }
    float tofloat() const {
        return a_ + b_*sqrt(2);
    }
    std::string tostring() const{
        return std::to_string(a_) + ";" + std::to_string(b_) + "k";
    }
private:
    float a_;
    float b_;
};

const TransNumber operator"" _trans(const char *str, size_t size) {
    char str_temp[size + 1];
    strcpy(str_temp, str);
    int index = size - 1;
    for (int i = 0; i < size; ++i) {
        if (str_temp[i] == ';') {
            index = i;
            str_temp[i] = '\0';
            break;
        }
    }
    return TransNumber(atof(str_temp), atof(str_temp + index + 1));
}

int main() {
    float a1, a2, b1, b2;
    char operation[OPER_BUFFER + 1];
    for (int i = 0; i < OPER_BUFFER + 1; ++i) {
        operation[i] = '\0';
    }
    scanf("%f;%f %s %f;%f", &a1, &b1, operation, &a2, &b2);
    TransNumber lhs(a1, b1);
    TransNumber rhs(a2, b2);
    std::cout << std::boolalpha;
    printf("%f;%f %s %f;%f\n", a1, b1, operation, a2, b2);
    if (strcmp(operation, "+") == 0) {
        TransNumber result = lhs + rhs;
        std::cout << "= " << result.tostring() << " = " << result.tofloat() << std::endl;
    }
    else if (strcmp(operation, "-") == 0) {
        TransNumber result = lhs - rhs;
        std::cout << "= " << result.tostring() << " = " << result.tofloat() << std::endl;
    }
    else if (strcmp(operation, "*") == 0) {
        TransNumber result = lhs * rhs;
        std::cout << "= " << result.tostring() << " = " << result.tofloat() << std::endl;
    }
    else if (strcmp(operation, "/") == 0) {
        TransNumber result = lhs / rhs;
        std::cout << "= " << result.tostring() << " = " << result.tofloat() << std::endl;
    }
    else if (strcmp(operation, ">") == 0) {
        std::cout << "= " << (lhs > rhs) << std::endl;
    }
    else if (strcmp(operation, "<") == 0) {
        std::cout << "= " << (lhs < rhs) << std::endl;
    }
    else if (strcmp(operation, "==") == 0) {
        std::cout << "= " << (lhs == rhs) << std::endl;
    }
    else if (strcmp(operation, ">=") == 0) {
        std::cout << "= " << (lhs >= rhs) << std::endl;
    }
    else if (strcmp(operation, "<=") == 0) {
        std::cout << "= " << (lhs <= rhs) << std::endl;
    }
    else if (strcmp(operation, "!=") == 0) {
        std::cout << "= " << (lhs != rhs) << std::endl;
    }
    else if (strcmp(operation, "??") == 0) {
        std::cout << "= " << "5;3"_trans.tostring() << std::endl;
    }
    else {
        printf("something went terribly wrong\n");
    }

    return 0;
}