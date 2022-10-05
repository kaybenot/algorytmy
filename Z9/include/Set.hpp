#pragma once
#include <vector>
#include <iostream>

template<typename T>
class Set
{
public:
    std::vector<T> arr;

    Set uni(Set other)
    {
        Set<T> set;
        for(auto e : other.arr)
            if(!isMember(e))
                set.insert(e);
        for(auto e : arr)
            set.insert(e);
        return set;
    }

    Set intersection(Set other)
    {
        Set<T> set;
        for(auto e : other.arr)
            if(isMember(e))
                set.insert(e);
        return set;
    }

    Set difference(Set other)
    {
        Set<T> set;
        for(auto e : other.arr)
            if(!isMember(e))
                set.insert(e);
        for(auto e : arr)
            if(!other.isMember(e))
                set.insert(e);
        return set;
    }

    void insert(T el)
    {
        if(!isMember(el))
            arr.push_back(el);
    }

    bool isMember(T el)
    {
        for(auto e : arr)
            if(e == el)
                return true;
        return false;
    }

    T pop(T el)
    {
        for(auto i = arr.begin(); i != arr.end(); i++)
        {
            if(*i == el)
            {
                arr.erase(i);
                return el;
            }
        }
        return T();
    }

    void popAll(Set other)
    {
        for(auto e : other.arr)
        {
            if(isMember(e))
                pop(e);
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Set<T>& set)
    {
        for(auto a : set.arr)
            os << a << ' ';
        return os;
    }

    bool operator==(const Set<T>& r)
    {
        for(T el : r.arr)
        {
            if(!isMember(el))
                return false;
        }
        return true;
    }
};
