
#ifndef STD_TYPES_H_
#define STD_TYPES_H_


typedef enum {

	E_OK,
	E_NOK,
	E_NOK_NULL_PTR,
	E_NOK_OUT_OF_RANGE
}ReturnType_State_t;

#define  	NULL   (void *)0
typedef	    void(*PtrToFunc_void)(void);

typedef char s8;
typedef unsigned char u8;
typedef short int s16;
typedef unsigned short int u16;
typedef  int s32;
typedef unsigned int u32;
typedef long long s64;
typedef unsigned long long u64;
typedef float f32;
typedef double f64;
typedef long double f128;



#endif
