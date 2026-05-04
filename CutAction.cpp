#include "CutAction.h"
#include "ApplicationManager.h"
#include "Grid.h"
#include "Cell.h"
#include "GameObject.h"

CutAction::CutAction(ApplicationManager* pApp) : Action(pApp)
{
}

void CutAction::ReadActionParameters()
{
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

    pOut->PrintMessage("Cut: Click on the cell of the object to cut ...");
    cutPos = pIn->GetCellClicked();

    if (!cutPos.IsValidCell())
    {
        cutPos = CellPosition(-1, -1);
        pOut->PrintMessage("Error: Invalid Cell! Click to continue...");
        pIn->GetCellClicked();
        return;
    }

    pOut->ClearStatusBar();
}

void CutAction::Execute()
{
    ReadActionParameters();

    if (!cutPos.IsValidCell())
        return;

    Grid* pGrid = pManager->GetGrid();
    Cell* pCell = pGrid->GetCell(cutPos);
    GameObject* pObject = pCell->GetGameObject();

   
    if (pObject == NULL)
    {
        pGrid->PrintErrorMessage("Error: No object in this cell to cut! Click to continue...");
        return;
    }

   
    GameObject* oldClipboard = pGrid->GetClipboard();
    if (oldClipboard != NULL)
        delete oldClipboard;

   
    pGrid->SetClipboard(pObject);

    
    pCell->SetGameObject(NULL);

   
    pGrid->UpdateInterface(pManager->GetGameState());

    pGrid->PrintErrorMessage("Object cut successfully! Click to continue...");
}

CutAction::~CutAction()
{
}
