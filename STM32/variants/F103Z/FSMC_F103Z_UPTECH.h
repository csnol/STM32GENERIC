#ifndef __FSMC_F103Z_UPTECH_H__
#define __FSMC_F103Z_UPTECH_H__

//up-tech  103zet6

 /* !!!该板子硬件连接错误！ NBL0/1 错误连接接在SDRAM UQ/DQ，导致 8bit读写错误
  * 8 位读写用16位代替，并通过判断地址选择读写16位的高8位或低8位来修正
**/ 
#define FIXED_NBL01_CONNECTEDERR  1

//sram ISSI61LV12816L-10TL
#define FSMC_SRAMBANK               FSMC_NORSRAM_BANK2
#define SRAM_LENGTH	                ((uint32_t)(2*128*1024))  /* 128*16 256k byte length*/
//#define FSMC_ADDRESSBITS 17       /* 128K*16 17bit */

//nor SST39VF040-70
#define SST39VF040
#define FSMC_NORBANK                FSMC_NORSRAM_BANK3 
#define NOR_DEVICE_LENGTH           ((uint32_t)(512*1024)) /* 512K * 8bit 512K byte length*/
#define NOR_WAIT_PIN                PD6
//#define FSMC_ADDRESSBITS          19                     /* 512K * 8 19bit */
#define FSMC_NORSRAM_MEM_BUS_WIDTH  FSMC_NORSRAM_MEM_BUS_WIDTH_8 // SST39VF040 is 8 bit width
#define __NOR_MEMORY_WIDTH_         FSMC_NORSRAM_MEM_BUS_WIDTH
//nand K9F1208U0C
#define FSMC_NANDBANK    FSMC_NAND_BANK2
#define FSMC_NWAIT_PD6   1
#define FSMC_INT2        1


#define NAND_PAGE_SIZE             ((uint16_t)0x0200) /* 512 bytes per page w/o Spare Area */
#define NAND_BLOCK_SIZE            ((uint16_t)0x0020) /* 32x512 bytes pages per block */
#define NAND_PLANE_SIZE            ((uint16_t)0x0400) /* 1024 Block per plane */
#define NAND_SPARE_AREA_SIZE       ((uint16_t)0x0010) /* last 16 bytes as spare area */
#define NAND_MAX_PLANE             ((uint16_t)0x1000) /* 4 planes of 1024 block */

//lcd
#define FSMC_LCDBANK                FSMC_NORSRAM_BANK4
#define FSMC_ADDRESSBITS            26                /*  26bits LVC61425 rw addr range AD0~AD25*/

#define NORSRAM_BANK1_1  0x01
#define NORSRAM_BANK1_2  0x02
#define NORSRAM_BANK1_3  0x04
#define NORSRAM_BANK1_4  0x08

//                         NAND/NCE2            SRAM           NOR            BANK4 for LVC61245     
#define NORSRAM_BANKS  (NORSRAM_BANK1_1 | NORSRAM_BANK1_2 | NORSRAM_BANK1_3 | NORSRAM_BANK1_4)

#define FSMC_BASE_BK11	(0x60000000 | 0x00000000) /*PD7 /NE1/NCE2 FSMC_BANK1_1   */
#define FSMC_BASE_BK12	(0x60000000 | 0x04000000) /*PG9 /NE2 FSMC_BANK1_2        */
#define FSMC_BASE_BK13	(0x60000000 | 0x08000000) /*PG10/NE3 FSMC_BANK1_3        */
#define FSMC_BASE_BK14	(0x60000000 | 0x0C000000) /*PG12/NE4 FSMC_BANK1_4        */

//sram
#if FSMC_SRAMBANK == FSMC_NORSRAM_BANK1
#define SRAM_START	FSMC_BASE_BK11
#elif FSMC_SRAMBANK == FSMC_NORSRAM_BANK2
#define SRAM_START	FSMC_BASE_BK12
#elif FSMC_SRAMBANK == FSMC_NORSRAM_BANK3
#define SRAM_START	FSMC_BASE_BK13
#elif FSMC_SRAMBANK == FSMC_NORSRAM_BANK4
#define SRAM_START	FSMC_BASE_BK14
#endif

//nor
#if FSMC_NORBANK == FSMC_NORSRAM_BANK1
#define NOR_DEVICE_ADDR	FSMC_BASE_BK11
#elif FSMC_NORBANK == FSMC_NORSRAM_BANK2
#define NOR_DEVICE_ADDR	FSMC_BASE_BK12
#elif FSMC_NORBANK == FSMC_NORSRAM_BANK3
#define NOR_DEVICE_ADDR	FSMC_BASE_BK13
#elif FSMC_NORBANK == FSMC_NORSRAM_BANK4
#define NOR_DEVICE_ADDR	FSMC_BASE_BK14
#endif


#ifdef __cplusplus
extern "C"{
#endif

void    STM_FSMC_SRAM_Init(void);
void    STM_FSMC_NOR_Init(void);
void    STM_FSMC_NAND_Init(void);

#if USE_EXTRAMSYSMALLOC
void setHeapAtSram(void);
#endif

#ifdef __cplusplus
} //extern "C"
#endif

#endif /* __FSMC_F103Z_UPTECH_H__ */
