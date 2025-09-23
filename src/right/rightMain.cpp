/**
 * @file rightMain.cpp
 */

#include "rightMain.h"

#include "common/common.h"
#include "common/paramStorage.h"


#define ONE_SECOND_MS (1000)
#define ONE_MINUTES (60)
#define HIGH_SPEED_MODE_DURATION_1 (5000 * ONE_SECOND_MS) /* ライントレース1高速モード継続時間 */
#define HIGH_SPEED_MODE_DURATION_2 (2000 * ONE_SECOND_MS) /* ライントレース2高速モード継続時間 */

// パラメータストレージインスタンス生成（右コース用）
static ParamStorage s_paramStorage;

RightCource::RightCource(Walker *pWalker, Timer *pTimer, Starter *pStarter, LineMonitor *pLineMonitor):
    m_pWalker(pWalker),
    m_pTimer(pTimer),
    m_pLineMonitor(pLineMonitor),
    m_pStarter(pStarter)
{
    /* TODO: ono 各センサのAPIを固定で呼んで初期化のポート固定 */
    m_eExecuteSeq = Common::TaskSeq::Init;
    m_bIsRunning = false;
    m_pScenarioTrace = new ScenarioTrace(m_pWalker, m_pTimer); /* シナリオトレースの最大パラメータ数は5 */
    m_pLineTrace = new LineTrace(m_pWalker, m_pLineMonitor, m_pTimer); /* ライントレースの最大パラメータ数は5 */
    /* TODO: インスタンス作成時にいろいろなクラスを同時定義 */
    /* TODO: app系のクラスには、必要なパラメータをここでセットしに行く、関数を通して */
}

/**
 * @brief タスクシーケンス更新確認
 * @param c_eCurTaskSeq
 * @param c_eCurState
 * @return 次のタスクシーケンス
 */
