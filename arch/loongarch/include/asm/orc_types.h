/* SPDX-License-Identifier: GPL-2.0-or-later */
#ifndef _ORC_TYPES_H
#define _ORC_TYPES_H

#include <linux/types.h>

/*
 * The ORC_REG_* registers are base registers which are used to find other
 * registers on the stack.
 *
 * ORC_REG_PREV_SP, also known as DWARF Call Frame Address (CFA), is the
 * address of the previous frame: the caller's SP before it called the current
 * function.
 *
 * ORC_REG_UNDEFINED means the corresponding register's value didn't change in
 * the current frame.
 *
 * The most commonly used base registers are SP and FP -- which the previous SP
 * is usually based on -- and PREV_SP and UNDEFINED -- which the previous FP is
 * usually based on.
 *
 * The rest of the base registers are needed for special cases like entry code
 * and GCC realigned stacks.
 */
#define ORC_REG_UNDEFINED		0
#define ORC_REG_PREV_SP			1
#define ORC_REG_SP			2
#define ORC_REG_FP			3
#define ORC_REG_MAX			4

#define ORC_TYPE_UNDEFINED		0
#define ORC_TYPE_END_OF_STACK		1
#define ORC_TYPE_CALL			2
#define ORC_TYPE_REGS			3
#define ORC_TYPE_REGS_PARTIAL		4

#ifndef __ASSEMBLER__
/*
 * This struct is more or less a vastly simplified version of the DWARF Call
 * Frame Information standard.  It contains only the necessary parts of DWARF
 * CFI, simplified for ease of access by the in-kernel unwinder.  It tells the
 * unwinder how to find the previous SP and FP (and sometimes entry regs) on
 * the stack for a given code address.  Each instance of the struct corresponds
 * to one or more code locations.
 */
struct orc_entry {
	s16		sp_offset;
	s16		fp_offset;
	s16		ra_offset;
	unsigned int	sp_reg:4;
	unsigned int	fp_reg:4;
	unsigned int	ra_reg:4;
	unsigned int	type:3;
	unsigned int	signal:1;
};
#endif /* __ASSEMBLER__ */

#endif /* _ORC_TYPES_H */
