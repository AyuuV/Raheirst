; Rainbow Heart - Boot.asm

__MultiBoot_Alignment equ 0x01<<0x00
__MultiBoot_MemoryMap equ 0x01<<0x01
__MultiBoot_Flags equ __MultiBoot_Alignment|__MultiBoot_MemoryMap
__MultiBoot_MagicNumber equ 0x1BADB002
__MultiBoot_CheckSum equ -(__MultiBoot_MagicNumber+__MultiBoot_Flags)

section .__MultiBoot_Section
	align 0x04

	dd __MultiBoot_MagicNumber
	dd __MultiBoot_Flags
	dd __MultiBoot_CheckSum

section .__RainbowHeart_Stack
	align 0x04

	__RainbowHeart_StackBottom:

	times 0xFFFF db 0x00

	__RainbowHeart_StackTop:

section .__RainbowHeart_ProgramText
	global __RainbowHeart_ProgramEntry
	extern __RainbowHeart_ProgramMain

	__RainbowHeart_ProgramEntry:

		mov esp, __RainbowHeart_StackTop

		call __RainbowHeart_ProgramMain

		cli

	.__RainbowHeart_ProgramEnd:
		hlt
		jmp .__RainbowHeart_ProgramEnd
