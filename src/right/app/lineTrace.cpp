/**
 * @brief LineTrace.cpp
 */

#include "lineTrace.h"

/**
 * TOP_pwm = 50
 * #define DEFAULT_KP (1000) 
 *  #define DEFAULT_KI (30) 
    #define DEFAULT_KD (10)  
    #define PID_TARGET (18)
    がきれいにトレースできる
 */
// #define DEFAULT_KP (900) /* デフォルトの比例ゲイン(0.01単位のパーセント) */
// #define DEFAULT_KI (25) /* デフォルトの積分ゲイン(0.01単位のパーセント) */
// #define DEFAULT_KD (5) /* デフォルトの微分ゲイン(0.01単位のパーセント) */
// #define PID_TARGET (20)
// #define TOP_PWM (70) /* トップPWM値 */
#define DEFAULT_KP (1000) /* デフォルトの比例ゲイン(0.01単位のパーセント) */
#define DEFAULT_KI (30) /* デフォルトの積分ゲイン(0.01単位のパーセント) */
#define DEFAULT_KD (10) /* デフォルトの微分ゲイン(0.01単位のパーセント) */
#define PID_TARGET (18)
#define TOP_PWM (10) /* トップPWM値 */


using namespace Common;

LineTrace::LineTrace(Walker* pWalker, LineMonitor* pLineMonitor):
    m_pWalker(pWalker), m_pLineMonitor(pLineMonitor)
{
    m_pidCtrl = new Caculation::PidCtrl();
    m_pidCtrl->setGains(DEFAULT_KP, DEFAULT_KI, DEFAULT_KD);
    m_stColorTh_Min = {50, 72, 120}; /* デフォルトは青色検知 */
    m_stColorTh_Max = {70, 75, 255};

}

Common::ExecuteState LineTrace::excuteInitWalk(void)
{
    /* シナリオトレース部分 */
    /* TODO: ono ライントレース開始時の固定Runなかったかな？ */
    return Common::ExecuteState::Execute;
}

Common::ExecuteState LineTrace::executeTrace(void)
{
    Common::ExecuteState eNextState = Common::ExecuteState::Execute;
    /* 青色を検知で終了 */
    if(m_pLineMonitor->isLineDetected(m_stColorTh_Max.wR, m_stColorTh_Max.wG, m_stColorTh_Max.wB, m_stColorTh_Min.wR, m_stColorTh_Min.wG, m_stColorTh_Min.wB)) {
        eNextState = Common::ExecuteState::End;
    }

    /* Pid演算タスク */
    SDWORD dwPidResult = m_pidCtrl->Calculate_001(PID_TARGET, m_pLineMonitor->getReflection());

    /* 1000で割るのは、PID制御のゲインが0.01単位のパーセントなので */
    SWORD nLeftPWM = TOP_PWM - (dwPidResult / 1000);
    SWORD nRightPWM = TOP_PWM + (dwPidResult / 1000);

    /* メモ: Pid出力が20000以上だと完全にコース外にいる */
    // printf("Left PWM: %d, Right PWM: %d, PidResult: %d\n", nLeftPWM, nRightPWM, dwPidResult);
    m_pWalker->setPWMForLineTrace(nRightPWM, nLeftPWM);

    return eNextState;
}


Common::ExecuteState LineTrace::Run(void) {
    switch (m_eExecuteState)
    {
    case Common::ExecuteState::Init:
        printf("LineTrace start\n");
        m_eExecuteState = excuteInitWalk();
        break;

    case Common::ExecuteState::Execute:
        m_eExecuteState = executeTrace();
        break;

    case Common::ExecuteState::End:
        m_eExecuteState = Common::ExecuteState::End;
        break;
    
    default:
        break;
    }
    return m_eExecuteState;
}
