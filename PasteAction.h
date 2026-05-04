#pragma once
#include "Action.h"
#include "Input.h"
#include "Output.h"

class PasteAction : public Action
{
    CellPosition pastePos;

public:
    PasteAction(ApplicationManager* pApp);
    virtual void ReadActionParameters();
    virtual void Execute();
    ~PasteAction();
};