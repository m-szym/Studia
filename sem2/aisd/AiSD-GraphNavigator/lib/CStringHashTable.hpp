#pragma once

#include <cmath>
#include <cstring>

#include "HashTable.hpp"

const int STRING_HASH_MAX_KEY_SIZE = 20;
const int STRING_HASH_PRIME_LIMITER = 15485863;
const int STRING_HASH_BASE_PRIME = 67;
const char STRING_HASH_FLOOR_CHAR = '0';

const double HASH_PRIME = (sqrt(5) - 1) / 2;

template<typename DataT>
class CStringHashTable : public HashTable<char*, DataT>
{
private:
    size_t hash(char* key) override;
public:
    CStringHashTable(size_t newSize);
};

template<typename DataT>
size_t CStringHashTable<DataT>::hash(char* key)
{
   
    if (strlen(key) > STRING_HASH_MAX_KEY_SIZE)
        throw "Key too long";


    int i = 0;
    int poweredPrime = STRING_HASH_BASE_PRIME;        
    size_t hashValue = 0;   

    while (i < STRING_HASH_MAX_KEY_SIZE)
    {
        if (key[i] == '\0') 
            break;
        hashValue = (hashValue + (key[i] - STRING_HASH_FLOOR_CHAR + 1) * poweredPrime) % STRING_HASH_PRIME_LIMITER;
        poweredPrime = (poweredPrime * STRING_HASH_BASE_PRIME) % STRING_HASH_PRIME_LIMITER;
        ++i;
    }

    size_t index = this->size * fmod(hashValue * HASH_PRIME, 1);
    
    return index;
}

template<typename DataT>
CStringHashTable<DataT>::CStringHashTable(size_t newSize)
    : HashTable<char*, DataT>(newSize)
{}



