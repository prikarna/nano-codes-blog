MEMORY
{
	FLASH	(rwx)	: ORIGIN = 0x00000000, LENGTH = 64K
}

SECTIONS
{
	.text :
	{
		KEEP(*(.eisr_vector .eisr_vector.*))
		*(.text .text.*)
	} > FLASH
}
