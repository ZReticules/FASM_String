include "fstr.inc"

struct String
    __size  dd ?
    len     dd ?
    union
        __lpChars   dq ?
        __chars     db 8 dup(?)
    ends
ends
