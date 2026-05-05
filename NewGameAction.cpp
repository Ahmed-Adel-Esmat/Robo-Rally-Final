#include "NewGameAction.h"
#include "Grid.h"          
#include "ApplicationManager.h"
#include "GameState.h"
#include "Player.h"
#include "Cell.h"

NewGameAction::NewGameAction(ApplicationManager* pApp) : Action(pApp) {
}

void NewGameAction::ReadActionParameters()
{

}

void NewGameAction::Execute() {
	
	
		Grid* pGrid = pManager->GetGrid();
		GameState* pState = pManager->GetGameState();

		for (int i = 0; i < MaxPlayerCount; i++)
		{
			Player* pPlayer = pState->GetPlayer(i);

			if (pPlayer != NULL)
			{
				pGrid->UpdatePlayerCell(pPlayer, pGrid->GetStartCell()->GetCellPosition());
				pPlayer->SetHealth(10);
				pPlayer->ClearSavedCommands();
				pGrid->ClearAllObjects();
				
			}
		}
		pState->SetFirstPlayer(0);
		pState->SetCurrentPhase(PHASE_MOVEMENT);
		pManager->UpdateInterface();
		
	
}