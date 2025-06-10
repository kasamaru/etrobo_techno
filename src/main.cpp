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

#include "common/mid/Walker.h"
#include "app.h"

// デストラクタ問題の回避
// https://github.com/ETrobocon/etroboEV3/wiki/problem_and_coping
void *__dso_handle=0;

// using宣言
using ev3api::ColorSensor;
using ev3api::GyroSensor;
using ev3api::SonarSensor;
using ev3api::TouchSensor;
using ev3api::Motor;
using ev3api::Clock;

// Device objects
// オブジェクトを静的に確保する
ColorSensor gColorSensor(PORT_2);//ColorSensor:PORT_2
TouchSensor gTouchSensor(PORT_1);//TouchSensor:PORT_1
Motor       gLeftWheel(PORT_C);
Motor       gRightWheel(PORT_B);
Motor       gTailMotor(PORT_D);

#ifdef SAVE_LOG
SonarSensor gSonarSensor(PORT_3);//SonarSensor:PORT_3
GyroSensor  gGyroSensor(PORT_4); //GyroSensor:PORT_4
Clock       gClock;
#endif//SAVE_LOG

// オブジェクトの定義
static Walker          *gWalker;
static Starter         *gStarter;
static ColorMonitor    *gColorMonitor;
static PidControl      *gPidControl;

static SelectPlayer    *gSelectPlayer;
static LineWalker      *gLineWalker;
static TimerWalker     *gTimerWalker;
static ScenarioWalker  *gScenarioWalker;

#ifdef SAVE_LOG
static SonarMonitor    *gSonarMonitor;
static GyroMonitor     *gGyroMonitor;
#endif//SAVE_LOG

/**
 * EV3システム生成
 */
static void user_system_create() {
    // [TODO] タッチセンサの初期化に2msのdelayがあるため、ここで待つ
    tslp_tsk(2U * 1000U);

    // オブジェクトの作成
    gWalker          = new Walker(gLeftWheel, gRightWheel,gTailMotor);
    gStarter         = new Starter(gTouchSensor);
    gColorMonitor    = new ColorMonitor(gColorSensor);
#ifdef SAVE_LOG
    gGyroMonitor     = new GyroMonitor(gGyroSensor);
    gSonarMonitor    = new SonarMonitor(gSonarSensor);
#endif//SAVE_LOG
/* ここまではcommonの定義 */
    gPidControl      = new PidControl();
    gLineWalker      = new LineWalker(gWalker, gPidControl);
    gTimerWalker     = new TimerWalker(gWalker);
    gScenarioWalker  = new ScenarioWalker(gWalker);
    gSelectPlayer    = new SelectPlayer(gLineWalker,
                                        gTimerWalker,
                                        gScenarioWalker,
                                        gStarter,
                                        gColorMonitor,
                                        gWalker,
                                        gPidControl
#ifdef SAVE_LOG
                                        ,gClock
                                        ,gGyroMonitor
                                        ,gSonarMonitor
#endif//SAVE_LOG
    );

    // 初期化完了通知
    ev3_led_set_color(LED_ORANGE);
}

/**
 * EV3システム破棄
 */
static void user_system_destroy() {
    gLeftWheel.reset();
    gRightWheel.reset();
	gTailMotor.reset();

    delete gWalker;
    delete gStarter;
    delete gColorMonitor;
#ifdef SAVE_LOG
    delete gGyroMonitor;
    delete gSonarMonitor;
#endif//SAVE_LOG
/* ここまでは、commonの定義 */
    delete gPidControl;

    delete gSelectPlayer;
    delete gLineWalker;
    delete gTimerWalker;
    delete gScenarioWalker;
}

/**
 * メインタスク
 */
void main_task(intptr_t unused) {
    user_system_create();  // センサやモータの初期化処理
	printf("**** after user_system_create()\n");
	
    // 周期ハンドラ開始
    sta_cyc(CYC_TRACER);

    slp_tsk();  // バックボタンが押されるまで待つ

    // 周期ハンドラ停止
    stp_cyc(CYC_TRACER);

    user_system_destroy();  // 終了処理

    ext_tsk();
}

/**
 * ライントレースタスク
 */
void tracer_task(intptr_t exinf) {
    if (ev3_button_is_pressed(BACK_BUTTON)) {
    	printf("**** ev3_button_is_pressed(BACK_BUTTON)\n");
        wup_tsk(MAIN_TASK);  // バックボタン押下
    } else {
        gSelectPlayer->run();  // 走行
    }

    ext_tsk();
}
