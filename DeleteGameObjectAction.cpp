#include "DeleteGameObjectAction.h"
#include "Grid.h"

DeleteGameObjectAction::DeleteGameObjectAction(ApplicationManager* pApp) : Action(pApp) {}

void DeleteGameObjectAction::ReadActionParameters() {
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

    pOut->PrintMessage("Delete Object: Click on the object you want to delete...");
    pos = pIn->GetCellClicked(); 
}

void DeleteGameObjectAction::Execute()
{
    ReadActionParameters(); 

    Grid* pGrid = pManager->GetGrid();
    if (pos.IsValidCell()) {
        pGrid->RemoveObjectFromCell(pos);

        pGrid->PrintErrorMessage("Object deleted successfully. Click to continue...");
    }
    else {
        pGrid->PrintErrorMessage("Invalid cell! Click to continue...");
    }
}
