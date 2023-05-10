#ifndef VM_H
#define VM_H

#include <stdbool.h>

union Value {
  int i;
  float f;
  bool b;
  char *string;
  struct {
    int size;
    int capacity;
    union Value *elements;
  } array;
};

typedef enum {
  OP_PUSH,
  OP_POP,
  OP_ADD,
  OP_SUB,
  OP_MUL,
  OP_DIV,
  OP_MOD,
  OP_POW,
  OP_NEG,
  OP_NOT,
  OP_EQ,
  OP_NEQ,
  OP_LT,
  OP_LTE,
  OP_GT,
  OP_GTE,
  OP_AND,
  OP_OR,
  OP_XOR,
  OP_LSHIFT,
  OP_RSHIFT,
  OP_JMP,
  OP_JMP_IF,
  OP_JMP_IF_NOT,
  OP_CALL,
  OP_RET,
  OP_HALT
} OpCode;

typedef struct {
  OpCode op;
} Instruction;

typedef struct {
  Instruction *code;
  int code_size;
  int code_capacity;
} Chunk;

#endif