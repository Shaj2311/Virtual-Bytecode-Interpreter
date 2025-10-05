#include "interpreter.c"
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
	printf("Program exited with code %d\n", interpret(bytecode));
}
