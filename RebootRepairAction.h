#pragma once
#include "Action.h"

class RebootRepairAction : public Action
{
public:
	RebootRepairAction(ApplicationManager* appmanager);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual ~RebootRepairAction();
};