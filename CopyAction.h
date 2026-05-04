#pragma once
#include "Action.h"
#include "Input.h"
#include "Output.h"

class CopyAction : public Action
{
   
    CellPosition copyPos;   

public:
    CopyAction(ApplicationManager* pApp);
    virtual void ReadActionParameters();
    virtual void Execute();
    ~CopyAction();
};