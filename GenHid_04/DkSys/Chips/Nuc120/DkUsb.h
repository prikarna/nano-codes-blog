#ifndef DK_USB_H
#define DK_USB_H

#include "DkSys.h"

#define USB_BA				0x40060000
#define USB_INTEN			(USB_BA + 0x000)
#define USB_INTSTS			(USB_BA + 0x004)
#define USB_FADDR			(USB_BA + 0x008)
#define USB_EPSTS			(USB_BA + 0x00C)
#define USB_ATTR			(USB_BA + 0x010)
#define USB_FLDET			(USB_BA + 0x014)
#define USB_STBUFSEG		(USB_BA + 0x018)
#define USB_BUFSEG0			(USB_BA + 0x020)
#define USB_MXPLD0			(USB_BA + 0x024)
#define USB_CFG0			(USB_BA + 0x028)
#define USB_CFGP0			(USB_BA + 0x02C)
#define USB_DRVSE0			(USB_BA + 0x090)

#define USB_SRAM			(USB_BA + 0x100)
#define USB_SRAM_LEN		512

#define USB_MAX_ENDPOINT	6

#define USB_INTR_INNACK				0x00008000
#define USB_INTR_WAKEUP_FUNC		0x00000100
#define USB_INTR_WAKEUP				0x00000008
#define USB_INTR_FLDET				0x00000004
#define USB_INTR_USB				0x00000002
#define USB_INTR_BUS				0x00000001

#define USB_ENA_INTRS(Intrs, Ena)		ENABLE_BITS(USB_INTEN, Ena, Intrs)

#define USB_INTR_STATUS_BUS			0x00000001
#define USB_INTR_STATUS_USB			0x00000002
#define USB_INTR_STATUS_FLDET		0x00000004
#define USB_INTR_STATUS_WAKEUP		0x00000008
#define USB_INTR_STATUS_EPEVT0		0x00010000
#define USB_INTR_STATUS_EPEVT1		0x00020000
#define USB_INTR_STATUS_EPEVT2		0x00040000
#define USB_INTR_STATUS_EPEVT3		0x00080000
#define USB_INTR_STATUS_EPEVT4		0x00100000
#define USB_INTR_STATUS_EPEVT5		0x00200000
#define USB_INTR_STATUS_SETUP		0x80000000
#define USB_INTR_STATUS_USB_ALL		(USB_INTR_STATUS_USB | USB_INTR_STATUS_EPEVT0 |	USB_INTR_STATUS_EPEVT1 | USB_INTR_STATUS_EPEVT2 | USB_INTR_STATUS_EPEVT3 | USB_INTR_STATUS_EPEVT4 | USB_INTR_STATUS_EPEVT5 | USB_INTR_STATUS_SETUP)

#define USB_INTR_GET_STATUS()			IO_MMAP(USB_INTSTS)
#define USB_CLR_INTRS(IntrsStat)		IO_MMAP(USB_INTSTS) |= IntrsStat

#define USB_SET_FUNC_ADDR(Addr)			SET_BITS(USB_FADDR, BIT_NO_0, BIT_MASK_7_BITS, Addr)

#define USB_EP_IS_OVERRUN()				GET_BIT(USB_EPSTS, BIT_NO_7)

#define USB_EP_STATUS_ISOCH_TRAN_END		7
#define USB_EP_STATUS_SETUP_ACK				3
#define USB_EP_STATUS_OUT_PACK_DAT1_ACK		6
#define USB_EP_STATUS_OUT_PACK_DAT0_ACK		2
#define USB_EP_STATUS_IN_NACK				1
#define USB_EP_STATUS_IN_ACK				0

#define USB_EP_GET_STATUS(EpRegNo)			GET_BITS(USB_EPSTS, (8 + (EpRegNo * 3)), BIT_MASK_3_BITS)
#define USB_EP_GET_ALL_STATUS()				(IO_MMAP(USB_EPSTS))

#define USB_ATTR_BYTE_MODE					0x00000400
#define USB_ATTR_PWR_DOWN					0x00000200
#define USB_ATTR_PULL_UP_USB_DP				0x00000100
#define USB_ATTR_CTRL_ENABLE				0x00000080
#define USB_ATTR_REMOTE_WAKE_UP				0x00000020
#define USB_ATTR_PHY_ENABLE					0x00000010

#define USB_SET_ATTRS(Attr, Set)			ENABLE_BITS(USB_ATTR, Set, Attr)

#define USB_BUS_STATUS_TIMEOUT				0x00000008
#define USB_BUS_STATUS_RESUME				0x00000004
#define USB_BUS_STATUS_SUSPEND				0x00000002
#define USB_BUS_STATUS_RESET				0x00000001

