/**
 * @brief avr.cpp
 */
/* ↓参考コード */
/* https://github.com/lipoyang/AverageMedian/tree/master */
#include <stdio.h>
#include "avr.h"

void Average::Average(TYPE* ptBuff, WORD wSize): {
    
}

void Average::init(void) {
    s_stMovingAvrData.wIndex = 0;
    s_stMovingAvrData.tResult =0;
    s_stMovingAvrData.isReset = true;
    memset(s_stMovingAvrData.pstBuff, 0 , s_stMovingAvrData.wSize);
}
void reset(void);
void execute(TYPE tSrc);
void getResult(void);
