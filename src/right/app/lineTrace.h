/**
 * @brief LineTrace.h
 */
#pragma once

#include <stdio.h>
#include "common/common.h"
#include "common/mid/walker.h"
#include "common/app/lineMonitor.h"
#include "common/mid/timer.h"
#include "common/app/pidCtrl.h"

using namespace Common;
using namespace Caculation;

class LineTrace
{
    public:
        typedef struct{
            WORD wR; /* RGB値Rしきい値 */
            WORD wG;
            WORD wB; /* RGB値Bしきい値 */
        } ST_COLOR_TH;
        LineTrace(Walker* pWalker, LineMonitor* pLineMonitor, Timer* pTimer);
        void Init(WORD byCourse);
        void SetHighSpeedModeDeadLine(DWORD dwDuration);
        Common::ExecuteState Run(void);
    private:
        Walker* m_pWalker;
        LineMonitor* m_pLineMonitor;
        Timer* m_pTimer;
        Caculation::PidCtrl* m_pidCtrl;
        ST_COLOR_TH m_stColorTh_Max;
        ST_COLOR_TH m_stColorTh_Min;
        DWORD m_dwDuration; /* 高速モード継続時間 */
        DWORD m_dwStartTime; /* 高速モード開始時間 */
        WORD wCourse;
        bool m_bHighModeEnd;
        Common::ExecuteState m_eExecuteState;
        Common::ExecuteState executeTrace(void);
        Common::ExecuteState excuteInitWalk(void);
        Common::ExecuteState excuteLowSpeedMode(void);
        Common::ExecuteState excuteHighSpeedMode(void);
};