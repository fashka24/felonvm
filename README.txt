felonvm - vm in pure C code

features:
 - simple code
 - fast execution
 - light api

syntax:
  operation-dest-src
example:
  move      R0 10

registers (current num = 4):
  R + 0-3
  (R0, R1, ..., R3)

example code:
  const uint8_t program[] = {
      //  allocate | size | address
          OP_ALLOC,    5,      2,
      //  memset     | address | length |         data
          OP_MEMSET,      2,       5,    'f', 'e', 'l', 'o', 'n',
      //  print as char  |  address
          OP_PRINTCH_MEM,      2,
          OP_HALT
  };

build only with C compiler:
  gcc -Ofast main.c felonvm.c -o felonvm

build only with cmake (before it create dist folder):
  cmake --build <folder> --target felonvm -j 4

about memory:
memory consists (by default 1024 blocks) of blocks,
where they already consist of:
  int* data
  length (size) of the block
  address (identifier)