#include "AddDangerZoneAction.h"

AddDangerZoneAction::AddDangerZoneAction(ApplicationManager* pApp) : Action(pApp)
{
}

void AddDangerZoneAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("New Danger Zone: Click on its Cell ...");
	dangerZonePos = pIn->GetCellClicked();

	if (!dangerZonePos.IsValidCell())
	{
		dangerZonePos = CellPosition(-1, -1);
		pOut->PrintMessage("Error: Invalid Cell Position! Click to continue...");
		return;
	}
	else if (dangerZonePos.GetCellNum() == 1 || dangerZonePos.GetCellNum() == 55)
	{
		dangerZonePos = CellPosition(-1, -1);
		pOut->PrintMessage("Error: Cannot place objects on Cell 1 or Cell 55! Click to continue...");
		return;
	}

	pOut->ClearStatusBar();
}

void AddDangerZoneAction::Execute()
{
	ReadActionParameters();

	DangerZone* pDangerZone = new DangerZone(dangerZonePos);
	Grid* pGrid = pManager->GetGrid();

	bool added = pGrid->AddObjectToCell(pDangerZone);

	if (!added)
	{
		delete pDangerZone;
		pGrid->PrintErrorMessage("Error: Cell already has an object! Click to continue...");
	}
}

AddDangerZoneAction::~AddDangerZoneAction()
{
}