/**
 * @brief ScenatrioTrace.h
 */
#pragma once

#include <stdio.h>
#include "common/common.h"
#include "common/mid/walker.h"
#include "common/mid/timer.h"
#define MAX_PARAMS (30)
class ScenarioTrace 
    typedef enum{
        eCOMMAND_STRAIGHT = 0,
        eCOMMAND_RIGHT,
        eCOMMAND_LEFT,
        eCOMMAND_MAX = 3,
    } E_COMMANDS;

    typedef struct 
        E_COMMANDS eCommand; /* 実行コマンド */
        DWORD dwDuration; /* 実行時間 */
        SWORD nRightBias; /* 回転するときの右ホイールPWNバイアス値 */
        SWORD nLeftBias; /* 回転するときの左ホイールPWNバイアス値 */
        BYTE byMaxParams; /* パラメータ最大数 */
     ST_SCENARIO_TRACE_PARAMS;

    typedef struct{
        BYTE byExeParamsIndex; /* 実行パラメータ数 */
        DWORD dwStartTime; /* 1コマンド実行開始時間 */
    } ST_WORK;

    public:
        ScenarioTrace();
        E_EXECUTE_STATE Run(void);
        void SetParams(ST_SCENARIO_TRACE_PARAMS& stParams);
        E_COMMANDS GetCurExeCommand(void);
        DWORD GetCurDuration(void);
        E_EXECUTE_STATE getCurExeState(void);
    private:
        Walker* m_pWalker;
        Timer* m_pTimer;
        ST_SCENARIO_TRACE_PARAMS m_stParams[MAX_PARAMS];
        E_EXECUTE_STATE m_eExecuteState;
        ST_WORK m_stWork;
        E_EXECUTE_STATE executeInit(void);
        E_EXECUTE_STATE getNextState(E_EXECUTE_STATE eSrcState);
        void executeWalking(void);

