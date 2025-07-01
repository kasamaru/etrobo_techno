
#pragma once
#include <cstdint>
#include <cstring>
#include "mid/colorSense.h"
#include "mid/Walker.h"
using SBYTE = int8_t;
using BYTE = uint8_t;

using SWORD = int16_t;
using WORD = uint16_t;

using SDWORD = int32_t;
using DWORD = uint32_t;

#define MAX_SBYTE (127)
#define MIN_SBYTE (-128)
#define MAX_BYTE (255)
#define MIN_BYTE (0)
#define MAX_SWORD (32767)
#define MIN_SWORD (-32768)
#define MAX_WORD (65535)
#define MIN_WORD (0)
#define MAX_SDWORD (2147483647)
#define MIN_SDWORD (-2147483648)

#define MAX(src, dst) ((src > dst) ? src : dst)
#define MIN(src, dst) ((src < dst) ? src : dst)

/* TODO: ono 基本動作シーケンス名の変更と認識合わせ */
namespace Common
{
    enum class ExecuteState : BYTE {
        Init = 0,
        Execute,      /* 実行中 */
        End,      /* 処理終了 */
        MAX = 3,
    };

    enum class TaskSeq : BYTE {
        Init = 0, /* 初期化中 */
        SCENARIO_TRACE_1, /* シナリオトレース1(仮) */
        LINE_TRACE_1, /* ライントレース1(仮) */
        SMART_CARRY, /* スマートキャリー */
        SCENARIO_TRACE_2, /* シナリオトレース2(仮) */
        LINE_TRACE_2, /* ライントレース2(仮) */
        END, /* 終了 */
        MAX = 7,
    }
}