#define USB_BUS_GET_STATUS()				GET_BITS(USB_ATTR, BIT_NO_0, BIT_MASK_4_BITS)

#define USB_FLOAT_DETECT()					GET_BIT(USB_FLDET, BIT_NO_0)

#define USB_SET_BUF_SEG(Segment)			SET_BITS(USB_STBUFSEG, BIT_NO_0, BIT_MASK_9_BITS, Segment)

#define USB_GET_BUF_ADDR()					(USB_SRAM + IO_MMAP(USB_STBUFSEG))

#define USB_EP_REG0								0
#define USB_EP_REG1								1
#define USB_EP_REG2								2
#define USB_EP_REG3								3
#define USB_EP_REG4								4
#define USB_EP_REG5								5

#define USB_EP_OFFSET								0x10
#define USB_EP_ADDR(CAddr, EpRegNo)					(CAddr + (USB_EP_OFFSET * EpRegNo))

#define USB_EP_SET_BUFF_SEG(EpRegNo, Segment)		SET_BITS(USB_EP_ADDR(USB_BUFSEG0, EpRegNo), BIT_NO_0, BIT_MASK_9_BITS, Segment)

#define USB_EP_GET_BUFF_SEG(EpRegNo)				GET_BITS(USB_EP_ADDR(USB_BUFSEG0, EpRegNo), BIT_NO_0, BIT_MASK_9_BITS)

#define USB_EP_GET_BUF_ADDR(EpRegNo)				(USB_SRAM + USB_EP_GET_BUFF_SEG(EpRegNo))

#define USB_EP_SET_MAX_PAYLOAD(EpRegNo, PayLoad)	SET_BITS(USB_EP_ADDR(USB_MXPLD0, EpRegNo), BIT_NO_0, BIT_MASK_9_BITS, PayLoad)

#define USB_EP_GET_MAX_PAYLOAD(EpRegNo)				GET_BITS(USB_EP_ADDR(USB_MXPLD0, EpRegNo), BIT_NO_0, BIT_MASK_9_BITS)

#define USB_EP_STATE_DISABLE					0
#define USB_EP_STATE_OUT						1
#define USB_EP_STATE_IN							2
#define USB_EP_STATE_UNDEF						3

#define USB_EP_CLR_STALL(EpRegNo)					SET_BIT(USB_EP_ADDR(USB_CFG0, EpRegNo), BIT_NO_9)

#define USB_EP_GET_DSQ_SYNC(EpRegNo)				GET_BIT(USB_EP_ADDR(USB_CFG0, EpRegNo), BIT_NO_7)

#define USB_EP_SET_DSQ_SYNC(EpRegNo, Set)			ENABLE_BIT(USB_EP_ADDR(USB_CFG0, EpRegNo), BIT_NO_7, Set)

#define USB_EP_TOGGLE_DSQ_SYNC(EpRegNo)										\
	(USB_EP_GET_DSQ_SYNC(EpRegNo)) ?										\
	(USB_EP_SET_DSQ_SYNC(EpRegNo, 0)) : (USB_EP_SET_DSQ_SYNC(EpRegNo, 1))

#define USB_EP_SET_STATE(EpRegNo, State)			SET_BITS(USB_EP_ADDR(USB_CFG0, EpRegNo), BIT_NO_5, BIT_MASK_2_BITS, State)

#define USB_EP_SET_ADDR(EpRegNo, EpAddr)			SET_BITS(USB_EP_ADDR(USB_CFG0, EpRegNo), BIT_NO_0, BIT_MASK_4_BITS, EpAddr)

#define USB_EP_SET(EpRegNo, ClrStall, DsqSync, State, IsIsoch, EpAddr)		\
	IO_MMAP(USB_EP_ADDR(USB_CFG0, EpRegNo)) =								\
	((ClrStall & 0x1) << 9) |												\
	((DsqSync & 0x1) << 7) |												\
	((State & 0x3) << 5) |													\
	((IsIsoch & 0x1) << 4) |												\
	(EpAddr & 0xF)

#define USB_EP_CLR_RDY(EpRegNo)						SET_BIT(USB_EP_ADDR(USB_CFGP0, EpRegNo), BIT_NO_0)
#define USB_EP_SET_STALL(EpRegNo)					SET_BIT(USB_EP_ADDR(USB_CFGP0, EpRegNo), BIT_NO_1)
#define USB_EP_CLR_RDY_AND_SET_STALL(EpRegNo)		SET_BITS(USB_EP_ADDR(USB_CFGP0, EpRegNo), BIT_NO_0, BIT_MASK_2_BITS, 0x3)

#define USB_DRIVE_SE0(Set)							ENABLE_BIT(USB_DRVSE0, BIT_NO_0, Set)

#endif   // End of DK_USB_H
