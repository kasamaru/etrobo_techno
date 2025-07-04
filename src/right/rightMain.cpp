#include <stdio.h>
#include <cassert>

#include "rightMain.h"
#include "app/scenarioTrace.h"

#define ONE_SECOND_MS (1000)

static ST_SCENARIO_TRACE_PARAMS s_stScenarioParams1 ={
    {ScenarioTrace::eCOMMAND_STRAIGHT, (1 * ONE_SECOND_MS), 0, 0 }, /* 直進1秒タスク */
    {ScenarioTrace::eCOMMAND_STRAIGHT, (1 * ONE_SECOND_MS), 0, 0 },
    {ScenarioTrace::eCOMMAND_STRAIGHT, (1 * ONE_SECOND_MS), 0, 0 },
    {ScenarioTrace::eCOMMAND_STRAIGHT, (1 * ONE_SECOND_MS), 0, 0 },
    {ScenarioTrace::eCOMMAND_STRAIGHT, (1 * ONE_SECOND_MS), 0, 0 },
}

static ST_SCENARIO_TRACE_PARAMS s_stScenarioParams2 ={
    {ScenarioTrace::eCOMMAND_STRAIGHT, (1 * ONE_SECOND_MS), 0, 0 }, /* 直進1秒タスク */
    {ScenarioTrace::eCOMMAND_STRAIGHT, (1 * ONE_SECOND_MS), 0, 0 },
    {ScenarioTrace::eCOMMAND_STRAIGHT, (1 * ONE_SECOND_MS), 0, 0 },
    {ScenarioTrace::eCOMMAND_STRAIGHT, (1 * ONE_SECOND_MS), 0, 0 },
    {ScenarioTrace::eCOMMAND_STRAIGHT, (1 * ONE_SECOND_MS), 0, 0 },
}

static ST_SCENARIO_TRACE_PARAMS s_stSmartCarryParams1 ={
    {ScenarioTrace::eCOMMAND_STRAIGHT, (1 * ONE_SECOND_MS), 0, 0 }, /* 直進1秒タスク */
    {ScenarioTrace::eCOMMAND_STRAIGHT, (1 * ONE_SECOND_MS), 0, 0 },
    {ScenarioTrace::eCOMMAND_STRAIGHT, (1 * ONE_SECOND_MS), 0, 0 },
    {ScenarioTrace::eCOMMAND_STRAIGHT, (1 * ONE_SECOND_MS), 0, 0 },
    {ScenarioTrace::eCOMMAND_STRAIGHT, (1 * ONE_SECOND_MS), 0, 0 },
}

void RightCource::RihtCource(void){
    /* TODO: ono 各センサのAPIを固定で呼んで初期化のポート固定 */
    m_eExecuteSeq = Common::TaskSeq::Init;
    m_bIsRunning = true;
    /* TODO: インスタンス作成時にいろいろなクラスを同時定義 */
    /* TODO: app系のクラスには、必要なパラメータをここでセットしに行く、関数を通して */
}

/**
 * @brief タスクシーケンス更新確認
 * @param c_eCurTaskSeq
 * @param c_eCurState
 * @return 次のタスクシーケンス
 */
static Common::TaskSeq RightCource::checkNextTaskSeq(const Common::TaskSeq c_eCurTaskSeq, const Common::ExecuteState c_eCurState)
{
    Common::TaskSeq eNextTaskSeq = c_eCurTaskSeq;
    switch (c_eCurTaskSeq)
    {
        case Common::TaskSeq::Init:
        /* 起動時シーケンス */
            if(eEXECUTE_STATE_END == c_eCurState) {
                eNextTaskSeq = Common::TaskSeq::SCENARIO_TRACE_1;
            }
            break;

        case Common::TaskSeq::SCENARIO_TRACE_1:
            /* スタートしてからラップゲートまでのシナリオトレース */
            if(eEXECUTE_STATE_END == c_eCurState) {
                eNextTaskSeq = Common::TaskSeq::LINE_TRACE_1;
            }
            break;

        case Common::TaskSeq::LINE_TRACE_1:
            /* ラップゲートを超えてからスマートキャリースタート地点までのライントレース */
            if(eEXECUTE_STATE_END == c_eCurState) {
                eNextTaskSeq = Common::TaskSeq::SMART_CARRY;
            }
            break;

        case Common::TaskSeq::SMART_CARRY:
            /* スマートキャリ―スタートから物体をキャリーして円の中に動かすタスク */
            if(eEXECUTE_STATE_END == c_eCurState) {
                eNextTaskSeq = Common::TaskSeq::SCENARIO_TRACE_2;
            }
            break;
        
        case Common::TaskSeq::SCENARIO_TRACE_2:
            /* 円の中からコースラインまで戻るときのシナリオトレース */
            if(eEXECUTE_STATE_END == c_eCurState) {
                eNextTaskSeq = Common::TaskSeq::LINE_TRACE_2;
            }
            break;

        case Common::TaskSeq::LINE_TRACE_2:
            /* コースラインを発見してからゴールを超えるまで */
            if(eEXECUTE_STATE_END == c_eCurState) {
                eNextTaskSeq = Common::TaskSeq::END;
            }
            break;
        
        case Common::TaskSeq::END:
            /* ゴールした状態 */
            this.stopAlwaysTask();
            break;

        default:
            /* ここには来ない */
            assert(false);
            eNextTaskSeq = Common::TaskSeq::END;
            break;
    }
    return eNextTaskSeq;
}

/**
 * @brief 右コース常時タスク
 * @return true:常時タスク実行中 false:常時タスク終了or中断
 */
bool RightCource::StartAlwaysTask(void) {
    /* スタート開始 */
    while(m_bIsRunning) {
        Common::ExecuteState eExeState = Common::ExecuteState::Init;
        switch (m_eExecuteSeq)
        {
            case Common::TaskSeq::Init:
            /* 起動時シーケンス */
            /* TODO: 起動時シーケンスの洗だし */
                eExeState = Common::ExecuteState::End;
                break;

            case Common::TaskSeq::SCENARIO_TRACE_1:
                /* スタートしてからラップゲートまでのシナリオトレース */
                eExeState = checkNextTaskSeq;
                break;

            case Common::TaskSeq::LINE_TRACE_1:
                /* ラップゲートを超えてからスマートキャリースタート地点までのライントレース */
                eExeState = checkNextTaskSeq;
                break;

            case Common::TaskSeq::SMART_CARRY:
                /* スマートキャリ―スタートから物体をキャリーして円の中に動かすタスク */
                eExeState = checkNextTaskSeq;
                break;
            
            case Common::TaskSeq::SCENARIO_TRACE_2:
                /* 円の中からコースラインまで戻るときのシナリオトレース */
                eExeState = checkNextTaskSeq;
                break;

            case Common::TaskSeq::LINE_TRACE_2:
                /* コースラインを発見してからゴールを超えるまで */
                eExeState = checkNextTaskSeq;
                break;
            
            case Common::TaskSeq::END:
                /* ゴールした状態 */
                this.stopAlwaysTask();
                m_bIsRunning = false;
                break;

            default:
                /* ここには来ない */
                assert(false);
                m_eExecuteSeq = Common::TaskSeq::END;
                break;
        }
        m_eExecuteSeq = checkNextTaskSeq(m_eExecuteSeq, eExeState);

    }
    return m_bIsRunning;
}

static void RightCource::stopAlwaysTask(void) {
    /* TODO: ono  */
}