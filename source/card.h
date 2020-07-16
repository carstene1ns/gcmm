/*-------------------------------------------------------------
card.h -- Memory card subsystem ADDITIONS
*/

#ifndef GCMM_CARD_H
#define GCMM_CARD_H

/*!
\file card.h
\brief Memory card subsystem ADDITIONS

*/

#include <ogc/card.h>

#ifdef __cplusplus
   extern "C" {
#endif /* __cplusplus */

struct card_direntry {
	u8 gamecode[4];
	u8 company[2];
	u8 pad_00;
	u8 bannerfmt;
	u8 filename[CARD_FILENAMELEN];
	u32 lastmodified;
	u32 iconaddr;
	u16 iconfmt;
	u16 iconspeed;
	u8 permission;
	u8 copytimes;
	u16 block;
	u16 length;
	u16 pad_01;
	u32 commentaddr;
} ATTRIBUTE_PACKED;

/*! \fn s32 CARD_GetFreeBlocks(s32 chn)
\brief Get the free blocks in memory card
\param[in] chn CARD slot.
\param[in] freeblocks pointer to receive freeblocks value.

\return \ref card_errors "card error codes" or free blocks
*/
s32 CARD_GetFreeBlocks(s32 chn, u16* freeblocks);

/*! \fn s32 __card_getstatusex(s32 chn,s32 fileno,struct card_direntry *entry)
\brief Get the directory entry (GCI header)
\param[in] chn CARD slot.
\param[in] fileno file index. returned by a previous call to CARD_Open().
\param[out] entry pointer to receive the directory entry.

\return \ref card_errors "card error codes"
*/
s32 __card_getstatusex(s32 chn,s32 fileno,struct card_direntry *entry);

/*! \fn s32 __card_setstatusex(s32 chn,s32 fileno,struct card_direntry *entry)
\brief Set the directory entry (preferably from a GCI header), except block index and lenght
\param[in] chn CARD slot.
\param[in] fileno file index. returned by a previous call to CARD_Open().
\param[out] entry pointer to a directory entry structure (or GCI header).

\return \ref card_errors "card error codes"
*/
s32 __card_setstatusex(s32 chn,s32 fileno,struct card_direntry *entry);

/* CARD_GetSerialNo                                        */
/*                                                         */
/* serial1 & serial2: Encrypted memory card serial numbers */
/* chn: Memory card port                                   */
/* ret: Error code                                         */
s32 CARD_GetSerialNo(s32 chn,u32 *serial1,u32 *serial2);

// Raw read and write functions
s32 __card_read(s32 chn,u32 address,u32 block_len,void *buffer,cardcallback callback);
s32 __card_write(s32 chn,u32 address,u32 block_len,void *buffer,cardcallback callback);
s32 __card_sync(s32 chn);
s32 __card_sectorerase(s32 chn,u32 sector,cardcallback callback);

#ifdef __cplusplus
   }
#endif /* __cplusplus */

#endif
