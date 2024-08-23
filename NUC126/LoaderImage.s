;/*---------------------------------------------------------------------------------------------------------*/
;/*                                                                                                         */
;/* Copyright(c) 2009 Nuvoton Technology Corp. All rights reserved.                                         */
;/*                                                                                                         */
;/*---------------------------------------------------------------------------------------------------------*/


    AREA _image, DATA, READONLY

    EXPORT  FlashAlgoHeader
    EXPORT  FlashAlgoBase
    EXPORT  FlashAlgoLimit

    EXPORT  UserImageBase
    EXPORT  UserImageLimit
 
    ALIGN   4     
FlashAlgoHeader
    INCBIN .\..\BlobHeader.bin
FlashAlgoBase
    INCBIN .\FlashAlgo.bin
FlashAlgoLimit

    ALIGN   4
UserImageBase
    INCBIN .\GPIO_OutputInput.bin
UserImageLimit

    END