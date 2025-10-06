#include "interpreter.h"
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

	uint8_t overflowTest[1000];
	for (int i = 0; i < 1000; i+=2)
	{
		overflowTest[i] = OP_STACK_PUSH;
		overflowTest[i + 1] = 1;
	}
	printf("Program exited with code %d\n", interpret(overflowTest));
}
