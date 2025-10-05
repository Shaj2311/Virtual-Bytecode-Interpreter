#include <stdint.h>
#include <stdio.h>
#define STACK_SIZE 256
struct
{
	uint8_t* ip;
	uint8_t* accumulator;
	uint8_t stack[STACK_SIZE];
	uint8_t* stack_top;
} vm;

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

void resetVm()
{
	puts("Resetting vm");
	vm.accumulator = 0;
	vm.ip = NULL;
	vm.stack_top = vm.stack;
}

void stack_push(uint8_t byte)
{
	//handle overflow
	if (vm.stack_top == vm.stack + STACK_SIZE)
		return ERROR_STACK_OVERFLOW;
	*vm.stack_top = byte;		//push immediate byte to stack
	vm.stack_top++;			//increment stack pointer
}
void stack_pop()
{
	//handle underflow
	if (vm.stack_top == vm.stack)
		return ERROR_STACK_UNDERFLOW;
	vm.stack_top--;			//decrement stack pointer
	vm.accumulator = *vm.stack_top;	//pop byte from top of stack

}
void interpret(uint8_t* instructions)
{
	resetVm();
	vm.ip = instructions; //point ip to start of instructions
	while (1)
	{
		uint8_t instruction = *vm.ip;
		vm.ip++;
		switch (instruction)
		{
		case OP_STACK_PUSH:
			stack_push(*vm.ip);
			vm.ip++;		//increment instruction pointer
			break;
		
		case OP_STACK_POP:
			stack_pop();
			break;

		case OP_ADD:
		{
			//store accumulator's current value
			uint8_t accVal;
			accVal = vm.accumulator;

			//pop top two bytes
			stack_pop();
			uint8_t y = vm.accumulator;
			stack_pop();
			uint8_t x = vm.accumulator;

			//reset accumulator
			vm.accumulator = accVal;

			//push result
			stack_push(x + y);
			break;
		}
		case OP_SUB:
		{
			//store accumulator's current value
			uint8_t accVal;
			accVal = vm.accumulator;

			//pop top two bytes
			stack_pop();
			uint8_t y = vm.accumulator;
			stack_pop();
			uint8_t x = vm.accumulator;

			//reset accumulator
			vm.accumulator = accVal;

			//push result
			stack_push(x - y);
			break;
		}
		case OP_MUL:
		{
			//store accumulator's current value
			uint8_t accVal;
			accVal = vm.accumulator;

			//pop top two bytes
			stack_pop();
			uint8_t y = vm.accumulator;
			stack_pop();
			uint8_t x = vm.accumulator;

			//reset accumulator
			vm.accumulator = accVal;

			//push result
			stack_push(x * y);
			break;
		}
		case OP_DIV:
		{
			//store accumulator's current value
			uint8_t accVal;
			accVal = vm.accumulator;

			//pop top two bytes
			stack_pop();
			uint8_t y = vm.accumulator;
			stack_pop();
			uint8_t x = vm.accumulator;

			//handle zero division
			if (y == 0)
				return ERROR_ZERO_DIV;

			//reset accumulator
			vm.accumulator = accVal;

			//push result
			stack_push(x / y);
			break;
		}
		case OP_PRINT_RES:
			printf("%d\n", vm.accumulator);
			break;
		case OP_COMPLETE:
			return SUCCESS;
			break;
		default:
			return ERROR_INVALID_OPCODE;
		}
	}
	return SUCCESS;
}
int main()
{
	uint8_t bytecode[8] = {
		OP_STACK_PUSH, 1,
		OP_STACK_PUSH, 2,
		OP_ADD,
		OP_STACK_POP,
		OP_PRINT_RES,
		OP_COMPLETE
	};
	interpret(bytecode);
}