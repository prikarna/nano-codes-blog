#ifndef DK_USB_H
#define DK_USB_H

#include "DkSys.h"

#define USB_BASE		0x40005C00		// - 0x4000 5FFF USB device FS registers

#define USB_EP0R		0x40005C00		// (USB_BASE + 0x00)
#define USB_EP1R		0x40005C04		// (USB_BASE + 0x04)
#define USB_EP2R		0x40005C08		// (USB_BASE + 0x08)
#define USB_EP3R		0x40005C0C		// (USB_BASE + 0x0C)
#define USB_EP4R		0x40005C10		// (USB_BASE + 0x10)
#define USB_EP5R		0x40005C14		// (USB_BASE + 0x14)
#define USB_EP6R		0x40005C18		// (USB_BASE + 0x18)
#define USB_CNTR		0x40005C40		// (USB_BASE + 0x40)
#define USB_ISTR		0x40005C44		// (USB_BASE + 0x44)
#define USB_FNR			0x40005C48		// (USB_BASE + 0x48)
#define USB_DADDR		0x40005C4C		// (USB_BASE + 0x4C)
#define USB_BTABLE		0x40005C50		// (USB_BASE + 0x50)

#define USB_BUFF_ADDR	0x40006000

#define USB_EP_REG_0		0
#define USB_EP_REG_1		1
#define USB_EP_REG_2		2
#define USB_EP_REG_3		3

#define USB_CTL_EN_CORECT_TRANS_INT				BIT_HEX_15
#define USB_CTL_EN_PACK_MEM_OVR_UND_INT			BIT_HEX_14
#define USB_CTL_EN_ERROR_INT					BIT_HEX_13
#define USB_CTL_EN_WAKE_UP_INT					BIT_HEX_12
#define USB_CTL_EN_SUSPEND_INT					BIT_HEX_11
#define USB_CTL_EN_RESET_INT					BIT_HEX_10
#define USB_CTL_EN_START_OF_FRAME_INT			BIT_HEX_9
#define USB_CTL_EN_EXPECT_START_OF_FRAME_INT	BIT_HEX_8
#define USB_CTL_RESUME							BIT_HEX_4
#define USB_CTL_FORCE_SUSPEND					BIT_HEX_3
#define USB_CTL_LOW_POWER_MODE					BIT_HEX_2
#define USB_CTL_POWER_DOWN						BIT_HEX_1
#define USB_CTL_FORCE_USB_RESET					BIT_HEX_0

#define USB_SET_CTL(Set, UsbCtls)					\
	(Set) ? (IO_MMAP(USB_CNTR) |= (UsbCtls)) : (IO_MMAP(USB_CNTR) &= ~(UsbCtls))

#define USB_ENA_REQ_RESUME(Ena)						ENABLE_BIT(USB_CNTR, BIT_NO_4, Ena);

#define USB_SET_FORCE_SUSPEND(Set)					ENABLE_BIT(USB_CNTR, BIT_NO_3, Set)

#define USB_GET_CORRECT_TRANS_INT_STATUS()			(IO_MMAP(USB_ISTR) & BIT_HEX_15) ? 1 : 0

#define USB_GET_PACK_MEM_OVR_UND_INT_STATUS()		(IO_MMAP(USB_ISTR) & BIT_HEX_14) ? 1 : 0
#define USB_CLR_PACK_MEM_OVR_UND_RUN_INT()			IO_MMAP(USB_ISTR) = 0xFFFFBFFF

#define USB_GET_ERR_INT_STATUS()					(IO_MMAP(USB_ISTR) & BIT_HEX_13) ? 1 : 0
#define USB_CLR_ERR_INT()							IO_MMAP(USB_ISTR) = 0xFFFFDFFF

#define USB_GET_WAKE_UP_INT_STATUS()				(IO_MMAP(USB_ISTR) & BIT_HEX_12) ? 1 : 0
#define USB_CLR_WAKE_UP_INT()						IO_MMAP(USB_ISTR) = 0xFFFFEFFF

