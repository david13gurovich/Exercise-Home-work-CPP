#ifndef ILRD_RD61_COMMON_TYPES_HPP
#define ILRD_RD61_COMMON_TYPES_HPP

enum Condition {READ, WRITE, EXCEPTION, NUM_ELEMENTS}; 
typedef void (*Func)(int fd); 

#endif