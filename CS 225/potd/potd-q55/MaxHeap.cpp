#include "MaxHeap.h"

MaxHeap::MaxHeap(const vector<int> & vector)
{
    int inf = numeric_limits<int>::max();
    elements.push_back(inf);
    elements.insert(elements.end(), vector.begin(), vector.end());
    buildHeap();
}

MaxHeap::MaxHeap()
{
    int inf = numeric_limits<int>::max();
    elements.push_back(inf);
}

void MaxHeap::buildHeap()
{
    std::sort(elements.begin() + 1, elements.end(), std::greater<int>());
}

void MaxHeap::heapifyDown(int index)
{
    int length = elements.size();
    int leftChildIndex = 2 * index;
    int rightChildIndex = 2 * index + 1;

    if (leftChildIndex >= length)
        return; // index is a leaf

    int maxIndex = index;

    if (elements[index] < elements[leftChildIndex]) {
        maxIndex = leftChildIndex;
    }

    if ((rightChildIndex < length)
        && (elements[maxIndex] < elements[rightChildIndex])) {
        maxIndex = rightChildIndex;
    }

    if (maxIndex != index) {
        // need to swap
        int temp = elements[index];
        elements[index] = elements[maxIndex];
        elements[maxIndex] = temp;
        heapifyDown(maxIndex);
    }
}

void MaxHeap::heapifyUp(int index)
{
    if (index < 2)
        return;

    int parentIndex = index / 2;

    if (elements[parentIndex] < elements[index]) {
        int temp = elements[parentIndex];
        elements[parentIndex] = elements[index];
        elements[index] = temp;
        heapifyUp(parentIndex);
    }
}

void MaxHeap::insert(int newValue)
{
    int length = elements.size();
    elements.push_back(newValue);
    heapifyUp(length);
}

int MaxHeap::peek() const
{
    return elements.at(1);
}

int MaxHeap::pop()
{
    int length = elements.size();
    int p = -1;

    if (length > 1) {
        p = elements[1];
        elements[1] = elements[length - 1];
        elements.pop_back();
        heapifyDown(1);
    }

    return p;
}

void MaxHeap::print() const
{
    if (elements.size() > 1) {
        int length = elements.size();
        cout << "[";
        for (int i = 1; i < length - 1; i++) {
            cout << elements[i] << ", ";
        }
        cout << elements[elements.size() - 1] << "]" << endl;
    } else {
        cout << "[ ]" << endl;
    }
}
