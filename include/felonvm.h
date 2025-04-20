//
// Created by z1w2 on 19.04.2025.
//

#ifndef FELONVM_H
#define FELONVM_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef enum {
    OP_HALT = 0x00,
    OP_LOAD_CONST,  // LOAD_CONST reg, value
    OP_ADD,         // ADD reg_dest, reg_src = a + b
    OP_SUB,         // SUB reg_dest, reg_src = a - b
    OP_MULV,        // SUB reg_dest, reg_src = a * b
    OP_DEVD,        // SUB reg_dest, reg_src = a / b
    OP_DUMP,        // DUMP reg
    OP_PRINT,       // PRINT reg
    OP_ALLOC,       // ALLOCATE memory
} Opcode;

typedef enum {
    REG_R0,
    REG_R1,
    REG_R2,
    REG_R3,
} RegistersName;

#define MEMORY_SIZE 1024
#define NUM_REGS 4

typedef struct {
    int *data;
    size_t length;
    int address;
} MemoryClaster;

typedef struct {
    MemoryClaster clasters[MEMORY_SIZE];
} MemoryBehaiver;

typedef struct {
    uint8_t regs[NUM_REGS];
    const uint8_t *program;
    size_t program_size;
    size_t ip; // instruction pointer
    bool running;
    uint8_t memory_index;
    MemoryBehaiver memory;
} FelonVM;

void vm_init(FelonVM *vm, const uint8_t *program, size_t program_size);
bool check_is_register(FelonVM *vm, uint8_t reg_dest, uint8_t reg_src);
uint8_t fetch_byte(FelonVM *vm);
void init_memory(FelonVM* vm);
void free_memory(FelonVM* vm);
void run(FelonVM *vm);

#endif //FELONVM_H
