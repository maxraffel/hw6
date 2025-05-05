#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long* w = generateAllW(k);
        unsigned long long result = 0;

        for (size_t i = 0; i < 5; ++i) {
            result += rValues[i] * w[i];
        }

        delete [] w;

        return result;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        char lower = std::tolower(letter);
        if (lower >= 'a' && lower <= 'z') {
            return lower - 'a'; // letter
        } else if (lower >= '0' && lower <= '9') {
            return lower - '0' + 26; // number
        } else {
            return -1; // should never happen
        }

    }

    unsigned long long generateW(const std::string& substr) const {
        unsigned long long w = 0;
        unsigned long long multiplier = 1;
        for (size_t i = 0; i < substr.size(); ++i) {
            w += letterDigitToNumber(substr[substr.size() - i - 1]) * multiplier;
            multiplier *= 36;
        }
        return w;
    }

    unsigned long long* generateAllW(const std::string& k) const {
        unsigned long long* w = new unsigned long long[5];
        size_t index = 0;
        size_t wIndex = 0;
        size_t offset = k.size() % 6;
        for (size_t i = 4; i > (k.size() - 1) / 6; --i) {
            w[wIndex] = 0;
            std::cout << "w[" << wIndex << "] = 0" << std::endl;
            wIndex++;
        }
        if (offset != 0) {
            w[wIndex] = generateW(k.substr(0, offset));
            std::cout << "w[" << wIndex << "] = " << w[wIndex] << std::endl;
            index = offset;
            wIndex++;
        }
        for (; wIndex < 5; wIndex++) {
            w[wIndex] = generateW(k.substr(index, 6));
            index += 6;
            std::cout << "w[" << wIndex << "] = " << w[wIndex] << std::endl;
        }
        return w;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
