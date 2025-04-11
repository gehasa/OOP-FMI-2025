#pragma once
#include <cstring>
#include <exception>
#include <stdexcept>

class Utils {
public:
    static bool validName(char* name) {
        if (name == nullptr) {
            throw std::invalid_argument("Empty name!");
        }
        unsigned len = strlen(name);
        if (len < 2 || len > 20) {
            throw std::length_error("Invalid name lenght!");
        }
        char ch = name[len - 1];
        if ((ch < '0' || ch > '9') && (ch < 'a' || ch > 'z') && (ch < 'A' || ch > 'Z')) {
            throw std::invalid_argument("Invalid name!");
        }
        return true;
    }

    static bool validFloat(float price) {
        if (price <= 0) {
            throw std::invalid_argument("Price cannot be negative!");
        }
        else if (std::isnan(price) || std::isinf(price)) {
            throw std::invalid_argument("Price can't be Nan or Inf value");
        }
        return true;
    }
private:
};