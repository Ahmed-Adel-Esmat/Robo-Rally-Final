#pragma once
#pragma once
#include "Action.h"
#include "Input.h"
#include "Output.h"

class CutAction : public Action
{
    CellPosition cutPos;

public:
    CutAction(ApplicationManager* pApp);
    virtual void ReadActionParameters();
    virtual void Execute();
    ~CutAction();
};
