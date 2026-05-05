#include "AddWaterPitAction.h"

AddWaterPitAction::AddWaterPitAction(ApplicationManager* pApp) : Action(pApp)
{
}

void AddWaterPitAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("New Water Pit: Click on its Cell ...");
	waterPitPos = pIn->GetCellClicked();

	if (!waterPitPos.IsValidCell())
	{
		waterPitPos = CellPosition(-1, -1);
		pOut->PrintMessage("Error: Invalid Cell Position! Click to continue...");
		return;
	}
	else if (waterPitPos.GetCellNum() == 1 || waterPitPos.GetCellNum() == 55)
	{
		waterPitPos = CellPosition(-1, -1);
		pOut->PrintMessage("Error: Cannot place objects on Cell 1 or Cell 55! Click to continue...");
		return;
	}

	pOut->ClearStatusBar();
}

void AddWaterPitAction::Execute()
{
	ReadActionParameters();

	WaterPit* pWaterPit = new WaterPit(waterPitPos);
	Grid* pGrid = pManager->GetGrid();

	bool added = pGrid->AddObjectToCell(pWaterPit);

	if (!added)
	{
		delete pWaterPit;
		pGrid->PrintErrorMessage("Error: Cell already has an object! Click to continue...");
	}
}

AddWaterPitAction::~AddWaterPitAction()
{
}