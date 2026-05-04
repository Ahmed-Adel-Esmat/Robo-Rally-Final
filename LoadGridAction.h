#pragma once
#include "Action.h"

class LoadGridAction : public Action
{
public:
	LoadGridAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();
	virtual void Execute();

	virtual ~LoadGridAction();
};