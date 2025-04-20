#include <stdio.h>
#include "include/felonvm.h"

int main(void) {
    const uint8_t program[] = {
        OP_ALLOC, 10, 1,
        OP_HALT
    };

    FelonVM vm;
    vm_init(&vm, program, sizeof(program));

    run(&vm);

    return 0;
}