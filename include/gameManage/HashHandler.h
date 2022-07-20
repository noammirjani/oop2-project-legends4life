#pragma once
#include <unordered_map>


//in the multimethods we disided to hold the functions in order map while the keys are pair of typeIndex.
//that contains that the unordermap we used will call key,val,hashFunction and key comparision function. 
// to read more: https://en.cppreference.com/w/cpp/container/unordered_map/unordered_map



// A hash function used to hash a pair of any kind, hashing each one of the keys and returns the xoe value
// of the two hashing. if they both equal the xor will return 0.
struct PairKeysHash 
{
    template <class T>
    size_t operator()(const std::pair<T, T>& p) const
    {
        return std::hash<T>{}(p.first) ^ std::hash<T>{}(p.second);
    }
};



//comparison function to use for all key comparisons of this container
//compare each component of the pairs
struct KeyEqual 
{
    template <class T>
    bool operator()(const std::pair<T, T>& lKey, const std::pair<T, T>& rKey) const
    {
        return lKey.first == rKey.first && lKey.second == rKey.second;
    }
};