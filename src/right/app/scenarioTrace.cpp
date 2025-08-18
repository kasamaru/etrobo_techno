/**
 * ScenarioTrace.cpp
 */
#include <stdio.h>
#include "scenarioTrace.h"

#define DEFAULT_STRAIGHT_PWM (100) // デフォルトの前進時PWM値
static WORD straight_pwm = DEFAULT_STRAIGHT_PWM; // 設定可能な前進時PWM値


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
    if(byMaxParams > MAX_PARAMS || pstParams == nullptr) {
        /* 最大パラメータ数を超えているか、無効なポインタなのでエラー */
        return;
    }
    for(BYTE i = 0; i < byMaxParams; i++) {
        m_stParams[i] = pstParams[i];
    }
    m_stWork.byMaxExePrams = byMaxParams;
}

/**
 * @brief 実行準備処理
 * @details パラメータインデックスと実行状態を初期化する
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
    // printf("Exe %d\n", static_cast<int>(m_eExecuteState));
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
        m_pWalker->stop(); // タイマーを停止
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
        break;
    case Common::ExecuteState::Execute:
        /* 実行状態 */
        if(m_pTimer->isTimeout()) {
            /* タイムアウトしたので、次の状態へ */
            m_stWork.byExeParamsIndex++;
            if(m_stWork.byExeParamsIndex >= m_stWork.byMaxExePrams) {
                printf("ScenarioEnd\n");
                /* 登録パラメータ実行完了の場合 */
                eNextState = Common::ExecuteState::End;
            } else {
                eNextState = Common::ExecuteState::Init;
            }
        } else {
            /* 実行中なので、実行状態を維持 */
            eNextState = Common::ExecuteState::Execute;
        }
        break;
    case Common::ExecuteState::End:
        /* 実行完了状態 */
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
    m_pTimer->reset(); // タイマーをリセット
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
            m_pWalker->runForward(straight_pwm, straight_pwm);
            break;

        case eCOMMAND_RIGHT:
            /* 右回転 */
            m_pWalker->runForward(straight_pwm + m_stParams[m_stWork.byExeParamsIndex].nRightBias, 
                                  straight_pwm - m_stParams[m_stWork.byExeParamsIndex].nLeftBias);
            break;

        case eCOMMAND_LEFT:
            /* 左回転 */
            m_pWalker->runForward(straight_pwm - m_stParams[m_stWork.byExeParamsIndex].nRightBias, 
                                  straight_pwm + m_stParams[m_stWork.byExeParamsIndex].nLeftBias);
            break;
        case eCOMMAND_STOP:
            /* 停止 */
            m_pWalker->stop();
            break;
        default:
            /* 想定外のコマンドなので、停止 */
            m_pWalker->stopRightWheel();
            m_pWalker->stopLeftWheel();
            break;
    }
}
