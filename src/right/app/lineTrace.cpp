/**
 * @brief LineTrace.cpp
 */

#include "lineTrace.h"

#define DEFAULT_KP (10) /* デフォルトの比例ゲイン(0.01単位のパーセント) */
#define DEFAULT_KI (10) /* デフォルトの積分ゲイン(0.01単位のパーセント) */
#define DEFAULT_KD (10) /* デフォルトの微分ゲイン(0.01単位のパーセント) */
#define PID_TARGET (18)

#define TOP_PWM (30) /* トップPWM値 */
#define RGB_R_THRESHOLD (0) /* RGB値Rしきい値 */
#define RGB_G_THRESHOLD (0) /* RGB値Gしきい値 */
#define RGB_B_THRESHOLD (255) /* RGB値Bしきい値 */

using namespace Common;

LineTrace::LineTrace(Walker* pWalker, LineMonitor* pLineMonitor):
    m_pWalker(pWalker), m_pLineMonitor(pLineMonitor)
{
    m_pidCtrl = new Caculation::PidCtrl();
    m_pidCtrl->setGains(DEFAULT_KP, DEFAULT_KI, DEFAULT_KD);
}

void LineTrace::setColorTh(ST_COLOR_TH* pstColorTh)
{
    memcpy(&m_stColorTh, pstColorTh, sizeof(ST_COLOR_TH));
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
    if(m_pLineMonitor->isLineDetected(m_stColorTh.wR, m_stColorTh.wG, m_stColorTh.wB)) {
        eNextState = Common::ExecuteState::End;
    }

    /* Pid演算タスク */
    SDWORD dwPidResult = m_pidCtrl->Calculate_001(PID_TARGET, m_pLineMonitor->getReflection());
    SWORD nBasePWM;
    /* TODO:ono 昨年は低速モード作成していた */
    nBasePWM = TOP_PWM;
    if(dwPidResult < 0)
    {
        nBasePWM = -nBasePWM;
    }
    SWORD nLeftPWM = nBasePWM + (dwPidResult / 1000); // 1000で割るのは、PID制御のゲインが0.01単位のパーセントなので
    SWORD nRightPWM = nBasePWM - (dwPidResult / 1000);
    printf("LineTrace::executeTrace() called. Left PWM: %d, Right PWM: %d\n", nLeftPWM, nRightPWM);
    m_pWalker->setPWMForLineTrace(nRightPWM, nLeftPWM);

    return eNextState;
}


Common::ExecuteState LineTrace::Run(void) {
    printf("go LineTrace\n");
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
