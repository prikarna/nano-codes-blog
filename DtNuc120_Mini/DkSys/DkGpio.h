#ifndef DK_GPIO_H
#define DK_GPIO_H

#include "DkSys.h"

#define GPIO_PORT_A			0
#define GPIO_PORT_B			1
#define GPIO_PORT_C			2
#define GPIO_PORT_D			3
#define GPIO_PORT_E			4

#define GPIO_PIN_0			0
#define GPIO_PIN_1			1
#define GPIO_PIN_2			2
#define GPIO_PIN_3			3
#define GPIO_PIN_4			4
#define GPIO_PIN_5			5
#define GPIO_PIN_6			6
#define GPIO_PIN_7			7
#define GPIO_PIN_8			8
#define GPIO_PIN_9			9
#define GPIO_PIN_10			10
#define GPIO_PIN_11			11
#define GPIO_PIN_12			12
#define GPIO_PIN_13			13
#define GPIO_PIN_14			14
#define GPIO_PIN_15			15

#define GP_BA			0x50004000

#define GPIOA_PMD		(GP_BA + 0x000)
#define GPIOA_OFFD		(GP_BA + 0x004)
#define GPIOA_DOUT		(GP_BA + 0x008)
#define GPIOA_DMASK		(GP_BA + 0x00C)
#define GPIOA_PIN		(GP_BA + 0x010)
#define GPIOA_DBEN		(GP_BA + 0x014)
#define GPIOA_IMD		(GP_BA + 0x018)
#define GPIOA_IEN		(GP_BA + 0x01C)
#define GPIOA_ISRC		(GP_BA + 0x020)

#define DBNCECON		(GP_BA + 0x180)

#define	GPIO_PORTS			3
#define GPIO_PINS_PER_PORT	16

#define GPIO_MAX_PORT			(GPIO_PORTS - 1)
#define GPIO_MAX_PIN			(GPIO_PINS_PER_PORT - 1)

#define GPIO_PORT_OFFSET		0x40

#define GPIO_MODE_INPUT				0
#define GPIO_MODE_OUTPUT			1
#define GPIO_MODE_OPEN_DRAIN		2
#define GPIO_MODE_QUASI_BIDI		3

#define GPIO_ADDR(CAddr, Port)					((CAddr + (GPIO_PORT_OFFSET * Port)))

#define GPIO_SET_MODE(Port, Pin, Mode)				\
	SET_BITS(GPIO_ADDR(GPIOA_PMD, Port), (Pin * 2), BIT_MASK_2_BITS, Mode)

#define GPIO_SET_MODE_4(Port, StartPin, Mode)		\
	SET_BITS(GPIO_ADDR(GPIOA_PMD, Port), (StartPin * 2), BIT_MASK_8_BITS, ((Mode & BIT_MASK_2_BITS) * 0x55))

#define GPIO_SET_MODE_8(Port, StartPin, Mode)		\
	SET_BITS(GPIO_ADDR(GPIOA_PMD, Port), (StartPin * 2), BIT_MASK_16_BITS, ((Mode & BIT_MASK_2_BITS) * 0x5555))

#define GPIO_SET_MODE_16(Port, StartPin, Mode)		\
	SET_BITS(GPIO_ADDR(GPIOA_PMD, Port), (StartPin * 2), BIT_MASK_32_BITS, ((Mode & BIT_MASK_2_BITS) * 0x555555))

#define GPIO_DISABLE_DIGITAL_INPUT_PATH(Port, Pin, Disable)		ENABLE_BIT(GPIO_ADDR(GPIOA_OFFD, Port), Pin, Disable)

#define GPIO_WRITE(Port, Pin, Dat)				ENABLE_BIT(GPIO_ADDR(GPIOA_DOUT, Port), Pin, Dat)
#define GPIO_WRITE_4(Port, StartPin, Dat)		SET_BITS(GPIO_ADDR(GPIOA_DOUT, Port), StartPin, BIT_MASK_4_BITS, Dat)
#define GPIO_WRITE_8(Port, StartPin, Dat)		SET_BITS(GPIO_ADDR(GPIOA_DOUT, Port), StartPin, BIT_MASK_8_BITS, Dat)
#define GPIO_WRITE_16(Port, StartPin, Dat)		SET_BITS(GPIO_ADDR(GPIOA_DOUT, Port), StartPin, BIT_MASK_16_BITS, Dat)

