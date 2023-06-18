#include "FLASH.h"


/***********************************************Sector Erase Bits Masking***********************************************/
#define SECTOR_ERASE_MASK								0xF
#define SECTOR_ERASE_SHIFTBITS					3
/***********************************************Program size Parallelism masking****************************************/
#define PROGRAM_SIZE_MASK								0x3
#define PROGRAM_SIZE_SHIFTBITS					8
/************************************************Register Bits*********************************************************/
#define BSY_BIT											    16
#define LOCK_BIT										    31
#define	SER_BIT											    1
#define STRT_BIT										    16
#define EOP_BIT											    0
#define PG_BIT											    0
/***********************************************Unlock Keys to access flash control register***************************/
#define KEY1  		 									    0x45670123
#define	KEY2 											      0xCDEF89AB

/*********************************Static function to unlock FLASH_KEYR register****************************************/
static void FlashUnlock(void);
/**************************************************Flash Interface Functions*******************************************/
void MFLASH_voidAreaErase(void)
{
	u8 LoopCounter;

	/* Looping with sector erase from start sector to the end sector  each sector is 16kb */
	for(LoopCounter = START_SECTOR; LoopCounter < END_SECTOR; LoopCounter++)
	{
		/* Sector Erase Function */
		MFLASH_voidSectorErase(LoopCounter);
	}
}

void MFLASH_voidSectorErase(u8 SectorNum )
{
	u32 temp;

	/*Check that no Flash memory operation is ongoing by checking the BSY bit in the FLASH_SR register */
	while((FLASH-> FLASH_SR >> BSY_BIT) & 1);

	/* call flash unlock function to write the keys for accessing the control register */
	FlashUnlock();

	/*Set the SER bit : Sector erase activate */
	FLASH->FLASH_CR |= (1 << SER_BIT);

	/*  Select the sector out of the 5 sectors to erase  */
	temp = FLASH->FLASH_CR;
	temp &= ~(SECTOR_ERASE_MASK<<SECTOR_ERASE_SHIFTBITS);
	temp |= (SectorNum<<SECTOR_ERASE_SHIFTBITS);
	FLASH->FLASH_CR = temp;

	/* Set the STRT bit in the FLASH_CR register */
	FLASH->FLASH_CR |= (1 << STRT_BIT);

	/* Wait for the BSY bit to be cleared */
	while((FLASH-> FLASH_SR >> BSY_BIT) & 1);

	/*clear  the SER bit : Sector erase deactivate */
	FLASH->FLASH_CR &= ~(1 << SER_BIT);
}

void MFLASH_voidWrite(u32 Address, u16 * Data, u8 Length)
{
	u8 LoopCounter;
	u32 temp;
	/*Check that no Flash memory operation is ongoing by checking the BSY bit in the FLASH_SR register */
	while((FLASH-> FLASH_SR >> BSY_BIT) & 1);

	/* call flash unlock function to write the keys for accessing the control register */
	FlashUnlock();

	/* set the program size to half word mode */
	temp=FLASH->FLASH_CR;
	temp&=~(PROGRAM_SIZE_MASK<<PROGRAM_SIZE_SHIFTBITS);
	temp|=(1<<PROGRAM_SIZE_SHIFTBITS);
	FLASH->FLASH_CR=temp;

	for (LoopCounter = 0; LoopCounter< Length; LoopCounter++)
	{
		/* Write Flash Programming activate */
		FLASH->FLASH_CR |= (1 << PG_BIT);

		/* Half word operation */
		*((volatile u16*)Address) = Data[LoopCounter];
		Address += 2 ;

		/* Wait Busy Flag */
		while ((FLASH->FLASH_SR >> BSY_BIT) & 1);

		/*clear  the SER bit : Sector erase deactivate */
		FLASH->FLASH_CR &= ~(1 << PG_BIT);
	}
}

static void FlashUnlock(void)
{
	/* check the lock bit on control register */
	if((FLASH->FLASH_CR >> LOCK_BIT) & 1)
	{
		/* write the unlock keys to access  flash control register */
		FLASH->FLASH_KEYR = KEY1;
		FLASH->FLASH_KEYR = KEY2;
	}
}


