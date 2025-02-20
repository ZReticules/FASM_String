include "fstr.inc"

struct String
    __size  dd ?
    len     dd ?
    union
        __lpChars   dd ?
        __chars     db 4 dup(?)
    ends
ends
