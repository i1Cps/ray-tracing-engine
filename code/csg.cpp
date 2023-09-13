
#include "csg.h"

#include "hit.h"

// Constructive Solid Geometry is a way to model complex objects by combining
// simpler objects using set operations on their volumes.

Csg::Csg(Object* object1, Object* object2, int operation) {
  obj1 = object1;
  obj2 = object2;
  operation_ = operation;
}

// Compute the intersection of each object
Hit* Csg::intersection(Ray ray) {
  Hit* obj1_hits = new Hit();
  Hit* obj2_hits = new Hit();

  obj1_hits = this->obj1->intersection(ray);
  obj2_hits = this->obj2->intersection(ray);
  Hit* final = 0;
  final = implement_csg(obj1_hits, obj2_hits);
  return final;
}

Hit* Csg::implement_csg(Hit* hit1, Hit* hit2) {
  Hit* hits = 0;
  Hit* current = 0;

  bool inside1 = false;
  bool inside2 = false;
  bool entering = true;
  while (hit1 != 0 || hit2 != 0) {
    // If A AND B run out of intersections we break loop and return current
    if (hit1 == 0 && hit2 == 0) {
      break;
    }
    // If A OR B run out of intersection we set it as a outside entry at
    // Infinity
    float hit1_t = (hit1 == 0) ? INFINITY : hit1->t;
    float hit2_t = (hit2 == 0) ? INFINITY : hit2->t;
    inside1 = (hit1 == 0) ? false : inside1;
    inside2 = (hit2 == 0) ? false : inside2;

    // Refer to the table below for which action to choose
    float comparison =
        comparison_table(operation_, inside1, inside2, hit1_t, hit2_t);
    if (comparison == 0) {
      // If return is 0: Keep A
      // First apply correct entering value
      bool temp_entering = entering;
      hit1->entering = temp_entering;
      // Make sure it attaches the csg material to the hit
      hit1->what = this;
      // Reverse the entering value
      entering = !entering;

      // Create hit to be added to main hits list
      Hit* temp = new Hit();
      temp->entering = hit1->entering;
      temp->t = hit1->t;
      temp->normal = hit1->normal;
      temp->position = hit1->position;
      temp->what = this;

      // Add the chosen hit to the new hit list for csg object
      if (hits == 0) {
        hits = temp;
        current = hits;
        // Important, Make sure it has a next of 0 to avoid segmentation error
        current->next = 0;
      } else {
        current->next = temp;
        current = current->next;
        current->next = 0;
      }
      // Get next hit1
      hit1 = hit1->next;
      // reverse inside value for hit1
      inside1 = !inside1;
    } else if (comparison == 1) {
      // If return is 1: Keep B
      // First make apply correct entering value
      bool temp_entering = entering;
      hit2->entering = temp_entering;
      // Make sure it attaches the csg material to the hit
      hit2->what = this;
      // reverse the entering value
      entering = !entering;

      // Create hit to be added to main hits list
      Hit* temp = new Hit();
      temp->entering = hit2->entering;
      temp->t = hit2->t;
      temp->normal = hit2->normal;
      temp->position = hit2->position;
      temp->what = this;

      // Add the chosen hit to the new hit list for csg object
      if (hits == 0) {
        hits = temp;
        current = hits;
        current->next = 0;
      } else {
        current->next = temp;
        current = current->next;
        current->next = 0;
      }
      // Get next hit2
      hit2 = hit2->next;
      // reverse inside value for hit2
      inside2 = !inside2;
    } else if (comparison == 2) {
      // If return is 2: Disgard A
      // Get next hit1
      hit1 = hit1->next;
      // reverse inside value for hit1
      inside1 = !inside1;
    } else {
      // If return is 3: Disgard B
      // Get next hit2
      hit2 = hit2->next;
      // reverse inside value for hit2
      inside2 = !inside2;
    }
  }
  return hits;
}

// Function that handles applying operation table, parameter operation can
// either be 0, 1, 2 representing Union, Difference and Intersection
// respectively
int Csg::comparison_table(int operation, bool inside1, bool inside2, float t1,
                          float t2) {
  // Create a comparision function returns 6 options in the form of ints
  // probably Keep A returns: 0 keep B returns: 1 Disgard A returns: 2 Disgard B
  // returns: 3

  if (operation == 0) {
    // Operation: Union
    if (!inside1 && !inside2) {
      if (t1 < t2) {
        return 0;
      } else {
        return 1;
      }
    } else if (inside1 && !inside2) {
      if (t1 < t2) {
        return 0;
      } else if (t2 < t1) {
        return 3;
      } else {
        return 1;
      }
    } else if (inside1 && inside2) {
      if (t1 < t2) {
        return 2;
      } else if (t2 < t1) {
        return 3;
      } else {
        return 1;
      }
    } else {
      if (t1 < t2) {
        return 2;
      } else {
        return 1;
      }
    }
  } else if (operation == 1) {
    // Operation: Difference
    if (!inside1 && !inside2) {
      if (t1 < t2) {
        return 0;
      } else {
        return 3;
      }
    } else if (inside1 && !inside2) {
      if (t1 > t2) {
        return 1;
      } else {
        return 0;
      }
    } else if (inside1 && inside2) {
      if (t1 > t2) {
        return 1;
      } else {
        return 2;
      }
    } else {
      if (t1 < t2) {
        return 2;
      } else {
        return 3;
      }
    }
  } else {
    // Operation: Intersection
    if (!inside1 && !inside2) {
      if (t1 < t2) {
        return 2;
      } else if (t2 < t1) {
        return 3;
      } else {
        return 0;
      }
    } else if (inside1 && !inside2) {
      if (t1 < t2) {
        return 2;
      } else {
        return 1;
      }
    } else if (inside1 && inside2) {
      if (t1 < t2) {
        return 0;
      } else if (t2 < t1) {
        return 1;
      } else {
        return 0;
      }
    } else {
      if (t1 < t2) {
        return 0;
      } else if (t2 < t1) {
        return 3;
      } else {
        return 0;
      }
    }
  }
}