#define USB_GET_SUSPEND_INT_STATUS()				(IO_MMAP(USB_ISTR) & BIT_HEX_11) ? 1 : 0
#define USB_CLR_SUSPEND_INT()						IO_MMAP(USB_ISTR) = 0xFFFFF7FF

#define USB_GET_RESET_INT_STATUS()					(IO_MMAP(USB_ISTR) & BIT_HEX_10) ? 1 : 0
#define USB_CLR_RESET_INT()							IO_MMAP(USB_ISTR) = 0xFFFFFBFF

#define USB_GET_START_OF_FRAME_INT_STATUS()			(IO_MMAP(USB_ISTR) & BIT_HEX_9) ? 1 : 0
#define USB_CLR_START_OF_FRAME_INT()				IO_MMAP(USB_ISTR) = 0xFFFFFDFF

#define USB_GET_EXPECT_START_OF_FRAME_INT_STATUS()	(IO_MMAP(USB_ISTR) & BIT_HEX_8) ? 1 : 0
#define USB_CLR_EXPECT_START_OF_FRAME_INT()			IO_MMAP(USB_ISTR) = 0xFFFFFEFF

#define USB_CLR_ALL_INTS()							IO_MMAP(USB_ISTR) = 0x0000

#define USB_INT_CORRECT_TRANS					BIT_HEX_15
#define USB_INT_PACK_MEM_OVR_UND_RUN			BIT_HEX_14
#define USB_INT_ERROR							BIT_HEX_13
#define USB_INT_WAKEUP							BIT_HEX_12
#define USB_INT_SUSPEND							BIT_HEX_11
#define USB_INT_RESET							BIT_HEX_10
#define USB_INT_START_OF_FRAME					BIT_HEX_9
#define USB_INT_EXPECT_START_OF_FRAME			BIT_HEX_8

#define USB_GET_ALL_INTS()						(IO_MMAP(USB_ISTR) & 0xFF00)

#define USB_GET_TRANSACT_DIR()					GET_BIT(USB_ISTR, BIT_NO_4)

#define USB_GET_TRANSACT_EP_ID()				GET_BITS(USB_ISTR, BIT_NO_0, BIT_MASK_4_BITS)

#define USB_GET_RXDP_STATUS()					GET_BIT(USB_FNR, BIT_NO_15)

#define USB_GET_RXDM_STATUS()					GET_BIT(USB_FNR, BIT_NO_14)

#define USB_GET_LOCK_STATUS()					GET_BIT(USB_FNR, BIT_NO_13)

#define USB_GET_LOST_START_OF_FRAME()			GET_BITS(USB_FNR, BIT_NO_11, BIT_MASK_2_BITS)

#define USB_GET_FRAME_NUMB()					(IO_MMAP(USB_FNR) & 0x7FF)

#define USB_ENABLE(Ena)							\
	(Ena) ? (IO_MMAP(USB_DADDR) |= BIT_HEX_7) : (IO_MMAP(USB_DADDR) &= ~(BIT_HEX_7))

#define USB_SET_DEV_ADDR(UsbAddr)				\
	IO_MMAP(USB_DADDR) = (IO_MMAP(USB_DADDR) & ~(0x3F)) | (UsbAddr & 0x7F)

#define USB_SET_BTBL_ADDR(UsbBTblAddr)			IO_MMAP(USB_BTABLE) = UsbBTblAddr & 0xFFFF
#define USB_GET_BTBL_ADDR()						(IO_MMAP(USB_BTABLE))

#define USB_EP_TYPE_BULK						0x0
#define USB_EP_TYPE_CONTROL						0x1
#define USB_EP_TYPE_ISO							0x2
#define USB_EP_TYPE_INTERRUPT					0x3

#define USB_EP_KIND_NONE						0x0
#define USB_EP_KIND_DOUBLE_BUF					0x1
#define USB_EP_KIND_STATUS_OUT					0x1

