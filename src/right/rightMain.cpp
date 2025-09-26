/**
 * @file rightMain.cpp
 */

#include "rightMain.h"
#include "common/common.h"
#define LEFT_COURSE
#ifndef LEFT_COURSE
#define RIGHT_COURSE
#endif

#define ONE_SECOND_MS (1000)
#define ONE_MINUTES (60)
#define PARAMS1_MAX_NUM (20)
#define PARAMS2_MAX_NUM (8)
#define PARAMS3_MAX_NUM (5)

#define HIGH_SPEED_MODE_DURATION_1 (6000 * ONE_SECOND_MS) /* ライントレース1高速モード継続時間 */
#define HIGH_SPEED_MODE_DURATION_2 (6000 * ONE_SECOND_MS) /* ライントレース2高速モード継続時間 */

#ifdef LEFT_COURSE
static ScenarioTrace::ST_SCENARIO_TRACE_PARAMS s_astScenarioParams1[PARAMS1_MAX_NUM] ={
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, 100 * ONE_SECOND_MS, 10, 14 },  
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, 100 * ONE_SECOND_MS, 20, 24 },  
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, 100 * ONE_SECOND_MS, 30, 34 },  
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, 100 * ONE_SECOND_MS, 40, 44 },  
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, 100 * ONE_SECOND_MS, 50, 54 },  
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, 100 * ONE_SECOND_MS, 60, 64 },  
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, 100 * ONE_SECOND_MS, 70, 74 },  
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, 100 * ONE_SECOND_MS, 80, 84 },  
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, 100 * ONE_SECOND_MS, 90, 94 },  
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (6700 * ONE_SECOND_MS), 100, 100 },
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (580 * ONE_SECOND_MS), 30, 90 },/* タイムつめるならここ */
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (490 * ONE_SECOND_MS), 50, 80 },
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (490 * ONE_SECOND_MS), 70, 75 },
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (490 * ONE_SECOND_MS), 90, 80 },
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (1100 * ONE_SECOND_MS), 100, 100 },
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (800 * ONE_SECOND_MS), 100, 100 },
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (500 * ONE_SECOND_MS), 30, 90 },
    /* ここまででターン終了 */
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (500 * ONE_SECOND_MS), 50, 70 },
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (2000 * ONE_SECOND_MS), 70, 70 },
    
};

static ScenarioTrace::ST_SCENARIO_TRACE_PARAMS s_astScenarioParams2[PARAMS3_MAX_NUM] = {
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (11000 * ONE_SECOND_MS), -30, -30 },
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (7200 * ONE_SECOND_MS), 10, 0 },
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (850 * ONE_SECOND_MS), 30, 30 },
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (200 * ONE_SECOND_MS), 0, 10 },
};

static ScenarioTrace::ST_SCENARIO_TRACE_PARAMS s_astSmartCarryParams1[PARAMS2_MAX_NUM] ={
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (6900 * ONE_SECOND_MS), 0, 10 }, /* 直進1msタスク */
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (100 * ONE_SECOND_MS), 10, 13 },
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (200 * ONE_SECOND_MS), 20, 23 },
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (220 * ONE_SECOND_MS), 30, 33 },
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (5500 * ONE_SECOND_MS), 30, 30 },
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (5050 * ONE_SECOND_MS), 30, 30 },
};

#else
static ScenarioTrace::ST_SCENARIO_TRACE_PARAMS s_astScenarioParams1[PARAMS1_MAX_NUM] ={
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, 100 * ONE_SECOND_MS, 14, 10 },  
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, 100 * ONE_SECOND_MS, 24, 20 },  
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, 100 * ONE_SECOND_MS, 34, 30 },  
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, 100 * ONE_SECOND_MS, 44, 40 },  
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, 100 * ONE_SECOND_MS, 54, 50 },  
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, 100 * ONE_SECOND_MS, 64, 60 },  
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, 100 * ONE_SECOND_MS, 74, 70 },  
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, 100 * ONE_SECOND_MS, 84, 80 },  
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, 100 * ONE_SECOND_MS, 94, 90 },  
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (6700 * ONE_SECOND_MS), 100, 100 },
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (580 * ONE_SECOND_MS), 90, 30 },/* タイムつめるならここ */
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (490 * ONE_SECOND_MS), 80, 50 },
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (490 * ONE_SECOND_MS), 75, 70 },
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (490 * ONE_SECOND_MS), 80, 90 },
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (1150 * ONE_SECOND_MS), 100, 100 },
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (800 * ONE_SECOND_MS), 100, 100 },
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (500 * ONE_SECOND_MS), 90, 30 },
    /* ここまででターン終了 */
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (500 * ONE_SECOND_MS), 70, 50 },
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (2200 * ONE_SECOND_MS), 70, 70 },
};

