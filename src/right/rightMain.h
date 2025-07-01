#pragma once
#include <stdio.h>
#include "common/common.h"

using namespace Common;

class RightCource {
    public:
    bool StartAlwaysTask(void);

    private:
     void stopAlwaysTask(void);
     Common::TaskSeq checkNextTaskSeq(const Common::TaskSeq c_eCurTaskSeq, const Common::ExecuteState c_eCurState);
     bool m_bIsRunning;
     Common::TaskSeq m_eExecuteSeq;
}