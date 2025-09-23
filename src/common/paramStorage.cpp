#define SCENARIO_NUM     3
#define PARAMS1_MAX_NUM  1
#define PARAMS2_MAX_NUM  5
#define PARAMS3_MAX_NUM  5

const int ParamStorage::SCENARIO_NUM    = SCENARIO_NUM;
const int ParamStorage::PARAMS1_MAX_NUM = PARAMS1_MAX_NUM;
const int ParamStorage::PARAMS2_MAX_NUM = PARAMS2_MAX_NUM;
const int ParamStorage::PARAMS3_MAX_NUM = PARAMS3_MAX_NUM;
#include "paramStorage.h"

ParamStorage::ParamStorage() {
    // 右コース用パラメータ
    m_rightParams[0] = {
        {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (10000 * 1000), 0, 0}
    };
    m_rightParams[1] = {
        {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (1.563 * 1000), 0, 0},
        {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (1 * 1000), 0, 0},
        {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (1 * 1000), 0, 0},
        {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (1 * 1000), 0, 0},
        {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (1 * 1000), 0, 0}
    };
    m_rightParams[2] = {
        {ScenarioTrace::E_COMMANDS::eCOMMAND_STRAIGHT, (1000 * 1000), 0, 0}
    };

    // 左コース用パラメータ（例：右と同じ。必要に応じて値を変更してください）
    m_leftParams[0] = m_rightParams[0];
    m_leftParams[1] = m_rightParams[1];
    m_leftParams[2] = m_rightParams[2];
}

const std::vector<ScenarioTrace::ST_SCENARIO_TRACE_PARAMS>& ParamStorage::getParams(ParamSide side, int scenarioIdx) const {
    if (side == ParamSide::RIGHT) {
        return m_rightParams[scenarioIdx];
    } else {
        return m_leftParams[scenarioIdx];
    }
}

int ParamStorage::getParamsCount(ParamSide side, int scenarioIdx) const {
    return static_cast<int>(getParams(side, scenarioIdx).size());
}