static ScenarioTrace::ST_SCENARIO_TRACE_PARAMS s_astScenarioParams2[PARAMS3_MAX_NUM] = {
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (11000 * ONE_SECOND_MS), -30, -30 },
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (7450 * ONE_SECOND_MS), 0, 10 },
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (850 * ONE_SECOND_MS), 30, 30 },
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (200 * ONE_SECOND_MS), 10, 0 },
};

static ScenarioTrace::ST_SCENARIO_TRACE_PARAMS s_astSmartCarryParams1[PARAMS2_MAX_NUM] ={
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (7150 * ONE_SECOND_MS), 10, 0 }, /* 直進1msタスク */
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (220 * ONE_SECOND_MS), 14, 10 },
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (200 * ONE_SECOND_MS), 24, 20 },
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (255 * ONE_SECOND_MS), 34, 30 },
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (5500 * ONE_SECOND_MS), 30, 30 },
    {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (5050 * ONE_SECOND_MS), 30, 30 },
};
#endif

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
    switch (c_eCurTaskSeq)
    {
        case Common::TaskSeq::Init:
        /* 起動時シーケンス */
            if(Common::ExecuteState::End == c_eCurState) {
                /* 次シーケンスのパラメータ渡し */
                printf("ScenarioTrace 1 Start.\n");
                scenarioTraceInit(s_astScenarioParams1, PARAMS1_MAX_NUM);
                eNextTaskSeq = Common::TaskSeq::SCENARIO_TRACE_1;
            }
            break;

        case Common::TaskSeq::SCENARIO_TRACE_1:
            /* スタートしてからラップゲートまでのシナリオトレース */
            if(Common::ExecuteState::End == c_eCurState) {
                /* シナリオトレース1をエンドしている */
#ifdef LEFT_COURSE
                m_pLineTrace->Init(0);
#else
                m_pLineTrace->Init(1);
#endif
                m_pLineTrace->SetHighSpeedModeDeadLine(HIGH_SPEED_MODE_DURATION_1);
                eNextTaskSeq = Common::TaskSeq::LINE_TRACE_1;
            }
            break;

        case Common::TaskSeq::LINE_TRACE_1:
            /* ラップゲートを超えてからスマートキャリースタート地点までのライントレース */
            if(Common::ExecuteState::End == c_eCurState) {
                printf("Start Smart Carry\n");
                scenarioTraceInit(s_astSmartCarryParams1, PARAMS2_MAX_NUM);
                eNextTaskSeq = Common::TaskSeq::SMART_CARRY;
            }
            break;

        case Common::TaskSeq::SMART_CARRY:
            /* スマートキャリ―スタートから物体をキャリーして円の中に動かすタスク */
            if(Common::ExecuteState::End == c_eCurState) {
                printf("go back to line\n");
                scenarioTraceInit(s_astScenarioParams2, PARAMS3_MAX_NUM);
                eNextTaskSeq = Common::TaskSeq::SCENARIO_TRACE_2;
            }
            break;
        
        case Common::TaskSeq::SCENARIO_TRACE_2:
            /* 円の中からコースラインまで戻るときのシナリオトレース */
            if(Common::ExecuteState::End == c_eCurState) {
                printf("last part line trace\n");
#ifdef LEFT_COURSE
                m_pLineTrace->Init(0);
#else
                m_pLineTrace->Init(1);
#endif
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
    m_bIsRunning = false;
    m_eExecuteSeq = Common::TaskSeq::END;
    m_pWalker->stop();
    printf("RightCource: Always Task Stop\n");
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
