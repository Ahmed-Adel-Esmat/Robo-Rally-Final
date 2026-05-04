#pragma once
#pragma once
#include "Action.h"

class SaveGridAction : public Action
{
public:
    SaveGridAction(ApplicationManager* pApp);
    virtual void ReadActionParameters();
    virtual void Execute();
};
