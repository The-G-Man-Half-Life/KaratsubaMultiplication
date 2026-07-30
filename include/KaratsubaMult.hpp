#pragma once

#include <vector>
#include <string>

using BigInt = std::vector<int>;

BigInt stringToBigInt(const std::string& stringInp);
std::string bigIntToString(const BigInt& number);

void trim(BigInt& num); 
BigInt sumBigInt(const BigInt& a, const BigInt& b);
BigInt subtractBigInt(const BigInt& a, const BigInt& b); 
BigInt bigMultiplication(const BigInt& number, size_t k);           

BigInt karatsuba(const BigInt& a, const BigInt& b);