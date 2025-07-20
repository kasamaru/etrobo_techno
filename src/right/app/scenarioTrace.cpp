/**
 * ScenarioTrace.cpp
 */

#include "scenarioTrace.h"

#define STRAIGHT_PWM (100) // 前進時のPWM値


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
    Common::ExecuteState eNextState = Common::ExecuteState::End;
    switch (eSrcState)
    {
    case Common::ExecuteState::Init:
        eNextState = Common::ExecuteState::Execute;
    case Common::ExecuteState::Execute:
        /* 実行状態 */
        if(m_pTimer->isTimeout()) {
            /* タイムアウトしたので、次の状態へ */
            m_stWork.byExeParamsIndex++;
            if(m_stWork.byExeParamsIndex < m_stWork.byMaxExePrams) {
                /* 登録パラメータが残っている場合 */
                eNextState = Common::ExecuteState::Init;
            } else {
                /* 登録パラメータ実行完了の場合 */
                eNextState = Common::ExecuteState::End;
            }
        } else {
            /* 実行中なので、実行状態を維持 */
            eNextState = Common::ExecuteState::Execute;
        }
        break;
    case Common::ExecuteState::End:
        /* 実行完了状態 */
        m_stWork.byExeParamsIndex = 0; // 実行パラメータインデックスをリセット
        m_eExecuteState = Common::ExecuteState::Init; // 次の実行に備えて初期化
        eNextState = Common::ExecuteState::End; // 実行完了状態を維持
        break;

    default:
        break;
    }

    return eNextState;
}

/**
 * @brief パラメータ実行前の初期化処理
 * @return 次の実行状態
 */
void ScenarioTrace::executeInit(void)
{
    /* 1パラメータを実行するための初期化 */
    m_pTimer->start(m_stParams[m_stWork.byExeParamsIndex].dwDuration);
}

/**
 * @brief 実行状態
 */
void ScenarioTrace::executeWalking(void)
{
    /* コマンド判定をする */
    switch (m_stParams[m_stWork.byExeParamsIndex].eCommand)
    {
        case eCOMMAND_STRAIGHT:
            /* 前進 */
            m_pWalker->runForward(STRAIGHT_PWM, STRAIGHT_PWM); // ここは適切なPWN値に置き換える
            break;

        case eCOMMAND_RIGHT:
            /* 右回転 */
            m_pWalker->runForward(STRAIGHT_PWM + m_stParams[m_stWork.byExeParamsIndex].nRightBias, 
                                  STRAIGHT_PWM - m_stParams[m_stWork.byExeParamsIndex].nLeftBias);
            break;

        case eCOMMAND_LEFT:
            /* 左回転 */
            m_pWalker->runForward(STRAIGHT_PWM - m_stParams[m_stWork.byExeParamsIndex].nRightBias, 
                                  STRAIGHT_PWM + m_stParams[m_stWork.byExeParamsIndex].nLeftBias);
            break;

        default:
            /* 想定外のコマンドなので、停止 */
            m_pWalker->stopRightWheel();
            m_pWalker->stopLeftWheel();
            break;
    }
}
