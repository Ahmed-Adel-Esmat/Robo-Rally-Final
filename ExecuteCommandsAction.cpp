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
	Output* pOut = pGrid->GetOutput();
	if (pPlayer->GetSavedCommandCount() == 0)
	{
		pGrid->PrintErrorMessage("No saved commands to execute!");
		return;
	}
	pPlayer->Move(pGrid, pState);
	pPlayer->ClearSavedCommands();
	pState->AdvanceCurrentPlayer();
	pGrid->UpdateInterface(pState);
	Command savedCommands[MaxSavedCommands];
	Command availableCommands[MaxAvailableCommands];

	for (int i = 0; i < MaxSavedCommands; i++)
		savedCommands[i] = NO_COMMAND;

	for (int i = 0; i < MaxAvailableCommands; i++)
		availableCommands[i] = NO_COMMAND;

	pOut->CreateCommandsBar(savedCommands, 0, availableCommands, 0);
}

ExecuteCommandsAction::~ExecuteCommandsAction()
{
}