#include "RebootRepairAction.h"
#include "ApplicationManager.h"
#include "Grid.h"
#include "GameState.h"
#include "Player.h"

RebootRepairAction::RebootRepairAction(ApplicationManager* appmanager) : Action(appmanager)
{
}
void RebootRepairAction::ReadActionParameters()
{
}
void RebootRepairAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	GameState* pState = pManager->GetGameState();
	Player* pPlayer = pState->GetCurrentPlayer();
	int newHealth = pPlayer->GetHealth() + 2;
	if (newHealth > 10)
		newHealth = 10;
	pPlayer->SetHealth(newHealth);
	pPlayer->ClearSavedCommands();
	pGrid->UpdateInterface(pState);
	pState->AdvanceCurrentPlayer();
}

RebootRepairAction::~RebootRepairAction()
{
}