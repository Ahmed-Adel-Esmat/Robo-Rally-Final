#include "AddRotatingGearAction.h"

AddRotatingGearAction::AddRotatingGearAction(ApplicationManager * pApp):Action(pApp)
{
}

void AddRotatingGearAction::ReadActionParameters()
{
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	// 2- Read the gearPos
	pOut->PrintMessage("New Rotating Gear: Click on its Cell ...");
	gearPos = pIn->GetCellClicked();
	// 3- Read whether the direction will be clockwise or not
	pOut->PrintMessage("Is the gear clockwise? (y/n) ...");
	string direction = pIn->GetString(pOut);
	if (direction == "y" || direction == "Y") {
		clockwise = true;
	}
	else if (direction == "n" || direction == "N") {
		clockwise = false;
	}
	else {
		gearPos = CellPosition(-1, -1);
		pOut->PrintMessage("Error: Invalid input for direction! Click to continue...");
		return;
	}

	// 4- Make the needed validations on the read parameters
if (!gearPos.IsValidCell()) {
		gearPos = CellPosition(-1, -1);
		pOut->PrintMessage("Error: Invalid Cell Position! Click to continue...");
		return;
	}
	else if (gearPos.GetCellNum() == 1 || gearPos.GetCellNum() == 55) {
		gearPos = CellPosition(-1, -1);
		pOut->PrintMessage("Error: Cannot place objects on Cell 1 or Cell 55! Click to continue...");
		return;
}
	// 5- Clear status bar
pOut->ClearStatusBar();
}

void AddRotatingGearAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1-Create a rotating gear object
	RotatingGear* pRotatingGear = new RotatingGear(gearPos, clockwise);
	// 2-get a pointer to the Grid from the ApplicationManager
	Grid* pGrid = pManager->GetGrid();
	// 3-Add the rotating object to the GameObject of its Cell:
	bool added = pGrid->AddObjectToCell(pRotatingGear);
	// 4-Check if the rotating gear was added and print an errror message if flag couldn't be added
	if (!added) {
		delete pRotatingGear;
		pGrid->PrintErrorMessage("Error: Cell already has an object! Click to continue...");
	}
}

AddRotatingGearAction::~AddRotatingGearAction()
{
}
