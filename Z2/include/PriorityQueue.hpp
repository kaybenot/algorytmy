#pragma once
#include <utility>
#include <array>
#include <cmath>
#include <stdexcept>

template<typename T>
class Element
{
private:
    std::pair<T, int> p;

public:
    Element()
    {}

    Element(T val, int priority)
    {
        p.first = val;
        p.second = priority;
    }

    T val()
    {
        return p.first;
    }

    int priority()
    {
        return p.second;
    }
};

template<typename T>
class PriorityQueue
{
private:
    Element<T>* arr;
    unsigned int maxSize;
    unsigned int size;
    unsigned int largest;

    unsigned int left(unsigned int i)
    {
        return i * 2;
    }

    unsigned int right(unsigned int i)
    {
        return i * 2 + 1;
    }

    unsigned int parent(unsigned int i)
    {
        return i / 2;
    }

    void swap(Element<T>* A, unsigned int i, unsigned int j)
    {
        Element<T> tmp = A[j];
        A[j] = A[i];
        A[i] = tmp;
    }

    void buildMaxHeap(Element<T>* A, unsigned int& heapSize)
    {
        for (int i = heapSize / 2; i >= 0; i--)
            maxHeapify(A, heapSize, i);
    }

    void maxHeapify(Element<T>* A, unsigned int& heapSize, unsigned int i)
    {
        unsigned int l = left(i);
        unsigned int r = right(i);
        if ((l < heapSize) && (A[l].priority() > A[i].priority()))
            largest = l;
        else
            largest = i;
        if ((r < heapSize) && (A[r].priority() > A[largest].priority()))
            largest = r;
        if (largest != i)
        {
            swap(A, i, largest);
            maxHeapify(A, heapSize, largest);
        }
    }

    void maxHeapInsert(Element<T>* A, unsigned int& heapSize, Element<T> el)
    {
        A[heapSize] = el;
        heapIncreaseKey(A, heapSize, el);
        heapSize++;
    }

    void heapIncreaseKey(Element<T>* A, unsigned int i, Element<T> el)
    {
        if (el.priority() < A[i].priority())
            throw std::runtime_error("New key is smaller than current key");
        A[i] = el;
        while ((i > 0) && A[parent(i)].priority() < A[i].priority())
        {
            swap(A, i, parent(i));
            i = parent(i);
        }
    }

    void removeFirst()
    {
        arr[0] = arr[size - 1];
        size--;
        buildMaxHeap(arr, size);
    }

public:
    PriorityQueue(unsigned int size)
    {
        arr = new Element<T>[size];
        maxSize = size;
        this->size = 0;
    }

    void InsertElement(Element<T> e)
    {
        maxHeapInsert(arr, size, e);
    }

    int getMaxPriority()
    {
        return arr[0].priority;
    }

    Element<T> Pop()
    {
        Element<T> el = arr[0];
        removeFirst();
        return el;
    }

    void IncreasePriority(Element<T> e, int priority)
    {
        for (int i = 0; i < size; i++)
        {
            if (arr[i].val() == e.val())
                arr[i].priority() += priority;
        }
        buildMaxHeap(arr, size);
    }
};
