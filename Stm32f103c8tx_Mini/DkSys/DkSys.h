#ifndef DK_SYS_H
#define DK_SYS_H

typedef unsigned int			uint32_t;
typedef unsigned int *			uint32_ptr_t;
typedef unsigned short			uint16_t;
typedef unsigned short *		uint16_ptr_t;
typedef unsigned char			uint8_t;
typedef unsigned char *			uint8_ptr_t;
typedef int						int32_t;
typedef char					int8_t;
typedef char *					int8_ptr_t;

#define BIT_HEX_0				0x00000001
#define BIT_HEX_1				0x00000002
#define BIT_HEX_2				0x00000004
#define BIT_HEX_3				0x00000008
#define BIT_HEX_4				0x00000010
#define BIT_HEX_5				0x00000020
#define BIT_HEX_6				0x00000040
#define BIT_HEX_7				0x00000080
#define BIT_HEX_8				0x00000100
#define BIT_HEX_9				0x00000200
#define BIT_HEX_10				0x00000400
#define BIT_HEX_11				0x00000800
#define BIT_HEX_12				0x00001000
#define BIT_HEX_13				0x00002000
#define BIT_HEX_14				0x00004000
#define BIT_HEX_15				0x00008000
#define BIT_HEX_16				0x00010000
#define BIT_HEX_17				0x00020000
#define BIT_HEX_18				0x00040000
#define BIT_HEX_19				0x00080000
#define BIT_HEX_20				0x00100000
#define BIT_HEX_21				0x00200000
#define BIT_HEX_22				0x00400000
#define BIT_HEX_23				0x00800000
#define BIT_HEX_24				0x01000000
#define BIT_HEX_25				0x02000000
#define BIT_HEX_26				0x04000000
#define BIT_HEX_27				0x08000000
#define BIT_HEX_28				0x10000000
#define BIT_HEX_29				0x20000000
#define BIT_HEX_30				0x40000000
#define BIT_HEX_31				0x80000000

#define BIT_MASK_1_BIT			0x00000001
#define BIT_MASK_2_BITS			0x00000003
#define BIT_MASK_3_BITS			0x00000007
#define BIT_MASK_4_BITS			0x0000000F
#define BIT_MASK_5_BITS			0x0000001F
#define BIT_MASK_6_BITS			0x0000003F
#define BIT_MASK_7_BITS			0x0000007F
#define BIT_MASK_8_BITS			0x000000FF
#define BIT_MASK_9_BITS			0x000001FF
#define BIT_MASK_10_BITS		0x000003FF
#define BIT_MASK_11_BITS		0x000007FF
#define BIT_MASK_12_BITS		0x00000FFF
#define BIT_MASK_13_BITS		0x00001FFF
#define BIT_MASK_14_BITS		0x00003FFF
#define BIT_MASK_15_BITS		0x00007FFF
#define BIT_MASK_16_BITS		0x0000FFFF
#define BIT_MASK_17_BITS		0x0001FFFF
#define BIT_MASK_18_BITS		0x0003FFFF
#define BIT_MASK_19_BITS		0x0007FFFF
#define BIT_MASK_20_BITS		0x000FFFFF
#define BIT_MASK_21_BITS		0x001FFFFF
#define BIT_MASK_22_BITS		0x003FFFFF
#define BIT_MASK_23_BITS		0x007FFFFF
#define BIT_MASK_24_BITS		0x00FFFFFF
#define BIT_MASK_25_BITS		0x01FFFFFF
#define BIT_MASK_26_BITS		0x03FFFFFF
#define BIT_MASK_27_BITS		0x07FFFFFF
#define BIT_MASK_28_BITS		0x0FFFFFFF
#define BIT_MASK_29_BITS		0x1FFFFFFF
#define BIT_MASK_30_BITS		0x3FFFFFFF
#define BIT_MASK_31_BITS		0x7FFFFFFF
#define BIT_MASK_32_BITS		0xFFFFFFFF

#define BIT_NO_0				0
#define BIT_NO_1				1
#define BIT_NO_2				2
#define BIT_NO_3				3
#define BIT_NO_4				4
#define BIT_NO_5				5
#define BIT_NO_6				6
#define BIT_NO_7				7
#define BIT_NO_8				8
#define BIT_NO_9				9
#define BIT_NO_10				10
#define BIT_NO_11				11
#define BIT_NO_12				12
#define BIT_NO_13				13
#define BIT_NO_14				14
#define BIT_NO_15				15
#define BIT_NO_16				16
#define BIT_NO_17				17
#define BIT_NO_18				18
#define BIT_NO_19				19
#define BIT_NO_20				20
#define BIT_NO_21				21
#define BIT_NO_22				22
#define BIT_NO_23				23
#define BIT_NO_24				24
#define BIT_NO_25				25
#define BIT_NO_26				26
#define BIT_NO_27				27
#define BIT_NO_28				28
#define BIT_NO_29				29
#define BIT_NO_30				30
#define BIT_NO_31				31

#ifndef TRUE
# define TRUE					1
# define FALSE					0
#endif

#ifndef ENABLE
# define ENABLE					1
# define DISABLE				0
#endif

#ifndef HIGH
# define HIGH					1
# define LOW					0
#endif

#ifndef SET
# define SET					1
# define RESET					0
# define CLEAR					0
#endif

typedef void (* HandlerPtrT)(void);

#define ADDR_OF(CAddr)				(volatile uint32_ptr_t)	(CAddr)
#define IO_MMAP(CAddr)				(*((volatile uint32_ptr_t) (CAddr)))

#define SET_BIT(CAddr, NthBit)		IO_MMAP(CAddr) |= (0x1 << NthBit)
#define CLR_BIT(CAddr, NthBit)		IO_MMAP(CAddr) &= ~(0x1 << NthBit)
#define GET_BIT(CAddr, NthBit)		((IO_MMAP(CAddr) >> NthBit) & 0x1)

#define GET_BITS(CAddr, NthBit, BitMask)		((IO_MMAP(CAddr) >> NthBit) & BitMask)
#define SET_BITS(CAddr, NthBit, BitMask, Val)	IO_MMAP(CAddr) = ((IO_MMAP(CAddr) & ~(BitMask << NthBit)) | ((Val & BitMask) << NthBit))

#define ENABLE_BIT(CAddr, NthBit, Enable)		(Enable) ? (SET_BIT(CAddr, NthBit)) : (CLR_BIT(CAddr, NthBit))
#define ENABLE_BITS(CAddr, Enable, Values)		(Enable) ? (IO_MMAP(CAddr) |= Values) : (IO_MMAP(CAddr) &= ~(Values))

#define DBG_BREAK()								__asm("bkpt 0x0")

#endif   // End of DK_SYS_H
