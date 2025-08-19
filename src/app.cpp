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
#include "Button.h"
#include "Display.h"
#include "Light.h"


// #include "left/leftMain.h"
using namespace spikeapi;

// デストラクタ問題の回避
// https://github.com/ETrobocon/etroboEV3/wiki/problem_and_coping
// void *__dso_handle=0;

ColorSensor gColorSensor(EPort::PORT_E);
ForceSensor gForceSensor(EPort::PORT_D);
Motor       gLeftWheel(EPort::PORT_B,Motor::EDirection::COUNTERCLOCKWISE,true);
Motor       gRightWheel(EPort::PORT_A,Motor::EDirection::CLOCKWISE,true);
Clock       gClock;
Display     gDisplay;
Light       gLight;

static Starter *gStarter;
static Walker *gWalker;
static LineMonitor *gLineMonitor;
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
    gStarter = new Starter(gForceSensor);
    gWalker = new Walker(gLeftWheel, gRightWheel);
    gTimer = new Timer(gClock);
    gLineMonitor = new LineMonitor(gColorSensor);

    // 初期化完了通知
    if (CURRENT_COURCE == COURCE_RIGHT) {
    s_pRightCource = new RightCource(gWalker, gTimer, gStarter, gLineMonitor);
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
        delete gWalker;
        delete gTimer;
        delete gStarter;
        delete gLineMonitor;
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
    /* ボタン押下 */
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
