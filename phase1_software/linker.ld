ENTRY(_start)

SECTIONS
{
  . = 0x00000000;
  .text : { *(.text*) *(.rodata*) }
  .data : { *(.data*) }
  .bss  : { *(.bss*) *(COMMON) }

  _stack_top = 0x00001000; /* 4KB */
}