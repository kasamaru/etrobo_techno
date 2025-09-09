/**
 * @file pidCtrl.cpp
 */
#include "pidCtrl.h"
#include "common/common.h"
#include <stdio.h>

using namespace Caculation;

PidCtrl::PidCtrl(void)
{
    m_nIntegral = 0;
    for (int i = 0; i < PID_CTRL_MAX_SIZE; ++i) {
        m_anPrevError[i] = 0;
    }
}

void PidCtrl::setGains(WORD wKp_001, WORD wKi_001, WORD wKd_001)
{
    m_wKp = wKp_001;
    m_wKi = wKi_001;
    m_wKd = wKd_001;
}

SDWORD PidCtrl::Calculate_001(WORD wTarget, WORD wCurrent)
{
    SWORD nError = wCurrent - wTarget; // 誤差計算
    /* PID_CTRL_MAX_SIZEで積分する */

    m_nIntegralSum += nError; /* 誤差合計 */
    m_nIntegralSum -= m_anPrevError[PID_CTRL_MAX_SIZE - 1];
    m_nIntegral = m_nIntegralSum;

    // 微分値計算
    SWORD nDerivative = 0;
    if (m_anPrevError[0] != 0) {
        nDerivative = nError - m_anPrevError[0];
    }

    // printf("PidCtrl::Calculate_001() called. Target: %d, Current: %d, Error: %d, Integral: %d, Derivative: %d\n",
    //        wTarget, wCurrent, nError, m_nIntegral, nDerivative);
    // PID制御計算
    SDWORD lOutput = (m_wKp * nError) + (m_wKi * m_nIntegral) + (m_wKd * nDerivative);

    // 前回の誤差を更新
    for (int i = PID_CTRL_MAX_SIZE - 1; i > 0; --i) {
        m_anPrevError[i] = m_anPrevError[i - 1];
    }
    m_anPrevError[0] = nError;

    return lOutput;
}


void PidCtrl::Reset(void)
{
    m_nIntegral = 0; // 積分値リセット
    for (int i = 0; i < PID_CTRL_MAX_SIZE; ++i) {
        m_anPrevError[i] = 0; // 前回の誤差リセット
    }
}