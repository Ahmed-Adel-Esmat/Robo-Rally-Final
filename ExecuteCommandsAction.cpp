#include "ExecuteCommandsAction.h"

#include "ApplicationManager.h"
#include "Grid.h"
#include "GameState.h"
#include "Player.h"

ExecuteCommandsAction::ExecuteCommandsAction(ApplicationManager* appmanager) : Action(appmanager)
{
}
void ExecuteCommandsAction::ReadActionParameters()
{
}
void ExecuteCommandsAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	GameState* pState = pManager->GetGameState();
	Player* pPlayer = pState->GetCurrentPlayer();
	if (pPlayer->GetSavedCommandCount() == 0)
	{
		pGrid->PrintErrorMessage("No saved commands to execute!");
		return;
	}

	pPlayer->Move(pGrid, pState);
	pPlayer->ClearSavedCommands();
	pGrid->UpdateInterface(pState);
	pState->AdvanceCurrentPlayer();
}

ExecuteCommandsAction::~ExecuteCommandsAction()
{
}