#include "CopyAction.h"
#include "ApplicationManager.h"
#include "Grid.h"
#include "Cell.h"
#include "GameObject.h"

CopyAction::CopyAction(ApplicationManager* pApp) : Action(pApp)
{
}

void CopyAction::ReadActionParameters()
{
    
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

    pOut->PrintMessage("Copy: Click on the cell of the object to copy ...");
    copyPos = pIn->GetCellClicked();

    
    if (!copyPos.IsValidCell())
    {
        copyPos = CellPosition(-1, -1);
        pOut->PrintMessage("Error: Invalid Cell! Click to continue...");
        pIn->GetCellClicked();
        return;
    }

  
    pOut->ClearStatusBar();
}

void CopyAction::Execute()
{
   
    ReadActionParameters();

    
    if (!copyPos.IsValidCell())
        return;

    Grid* pGrid = pManager->GetGrid();

    
    Cell* pCell = pGrid->GetCell(copyPos);

   
    GameObject* pObject = pCell->GetGameObject();

   
    if (pObject == NULL)
    {
        pGrid->PrintErrorMessage("Error: No object in this cell to copy! Click to continue...");
        return;
    }

   
    GameObject* pClone = pObject->Clone();

    
    GameObject* oldClipboard = pGrid->GetClipboard();
    if (oldClipboard != NULL)
        delete oldClipboard;

    pGrid->SetClipboard(pClone);

    pGrid->PrintErrorMessage("Object copied successfully! Click to continue...");
}

CopyAction::~CopyAction()
{
}