/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // finished 
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    //finished
    return 2*currentIdx;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    //finished
    return 2*currentIdx + 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    //finished
    return currentIdx/2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    //finished
    return (currentIdx*2) < _elems.size();
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    //finished
    if(hasAChild(currentIdx)){
       if(currentIdx*2+1 >= _elems.size())
            return leftChild(currentIdx);
       else { 
           if(higherPriority(_elems[leftChild(currentIdx)],_elems[rightChild(currentIdx)]))
            return leftChild(currentIdx);
           else 
            return rightChild(currentIdx);
          }
       }
       return 0;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    //finished
    if(hasAChild(currentIdx)){
      size_t childIdx = maxPriorityChild(currentIdx);
      if(higherPriority(_elems[childIdx],_elems[currentIdx])){
        /*  T temp = _elems[maxPriorityChild(currentIdx)];
          _elems[maxPriorityChild(currentIdx)] = _elems[currentIdx];
          _elems[currentIdx] = temp; */
          std::swap(_elems[currentIdx],_elems[childIdx]);
          heapifyDown(childIdx); 
        }   
     }  
           
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    //finished
    _elems.push_back(T());
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
    //finished
      _elems.push_back(T());
    for(size_t i = 0; i < elems.size(); i++)
      _elems.push_back(elems[i]);
    for(size_t i = parent(_elems.size()-1);i>0;i--)
       heapifyDown(i);
         
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    //finished
    if(_elems.size() != 1){
    
    T temp = _elems[1];
    _elems[1] = _elems[_elems.size()-1]; 
    _elems.pop_back();
    heapifyDown(1);
    return temp;
   }
     return T();
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    //finished
    if(_elems.size() != 1){
       return  _elems[1];
     }
    return T();
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    //finished
    _elems.push_back(elem);
    heapifyUp(_elems.size()-1); 
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    if(_elems.size() == 1)
      return true;
    // finished
    return false;
}
