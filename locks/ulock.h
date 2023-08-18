#include "types.h"

struct lock_t {
    uint locked; 
};

struct sem_t {
    int val;
    struct lock_t lk;
};
