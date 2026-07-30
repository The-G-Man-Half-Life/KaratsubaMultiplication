#include "KaratsubaMult.hpp"
#include <algorithm>
#include <stdexcept>

void trim(BigInt& num) {
    while (num.size() > 1 && num.back() == 0) {
        num.pop_back();
    }
}

BigInt stringToBigInt(const std::string& str) {
    BigInt num;

    for (int i = str.length() - 1; i >= 0; --i) {
        if (!isdigit(str[i])) {
            throw std::invalid_argument("El input debe de contener solo caracteres numericos");
        }
        num.push_back(str[i] - '0');
    }
    trim(num);

    return num;
}

std::string bigIntToString(const BigInt& num) {
    if (num.empty()) return "0";
    std::string result = "";
    for (int i = num.size() - 1; i >= 0; --i) {
        result += std::to_string(num[i]);
    }

    return result;
}

BigInt addBigInt(const BigInt& a, const BigInt& b) {
    BigInt result;
    int carry = 0;
    size_t maxSize = std::max(a.size(), b.size());
    
    for (size_t i = 0; i < maxSize || carry > 0; ++i) {
        int valA = (i < a.size()) ? a[i] : 0;
        int valB = (i < b.size()) ? b[i] : 0;
        
        int sum = valA + valB + carry;
        result.push_back(sum % 10);
        carry = sum / 10;
    }

    return result;
}

BigInt subtractBigInt(const BigInt& a, const BigInt& b) {
    BigInt result;
    int borrow = 0;
    
    for (size_t i = 0; i < a.size(); ++i) {
        int valA = a[i];
        int valB = (i < b.size()) ? b[i] : 0;
        
        int diff = valA - valB - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.push_back(diff);
    }
    trim(result);

    return result;
}

BigInt shiftLeft(const BigInt& num, size_t k) {
    if (num.size() == 1 && num[0] == 0) return num; 
    BigInt result(k, 0);
    result.insert(result.end(), num.begin(), num.end());

    return result;
}

BigInt karatsuba(const BigInt& a, const BigInt& b) {
    if (a.size() <= 1 && b.size() <= 1) {
        int valA = a.empty() ? 0 : a[0];
        int valB = b.empty() ? 0 : b[0];
        int prod = valA * valB;
        if (prod < 10) return {prod};
        return {prod % 10, prod / 10}; 
    }

    size_t n = std::max(a.size(), b.size());
    BigInt a_pad = a;
    BigInt b_pad = b;
    while (a_pad.size() < n) a_pad.push_back(0);
    while (b_pad.size() < n) b_pad.push_back(0);

    size_t m = n / 2;

    BigInt a0(a_pad.begin(), a_pad.begin() + m);
    BigInt a1(a_pad.begin() + m, a_pad.end());
    
    BigInt b0(b_pad.begin(), b_pad.begin() + m);
    BigInt b1(b_pad.begin() + m, b_pad.end());

    trim(a0); trim(a1); trim(b0); trim(b1); 

  
    BigInt z0 = karatsuba(a0, b0);
    
    BigInt z2 = karatsuba(a1, b1);
    
    BigInt a_sum = addBigInt(a1, a0);
    BigInt b_sum = addBigInt(b1, b0);
    BigInt z1_temp = karatsuba(a_sum, b_sum);
    BigInt z1 = subtractBigInt(subtractBigInt(z1_temp, z2), z0);

    BigInt r1 = shiftLeft(z2, 2 * m);
    BigInt r2 = shiftLeft(z1, m);
    
    BigInt result = addBigInt(addBigInt(r1, r2), z0);
    trim(result); 
    return result;
}