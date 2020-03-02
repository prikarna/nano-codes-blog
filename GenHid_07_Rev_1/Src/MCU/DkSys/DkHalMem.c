#include "DkSys.h"

void MemCopy(uint8_ptr_t pDst, uint8_ptr_t pSrc, uint32_t uLen)
{
	uint32_t	u;
	
	if ((!pDst) || (!pSrc) || (uLen <= 0)) return;
	
	for (u = 0; u < uLen; u++) {
		*pDst++ = *pSrc++;
	}
}

void MemSet(uint8_ptr_t pMem, uint8_t uSet, uint32_t uLen)
{
	uint32_t	u;
	
	if ((!pMem) || (uLen <= 0)) return;
	
	for (u = 0; u < uLen; u++) {
		*pMem++ = uSet;
	}
}

void MemCopyToPaddedBuffer(uint32_ptr_t pDst, uint16_ptr_t pSrc, uint32_t uSrcLen)
{
	uint32_t	u, max;

	if ((!pDst) || (!pSrc) || (uSrcLen <= 0)) return;

	max = uSrcLen / 2;
	for (u = 0; u < max; u++) {
		*pDst++ = (uint32_t) *pSrc++;
	}

	u = uSrcLen - (max * 2);
	if (u > 0) {
		*pDst = (uint32_t) *pSrc;
	}
}

void MemCopyFromPaddedBuffer(uint16_ptr_t pDst, uint32_ptr_t pSrc, uint32_t uSrcLen)
{
	uint32_t	u, max;

	if ((!pDst) || (!pSrc) || (uSrcLen <= 0)) return;

	max = uSrcLen / 2;
	for (u = 0; u < max; u++) {
		*pDst++ = (uint16_t) (*pSrc++);
	}

	u = uSrcLen - (max * 2);
	if (u > 0) {
		*pDst = (uint16_t) *pSrc;
	}
}