#define GPIO_READ(Port, Pin)					GET_BIT(GPIO_ADDR(GPIOA_PIN, Port), Pin)
#define GPIO_READ_4(Port, StartPin)				GET_BITS(GPIO_ADDR(GPIOA_PIN, Port), StartPin, BIT_MASK_4_BITS)
#define GPIO_READ_8(Port, StartPin)				GET_BITS(GPIO_ADDR(GPIOA_PIN, Port), StartPin, BIT_MASK_8_BITS)
#define GPIO_READ_16(Port, StartPin)			GET_BITS(GPIO_ADDR(GPIOA_PIN, Port), StartPin, BIT_MASK_16_BITS)

#define GPIO_INTR_MODE_EDGE_TRIG				0
#define GPIO_INTR_MODE_LEVEL_TRIG				1

#define GPIO_SET_INTR_MODE(Port, Pin, IntMode)			ENABLE_BIT(GPIO_ADDR(GPIOA_IMD, Port), Pin, IntMode)
#define GPIO_SET_INTR_MODE_4(Port, StartPin, IntMode)	\
	SET_BITS(GPIO_ADDR(GPIOA_IMD, Port), StartPin, BIT_MASK_4_BITS, (IntMode * BIT_MASK_4_BITS))

#define GPIO_SET_INTR_MODE_8(Port, StartPin, IntMode)	\
	SET_BITS(GPIO_ADDR(GPIOA_IMD, Port), StartPin, BIT_MASK_8_BITS, (IntMode * BIT_MASK_8_BITS))

#define GPIO_SET_INTR_MODE_16(Port, StartPin, IntMode)	\
	SET_BITS(GPIO_ADDR(GPIOA_IMD, Port), StartPin, BIT_MASK_16_BITS, (IntMode * BIT_MASK_16_BITS))

#define GPIO_INTR_TYPE_LOW						0
#define GPIO_INTR_TYPE_HIGH						1

#define GPIO_SET_INTR_TYPE(Port, Pin, IntType)			\
	(IntType) ?											\
	(SET_BIT(GPIO_ADDR(GPIOA_IEN, Port), Pin)) :		\
	(SET_BIT(GPIO_ADDR(GPIOA_IEN, Port), (Pin + 16)))

#define GPIO_SET_INTR_TYPE_4(Port, StartPin, IntType)											\
	(IntType) ?																					\
	(SET_BITS(GPIO_ADDR(GPIOA_IEN, Port), StartPin, BIT_MASK_4_BITS, BIT_MASK_4_BITS)) :		\
	(SET_BITS(GPIO_ADDR(GPIOA_IEN, Port), (StartPin + 16), BIT_MASK_4_BITS, BIT_MASK_4_BITS))

#define GPIO_SET_INTR_TYPE_8(Port, StartPin, IntType)											\
	(IntType) ?																					\
	(SET_BITS(GPIO_ADDR(GPIOA_IEN, Port), StartPin, BIT_MASK_8_BITS, BIT_MASK_8_BITS)) :		\
	(SET_BITS(GPIO_ADDR(GPIOA_IEN, Port), (StartPin + 16), BIT_MASK_8_BITS, BIT_MASK_8_BITS))

#define GPIO_RESET_INTR_TYPE(Port, Pin, IntType)			\
	(IntType) ?												\
	(CLR_BIT(GPIO_ADDR(GPIOA_IEN, Port), Pin)) :			\
	(CLR_BIT(GPIO_ADDR(GPIOA_IEN, Port), (Pin + 16)))

#define GPIO_RESET_INTR_TYPE_4(Port, StartPin, IntType)								\
	(IntType) ?																		\
	(SET_BITS(GPIO_ADDR(GPIOA_IEN, Port), StartPin, BIT_MASK_4_BITS, 0x0)) :		\
	(SET_BITS(GPIO_ADDR(GPIOA_IEN, Port), (StartPin + 16), BIT_MASK_4_BITS, 0x0))

#define GPIO_RESET_INTR_TYPE_8(Port, StartPin, IntType)								\
	(IntType) ?																		\
	(SET_BITS(GPIO_ADDR(GPIOA_IEN, Port), StartPin, BIT_MASK_8_BITS, 0x0)) :		\
	(SET_BITS(GPIO_ADDR(GPIOA_IEN, Port), (StartPin + 16), BIT_MASK_8_BITS, 0x0))

