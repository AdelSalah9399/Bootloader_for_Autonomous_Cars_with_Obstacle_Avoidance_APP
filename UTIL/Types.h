#ifndef TYPES_H_
#define TYPES_H_


#define BIT0_MASK						 0x00000001UL
#define BIT1_MASK						 0x00000002UL
#define BIT2_MASK					 	 0x00000004UL
#define BIT3_MASK						 0x00000008UL
#define BIT4_MASK						 0x00000010UL
#define BIT5_MASK				 		 0x00000020UL
#define BIT6_MASK				 		 0x00000040UL
#define BIT7_MASK				 		 0x00000080UL
#define BIT8_MASK				 		 0x00000100UL
#define BIT9_MASK						 0x00000200UL
#define BIT10_MASK						 0x00000400UL
#define BIT11_MASK						 0x00000800UL
#define BIT12_MASK						 0x00001000UL
#define BIT13_MASK						 0x00002000UL
#define BIT14_MASK						 0x00004000UL
#define BIT15_MASK						 0x00008000UL
#define BIT16_MASK						 0x00010000UL
#define BIT17_MASK						 0x00020000UL
#define BIT18_MASK						 0x00040000UL
#define BIT19_MASK						 0x00080000UL
#define BIT20_MASK						 0x00100000UL
#define BIT21_MASK						 0x00200000UL
#define BIT22_MASK						 0x00400000UL
#define BIT23_MASK						 0x00800000UL
#define BIT24_MASK						 0x01000000UL
#define BIT25_MASK						 0x02000000UL
#define BIT26_MASK						 0x04000000UL
#define BIT27_MASK						 0x08000000UL
#define BIT28_MASK						 0x10000000UL
#define BIT29_MASK						 0x20000000UL
#define BIT30_MASK						 0x40000000UL
#define BIT31_MASK						 0x80000000UL


typedef unsigned char           		 u8;
typedef signed   char           		 s8;
typedef unsigned short int     			 u16;
typedef signed   short int     			 s16;
typedef unsigned long  int     			 u32;
typedef signed   long  int     			 s32;
typedef unsigned long long int 			 u64;
typedef signed   long long int 			 s64;
typedef float                   		 f32;
typedef double                  		 f64;


typedef volatile unsigned char           v_u8;
typedef volatile signed   char           v_s8;
typedef volatile unsigned short int      v_u16;
typedef volatile signed   short int      v_s16;
typedef volatile unsigned long  int      v_u32;
typedef volatile signed   long  int      v_s32;
typedef volatile unsigned long long int  v_u64;
typedef volatile signed   long long int  v_s64;
typedef volatile float                   v_f32;
typedef volatile double                  v_f64;

typedef void (*PtrFun)(void);
#define NULL (void*)(0x0)


typedef enum
{
	NoError,
	Error
}
Error_t;


#endif

