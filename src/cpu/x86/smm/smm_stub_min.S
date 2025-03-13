
/*
 * Minimal SMM stub just issues rsm
 */

#include <cpu/x86/cr.h>
#include <cpu/x86/msr.h>
#include <cpu/x86/lapic_def.h>
#include <cpu/x86/64bit/entry64.inc>

.code32
.section ".module_parameters", "aw", @progbits
.text
.code16
.global _start
_start:
.align 4
.code32
.global smm_trampoline32
smm_trampoline32:
	/* Use flat data segment */
	movw	$0x10, %ax
	movw	%ax, %ds
	movw	%ax, %es
	movw	%ax, %ss
	xor	%ax, %ax /* zero out the gs and fs segment index */
	movw	%ax, %fs
	movw	%ax, %gs /* Used by cpu_info in ramstage */
1:
	rsm