Common::TaskSeq RightCource::checkNextTaskSeq(const Common::TaskSeq c_eCurTaskSeq, const Common::ExecuteState c_eCurState)
{
    Common::TaskSeq eNextTaskSeq = c_eCurTaskSeq;
    // 右コース用パラメータ取得用
    const ParamSide paramSide = ParamSide::RIGHT;
    switch (c_eCurTaskSeq)
    {
        case Common::TaskSeq::Init:
        /* 起動時シーケンス */
            if(Common::ExecuteState::End == c_eCurState) {
                printf("ScenarioTrace 1 Start.\n");
                scenarioTraceInit(
                    const_cast<ScenarioTrace::ST_SCENARIO_TRACE_PARAMS*>(s_paramStorage.getParams(paramSide, 0).data()),
                    s_paramStorage.getParamsCount(paramSide, 0)
                );
                eNextTaskSeq = Common::TaskSeq::SCENARIO_TRACE_1;
            }
            break;

        case Common::TaskSeq::SCENARIO_TRACE_1:
            /* スタートしてからラップゲートまでのシナリオトレース */
            if(Common::ExecuteState::End == c_eCurState) {
                /* シナリオトレース1をエンドしている */
                m_pLineTrace->SetHighSpeedModeDeadLine(HIGH_SPEED_MODE_DURATION_1);
                eNextTaskSeq = Common::TaskSeq::LINE_TRACE_1;
            }
            break;

        case Common::TaskSeq::LINE_TRACE_1:
            /* ラップゲートを超えてからスマートキャリースタート地点までのライントレース */
            if(Common::ExecuteState::End == c_eCurState) {
                printf("Start Smart Carry\n");
                scenarioTraceInit(
                    const_cast<ScenarioTrace::ST_SCENARIO_TRACE_PARAMS*>(s_paramStorage.getParams(paramSide, 1).data()),
                    s_paramStorage.getParamsCount(paramSide, 1)
                );
                eNextTaskSeq = Common::TaskSeq::SMART_CARRY;
            }
            break;

        case Common::TaskSeq::SMART_CARRY:
            /* スマートキャリ―スタートから物体をキャリーして円の中に動かすタスク */
            if(Common::ExecuteState::End == c_eCurState) {
                printf("go back to line\n");
                scenarioTraceInit(
                    const_cast<ScenarioTrace::ST_SCENARIO_TRACE_PARAMS*>(s_paramStorage.getParams(paramSide, 2).data()),
                    s_paramStorage.getParamsCount(paramSide, 2)
                );
                eNextTaskSeq = Common::TaskSeq::SCENARIO_TRACE_2;
            }
            break;
        
        case Common::TaskSeq::SCENARIO_TRACE_2:
            /* 円の中からコースラインまで戻るときのシナリオトレース */
            if(Common::ExecuteState::End == c_eCurState) {
                printf("last spart line trace\n");
                m_pLineTrace->SetHighSpeedModeDeadLine(HIGH_SPEED_MODE_DURATION_2);
                eNextTaskSeq = Common::TaskSeq::LINE_TRACE_2;
            }
            break;

        case Common::TaskSeq::LINE_TRACE_2:
            /* コースラインを発見してからゴールを超えるまで */
            if(Common::ExecuteState::End == c_eCurState) {
                printf("GOAL!!!\n");
                eNextTaskSeq = Common::TaskSeq::END;
            }
            break;
        
        case Common::TaskSeq::END:
            /* ゴールした状態 */
            this->StopAlwaysTask();
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
    if ((!m_pStarter->isPushed()) && (!m_bIsRunning)) {
        /* スタートボタンが押されたので、常時タスクを開始 */
        // printf("button is pushed, starting always task.\n");
        return false; // スタートボタンが押されていないので、常時タスクを開始しない
    }
    /* スタート開始 */
    Common::ExecuteState eExeState = Common::ExecuteState::Init;
    switch (m_eExecuteSeq)
    {
        case Common::TaskSeq::Init:
            /* 起動時シーケンス */
            eExeState = startedCompare();
            break;

        case Common::TaskSeq::SCENARIO_TRACE_1:
            /* スタートしてからラップゲートまでのシナリオトレース */
            /* ここまでにシナリオトレース1をエンドしている */
            eExeState = m_pScenarioTrace->Run();
            break;

        case Common::TaskSeq::LINE_TRACE_1:
            /* ラップゲートを超えてからスマートキャリースタート地点までのライントレース */
            eExeState = m_pLineTrace->Run();
            break;

        case Common::TaskSeq::SMART_CARRY:
            /* スマートキャリ―スタートから物体をキャリーして円の中に動かすタスク */
            eExeState = m_pScenarioTrace->Run();
            break;
        
        case Common::TaskSeq::SCENARIO_TRACE_2:
            /* 円の中からコースラインまで戻るときのシナリオトレース */
            eExeState = m_pScenarioTrace->Run();
            break;

        case Common::TaskSeq::LINE_TRACE_2:
            /* コースラインを発見してからゴールを超えるまで */
            eExeState = m_pLineTrace->Run();
            break;
        
        case Common::TaskSeq::END:
            /* ゴールした状態 */
            StopAlwaysTask();
            break;

        default:
            /* ここには来ない */
            assert(false);
            m_eExecuteSeq = Common::TaskSeq::END;
            break;
    }
    // printf("Current TaskSeq: %d, ExecuteState: %d\n", static_cast<int>(m_eExecuteSeq), static_cast<int>(eExeState));
    m_eExecuteSeq = checkNextTaskSeq(m_eExecuteSeq, eExeState);
    return m_bIsRunning;
}

void RightCource::StopAlwaysTask(void) {
    /* TODO: ono  */
}

Common::ExecuteState RightCource::startedCompare(void) {
    m_bIsRunning = true;
    return Common::ExecuteState::End;
}

/**
 * @brief シナリオトレース開始前の初期化処理
 * @param pstParams パラメータ
 * @param byMaxParams 最大パラメータ数
 */
void RightCource::scenarioTraceInit(ScenarioTrace::ST_SCENARIO_TRACE_PARAMS* pstParams, const BYTE byMaxParams)
{
    /* シナリオトレースの初期化 */
    m_pScenarioTrace->SetParams(pstParams, byMaxParams);
    /* シナリオトレースの初期化 */
    m_pScenarioTrace->RunReady();
}
