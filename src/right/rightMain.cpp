#include <stdio.h>
#include <cassert>

#include "rightMain.h"

void RightCource::RihtCource(void){
    /* TODO: ono 各センサのAPIを固定で呼んで初期化のポート固定 */
    s_eExecuteSeq = eSEQ_INIT;
    s_bIsRunning = true;
}

/**
 * 毎周期タスクのエントリーポイントの作成
 * 内部は、whileの中に状態遷移を入れる形
 */

 /**
  * 毎周期タスクのエンドポイントの作成
  * ークラスのデリートする
  */

  /**
   * @brief タスクシーケンス更新確認
   * @param c_eCurTaskSeq
   * @param c_eCurState
   * @return 次のタスクシーケンス
   */
static E_ALL_TASK_SEQ RightCource::checkNextTaskSeq(const E_ALL_TASK_SEQ c_eCurTaskSeq, const E_EXECUTE_STATE c_eCurState)
{
    E_ALL_TASK_SEQ eNextTaskSeq = c_eCurTaskSeq;
    switch (c_eCurTaskSeq)
    {
        case eSEQ_INIT:
        /* 起動時シーケンス */
            if(eEXECUTE_STATE_END == c_eCurState) {
                eNextTaskSeq = eSEQ_SCENARIO_TRACE_1;
            }
            break;

        case eSEQ_SCENARIO_TRACE_1:
            /* スタートしてからラップゲートまでのシナリオトレース */
            if(eEXECUTE_STATE_END == c_eCurState) {
                eNextTaskSeq = eSEQ_LINE_TRACE_1;
            }
            break;

        case eSEQ_LINE_TRACE_1:
            /* ラップゲートを超えてからスマートキャリースタート地点までのライントレース */
            if(eEXECUTE_STATE_END == c_eCurState) {
                eNextTaskSeq = eSEQ_SMART_CARRY;
            }
            break;

        case eSEQ_SMART_CARRY:
            /* スマートキャリ―スタートから物体をキャリーして円の中に動かすタスク */
            if(eEXECUTE_STATE_END == c_eCurState) {
                eNextTaskSeq = eSEQ_SCENARIO_TRACE_2;
            }
            break;
        
        case eSEQ_SCENARIO_TRACE_2:
            /* 円の中からコースラインまで戻るときのシナリオトレース */
            if(eEXECUTE_STATE_END == c_eCurState) {
                eNextTaskSeq = eSEQ_LINE_TRACE_2;
            }
            break;

        case eSEQ_LINE_TRACE_2:
            /* コースラインを発見してからゴールを超えるまで */
            if(eEXECUTE_STATE_END == c_eCurState) {
                eNextTaskSeq = eSEQ_END;
            }
            break;
        
        case eSEQ_END:
            /* ゴールした状態 */
            this.stopAlwaysTask();
            break;

        default:
            /* ここには来ない */
            assert(false);
            eNextTaskSeq = eSEQ_END;
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

    while(s_bIsRunning) {
        E_EXECUTE_STATE eExeState = eEXECUTE_STATE_INIT;
        switch (s_eExecuteSeq)
        {
            case eSEQ_INIT:
            /* 起動時シーケンス */
            /* TODO: 起動時シーケンスの洗だし */
                eExeState = eEXECUTE_STATE_END;
                break;

            case eSEQ_SCENARIO_TRACE_1:
                /* スタートしてからラップゲートまでのシナリオトレース */
                eExeState = ;
                break;

            case eSEQ_LINE_TRACE_1:
                /* ラップゲートを超えてからスマートキャリースタート地点までのライントレース */
                eExeState = ;
                break;

            case eSEQ_SMART_CARRY:
                /* スマートキャリ―スタートから物体をキャリーして円の中に動かすタスク */
                eExeState = ;
                break;
            
            case eSEQ_SCENARIO_TRACE_2:
                /* 円の中からコースラインまで戻るときのシナリオトレース */
                eExeState = ;
                break;

            case eSEQ_LINE_TRACE_2:
                /* コースラインを発見してからゴールを超えるまで */
                eExeState = ;
                break;
            
            case eSEQ_END:
                /* ゴールした状態 */
                this.stopAlwaysTask();
                s_bIsRunning = false;
                break;

            default:
                /* ここには来ない */
                assert(false);
                s_eExecuteSeq = eSEQ_END;
                break;
        }
        s_eExecuteSeq = checkNextTaskSeq(s_eExecuteSeq, eExeState);

    }
    return s_bIsRunning;
}

static void RightCource::stopAlwaysTask(void) {
    /* TODO: ono  */
}