#pragma once
#include "Action.h"

class SelectCommandAction : public Action
{
public:
    SelectCommandAction(ApplicationManager* appManager);
    virtual void ReadActionParameters();
    virtual void Execute();
    virtual ~SelectCommandAction();
};