#include "DkSys.h"

void MemCopy(uint8_ptr_t pDst, uint8_ptr_t pSrc, uint32_t uLen)
{
	uint32_t	u;
	
	if ((!pDst) || (!pSrc) || (uLen <= 0)) return;
	
	for (u = 0; u < uLen; u++) {
		*pDst++ = *pSrc++;
	}
}

void MemCopy16(uint32_ptr_t pBuf, uint16_ptr_t pSrc, uint32_t uSrcLen)
{
	uint32_t	u, max;

	if ((!pBuf) || (!pSrc) || (uSrcLen <= 0)) return;

	max = uSrcLen / 2;
	for (u = 0; u < max; u++) {
		*pBuf++ = (uint32_t) *pSrc++;
	}

	if ((u * 2) < uSrcLen) {
		*pBuf = (uint32_t) *pSrc;
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