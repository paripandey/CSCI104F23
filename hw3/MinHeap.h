#include <utility>
#include <vector>
#include <map>

template <class T>
  class MinHeap {
    public:
      MinHeap(int d);
      /* Constructor that builds a d-ary Min Heap
      This should work for any d >= 2,
      but doesn't have to do anything for smaller d.*/

      ~MinHeap();

      void add(T item, int priority);
      /* adds the item to the heap, with the given priority. */

      const T& peek() const;
      /* returns the element with smallest priority.  
      Break ties however you wish.  
      Throws an exception if the heap is empty. */

      void remove();
      /* removes the element with smallest priority.
      Break ties however you wish.
      Throws an exception if the heap is empty. */

      bool isEmpty() const;
      /* returns true iff there are no elements on the heap. */

  private:
    // whatever you need to naturally store things.
    // You may also add helper functions here.

    int d_; // stores the maximum number of children that each parent can have
    
    void swap(int parent, int loc);

    void trickleUp(int loc); // used in add()
    
    void trickleDown(unsigned int loc); // used in remove()
    
    std::vector<std::pair<T, int>> heap; // the actual heap

    /* NOTE: THE MAP IS USED ONLY FOR THE *DOUBLET* PART OF THE HOMEWORK.
      IT IS USED TO *UPDATE THE PRIORITY* OF AN EXISTING ITEM.
      MINHEAP, AND THE "REST" OF THE HEAP, IS BUILT ONLY WITH A VECTOR AS INSTRUCTED.
      *NICHOLAS* SAID THAT USING THE MAP FOR THIS PURPOSE IS OKAY. @1097 ON PIAZZA.
    */

    std::map<T, int> map_; // stores the location of each item
  };

template <class T>
MinHeap<T>::MinHeap(int d) : d_(d) {
}
    
template <class T>
MinHeap<T>::~MinHeap() {}

template <class T>
void MinHeap<T>::add(T item, int priority) {
  // IF THE ITEM ALREADY EXISTS, UPDATE ITS PRIORITY
  if (map_.find(item) != map_.end()) {
    int loc = map_[item]; // FIND THE LOCATION OF THE ITEM

    // THE NEW PRIORITY IS HIGHER
    if (heap[loc].second < priority) {
      heap[loc].second = priority;
      trickleDown(loc);
    }

      // THE NEW PRIORITY IS LOWER
    else {
      heap[loc].second = priority;
      trickleUp(loc);
    }
  }

  // ADD A NEW ITEM TO THE HEAP
  else {
    heap.push_back(std::pair<T, int>(item, priority));
    map_[item] = heap.size() - 1; // INITIALIZE THE LOCATION OF THE ITEM
    trickleUp(heap.size()-1);
  }
}

template <class T>
void MinHeap<T>::trickleUp(int loc)
{
  int parent = (loc-1)/d_; // STORES THE PARENT OF THE ITEM
  bool done = false; // TRACKS WHETHER THE PROCESS IS COMPLETE

  // WHILE THE PROCESS IS INCOMPLETE
  while (!done) {
    // WHILE THE ITEM HAS A LOWER PRIORITY THAN ITS PARENT
    while (parent >= 0 && heap[loc].second < heap[parent].second) {
        swap(parent, loc); // SWAPS THE 2 ITEMS
        // SWAPS THEIR LOCATIONS
        loc = parent;
        parent = (loc-1)/d_;
    }

    // TIE-BREAKER: THE 2 ITEMS HAVE THE SAME PRIORITY. SORT BASED ON THE VALUE OF THE ITEM.
    if ((heap[loc].second == heap[parent].second) && (heap[loc].first < heap[parent].first)) {
      swap(parent, loc);
      loc = parent;
      parent = (loc-1)/d_;
    }

    else { // THE PROCESS IS COMPLETE
      done = true;
    }
  }
}

template <class T>
void MinHeap<T>::swap(int parent, int loc) {
  // SWAPS THE 2 ITEMS' LOCATIONS
  map_[heap[loc].first] = parent;
  map_[heap[parent].first] = loc;
  
  // STORES THE PARENT'S ORIGINAL ITEM
  std::pair<T, int> temp = heap[parent];

  // SWAPS THE 2 ITEMS
  heap[parent] = heap[loc];
  heap[loc] = temp;
}

template <class T>
const T& MinHeap<T>::peek() const {
  // IF THE HEAP IS EMPTY, THERE IS NOTHING TO RETURN
  if (isEmpty()) {
    throw 0; 
  }

  return heap.front().first; // RETURN THE 1ST ITEM
}

template <class T>
void MinHeap<T>::remove() {
  // IF THE HEAP IS EMPTY, THERE IS NOTHING TO RETURN
  if (isEmpty()) {
    throw 0;
  }

  map_.erase(heap[0].first); // REMOVES THE LOCATION OF THE 1ST ITEM
  heap[0] = heap.back(); // REPLACES THE 1ST ITEM WITH THE LAST ITEM
  map_[heap.back().first] = 0; // SETS THE NEW LOCATION OF THE LAST ITEM (TO 0)
  heap.pop_back(); // REMOVES THE LAST "LOCATION" OF THE HEAP
  trickleDown(0);
}

template <class T>
void MinHeap<T>::trickleDown(unsigned int loc) {
  // IF THE ITEM HAS NO CHILDREN (LEAF NODE)
  if(d_ * loc + 1 >= heap.size()) {
    return;
  }

  int smallerChild = d_ * loc + 1; // START WITH THE 1ST/LEFTMOST CHILD
  unsigned int rChild = smallerChild+1; // STORE THE NEXT (RIGHT) CHILD

  // WHILE A RIGHT CHILD EXISTS
  while ((rChild < heap.size()) && (rChild <= (d_ * (loc+1)))) {
    // THE RIGHT CHILD HAS A LOWER PRIORITY THAN THE LEFT CHILD
    if(heap[rChild].second < heap[smallerChild].second) {
      // THE RIGHT CHILD IS NOW THE SMALLER CHILD
      smallerChild = rChild;
    }

    // TIE-BREAKER; BOTH CHILDREN HAVE THE SAME PRIORITY. SORT BASED ON THE VALUE OF THE ITEM.
    else if ((heap[rChild].second == heap[smallerChild].second) && (heap[rChild].first < heap[smallerChild].first)) {
      smallerChild = rChild;
    }

    // MOVE TO THE NEXT CHILD
    else {
      rChild++;
    }
  }

  // THE PARENT HAS A HIGHER PRIORITY THAN THE CHILD
  if(heap[loc].second > heap[smallerChild].second){
    swap(loc, smallerChild);
    trickleDown(smallerChild);
  }

  // TIE-BREAKER: THE 2 ITEMS HAVE THE SAME PRIORITY. SORT BASED ON THE VALUE OF THE ITEM.
  else if ((heap[loc].second == heap[smallerChild].second) && (heap[loc].first > heap[smallerChild].first)) {
    swap(loc, smallerChild);
    trickleDown(smallerChild);
  }
}

template <class T>
bool MinHeap<T>::isEmpty() const {
  return (heap.size() == 0);
}