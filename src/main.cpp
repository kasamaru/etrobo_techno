/******************************************************************************
 *  app.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/25
 *  Implementation of the Task main_task
 *  Author: Kazuhiro.Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compileSW.h"
#include "right/rightMain.h"
#include "left/leftMain.h"

// デストラクタ問題の回避
// https://github.com/ETrobocon/etroboEV3/wiki/problem_and_coping
void *__dso_handle=0;

static RightCource *s_pRightCource;
static LeftCource *s_pLeftCource;

/**
 * EV3システム生成
 */
static void user_system_create() {

    // 初期化完了通知
    if (CURRENT_COURCE == COURCE_RIGHT) {
        s_pRightCource = new RightCource();
    } else {
        s_pLeftCource = new LeftCource();
    }
    ev3_led_set_color(LED_ORANGE);
}

/**
 * EV3システム破棄
 */
static void user_system_destroy() {
    if (CURRENT_COURCE == COURCE_RIGHT) {
        s_pRightCource->stopAlwaysTask();
        delete s_pRightCource;
    } else {
        s_pLeftCource->stopAlwaysTask();
        delete s_pLeftCource;
    }
}

/**
 * メインタスク
 */
void mainTask(intptr_t unused) {
    user_system_create();  // センサやモータの初期化処理
	printf("**** after user_system_create()\n");
	
    // 周期ハンドラ開始
    sta_cyc(CYC_TRACER);

    slp_tsk();  // バックボタンが押されるまで待つ
    /* TODO: ono システムエンドは、競技制限時間固定にするのと終わったことのふたつ */

    // 周期ハンドラ停止
    stp_cyc(CYC_TRACER);

    user_system_destroy();  // 終了処理

    ext_tsk();
}

/**
 * ライントレースタスク
 */
void courceTaskEntry(intptr_t exinf) {
    if (ev3_button_is_pressed(BACK_BUTTON)) {
    	printf("**** ev3_button_is_pressed(BACK_BUTTON)\n");
        wup_tsk(MAIN_TASK);  // バックボタン押下
    } else {
        if (CURRENT_COURCE == COURCE_RIGHT) {
            s_pRightCource->startAlwaysTask();
        } else {
            s_pLeftCource->startAlwaysTask();
        }
    }

    ext_tsk();
}
