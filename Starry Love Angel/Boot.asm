; Starry Love Angle
; Boot.asm

bits 32

section .__SLA_multiboot__
	align 0x04

	__SLA_multibootMagicNumber__ dd 0x1BADB002
	__SLA_multibootFlags__ dd (0x01<<0x00)|(0x01<<0x01)
	__SLA_multibootChecksum__ dd -(0x1BADB002+(0x01<<0x00)|(0x01<<0x01))

section .__SLA_initialStack__
	align 0x04

	__SLA_initialStackBottom__:

		times 0xFFFF db 0x00

	__SLA_initialStackTop__:

section .text

	global __SLA_initialise__
	extern __SLA_initialise__

	__SLA_bootInitialise__:

		mov esp, __SLA_initialStackTop__

		call __SLA_initialise__

	__SLA_bootRelease__:

		cli
		hlt

	jmp __SLA_bootRelease__
