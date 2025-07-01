#pragma once

#include "common.h"
template <typename TYPE>
class Average {
    public:
        typedef struct {
            TYPE* ptBuff; /* データ格納バッファ */
            WORD wSize;   /* 移動平均対象最大データ点数 */
            WORD wIndex;  /* 現在のインデックス */
            TYPE tResult; /* 演算値 */
            bool isReset; /* リセットするかどうか */
        } ST_MOVING_AVR;
        
        void Average(TYPE* ptBuff, WORD wSize);
        void init(void);
        void reset(void);
        void execute(TYPE tSrc);
        void getResult(void);
    private:
        static ST_MOVING_AVR s_stMovingAvrData;
}