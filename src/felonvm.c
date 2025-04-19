//
// Created by z1w2 on 19.04.2025.
//
#include "../include/felonvm.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

 void vm_init(FelonVM *vm, const uint8_t *program, size_t program_size) {
    for (int i = 0; i < NUM_REGS; i++) {
        vm->regs[i] = 0;
    }
    vm->program = program;
    vm->program_size = program_size;
    vm->ip = 0;
    vm->running = true;
}

 uint8_t fetch_byte(FelonVM *vm) {
    if (vm->ip >= vm->program_size) {
        fprintf(stderr, "Error: Instruction pointer out of bounds\n");
        vm->running = false;
        return 0;
    }
    return vm->program[vm->ip++];
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
                if (reg >= NUM_REGS) {
                    fprintf(stderr, "Error: Invalid register %u\n", reg);
                    vm->running = false;
                    break;
                }
                vm->regs[reg] = val;
                break;
            }

            case OP_ADD: {
                uint8_t reg_dest = fetch_byte(vm);
                uint8_t reg_src = fetch_byte(vm);
                if (reg_dest >= NUM_REGS || reg_src >= NUM_REGS) {
                    fprintf(stderr, "Error: Invalid register\n");
                    vm->running = false;
                    break;
                }
                vm->regs[reg_dest] += vm->regs[reg_src];
                break;
            }

            case OP_SUB: {
                uint8_t reg_dest = fetch_byte(vm);
                uint8_t reg_src = fetch_byte(vm);
                if (reg_dest >= NUM_REGS || reg_src >= NUM_REGS) {
                    fprintf(stderr, "Error: Invalid register\n");
                    vm->running = false;
                    break;
                }
                vm->regs[reg_dest] -= vm->regs[reg_src];
                break;
            }

            case OP_DUMP: {
                uint8_t reg = fetch_byte(vm);
                if (reg >= NUM_REGS) {
                    fprintf(stderr, "Error: Invalid register %u\n", reg);
                    vm->running = false;
                    break;
                }
                printf("Reg[%u] = %u\n", reg, vm->regs[reg]);
                break;
            }
            case OP_PRINT: {
                uint8_t reg = fetch_byte(vm);
                if (reg >= NUM_REGS) {
                    fprintf(stderr, "Error: Invalid register %u\n", reg);
                    vm->running = false;
                    break;
                }
                printf("%u", vm->regs[reg]);
                break;
            }

            default:
                fprintf(stderr, "Error: Unknown opcode 0x%02X\n", opcode);
                vm->running = false;
        }
    }
}