
#ifndef __SWD_LIB_H__
#define __SWD_LIB_H__


/* SWD Command */
uint32_t SWD_GetVersion(void);
uint32_t SWD_Open(uint32_t u32Clock);
void SWD_Close(void);
void SWD_Sequence(uint32_t u32Count, uint32_t u32Data);
// SWD Transfer I/O
//   u32Request: A[3:2] RnW APnDP
//   pu32Data:   DATA[31:0]
//   return:     ACK[2:0]
uint8_t SWD_Transfer(uint32_t u32Request, uint32_t *pu32Data);


#endif /* __SWD_LIB_H__ */