#define USB_EP_STAT_DISABLED					0x0
#define USB_EP_STAT_STALL						0x1
#define USB_EP_STAT_NAK							0x2
#define USB_EP_STAT_VALID						0x3

#define USB_EP_REG_ADDR(EpRegNo)				(USB_EP0R + (EpRegNo * 4))

#define USB_EP_GET_REG(EpRegNo)					(IO_MMAP(USB_EP_REG_ADDR(EpRegNo)))

#define USB_EP_SET(EpRegNo, EpType, EpKind, EpAddr)					\
	IO_MMAP(USB_EP_REG_ADDR(EpRegNo)) = (BIT_HEX_15 | ((EpType & 0x3) << 9) | ((EpKind & 0x1) << 8) | BIT_HEX_7 | (EpAddr & 0xF))

#define USB_EP_GET_RX_CTR(EpRegNo)				(IO_MMAP(USB_EP_REG_ADDR(EpRegNo)) & BIT_HEX_15) ? 1 : 0
#define USB_EP_GET_RX_SYNC_DAT(EpRegNo)			(IO_MMAP(USB_EP_REG_ADDR(EpRegNo)) & BIT_HEX_14) ? 1 : 0
#define USB_EP_GET_RX_STAT(EpRegNo)				GET_2BITS(USB_EP_REG_ADDR(EpRegNo), 12)

#define USB_EP_IS_SETUP(EpRegNo)				(IO_MMAP(USB_EP_REG_ADDR(EpRegNo)) & BIT_HEX_11) ? 1 : 0

#define USB_EP_GET_TYPE(EpRegNo)				GET_BITS(USB_EP_REG_ADDR(EpRegNo), BIT_NO_9, BIT_MASK_2_BITS)

#define USB_EP_GET_KIND(EpRegNo)				(IO_MMAP(USB_EP_REG_ADDR(EpRegNo)) & BIT_HEX_8) ? 1 : 0

#define USB_EP_GET_TX_CTR(EpRegNo)				(IO_MMAP(USB_EP_REG_ADDR(EpRegNo)) & BIT_HEX_7) ? 1 : 0
#define USB_EP_GET_TX_SYNC_DAT(EpRegNo)			(IO_MMAP(USB_EP_REG_ADDR(EpRegNo)) & BIT_HEX_6) ? 1 : 0
#define USB_EP_GET_TX_STAT(EpRegNo)				GET_BITS(USB_EP_REG_ADDR(EpRegNo), BIT_NO_4, BIT_MASK_2_BITS)

#define USB_EP_GET_ADDR(EpRegNo)				GET_BITS(USB_EP_REG_ADDR(EpRegNo), BIT_NO_0, BIT_MASK_4_BITS)

#define USB_EP_SET_TX_BUF_ADDR(EpRegNo, BTbl, Addr)			\
	IO_MMAP((USB_BUFF_ADDR + BTbl + (EpRegNo * 16))) = (Addr & BIT_MASK_16_BITS)

#define USB_EP_GET_TX_BUF_ADDR(EpRegNo, BTbl)				\
	(USB_BUFF_ADDR + ((IO_MMAP((USB_BUFF_ADDR + BTbl + (EpRegNo * 16)))) * 2))

#define USB_EP_SET_TX_BUF_LEN(EpRegNo, BTbl, Len)			\
	IO_MMAP((USB_BUFF_ADDR + BTbl + (EpRegNo * 16) + 4)) = (Len & BIT_MASK_10_BITS)

#define USB_EP_SET_RX_BUF_ADDR(EpRegNo, BTbl, Addr)			\
	IO_MMAP((USB_BUFF_ADDR + BTbl + (EpRegNo * 16) + 8)) = (Addr & BIT_MASK_16_BITS)

#define USB_EP_GET_RX_BUF_ADDR(EpRegNo, BTbl)				\
	(USB_BUFF_ADDR + ((IO_MMAP((USB_BUFF_ADDR + BTbl + (EpRegNo * 16) + 8))) * 2))

