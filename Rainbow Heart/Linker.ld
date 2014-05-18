/* Rainbow Heart - Linker.ld */

ENTRY(__RainbowHeart_ProgramEntry)

SECTIONS
{
	. = 0x100000;

	/* First put the multiboot header, as it is required to be put very early
	   early in the image or the bootloader won't recognize the file format.
	   Next we'll put the .text section. */
	.text BLOCK(0x1000) : ALIGN(0x1000)
	{
		*(.__MultiBoot_Section)
		*(.__MultiBoot_ProgramText)
		*(.text)
	}

	.rodata BLOCK(0x1000) : ALIGN(0x1000)
	{
		*(.rodata)
	}

	/* Read-write data (initialized) */
	.data BLOCK(0x1000) : ALIGN(0x1000)
	{
		*(.data)
	}

	/* Read-write data (uninitialized) and stack */
	.bss BLOCK(0x1000) : ALIGN(0x1000)
	{
		*(COMMON)
		*(.bss)
		*(.__RainbowHeart_Stack)
	}
}
