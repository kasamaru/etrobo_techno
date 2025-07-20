/**
 * @brief LineTrace.h
 */
#pragma once

#include <stdio.h>
#include "common/common.h"
#include "common/mid/walker.h"
#include "common/mid/colorSense.h"
#include "common/mid/timer.h"

using namespace Common;

class LineTrace
{
    public:
        typedef struct{
            WORD wRGBRTh; /* RGB値Rしきい値 */
            WORD wRGBGTh; /* RGB値Gしきい値 */
            WORD wRGBBTh; /* RGB値Bしきい値 */
            BYTE byHSVHTh; /* HSV値Hしきい値 */
            BYTE byHSVSTh; /* HSV値Sしきい値 */
            BYTE byHSVVTh; /* HSV値Vしきい値 */
        } ST_COLOR_TH;

        LineTrace(Walker* pWalker, ColorSense* pColorSense, Timer* pTimer);
        Common::ExecuteState Run(void);
        void setColorTh(ST_COLOR_TH* pstColorTh);

    private:
        Walker* m_pWalker;
        ColorSense* m_pColorSense;
        Timer* m_pTimer;
        ST_COLOR_TH m_stColorTh;
        Common::ExecuteState m_eExecuteState;
        Common::ExecuteState executeInit(void);
        Common::ExecuteState getNextState(ExecuteState eSrc);
        void executeTrace(void);
};