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
        LineTrace(Walker* pWalker, LineMonitor* pLineMonitor);
        Common::ExecuteState Run(void);
        void setColorTh(ST_COLOR_TH* pstColorTh);
    private:
        Walker* m_pWalker;
        LineMonitor* m_pLineMonitor;
        Caculation::PidCtrl* m_pidCtrl;
        ST_COLOR_TH m_stColorTh;
        Common::ExecuteState m_eExecuteState;
        Common::ExecuteState executeTrace(void);
        Common::ExecuteState excuteInitWalk(void);
};