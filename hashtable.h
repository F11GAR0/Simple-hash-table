#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "main.h"

class HashGenerator{
public:
    template<typename T>
    static int GetHash(const T& key, unsigned int bound){
        int index = 0;
        for (int i = 0, len = sizeof(T); i < len; i++)
            index += *(byte*)&key;
        return (sizeof(T) * index) % bound;
    }
    static int GetHash(std::string key, unsigned int bound){
        int index = 0;
        for (int i = 0, len = key.length(); i < len; i++)
            index += 2 * key.c_str()[i];
        return (key.length() * index) % bound;
    }
};

template <typename TKey, typename TValue>
class HashTable
{
public:
    explicit HashTable(unsigned int supposed_len = 30){
        m_vecKeyLists.resize(supposed_len);
        m_uiKeyListLen = supposed_len;
    }
    TValue &operator[](const TKey &key){
        int index = HashGenerator::GetHash(key, m_uiKeyListLen);
        for(auto& var : m_vecKeyLists[index]){
            if(var.first == key){
                return var.second;
            }
        }
        std::pair<TKey,TValue> new_pair = std::make_pair(key, TValue());
        m_vecKeyLists[index].push_back(new_pair);
        return FindValue(key);
    }
#ifdef UNSAFE
    TValue Find(const TKey &key){
        return FindValue(key);
    }
#endif
private:
    TValue& FindValue(const TKey &key){
        //do not ever return a stack!
        TValue *nil = nullptr;
        int index = HashGenerator::GetHash(key, m_uiKeyListLen);
        for(auto& var : m_vecKeyLists[index]){
            if(var.first == key){
                return var.second;
            }
        }
        return *nil;
    }
    std::vector<std::list<std::pair<TKey, TValue>>> m_vecKeyLists;
    unsigned int m_uiKeyListLen;
};

#endif // HASHTABLE_H
