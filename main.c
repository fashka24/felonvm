#include <stdio.h>
#include "include/felonvm.h"

int main(void) {
    const uint8_t program[] = {
    //  allocate | size | address
        OP_ALLOC,    5,      2,
    //  memset    | address | length |         data
        OP_MEMSET,      2,      5,    'f', 'e', 'l', 'o', 'n',
    //  print as char  |  address
        OP_PRINTCH_MEM,      2,
        OP_HALT
    };

    FelonVM vm;
    vm_init(&vm, program, sizeof(program));

    run(&vm);

    free_memory(&vm);
    return 0;
}