#include "AddWorkshopAction.h"

AddWorkshopAction::AddWorkshopAction(ApplicationManager* pApp) : Action(pApp)
{
}

void AddWorkshopAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("New Workshop: Click on its Cell ...");
	workshopPos = pIn->GetCellClicked();

	if (!workshopPos.IsValidCell())
	{
		workshopPos = CellPosition(-1, -1);
		pOut->PrintMessage("Error: Invalid Cell Position! Click to continue...");
		return;
	}
	else if (workshopPos.GetCellNum() == 1 || workshopPos.GetCellNum() == 55)
	{
		workshopPos = CellPosition(-1, -1);
		pOut->PrintMessage("Error: Cannot place objects on Cell 1 or Cell 55! Click to continue...");
		return;
	}

	pOut->ClearStatusBar();
}

void AddWorkshopAction::Execute()
{
	ReadActionParameters();

	Workshop* pWorkshop = new Workshop(workshopPos);
	Grid* pGrid = pManager->GetGrid();

	bool added = pGrid->AddObjectToCell(pWorkshop);

	if (!added)
	{
		delete pWorkshop;
		pGrid->PrintErrorMessage("Error: Cell already has an object! Click to continue...");
	}
}

AddWorkshopAction::~AddWorkshopAction()
{
}