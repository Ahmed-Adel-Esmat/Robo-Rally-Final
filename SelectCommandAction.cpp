#include "SelectCommandAction.h"

#include "ApplicationManager.h"
#include "Grid.h"
#include "GameState.h"
#include "Player.h"
#include "Input.h"
#include "Output.h"
#include "UI_Info.h"
#include <cstdlib>

SelectCommandAction::SelectCommandAction(ApplicationManager* appManager) : Action(appManager)
{
}

void SelectCommandAction::ReadActionParameters()
{
}
Command GetRandomCommand()
{
	int r = rand() % 8 + 1;
	return (Command)r;
}
void SelectCommandAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	GameState* pState = pManager->GetGameState();
	Player* pPlayer = pState->GetCurrentPlayer();
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();

	
	if (pPlayer->GetHealth() <= 0)
	{
		pGrid->PrintErrorMessage("Player has no health!");
		return;
	}

	int maxToSave = pPlayer->GetHealth();
	if (maxToSave > MaxSavedCommands)
		maxToSave = MaxSavedCommands;

	if (pPlayer->GetSavedCommandCount() >= maxToSave)
	{
		pGrid->PrintErrorMessage("Maximum saved commands reached!");
		return;
	}

	int availableCount = pPlayer->GetHealth();
	if (availableCount > MaxAvailableCommands)
		availableCount = MaxAvailableCommands;

	Command availableCommands[MaxAvailableCommands];

	for (int i = 0; i < availableCount; i++)
	{
		availableCommands[i] = GetRandomCommand();
	}

	for (int i = availableCount; i < MaxAvailableCommands; i++)
	{
		availableCommands[i] = NO_COMMAND;
	}
	Command savedCommands[MaxSavedCommands];
	int savedCount = pPlayer->GetSavedCommandCount();

	for (int i = 0; i < savedCount; i++)
	{
		savedCommands[i] = pPlayer->GetSavedCommand(i);
	}

	for (int i = savedCount; i < MaxSavedCommands; i++)
	{
		savedCommands[i] = NO_COMMAND;
	}

	pOut->CreateCommandsBar(savedCommands, savedCount, availableCommands, availableCount);

	int selectedIndex = pIn->GetSelectedCommandIndex();

	if (selectedIndex < 0 || selectedIndex >= availableCount)
	{
		pGrid->PrintErrorMessage("Invalid command selection!");
		return;
	}

	pPlayer->AddSavedCommand(availableCommands[selectedIndex]);

	savedCount = pPlayer->GetSavedCommandCount();

	for (int i = 0; i < savedCount; i++)
	{
		savedCommands[i] = pPlayer->GetSavedCommand(i);
	}

	for (int i = savedCount; i < MaxSavedCommands; i++)
	{
		savedCommands[i] = NO_COMMAND;
	}

	
	pOut->CreateCommandsBar(savedCommands, savedCount, availableCommands, availableCount);
}

SelectCommandAction::~SelectCommandAction()
{
}