#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int __size;
    int len;
    union{
    	char __chars[sizeof(char *)];
    	char *__lpChars;
    };
} FASM_String_t ;

typedef char fstr;

fstr * fstr_dynamic(const char format[]);
void fstr_free(fstr *);

void String_input(FASM_String_t *_this);
void String_print(FASM_String_t *_this);
char * String_getLpChars(FASM_String_t *_this);
char * String_flush(FASM_String_t *_this);
void String_alloc(FASM_String_t *_this, int len);
void String_realloc(FASM_String_t *_this, int len);
void String_free(FASM_String_t *_this);
void String_fromBytes(FASM_String_t *_this, const char *lpBytes, int bCount);
void String_addBytes(FASM_String_t *_this, const char *lpBytes, int bCount);
void String_fromByte(FASM_String_t *_this, char bVal, int bCount);
void String_addByte(FASM_String_t *_this, char bVal, int bCount);
void String_fromString(FASM_String_t *_this, FASM_String_t *src);
void String_addString(FASM_String_t *_this, FASM_String_t *src);
void String_slice(FASM_String_t *_this, FASM_String_t *src, int _start, int _end);
void String_fromNum(FASM_String_t *_this, int num, int radix, int isSigned);
void String_addNum(FASM_String_t *_this, int num, int radix, int isSigned);
void String_sprintf(FASM_String_t *_this, fstr *format, ...);


#ifdef __cplusplus
}
#endif