#include "AddAntennaAction.h"

AddAntennaAction::AddAntennaAction(ApplicationManager* pApp) : Action(pApp)
{
}

void AddAntennaAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("New Antenna: Click on its Cell ...");
	antennaPos = pIn->GetCellClicked();

	if (!antennaPos.IsValidCell())
	{
		antennaPos = CellPosition(-1, -1);
		pOut->PrintMessage("Error: Invalid Cell Position! Click to continue...");
		return;
	}
	else if (antennaPos.GetCellNum() == 1 || antennaPos.GetCellNum() == 55)
	{
		antennaPos = CellPosition(-1, -1);
		pOut->PrintMessage("Error: Cannot place objects on Cell 1 or Cell 55! Click to continue...");
		return;
	}

	pOut->ClearStatusBar();
}

void AddAntennaAction::Execute()
{
	ReadActionParameters();

	Antenna* pAntenna = new Antenna(antennaPos);
	Grid* pGrid = pManager->GetGrid();

	bool added = pGrid->AddObjectToCell(pAntenna);

	if (!added)
	{
		delete pAntenna;
		pGrid->PrintErrorMessage("Error: Cell already has an object! Click to continue...");
	}
}

AddAntennaAction::~AddAntennaAction()
{
}