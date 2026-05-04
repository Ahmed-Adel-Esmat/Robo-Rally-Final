#include "NewGameAction.h"
#include "Grid.h"          
#include "ApplicationManager.h"

NewGameAction::NewGameAction(ApplicationManager* pApp) : Action(pApp) {
}

void NewGameAction::ReadActionParameters()
{

}

void NewGameAction::Execute() {
    Grid* pGrid = pManager->GetGrid();
    pGrid->ClearAllObjects();
    pGrid->PrintErrorMessage("New Game Started! Grid Cleared. Click to continue...");
}