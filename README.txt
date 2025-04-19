felonvm - vm in pure C code

features:
 - simple code
 - fast execution
 - light api

syntax:
  operation-to-from
example:
  move      R0 10

registers (current num = 4):
  R + 0-3
  (R0, R1, ..., R3)

example code:
  const uint8_t program[] = {
          OP_LOAD_CONST, REG_R0, 10,
          OP_LOAD_CONST, REG_R1, 20,
          OP_ADD,        REG_R0, REG_R1,
          OP_DUMP,       REG_R0,
          OP_PRINT,      REG_R0,
          OP_HALT
  };