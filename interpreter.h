#ifndef INTERPRETER_H
#define INTERPRETER_H
#include <stdint.h>
#include <stdio.h>
#define STACK_SIZE 256

typedef uint8_t byteVal_t, byteInstruction_t;

typedef enum
{
	OP_STACK_PUSH,
	OP_STACK_POP,
	OP_ADD,
	OP_SUB,
	OP_MUL,
	OP_DIV,
	OP_PRINT_RES,
	OP_COMPLETE
} opcode;

typedef enum
{
	SUCCESS,
	ERROR_INVALID_OPCODE,
	ERROR_STACK_OVERFLOW,
	ERROR_STACK_UNDERFLOW,
	ERROR_ZERO_DIV
} returnCode;

void resetVm();
returnCode stack_push(byteVal_t byte);
returnCode stack_pop();
returnCode interpret(byteInstruction_t* instructions);

#endif
