#include "interpreter.h"

struct
{
	uint8_t* ip;
	uint8_t accumulator;
	uint8_t stack[STACK_SIZE];
	uint8_t* stack_top;
} vm;

void resetVm()
{
	puts("Resetting vm");
	vm.accumulator = 0;
	vm.ip = NULL;
	vm.stack_top = vm.stack;
}

returnCode stack_push(byteVal_t byte)
{
	//handle overflow
	if (vm.stack_top == vm.stack + STACK_SIZE)
		return ERROR_STACK_OVERFLOW;
	*vm.stack_top = byte;		//push immediate byte to stack
	vm.stack_top++;			//increment stack pointer
	return SUCCESS;
}
returnCode stack_pop()
{
	//handle underflow
	if (vm.stack_top == vm.stack)
		return ERROR_STACK_UNDERFLOW;
	vm.stack_top--;			//decrement stack pointer
	vm.accumulator = *vm.stack_top;	//pop byte from top of stack
	return SUCCESS;

}
returnCode interpret(byteInstruction_t* instructions)
{
	resetVm();
	vm.ip = instructions; //point ip to start of instructions
	while (1)
	{
		byteInstruction_t instruction = *vm.ip;
		vm.ip++;
		switch (instruction)
		{
		case OP_STACK_PUSH:
			if(stack_push(*vm.ip) == ERROR_STACK_OVERFLOW)
				return ERROR_STACK_OVERFLOW;
			vm.ip++;		//increment instruction pointer
			break;

		case OP_STACK_POP:
			if (stack_pop() == ERROR_STACK_UNDERFLOW)
				return ERROR_STACK_UNDERFLOW;
			break;

		case OP_ADD:
		{
			//store accumulator's current value
			byteVal_t accVal;
			accVal = vm.accumulator;

			//pop top two bytes
			if (stack_pop() == ERROR_STACK_UNDERFLOW)
				return ERROR_STACK_UNDERFLOW;
			byteVal_t y = vm.accumulator;
			if (stack_pop() == ERROR_STACK_UNDERFLOW)
				return ERROR_STACK_UNDERFLOW;
			byteVal_t x = vm.accumulator;

			//reset accumulator
			vm.accumulator = accVal;

			//push result
			if (stack_push(x + y) == ERROR_STACK_OVERFLOW)
				return ERROR_STACK_OVERFLOW;
			break;
		}
		case OP_SUB:
		{
			//store accumulator's current value
			byteVal_t accVal;
			accVal = vm.accumulator;

			//pop top two bytes
			if (stack_pop() == ERROR_STACK_UNDERFLOW)
				return ERROR_STACK_UNDERFLOW;
			byteVal_t y = vm.accumulator;
			if (stack_pop() == ERROR_STACK_UNDERFLOW)
				return ERROR_STACK_UNDERFLOW;
			byteVal_t x = vm.accumulator;

			//reset accumulator
			vm.accumulator = accVal;

			//push result
			if (stack_push(x - y) == ERROR_STACK_OVERFLOW)
				return ERROR_STACK_OVERFLOW;
			break;
		}
		case OP_MUL:
		{
			//store accumulator's current value
			byteVal_t accVal;
			accVal = vm.accumulator;

			//pop top two bytes
			if (stack_pop() == ERROR_STACK_UNDERFLOW)
				return ERROR_STACK_UNDERFLOW;
			byteVal_t y = vm.accumulator;
			if (stack_pop() == ERROR_STACK_UNDERFLOW)
				return ERROR_STACK_UNDERFLOW;
			byteVal_t x = vm.accumulator;

			//reset accumulator
			vm.accumulator = accVal;

			//push result
			if (stack_push(x * y) == ERROR_STACK_OVERFLOW)
				return ERROR_STACK_OVERFLOW;
			break;
		}
		case OP_DIV:
		{
			//store accumulator's current value
			byteVal_t accVal;
			accVal = vm.accumulator;

			//pop top two bytes
			if (stack_pop() == ERROR_STACK_UNDERFLOW)
				return ERROR_STACK_UNDERFLOW;
			byteVal_t y = vm.accumulator;
			if (stack_pop() == ERROR_STACK_UNDERFLOW)
				return ERROR_STACK_UNDERFLOW;
			byteVal_t x = vm.accumulator;

			//handle zero division
			if (y == 0)
				return ERROR_ZERO_DIV;

			//reset accumulator
			vm.accumulator = accVal;

			//push result
			if (stack_push(x / y) == ERROR_STACK_OVERFLOW)
				return ERROR_STACK_OVERFLOW;
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
