# Virtual-Bytecode-Interpreter
This is an extremely basic virtual machine that interprets and executes bytecode instructions.

## Repo Overview
### interpreter.h
Contains definitions for typedefs, enumerations and functions used by the interpreter
### interpreter.c
Contains VM instantiation and function definitions
### main.c
Defines a sample bytecode program and executes it using the interpreter

## Interpreter Details

### Virtual Machine
The VM consists of:
* One 256-byte stack
* One accumulator register
* One instruction pointer

### Instruction Set
Instructions accepted by the machine are:
* **OP_STACK_PUSH**    Push immediate byte to stack (returns stack overflow error if occurs)
* **OP_STACK_POP**     Pop byte from stack into accumulator (returns stack underflow error if occurs)
* **OP_ADD**           Pop top two bytes from stack, add them together and push the result back onto the stack
* **OP_SUB**           Pop top two bytes from stack, subtract the first from the second, and push the result back onto the stack
* **OP_MUL**           Pop top two bytes from stack and push their product back onto the stack
* **OP_DIV**           Pop top two bytes from stack, divide the first from the second, and push the result back onto the stack (returns division by zero error if occurs)
* **OP_PRINT_RES**     Prints the integer value stored in accumulator register
* **OP_COMPLETE**      Stops interpreter and exits successfully

### Exit Codes
Exit codes the machine can return are:
* **0: *SUCCESS***               Code successfully interpreted and executed
* **1: *ERROR_INVALID_OPCODE***  Instruction not recognized
* **2: *ERROR_STACK_OVERFLOW***  Attempted to push a byte to an already full stack
* **3: *ERROR_STACK_UNDERFLOW*** Attempted to pop a byte from an empty stack
* **4: *ERROR_ZERO_DIV***        Attempted to divide by zero
