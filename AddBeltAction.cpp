#include "AddBeltAction.h"

AddBeltAction::AddBeltAction(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer

}


void AddBeltAction::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the startPos parameter
	pOut->PrintMessage("New Belt: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();

	// Read the endPos parameter
	pOut->PrintMessage("New Belt: Click on its End Cell ...");
	endPos = pIn->GetCellClicked();



	///TODO: Make the needed validations on the read parameters
	if (!startPos.IsValidCell() || !endPos.IsValidCell())
	{
		startPos = CellPosition(-1, -1);
		pOut->PrintMessage("Error: Invalid Cell Position! Click to continue...");
		return;
	}
	else if (startPos.GetCellNum() == 1 || startPos.GetCellNum() == 55 || endPos.GetCellNum() == 1 || endPos.GetCellNum() == 55)
	{
		startPos = CellPosition(-1, -1);
		pOut->PrintMessage("Error: Cannot place objects on Cell 1 or Cell 55! Click to continue...");
		return;
	}
	else if (startPos.GetCellNum() == endPos.GetCellNum())
	{
		startPos = CellPosition(-1, -1);
		pOut->PrintMessage("Error: Start and End Cells cannot be the same! Click to continue...");
		return;
	}
	else if (startPos.VCell() != endPos.VCell() && startPos.HCell() != endPos.HCell())
	{
		startPos = CellPosition(-1, -1);
		pOut->PrintMessage("Error: Belt must be either horizontal or vertical! Click to continue...");
		return;
	}


	// Clear messages
	pOut->ClearStatusBar();
}

void AddBeltAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();

	// Create a belt object with the parameters read from the user
	Belt * pBelt = new Belt(startPos, endPos);

	Grid * pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager

										
	bool added = pGrid->AddObjectToCell(pBelt);

	// if the GameObject cannot be added
	if (!added)
	{
		// Print an appropriate message
		delete pBelt; 
		pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
	}
	// Here, the belt is created and added to the GameObject of its Cell, so we finished executing the AddBeltAction

}

AddBeltAction::~AddBeltAction()
{
}
