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
// #define DEFAULT_KD (6) /* デフォルトの微分ゲイン(0.01単位のパーセント) */
// #define PID_TARGET (18)
// #define TOP_PWM (70) /* トップPWM値 */
#define DEFAULT_KP (900) /* デフォルトの比例ゲイン(0.01単位のパーセント) */
#define DEFAULT_KI (25) /* デフォルトの積分ゲイン(0.01単位のパーセント) */
#define DEFAULT_KD (5) /* デフォルトの微分ゲイン(0.01単位のパーセント) */
#define PID_TARGET (20)
#define HIGH_MODE_PWM (20) /* 高速モードPWM値 */
#define LOW_MODE_PWM (10) /* 低速モードPWM値 */


using namespace Common;

LineTrace::LineTrace(Walker* pWalker, LineMonitor* pLineMonitor, Timer* pTimer) :
    m_pWalker(pWalker), m_pLineMonitor(pLineMonitor), m_pTimer(pTimer)
{
    m_pidCtrl = new Caculation::PidCtrl();
    m_pidCtrl->setGains(DEFAULT_KP, DEFAULT_KI, DEFAULT_KD);
    m_stColorTh_Min = {27, 30, 110}; /* デフォルトは青色検知 */
    m_stColorTh_Max = {100, 100, 255};

}

void LineTrace::Init(WORD wCourse) {
    m_eExecuteState = Common::ExecuteState::Init;
    m_bHighModeEnd = false;
    m_dwDuration = 0;
    this->wCourse = wCourse;
    m_pTimer->stop();
    m_pTimer->reset();
    m_pidCtrl->Reset();
}

void LineTrace::SetHighSpeedModeDeadLine(DWORD dwDuration) {
    m_dwDuration = dwDuration;
    m_bHighModeEnd = false;
}

Common::ExecuteState LineTrace::excuteInitWalk(void)
{
    /* ライントレース開始後すぐに高速モードに遷移する */
    m_pTimer->reset();
    m_pTimer->start(m_dwDuration);
    return Common::ExecuteState::Execute;
}

Common::ExecuteState LineTrace::excuteHighSpeedMode(void)
{
    /* Pid演算タスク */
    SDWORD dwPidResult = m_pidCtrl->Calculate_001(PID_TARGET, m_pLineMonitor->getReflection());
    SDWORD nLeftPWM;
    SDWORD nRightPWM;
    /* 1000で割るのは、PID制御のゲインが0.01単位のパーセントなので */
    if(wCourse == 0) { // 左コース
        nLeftPWM = HIGH_MODE_PWM - (dwPidResult / 1000);
        nRightPWM = HIGH_MODE_PWM + (dwPidResult / 1000);
    } else { // 右コース
        nLeftPWM = HIGH_MODE_PWM - (dwPidResult / 1000);
        nRightPWM = HIGH_MODE_PWM + (dwPidResult / 1000);
    }
    m_pWalker->setPWMForLineTrace(nRightPWM, nLeftPWM);
    return Common::ExecuteState::Execute;
}

Common::ExecuteState LineTrace::excuteLowSpeedMode(void)
{
    Common::ExecuteState eNextState = Common::ExecuteState::Execute;
    if(m_pLineMonitor->isLineDetected(m_stColorTh_Max.wR, m_stColorTh_Max.wG, m_stColorTh_Max.wB, m_stColorTh_Min.wR, m_stColorTh_Min.wG, m_stColorTh_Min.wB)) {
        eNextState = Common::ExecuteState::End;
    }
    /* Pid演算タスク */
    SDWORD dwPidResult = m_pidCtrl->Calculate_001(PID_TARGET, m_pLineMonitor->getReflection());
    SDWORD nLeftPWM;
    SDWORD nRightPWM;

    /* 1000で割るのは、PID制御のゲインが0.01単位のパーセントなので */
    if(wCourse == 0) { // 左コース
        nLeftPWM = LOW_MODE_PWM - (dwPidResult / 1000);
        nRightPWM = LOW_MODE_PWM + (dwPidResult / 1000);
        if(nRightPWM < 9) {
            nRightPWM = 10;
            nLeftPWM = 10;
        }
    } else {
        nLeftPWM = LOW_MODE_PWM - (dwPidResult / 1000);
        nRightPWM = LOW_MODE_PWM + (dwPidResult / 1000);
        if(nRightPWM < 9) {
            nRightPWM = 10;
            nLeftPWM = 10;
        }
    }
    m_pWalker->setPWMForLineTrace(nRightPWM, nLeftPWM);
    return eNextState;
}

Common::ExecuteState LineTrace::executeTrace(void)
{
    Common::ExecuteState eNextState = Common::ExecuteState::Execute;
    if(!m_bHighModeEnd) {
        if(m_pTimer->isTimeout()) {
            /* 高速モード継続時間を超えた */
            m_bHighModeEnd = true;
        }
    }
    if(!m_bHighModeEnd) {
        /* 高速モード */
        eNextState = excuteHighSpeedMode();
    } else {
        /* 低速モード */
        eNextState = excuteLowSpeedMode();
    }
    return eNextState;
}


Common::ExecuteState LineTrace::Run(void) {
    switch (m_eExecuteState)
    {
    case Common::ExecuteState::Init:
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
