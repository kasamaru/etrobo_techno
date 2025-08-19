/**
 * @file pidCtrl.h
 * @brief PID制御クラスのヘッダファイル
 */

 #pragma once
#include "common.h"

namespace Caculation
{
    class PidCtrl
    {
        #define PID_CTRL_MAX_SIZE (10) // PID制御の最大サイズ
        public:
            PidCtrl(void);
            void setGains(WORD wKp_001, WORD wKi_001, WORD wKd_001);
            SDWORD Calculate_001(WORD wTarget, WORD wCurrent);
            void Reset(void);

        private:
            WORD m_wKp; // 比例ゲイン
            WORD m_wKi; // 積分ゲイン
            WORD m_wKd; // 微分ゲイン
            SWORD m_anPrevError[PID_CTRL_MAX_SIZE]; // 前回の誤差
            SWORD m_nIntegral; // 積分値
            SWORD m_nIntegralSum;
    };
}