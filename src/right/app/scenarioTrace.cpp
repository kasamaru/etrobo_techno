/**
 * ScenarioTrace.cpp
 */

#include "scenarioTrace.h"

ScenarioTrace::ScenarioTrace(Walker *pWalker, Timer *pTimer) : m_pWalker(pWalker), m_pTimer(pTimer)
{
    m_stWork.byExeParamsIndex = 0;
    m_eExecuteState = Common::ExecuteState::Init;
}

/**
 * @brief シナリオトレースパラメータセット
 * @param stParams パラメータ構造体
 * @param byMaxParams 最大パラメータ数
 */
void ScenarioTrace::SetParams(ST_SCENARIO_TRACE_PARAMS* pstParams, const BYTE byMaxParams)
{
    if(byMaxParams > MAX_PARAMS) {
        /* 最大パラメータ数を超えているので、エラー */
        return;
    }
    for(BYTE i = 0; i < byMaxParams; i++) {
        m_stParams[i] = pstParams[i];
    }
    m_stWork.byMaxExePrams = byMaxParams;
}

/**
 * @brief 現在の実行コマンド取得
 * @return 現在の実行コマンド
 */
void ScenarioTrace::RunReady(void)
{
    m_stWork.byExeParamsIndex = 0;
    m_eExecuteState = Common::ExecuteState::Init;
}

/**
 * @brief シナリオトレース実行
 * @return 実行状態
 */
Common::ExecuteState ScenarioTrace::Run(void)
{
    switch (m_eExecuteState)
    {
    case Common::ExecuteState::Init:
        /* 初期化 */
        this->executeInit();
        break;

    case Common::ExecuteState::Execute:
        /* 実行状態 */
        /* 中身でパラメータ入力している分だけぶん回すイメージ */
        this->executeWalking();
        break;

    case Common::ExecuteState::End:
        break;

    default:
        /* 想定外なので実行しない状態に遷移する */
        break;
    }

    /* ここで状態遷移 */
    m_eExecuteState = this->getNextState(m_eExecuteState);
    return m_eExecuteState;
}

/**
 * @brief 次の状態遷移を確定させる
 * @param eSrcState
 * @return 次の状態
 */
Common::ExecuteState ScenarioTrace::getNextState(Common::ExecuteState eSrcState)
{
    Common::ExecuteState eNextState = eSrcState;
    if (Common::ExecuteState::Init == eSrcState)
    {
        eNextState = Common::ExecuteState::Execute;
    } else if (Common::ExecuteState::Execute == eSrcState)
    {
        if (m_stWork.byExeParamsIndex == m_stWork.byMaxExePrams)
        {
            eNextState = Common::ExecuteState::End;
        }
    }else 
    {
        /* これ以外は、ENDを強制的に返す */
        eNextState = Common::ExecuteState::End;
    }
    return eNextState;
}

Common::ExecuteState ScenarioTrace::executeInit(void)
{
    /* 1パラメータを実行するための初期化 */
    m_pTimer->start(m_stParams[m_stWork.byExeParamsIndex].dwDuration);

    return Common::ExecuteState::Execute;
}

/**
 * @brief 実行状態
 */
Common::ExecuteState ScenarioTrace::executeWalking(void)
{
    Common::ExecuteState eNextState = Common::ExecuteState::Execute;
    /* コマンド判定をする */
    /* 回転のためのバイアスは、右回転向けのインプットであると判断する */
    BYTE byParamsIndex = m_stWork.byExeParamsIndex;
    /* 前進するときの車輪のPWNバイアス登録 */
    m_pWalker->runForward(m_stParams[byParamsIndex].nRightBias, m_stParams[byParamsIndex].nLeftBias);

    /* 制限時間の判定 */
    if (m_pTimer->isTimeout())
    {
        /* 制限時間が来たので、次のパラメータへ移行 */
        m_stWork.byExeParamsIndex++;
        m_pTimer->reset(); // タイマーをリセット
        eNextState = Common::ExecuteState::Init; // 次の状態はENDにする
    }
    return eNextState;
}