#define GPIO_ENA_INTR(Port, Pin, IntMode, IntType, Ena)					\
	if (Ena) {															\
	GPIO_SET_INTR_MODE(Port, Pin, IntMode);								\
	GPIO_SET_INTR_TYPE(Port, Pin, IntType);								\
	} else {															\
	GPIO_RESET_INTR_TYPE(Port, Pin, IntType);							\
	}

#define GPIO_ENA_INTR_4(Port, StartPin, IntMode, IntType, Ena)			\
	if (Ena) {															\
	GPIO_SET_INTR_MODE_4(Port, StartPin, IntMode);						\
	GPIO_SET_INTR_TYPE_4(Port, StartPin, IntType);						\
	} else {															\
	GPIO_RESET_INTR_TYPE_4(Port, StartPin, IntType);					\
	}

#define GPIO_GET_INTR(Port, Pin)				GET_BIT(GPIO_ADDR(GPIOA_ISRC, Port), Pin)
#define GPIO_GET_INTR_4(Port, StartPin)			GET_BITS(GPIO_ADDR(GPIOA_ISRC, Port), StartPin, BIT_MASK_4_BITS)
#define GPIO_GET_INTR_8(Port, StartPin)			GET_BITS(GPIO_ADDR(GPIOA_ISRC, Port), StartPin, BIT_MASK_8_BITS)

#define GPIO_CLR_INTR(Port, Pin)				SET_BIT(GPIO_ADDR(GPIOA_ISRC, Port), Pin)
#define GPIO_CLR_INTR_4(Port, StartPin)			SET_BITS(GPIO_ADDR(GPIOA_ISRC, Port), StartPin, BIT_MASK_4_BITS, BIT_MASK_4_BITS)
#define GPIO_CLR_INTR_8(Port, StartPin)			SET_BITS(GPIO_ADDR(GPIOA_ISRC, Port), StartPin, BIT_MASK_8_BITS, BIT_MASK_8_BITS)

#define GPIO_ENABLE_DEBOUNCE(Port, Pin, Enable)				ENABLE_BIT(GPIO_ADDR(GPIOA_DBEN, Port), Pin, Enable)

#define GPIO_ENABLE_DEBOUNCE_4(Port, StartPin, Enable)							\
	(Enable) ?																	\
	(SET_BITS(GPIO_ADDR(GPIOA_DBEN, Port), StartPin, BIT_MASK_4_BITS, 0xF)) :	\
	(SET_BITS(GPIO_ADDR(GPIOA_DBEN, Port), StartPin, BIT_MASK_4_BITS, 0x0))

#define GPIO_SAMPLE_ONCE_PER_1_CLOCK					0
#define GPIO_SAMPLE_ONCE_PER_2_CLOCKS					1
#define GPIO_SAMPLE_ONCE_PER_4_CLOCKS					2
#define GPIO_SAMPLE_ONCE_PER_8_CLOCKS					3
#define GPIO_SAMPLE_ONCE_PER_16_CLOCKS					4
#define GPIO_SAMPLE_ONCE_PER_32_CLOCKS					5
#define GPIO_SAMPLE_ONCE_PER_64_CLOCKS					6
#define GPIO_SAMPLE_ONCE_PER_128_CLOCKS					7
#define GPIO_SAMPLE_ONCE_PER_256_CLOCKS					8
#define GPIO_SAMPLE_ONCE_PER_2X256_CLOCKS				9
#define GPIO_SAMPLE_ONCE_PER_4X256_CLOCKS				10
#define GPIO_SAMPLE_ONCE_PER_8X256_CLOCKS				11
#define GPIO_SAMPLE_ONCE_PER_16X256_CLOCKS				12
#define GPIO_SAMPLE_ONCE_PER_32X256_CLOCKS				13
#define GPIO_SAMPLE_ONCE_PER_64X256_CLOCKS				14
#define GPIO_SAMPLE_ONCE_PER_128X256_CLOCKS				15

#define GPIO_DEBOUNCE_CLK_SRC_10_KHZ					1
#define GPIO_DEBOUNCE_CLK_SRC_HCLK						0

#define GPIO_DEBOUNCE_MOD_ALLWAYS_ACTICE				1
#define GPIO_DEBOUNCE_MOD_ONLY_ON_INTR					0

#define GPIO_SET_DEBOUNCE_CYCLE(SampleClk, DbncClkSource, DbncMode)	\
	IO_MMAP(DBNCECON) =	((SampleClk & 0xF) | ((DbncClkSource & 0x1) << 4) | ((DbncMode & 0x1) << 5))

#endif  // End of DK_GPIO_H
