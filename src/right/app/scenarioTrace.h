/**
 * @brief ScenatrioTrace.h
 */
#pragma once

#include <stdio.h>
#include "common/common.h"
#include "common/mid/walker.h"
#include "common/mid/timer.h"
#define MAX_PARAMS (30)

using namespace Common;

class ScenarioTrace 
{
    public:
        typedef enum
        {
            eCOMMAND_STRAIGHT = 0,
            eCOMMAND_RIGHT,
            eCOMMAND_LEFT,
            eCOMMAND_MAX = 3,
        } E_COMMANDS;

        typedef struct 
        {
            E_COMMANDS eCommand; /* 実行コマンド */
            DWORD dwDuration; /* 実行時間 */
            SWORD nRightBias; /* 回転するときの右ホイールPWNバイアス値 */
            SWORD nLeftBias; /* 回転するときの左ホイールPWNバイアス値 */
        } ST_SCENARIO_TRACE_PARAMS;

        typedef struct{
            BYTE byExeParamsIndex; /* 実行パラメータ数 */
            DWORD dwStartTime; /* 1コマンド実行開始時間 */
        } ST_WORK;
        ScenarioTrace(Walker *pWalker, Timer *pTimer, BYTE byMaxParams);
        Common::ExecuteState Run(void);
        void SetParams(ST_SCENARIO_TRACE_PARAMS& stParams);
        E_COMMANDS GetCurExeCommand(void);
        DWORD GetCurDuration(void);
        Common::ExecuteState getCurExeState(void);
    private:
        Walker* m_pWalker;
        Timer* m_pTimer;
        ST_SCENARIO_TRACE_PARAMS m_stParams[MAX_PARAMS];
        Common::ExecuteState m_eExecuteState;
        ST_WORK m_stWork;
        Common::ExecuteState executeInit(void);
        Common::ExecuteState getNextState(ExecuteState eSrcState);
        void executeWalking(void);
}

