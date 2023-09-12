// Hit is a class to store and maniplulate information about an intersection
// between a ray and an object.

#include "hit.h"

Hit* Hit::free_pool = (Hit*)0;

int Hit::allocated = 0;
int Hit::pool_size = 0;

// Custom memory allocation operator new
void* Hit::operator new(size_t size) {
  allocated += 1;

  // If the free pool is empty, allocate a new pool of 100 Hit objects
  if (free_pool == 0) {
    Hit* pool = new Hit[100];
    free_pool = pool;  // Set the free_pool to the newly allocated pool

    // Create a linked list within the pool for reuse
    for (int i = 0; i < 99; i += 1) {
      pool[i].next = &pool[i + 1];
    }
    pool[99].next = 0;  // Set the last Hit object's next pointer to nul

    pool_size += 100;  // Update the pool size
  }

  Hit* next = free_pool;  // Get the next available Hit object from the pool
  free_pool =
      free_pool->next;  // Update the free pool to exclude the allocated object
  next->next = 0;       // Set the next pointer of the allocated object to null
  return next;          // Return the allocated Hit object
}

// Custom memory deallocation operator delete
void Hit::operator delete(void* p) {
  allocated -= 1;
  ((Hit*)p)->next = free_pool;  // Link the deleted object to the free pool
  free_pool = (Hit*)p;  // Update the free pool to include the deleted object
}

// Overloaded output stream operator for easy printing
ostream& operator<<(ostream& os, const Hit& h) {
  os << "Hit{"
     << ",[" << h.position.x << "," << h.position.y << "," << h.position.z
     << "],[" << h.normal.x << "," << h.normal.y << "," << h.normal.z << "]}\n";
  return os;
}
