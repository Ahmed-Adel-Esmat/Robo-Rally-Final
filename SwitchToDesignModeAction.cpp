#include "SwitchToDesignModeAction.h"
#include "Grid.h"
#include "Output.h"
#include "ApplicationManager.h"
#include "GameState.h"
#include "Player.h"
#include "Cell.h"


SwitchToDesignModeAction::SwitchToDesignModeAction(ApplicationManager* pApp) : Action(pApp)
{
}

void SwitchToDesignModeAction::ReadActionParameters()
{
	// No parameters needed -- a mode switch requires no user input
}

void SwitchToDesignModeAction::Execute()
{

		Grid* pGrid = pManager->GetGrid();
		GameState* pState = pManager->GetGameState();
		Output* pOut = pGrid->GetOutput();

		
		pGrid->ClearAllObjects();

		
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			Player* pPlayer = pState->GetPlayer(i);

			if (pPlayer != NULL)
			{
				pGrid->UpdatePlayerCell(pPlayer, pGrid->GetStartCell()->GetCellPosition());
				pPlayer->SetHealth(10);
				pPlayer->ClearSavedCommands();
			}
		}
		pState->SetFirstPlayer(0);
		pState->SetCurrentPhase(PHASE_MOVEMENT);
		UI.InterfaceMode = MODE_DESIGN;
		pOut->CreateDesignModeToolBar();
		pManager->UpdateInterface();
		pOut->PrintMessage("Switched to Design Mode.");
	
}

SwitchToDesignModeAction::~SwitchToDesignModeAction()
{
}
