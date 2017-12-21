#ifndef __CHIPINFOS_H__
#define __CHIPINFOS_H__

/* chip info
 * see dev_table.h & dev_table.c *
 *            ID     SRAM_END   FLASH_END pps ps    ops         ope       ms         me      flags
*/ 
/* F0 */
#define CHIP_ID440  0x20002000,0x08010000,4,p_1k ,0x1FFFF800,0x1FFFF80F,0x1FFFEC00,0x1FFFF800,0
#define CHIP_ID442  0x20008000,0x08040000,2,p_2k ,0x1FFFF800,0x1FFFF80F,0x1FFFD800,0x1FFFF800,2
#define CHIP_ID444  0x20001000,0x08008000,4,p_1k ,0x1FFFF800,0x1FFFF80F,0x1FFFEC00,0x1FFFF800,0
#define CHIP_ID445  0x20001800,0x08008000,4,p_1k ,0x1FFFF800,0x1FFFF80F,0x1FFFC400,0x1FFFF800,0
#define CHIP_ID448  0x20004000,0x08020000,2,p_2k ,0x1FFFF800,0x1FFFF80F,0x1FFFC800,0x1FFFF800,0
/* F1 */
#define CHIP_ID412  0x20002800,0x08008000,4,p_1k ,0x1FFFF800,0x1FFFF80F,0x1FFFF000,0x1FFFF800,0
#define CHIP_ID410  0x20005000,0x08020000,4,p_1k ,0x1FFFF800,0x1FFFF80F,0x1FFFF000,0x1FFFF800,0
#define CHIP_ID414  0x20010000,0x08080000,2,p_2k ,0x1FFFF800,0x1FFFF80F,0x1FFFF000,0x1FFFF800,0
#define CHIP_ID420  0x20002000,0x08020000,4,p_1k ,0x1FFFF800,0x1FFFF80F,0x1FFFF000,0x1FFFF800,0
#define CHIP_ID428  0x20008000,0x08080000,2,p_2k ,0x1FFFF800,0x1FFFF80F,0x1FFFF000,0x1FFFF800,0
#define CHIP_ID418  0x20010000,0x08040000,2,p_2k ,0x1FFFF800,0x1FFFF80F,0x1FFFB000,0x1FFFF800,0
#define CHIP_ID430  0x20018000,0x08100000,2,p_2k ,0x1FFFF800,0x1FFFF80F,0x1FFFE000,0x1FFFF800,0
/* F2 */ 
#define CHIP_ID411  0x20020000,0x08100000,1,f2f4 ,0x1FFFC000,0x1FFFC00F,0x1FFF0000,0x1FFF7800,0
/* F3 */
#define CHIP_ID432  0x20008000,0x08040000,2,p_2k ,0x1FFFF800,0x1FFFF80F,0x1FFFD800,0x1FFFF800,0
#define CHIP_ID422  0x2000A000,0x08040000,2,p_2k ,0x1FFFF800,0x1FFFF80F,0x1FFFD800,0x1FFFF800,0
#define CHIP_ID439  0x20004000,0x08010000,2,p_2k ,0x1FFFF800,0x1FFFF80F,0x1FFFD800,0x1FFFF800,0
#define CHIP_ID438  0x20003000,0x08010000,2,p_2k ,0x1FFFF800,0x1FFFF80F,0x1FFFD800,0x1FFFF800,0
#define CHIP_ID446  0x20010000,0x08080000,2,p_2k ,0x1FFFF800,0x1FFFF80F,0x1FFFD800,0x1FFFF800,0
/* F4 */
#define CHIP_ID413  0x20020000,0x08100000,1,f2f4 ,0x1FFFC000,0x1FFFC00F,0x1FFF0000,0x1FFF7800,0
#define CHIP_ID419  0x20030000,0x08200000,1,f4db ,0x1FFEC000,0x1FFFC00F,0x1FFF0000,0x1FFF7800,0
#define CHIP_ID423  0x20010000,0x08040000,1,f2f4 ,0x1FFFC000,0x1FFFC00F,0x1FFF0000,0x1FFF7800,0
#define CHIP_ID433  0x20018000,0x08080000,1,f2f4 ,0x1FFFC000,0x1FFFC00F,0x1FFF0000,0x1FFF7800,0
#define CHIP_ID458  0x20008000,0x08020000,1,f2f4 ,0x1FFFC000,0x1FFFC00F,0x1FFF0000,0x1FFF7800,0
#define CHIP_ID431  0x20020000,0x08080000,1,f2f4 ,0x1FFFC000,0x1FFFC00F,0x1FFF0000,0x1FFF7800,0
#define CHIP_ID441  0x20020000,0x08100000,1,f2f4 ,0x1FFFC000,0x1FFFC00F,0x1FFF0000,0x1FFF7800,0
#define CHIP_ID463  0x20050000,0x08180000,1,f2f4 ,0x1FFFC000,0x1FFFC00F,0x1FFF0000,0x1FFF7800,0
#define CHIP_ID421  0x20020000,0x08080000,1,f2f4 ,0x1FFFC000,0x1FFFC00F,0x1FFF0000,0x1FFF7800,0
#define CHIP_ID434  0x20060000,0x08200000,1,f4db ,0x1FFEC000,0x1FFFC00F,0x1FFF0000,0x1FFF7800,0
/* F7 */
#define CHIP_ID452  0x20040000,0x08080000,1,f7   ,0x1FFF0000,0x1FFF001F,0x1FF00000,0x1FF0EDC0,0
#define CHIP_ID449  0x20050000,0x08100000,1,f7   ,0x1FFF0000,0x1FFF001F,0x1FF00000,0x1FF0EDC0,0
#define CHIP_ID451  0x20080000,0x08200000,1,f7   ,0x1FFF0000,0x1FFF001F,0x1FF00000,0x1FF0EDC0,0
/* L0 */
#define CHIP_ID425  0x20002000,0x08008000,2,p_128,0x1FF80000,0x1FF8001F,0x1FF00000,0x1FF01000,0
#define CHIP_ID417  0x20002000,0x08010000,2,p_128,0x1FF80000,0x1FF8001F,0x1FF00000,0x1FF01000,1
#define CHIP_ID447  0x20005000,0x08030000,2,p_128,0x1FF80000,0x1FF8001F,0x1FF00000,0x1FF02000,0
/* L1 */
#define CHIP_ID416  0x20004000,0x08020000,6,p_256,0x1FF80000,0x1FF8001F,0x1FF00000,0x1FF01000,1
#define CHIP_ID429  0x20008000,0x08020000,6,p_256,0x1FF80000,0x1FF8001F,0x1FF00000,0x1FF01000,1
#define CHIP_ID427  0x20008000,0x08040000,6,p_256,0x1FF80000,0x1FF8001F,0x1FF00000,0x1FF02000,1
#define CHIP_ID436  0x2000C000,0x08060000,6,p_256,0x1FF80000,0x1FF8009F,0x1FF00000,0x1FF02000,0
#define CHIP_ID437  0x20014000,0x08080000,6,p_256,0x1FF80000,0x1FF8009F,0x1FF00000,0x1FF02000,1
/* L4 */
#define CHIP_ID415  0x20018000,0x08100000,1,p_2k ,0x1FFF7800,0x1FFFF80F,0x1FFF0000,0x1FFF7000,0
#define CHIP_ID435  0x2000C000,0x08040000,1,p_2k ,0x1FFF7800,0x1FFFF80F,0x1FFF0000,0x1FFF7000,0
#define CHIP_ID461  0x20040000,0x08100000,1,p_2k ,0x1FFF7800,0x1FFFF80F,0x1FFF0000,0x1FFF7000,0
/*AN2606: */
#define CHIP_ID641 	0x20005000,0x08020000,4,p_1k ,0x1FFFF800,0x1FFFF80F,0x1FFFF000,0x1FFFF800,0
#define CHIP_ID9a8 	0x20002000,0x08020000,4,p_1k ,0x08040800,0x0804080F,0x08040000,0x08040800,0
#define CHIP_ID9b0 	0x20004000,0x08040000,4,p_2k ,0x08040800,0x0804080F,0x08040000,0x08040800,0

 
#endif