#define USB_EP_SET_RX_BUF_LEN(EpRegNo, BTbl, BlockSz, NumbOfBlock)				\
	IO_MMAP((USB_BUFF_ADDR + BTbl + (EpRegNo * 16) + 12)) =						\
	(IO_MMAP((USB_BUFF_ADDR + BTbl + (EpRegNo * 16) + 12)) & ~(0x3F << 10)) |	\
	((((BlockSz & 0x1) << 5) | (NumbOfBlock & 0x1F)) << 10)

#define USB_EP_GET_RX_DAT_COUNT(EpRegNo, BTbl)									\
	((IO_MMAP((USB_BUFF_ADDR + BTbl + (EpRegNo * 16) + 12))) & 0x3FF)

/*
	USB_EP_CTL_CTRL_TRANS_INIT
		- Keep CTR_RX
		- Keep DTOG_RX
		- Toggle STAT_RX, DISABLE -> STALL
		- Set EP_TYPE to control transfer
		- Set EP_KIND to none
		- Keep CTR_TX
		- Keep DTOG_TX
		- Toggle STAT_TX, DISABLE -> STALL
		- Set EA to endpoint 0
*/
#define USB_EP_CTL_CTRL_TRANS_INIT					(BIT_HEX_15 | BIT_HEX_12 | (USB_EP_TYPE_CONTROL << 9) | BIT_HEX_7 | BIT_HEX_4)

/*
	USB_EP_CTL_CTRL_TRANS_IN
		- Clear CTR_RX
		- Keep DTOG_RX
		- Keep STAT_RX, NACK
		- Set EP_TYPE to control transfer
		- Set EP_KIND to none
		- Keep CTR_TX
		- Keep DTOG_TX
		- Toggle STAT_TX, NACK -> VALID
		- Set EA to endpoint 0
*/
#define USB_EP_CTL_CTRL_TRANS_SETUP_IN					((USB_EP_TYPE_CONTROL << 9) | BIT_HEX_7 | BIT_HEX_4)

/*
	USB_EP_CTL_CTRL_TRANS_IN_STALL
		- Clear CTR_RX
		- Keep DTOG_RX
		- Keep STAT_RX, NACK
		- Set EP_TYPE tp control transfer
		- Set EP_KIND to none
		- Keep CTR_TX
		- Keep DTOG_TX
		- Toggle STAT_TX, NACK -> STALL
		- Set EA to endpoint 0
*/
#define USB_EP_CTL_CTRL_TRANS_SETUP_IN_STALL			((USB_EP_TYPE_CONTROL << 9) | BIT_HEX_7 | (0x3 << 4))

/*
	USB_EP_CTL_CTRL_TRANS_OUT_STALL
		- Clear CTR_RX
		- Keep DTOG_RX
		- Toggle STAT_RX, NACK -> STALL
		- Set EP_TYPE tp control transfer
		- Set EP_KIND to none
		- Keep CTR_TX
		- Keep DTOG_TX
		- Keep STAT_TX, NACK
		- Set EA to endpoint 0
*/
#define USB_EP_CTL_CTRL_TRANS_SETUP_OUT_STALL			((0x3 << 12) | (USB_EP_TYPE_CONTROL << 9) | BIT_HEX_7)

/*
	USB_EP_CTL_CTRL_TRANS_OUT
		- Clear CTR_RX
		- Keep DTOG_RX
		- Toggle STAT_RX, NACK
		- Set EP_TYPE to control transfer
		- Set EP_KIND to none
		- Keep CTR_TX
		- Keep DTOG_TX
		- Keep STAT_TX, NACK
		- Set EA to endpoint 0
*/
#define USB_EP_CTL_CTRL_TRANS_SETUP_OUT					(BIT_HEX_12 | (USB_EP_TYPE_CONTROL << 9) | BIT_HEX_7)

