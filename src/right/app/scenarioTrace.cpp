/**
 * ScenarioTrace.cpp
 */

#include "scenarioTrace.h"

void ScenarioTrace::ScenarioTrace(Walker *pWalker, Timer *pTimer) : m_pWalker(pWalker), m_pTimer(pTimer)
{
    m_stWork.byExeParamsIndex = 0;
    m_stWork.dwStartTime = 0;
    m_eExecuteState = eExECUTE_STATE_INIT;
}

/**
 * @brief シナリオトレース実行
 * @return 実行状態
 */
E_EXECUTE_STATE ScenarioTrace::Run(void)
{
    switch (m_stExecuteSate)
    {
    case eEXECUTE_STATE_INIT:
        /* 初期化 */
        this.executeInit();
        break;

    case eEXECUTE_STATE_EXE:
        /* 実行状態 */
        /* 中身でパラメータ入力している分だけぶん回すイメージ */
        this.executeWalking();
        break;

    case eEXECUTE_STATE_END:
        break;

    default:
        /* 想定外なので実行しない状態に遷移する */
        break;
    }

    /* ここで状態遷移 */
    m_stExecuteSate = this.getNextState(m_stExecuteSate);
    return m_stExecuteSate;
}

/**
 * @brief 次の状態遷移を確定させる
 * @param eSrcState
 * @return 次の状態
 */
E_EXECUTE_STATE ScenarioTrace::getNextState(E_EXECUTE_STATE eSrcState)
{
    E_EXECUTE_STATE eNextState = eSrcState;
    if (eEXECUTE_STATE_INIT == eSrcState)
    {
        eNextState = eEXECUTE_STATE_EXE
    } else if (eEXECUTE_STATE_EXE == eSrcState)
    {
        if (m_stWork.byExeParamsIndex == m_stParams.byMaxParams)
        {
            eNextState = eEXECUTE_STATE_END;
        }
    }else 
    {
        /* これ以外は、ENDを強制的に返す */
        eNextState = eEXECUTE_STATE_END;
    }
    return eNextState;
}

E_EXECUTE_STATE ScenarioTrace::executeInit(void)
{
    /* ウォーカー初期化 */
    return eEXECUTE_STATE_EXE;
}

/**
 * @brief 実行状態
 */
void ScenarioTrace::executeWalking(void)
{
    /* コマンド判定をする */
    /* 回転のためのバイアスは、右回転向けのインプットであると判断する */
    BYTE byParamsIndex = m_stWork.byExeParamsIndex;
    /* 前進するときの車輪のPWNバイアス登録 */
    m_pWalker->setXXX(m_stParams[byParamsIndex].nRightBias, m_stParams[byParamsIndex].nLeftBias);
    /* walkerの実行 */
    m_pWalker->run();

    /* 制限時間の判定 */
    DWORD dwCurTime = m_pTimer->getTime();
    DWORD dwTimeLimit = m_stWork.dwStartTime + m_stParams[byParamsIndex].dwDuration;

    if (dwTimeLimit >= dwCurTime)
    {
        m_stWork.byExeParamsIndex++;
    }
}
