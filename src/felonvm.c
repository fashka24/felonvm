//
// Created by z1w2 on 19.04.2025.
//
#include "../include/felonvm.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

void vm_init(FelonVM *vm, const uint8_t *program, size_t program_size) {
    for (int i = 0; i < NUM_REGS; i++) {
        vm->regs[i] = 0;
    }
    vm->program = program;
    vm->program_size = program_size;
    vm->ip = 0;
    vm->memory_index = 0;
    vm->running = true;
    init_memory(vm);
}

uint8_t fetch_byte(FelonVM *vm) {
    if (vm->ip >= vm->program_size) {
        fprintf(stderr, "Error: Instruction pointer out of bounds\n");
        vm->running = false;
        return 0;
    }
    return vm->program[vm->ip++];
}
bool check_is_register(FelonVM *vm, uint8_t reg_dest, uint8_t reg_src) {
    if (reg_dest >= NUM_REGS || reg_src >= NUM_REGS) {
        fprintf(stderr, "Error: Invalid register\n");
        vm->running = false;
        return false;
    }
    return true;
}

void init_memory(FelonVM *vm) {
    for (int i = 0; i < MEMORY_SIZE; ++i) {
        vm->memory.clasters[i].address = 0;
    }
}

void free_memory(FelonVM *vm) {
    free(vm->memory.clasters);
}

void run(FelonVM *vm) {
    while (vm->running) {
        uint8_t opcode = fetch_byte(vm);
        switch (opcode) {
            case OP_HALT:
                vm->running = false;
                break;
            case OP_LOAD_CONST: {
                uint8_t reg = fetch_byte(vm);
                uint8_t val = fetch_byte(vm);
                if (!check_is_register(vm, reg, 0)) break;
                vm->regs[reg] = val;
                break;
            }
            case OP_ADD: {
                uint8_t reg_dest = fetch_byte(vm);
                uint8_t reg_src = fetch_byte(vm);
                if (!check_is_register(vm, reg_dest, reg_src)) break;
                vm->regs[reg_dest] += vm->regs[reg_src];
                break;
            }
            case OP_SUB: {
                uint8_t reg_dest = fetch_byte(vm);
                uint8_t reg_src = fetch_byte(vm);
                if (!check_is_register(vm, reg_dest, reg_src)) break;
                vm->regs[reg_dest] -= vm->regs[reg_src];
                break;
            }
            case OP_MULV: {
                uint8_t reg_dest = fetch_byte(vm);
                uint8_t reg_src = fetch_byte(vm);
                if (!check_is_register(vm, reg_dest, reg_src)) break;
                vm->regs[reg_dest] *= vm->regs[reg_src];
                break;
            }
            case OP_DEVD: {
                uint8_t reg_dest = fetch_byte(vm);
                uint8_t reg_src = fetch_byte(vm);
                if (!check_is_register(vm, reg_dest, reg_src)) break;
                vm->regs[reg_dest] /= vm->regs[reg_src];
                break;
            }
            case OP_DUMP: {
                uint8_t reg = fetch_byte(vm);
                if (!check_is_register(vm, reg, 0)) break;
                printf("Reg[%u] = %u\n", reg, vm->regs[reg]);
                break;
            }
            case OP_PRINT: {
                uint8_t reg = fetch_byte(vm);
                if (!check_is_register(vm, reg, 0)) break;
                printf("%u", vm->regs[reg]);
                break;
            }
            case OP_ALLOC: {
                uint8_t to_allocate = fetch_byte(vm);
                uint8_t address = fetch_byte(vm);
                if (vm->memory_index >= MEMORY_SIZE) {
                    fprintf(stderr, "Error: memory full");
                    exit(EXIT_FAILURE);
                }
                vm->memory.clasters[vm->memory_index].data    = realloc(vm->memory.clasters[vm->memory_index].data, to_allocate);
                vm->memory.clasters[vm->memory_index].length  = to_allocate;
                vm->memory.clasters[vm->memory_index].address = address;
                // printf("Allocated memory, index: %d length: %d address: %d", vm->memory_index, to_allocate, address);
                vm->memory_index++;
                break;
            }
            default:
                fprintf(stderr, "Error: Unknown opcode 0x%02X\n", opcode);
                vm->running = false;
        }
    }
}