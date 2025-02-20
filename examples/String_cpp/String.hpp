#include "String.h"

class FASM_Fstr{
private:
	fstr *format;
public:
	inline FASM_Fstr(const char fmt[]){
		this->format = fstr_dynamic(fmt);
	};
	inline fstr * getLpFstr(){
		return this->format;
	};
	inline ~FASM_Fstr(){
		fstr_free(this->format);
	};
};

class FASM_String {
private:
    FASM_String_t fasmstr;
public:
    inline FASM_String(){
		this->fasmstr.__size = sizeof(char *) - 1;
		this->fasmstr.len = 0;
	};
	inline FASM_String(const char * lpCstr, int size=-1){
		this->fasmstr.__size = sizeof(char *) - 1;
		this->fasmstr.len = 0;
		String_fromBytes(&this->fasmstr, lpCstr, size);
	};
	inline void from(const char * lpCstr, int len=-1){
		String_fromBytes(&this->fasmstr, lpCstr, len);
	};
	inline FASM_String& operator = (const char lpCstr[]){
		String_fromBytes(&this->fasmstr, lpCstr, -1);
		return *this;
	};
	inline void add(const char * lpCstr, int len=-1){
		String_addBytes(&this->fasmstr, lpCstr, len);
	};
	inline FASM_String operator + (const char lpCstr[]){
		return FASM_String(*this) += lpCstr;
	};
	inline FASM_String& operator += (const char lpCstr[]){
		String_addBytes(&this->fasmstr, lpCstr, -1);
		return *this;
	};
	inline FASM_String(int num){
		this->fasmstr.__size = sizeof(char *) - 1;
		this->fasmstr.len = 0;
		String_fromNum(&this->fasmstr, num, 10, 0);
	};
	inline FASM_String(unsigned int num){
		this->fasmstr.__size = sizeof(char *) - 1;
		this->fasmstr.len = 0;
		String_fromNum(&this->fasmstr, num, 10, 0);
	};
	inline void from(int num, int radix, bool isSigned=true){
		String_fromNum(&this->fasmstr, num, radix, isSigned);
	};
	inline void from(unsigned int num, int radix, bool isSigned=true){
		String_fromNum(&this->fasmstr, num, radix, isSigned);
	};
	inline FASM_String& operator = (int num){
		String_fromNum(&this->fasmstr, num, 10, 1);
		return *this;
	};
	inline FASM_String& operator = (unsigned int num){
		String_fromNum(&this->fasmstr, num, 10, 0);
		return *this;
	};
	inline void add(int num, int radix, bool isSigned=true){
		String_addNum(&this->fasmstr, num, radix, isSigned);
	};
	inline FASM_String& operator += (int num){
		String_addNum(&this->fasmstr, num, 10, 1);
		return *this;
	};
	inline FASM_String& operator += (unsigned int num){
		String_addNum(&this->fasmstr, num, 10, 0);
		return *this;
	};
	inline FASM_String operator + (int num){
		return FASM_String(*this) += num;
	};
	inline FASM_String operator + (unsigned int num){
		return FASM_String(*this) += num;
	};
	inline FASM_String(char bVal, int bCount=1){
		this->fasmstr.__size = sizeof(char *) - 1;
		this->fasmstr.len = 0;
		String_fromByte(&this->fasmstr, bVal, bCount);
	};
	inline void from(char bVal, int bCount=1){
		String_fromByte(&this->fasmstr, bVal, bCount);
	};
	inline FASM_String& operator = (char bVal){
		String_fromByte(&this->fasmstr, bVal, 1);
		return *this;
	};
	inline void add(char bVal, int bCount=1){
		String_addByte(&this->fasmstr, bVal, bCount);
	};
	inline FASM_String& operator += (char bVal){
		String_addByte(&this->fasmstr, bVal, 1);
		return *this;
	};
	inline FASM_String operator + (char bVal){
		return FASM_String(*this) += bVal;
	};
	inline FASM_String(FASM_String& src){
		this->fasmstr.__size = sizeof(char *) - 1;
		this->fasmstr.len = 0;
		String_fromString(&this->fasmstr, &src.fasmstr);
	};
	inline FASM_String& operator = (FASM_String src){
		// printf("lol");
		String_fromString(&this->fasmstr, &src.fasmstr);
		return *this;
	};
	inline FASM_String& operator += (FASM_String src){
		String_addString(&this->fasmstr, &src.fasmstr);
		return *this;
	};
	inline FASM_String operator + (FASM_String src){
		return FASM_String(*this) += src;
	};
	inline void alloc(int size){
		String_alloc(&this->fasmstr, size);
	};
	inline void realloc(int size){
		String_realloc(&this->fasmstr, size);
	};
	inline void slice(FASM_String& src, int start, int end){
		String_slice(&this->fasmstr, &src.fasmstr, start, end);
	}
	FASM_String operator [] (const int(& indexes)[2]){
		FASM_String result;
		result.slice(*this, indexes[0], indexes[1]); 
		return result;
	};
	inline char * getLpChars(){
		return String_getLpChars(&this->fasmstr);
	};
	inline char operator [] (int index){
		return this->getLpChars()[index];
	};
	inline void print(){
		String_print(&this->fasmstr);
	};
	inline void input(){
		String_input(&this->fasmstr);
	};
    inline void flush(){
    	String_flush(&this->fasmstr);
    };
    inline int len(){
    	return this->fasmstr.len;
    };
    template <typename... Args>
	__forceinline void sprintf(FASM_Fstr format, Args... VaArgs){
		String_sprintf(&this->fasmstr, format.getLpFstr(), VaArgs...);
	};
    template <typename... Args>
	__forceinline void sprintf(const char * format, Args... VaArgs){
		String_sprintf(&this->fasmstr, FASM_Fstr(format).getLpFstr(), VaArgs...);
	};
    template <typename... Args>
	__forceinline void sprintf(fstr * format, Args... VaArgs){
		String_sprintf(&this->fasmstr, format, VaArgs...);
	};
    inline void free(){
    	String_free(&this->fasmstr);
    };
    inline ~FASM_String(){
    	String_free(&this->fasmstr);
    };
};