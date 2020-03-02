MEMORY
{
	FLASH	(rx)	: ORIGIN = 0x00000000, LENGTH = 64K
	SRAM	(rwx)	: ORIGIN = 0x20000000, LENGTH = 20K
}

SECTIONS
{
	.text :
	{
		KEEP(*(.eisr_vector .eisr_vector.*))
		*(.text .text.*)
	} > FLASH
		
	.bss (NOLOAD) :
	{
		*(.bss .bss.*)
	} > SRAM
}
