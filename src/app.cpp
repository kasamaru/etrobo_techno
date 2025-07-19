/******************************************************************************
 *  app.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/25
 *  Implementation of the Task main_task
 *  Author: Kazuhiro.Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/
#include "app.h"
#include "right/rightMain.h"
#include "compileSW.h"

#include "Light.h"
#include "Button.h"
#include "Display.h"

// #include "left/leftMain.h"
using namespace spikeapi;

// デストラクタ問題の回避
// https://github.com/ETrobocon/etroboEV3/wiki/problem_and_coping
// void *__dso_handle=0;

// ColorSensor gColorSensor(EPort::PORT_E);
// ForceSensor gForceSensor(EPort::PORT_D);
Motor       gLeftWheel(EPort::PORT_B,Motor::EDirection::COUNTERCLOCKWISE,true);
Motor       gRightWheel(EPort::PORT_A,Motor::EDirection::CLOCKWISE,true);
Clock       gClock;

static Walker *gWalker;
// static ColorSense *gColorSense;
// static ForceSense *gForceSense;
static Timer *gTimer;
static RightCource *s_pRightCource;
// static LeftCource *s_pLeftCource;

/**
 * EV3システム生成
 */
static void user_system_create() {
    /* タッチセンサの初期化に2msのdelayがあるので待機 */
    tslp_tsk(2U * 1000U);

    /* API関連の初期化を行う */
    gWalker = new Walker(gLeftWheel, gRightWheel);
    gTimer = new Timer(gClock);

    // 初期化完了通知
    if (CURRENT_COURCE == COURCE_RIGHT) {
        s_pRightCource = new RightCource(gWalker, gTimer);
    } else {
        // s_pLeftCource = new LeftCource();
    }

}

/**
 * EV3システム破棄
 */
static void user_system_destroy() {
    if (CURRENT_COURCE == COURCE_RIGHT) {
        s_pRightCource->StopAlwaysTask();
        delete s_pRightCource;
    } else {
        // s_pLeftCource->stopAlwaysTask();
        // delete s_pLeftCource;
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
void tracer_task(intptr_t exinf) {
    Button button;
    if (button.isLeftPressed()) {
        wup_tsk(MAIN_TASK);  // バックボタン押下
    } else {
        if (CURRENT_COURCE == COURCE_RIGHT) {
            s_pRightCource->StartAlwaysTask();
        } else {
            // s_pLeftCource->startAlwaysTask();
        }
    }

    ext_tsk();
}
