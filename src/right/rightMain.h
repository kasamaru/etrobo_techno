/**
 * @file rightMain.h
 */
#pragma once

#include "spikeapi.h"
#include "app/scenarioTrace.h"
#include "starter.h"

using namespace Common;

class RightCource {
    public:
        RightCource(Walker *pWalker, Timer *pTimer, Starter *pStarter);
        bool StartAlwaysTask(void);
        void StopAlwaysTask(void);

    private:
        Common::TaskSeq checkNextTaskSeq(const Common::TaskSeq c_eCurTaskSeq, const Common::ExecuteState c_eCurState);
        void scenarioTraceInit(ScenarioTrace::ST_SCENARIO_TRACE_PARAMS* pstParams, const BYTE byMaxParams);
        bool m_bIsRunning;
        Common::TaskSeq m_eExecuteSeq;
        Walker *m_pWalker;
        Timer *m_pTimer;
        Starter *m_pStarter; // Starterクラスのインスタンス
        ScenarioTrace *m_pScenarioTrace;
};