ENTRY(Reset_Handler)

MEMORY
{
	FLASH (rx)  : ORIGIN = 0x08000000 , LENGTH = 64K
	SRAM  (rwx) : ORIGIN = 0x20000000 , LENGTH = 20K
}

SECTIONS
{
	.isr_vectors :
	{
		*(.isr_vectors)
	}>FLASH
	
	.text :
	{
		*(.text)
	}>FLASH
	
	.rodata :
	{
		*(.rodata)
		_erodata = . ;
	}>FLASH
	
	.data :
	{
		_sdata = . ;
		*(.data)
		_edata = . ;
	}>SRAM AT>FLASH
	
	.bss :
	{
		_sbss = . ;
		*(.bss)
		_ebss = . ;
	}>SRAM 
}