//
// Created by julia on 1/10/2023.
//

#include "Counter.h"

Counter::Counter() { count = 0; }
int Counter::incr() { count++; return count; }
int Counter::decr() { count--; return count; }
int Counter::get() { return count; }