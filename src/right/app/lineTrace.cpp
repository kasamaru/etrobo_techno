/**
 * @brief LineTrace.cpp
 */

#include "lineTrace.h"

using namespace Common;

void LineTrace::LineTrace(Walker* pWalker, ColorSense* pColorSense, Timer* pTimer):
    m_pWalker(pWalker), m_pColorSense(pColorSense), m_pTimer(pTimer)
{
    /* TODO: 初期化類の追加 */
}

void LineTrace::setColorTh(ST_COLOR_TH* pstColorTh)
{
    memcpy(m_stColorTh, pstColorTh, (sizeof(ST_COLOR_TH) / sizeof(WORD)));
}

Common::ExecuteState LineTrace::executeInit(void)
{
    return Common::ExecuteState::Execute;
}

Common::ExecuteState LineTrace::executeTrace(void)
{
    Common::ExecuteState eNextState = Common::ExecuteState::Execute;
    /* TODO: ライントレースタスク昨日実装 */
    return eNextState;
}


Common::ExecuteState LineTrace::Run(void) {
    switch (m_eExecuteState)
    {
    case Common::ExecuteState::Init:
        m_eExecuteState = executeInit();
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
}