/*
	USB_EP_CTL_CTRL_TRANS_IN_OUT
		- Keep CTR_RX
		- Keep DTOG_RX
		- Toggle STAT_RX, NACK -> VALID
		- Set EP_TYPE to control transfer
		- Set EP_KIND to none
		- Clear CTR_TX
		- Keep DTOG_TX
		- Keep STAT_TX
		- Set EA to endpoint 0
*/
#define USB_EP_CTL_CTRL_TRANS_IN_OUT				(BIT_HEX_15 | BIT_HEX_12 | (USB_EP_TYPE_CONTROL << 9) | (USB_EP_KIND_STATUS_OUT << 8))

/*
	USB_EP_CTL_CTRL_TRANS_OUT_IN
		- Clear CTR_RX
		- Keep DTOG_RX
		- Keep STAT_RX, NACK
		- Set EP_TYPE to control transfer
		- Set EP_KIND to none
		- Keep CTR_TX
		- Keep DTOG_TX
		- Toggle STAT_TX, NACK -> VALID
		- Set EA to endpoint 0
*/
#define USB_EP_CTL_CTRL_TRANS_OUT_IN				((USB_EP_TYPE_CONTROL << 9) | BIT_HEX_7 | BIT_HEX_4)

/*
	USB_EP_CTL_CTRL_TRANS_OUT_END
		- Clear CTR_RX
		- Keep DTOG_RX
		- Keep STAT_RX
		- Set EP_TYPE to control transfer
		- Set EP_KIND to none
		- Keep CTR_TX
		- Keep DTOG_TX
		- Keep STAT_TX
		- Set EA to endpoint 0
*/
#define USB_EP_CTL_CTRL_TRANS_OUT_END				((USB_EP_TYPE_CONTROL << 9) | BIT_HEX_7)

/*
	USB_EP_CTL_CTRL_TRANS_IN_END
		- Keep CTR_RX
		- Keep DTOG_RX
		- Keep STAT_RX, NACK
		- Set EP_TYPE to control transfer
		- Set EP_KIND to none
		- Clear CTR_TX
		- Keep DTOG_TX
		- Toggle STAT_TX, NACK -> VALID
		- Set EA to endpoint 0
*/
#define USB_EP_CTL_CTRL_TRANS_IN_END				(BIT_HEX_15 | (USB_EP_TYPE_CONTROL << 9) | BIT_HEX_4)

#define USB_EP_CTL(EpRegNo, EpCtlCode)				IO_MMAP(USB_EP_REG_ADDR(EpRegNo)) = EpCtlCode

/*
	USB_EP_CTL_EX_INT_TRANS_TX_INIT
		- Keep CTR_RX
		- Keep DTOG_RX
		- Keep STAT_RX
		- Set EP_TYPE to interrupt transfer
		- Set EP_KIND to none
		- Keep CTR_TX
		- Keep DTOG_TX
		- Toggle STAT_TX, DISABLE -> VALID
*/
#define USB_EP_CTL_EX_INT_TRANS_TX_INIT			(BIT_HEX_15 | (USB_EP_TYPE_INTERRUPT << 9) | BIT_HEX_7 | (0x3 << 4))

/*
	USB_EP_CTL_EX_INT_TRANS_IN
		- Keep CTR_RX
		- Keep DTOG_RX
		- Keep STAT_RX
		- Set EP_TYPE to interrupt transfer
		- Set EP_KIND to none
		- Clear CTR_TX
		- Toggle DTOG_TX
		- Toggle STAT_TX, NACK -> VALID
*/
#define USB_EP_CTL_EX_INT_TRANS_IN				(BIT_HEX_15 | (USB_EP_TYPE_INTERRUPT << 9) | BIT_HEX_6 | BIT_HEX_4)

#define USB_EP_CTL_EX(EpRegNo, EpAddr, EpCtlExCode)			\
	IO_MMAP(USB_EP_REG_ADDR(EpRegNo)) = (EpCtlExCode | (EpAddr & 0xF))

#endif  // End of DK_USB_H
