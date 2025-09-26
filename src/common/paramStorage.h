#ifndef PARAM_STORAGE_H
#define PARAM_STORAGE_H

#include <vector>
#include "common/common.h"
#include "mid/scenarioTrace.h"

// パラメータ種別
enum class ParamSide {
    RIGHT,
    LEFT
};

// パラメータ格納クラス
class ParamStorage {
public:
    // 右・左のパラメータを初期化（ソース直書き）
    ParamStorage();

    // パラメータ取得
    const std::vector<ScenarioTrace::ST_SCENARIO_TRACE_PARAMS>& getParams(ParamSide side, int scenarioIdx) const;
    int getParamsCount(ParamSide side, int scenarioIdx) const;


    // シナリオ数（右・左で同じ数と仮定）
    static const int SCENARIO_NUM;
    static const int PARAMS1_MAX_NUM;
    static const int PARAMS2_MAX_NUM;
    static const int PARAMS3_MAX_NUM;

private:
    // 右・左それぞれのシナリオごとにパラメータ配列
    std::vector<ScenarioTrace::ST_SCENARIO_TRACE_PARAMS> m_rightParams[SCENARIO_NUM];
    std::vector<ScenarioTrace::ST_SCENARIO_TRACE_PARAMS> m_leftParams[SCENARIO_NUM];
};

#endif // PARAM_STORAGE_H
