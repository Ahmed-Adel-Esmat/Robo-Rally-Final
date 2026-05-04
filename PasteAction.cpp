#include "PasteAction.h"
#include "ApplicationManager.h"
#include "Grid.h"
#include "Cell.h"
#include "GameObject.h"

PasteAction::PasteAction(ApplicationManager* pApp) : Action(pApp)
{
}

void PasteAction::ReadActionParameters()
{
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

    pOut->PrintMessage("Paste: Click on the destination cell ...");
    pastePos = pIn->GetCellClicked();

    if (!pastePos.IsValidCell())
    {
        pastePos = CellPosition(-1, -1);
        pOut->PrintMessage("Error: Invalid Cell! Click to continue...");
        pIn->GetCellClicked();
        return;
    }

   
    if (pastePos.GetCellNum() == 1 || pastePos.GetCellNum() == 55)
    {
        pastePos = CellPosition(-1, -1);
        pOut->PrintMessage("Error: Cannot paste in cell 1 or cell 55! Click to continue...");
        pIn->GetCellClicked();
        return;
    }

    pOut->ClearStatusBar();
}

void PasteAction::Execute()
{
    ReadActionParameters();

    if (!pastePos.IsValidCell())
        return;

    Grid* pGrid = pManager->GetGrid();

   
    GameObject* pClipboardObj = pGrid->GetClipboard();
    if (pClipboardObj == NULL)
    {
        pGrid->PrintErrorMessage("Error: Clipboard is empty! Copy or Cut first. Click to continue...");
        return;
    }

    
    Cell* pDestCell = pGrid->GetCell(pastePos);
    if (pDestCell->GetGameObject() != NULL)
    {
        pGrid->PrintErrorMessage("Error: Destination cell already has an object! Click to continue...");
        return;
    }

  
    GameObject* pNewObject = pClipboardObj->Clone();

  
    pNewObject->SetPosition(pastePos);

   
    bool added = pGrid->AddObjectToCell(pNewObject);

    if (!added)
    {
        delete pNewObject;
        pGrid->PrintErrorMessage("Error: Failed to add object! Click to continue...");
        return;
    }

    pGrid->UpdateInterface(pManager->GetGameState());
    pGrid->PrintErrorMessage("Object pasted successfully! Click to continue...");
}

PasteAction::~PasteAction()
{
}
