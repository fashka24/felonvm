#include <stdio.h>
#include "include/felonvm.h"

int main(void) {
    const uint8_t program[] = {
        OP_LOAD_CONST, REG_R0, 10,
        OP_LOAD_CONST, REG_R1, 20,
        OP_ADD,        REG_R0, REG_R1,
        OP_DUMP,       REG_R0,
        OP_PRINT,      REG_R0,
        OP_HALT
    };

    FelonVM vm;
    vm_init(&vm, program, sizeof(program));

    run(&vm);

    return 0;
}