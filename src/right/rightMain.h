#pragma once
#include <stdio.h>
#include "common/common.h"

class RightCource {
    public:
    bool StartAlwaysTask(void);

    private:
    static void stopAlwaysTask(void);
    static E_ALL_TASK_SEQ checkNextTaskSeq(const E_ALL_TASK_SEQ c_eCurTaskSeq, const E_EXECUTE_STATE c_eCurState);
    static bool s_bIsRunning;
    static E_ALL_TASK_SEQ s_eExecuteSeq;
}