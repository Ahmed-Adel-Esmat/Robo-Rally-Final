#include "LoadGridAction.h"

#include "ApplicationManager.h"
#include "Grid.h"
#include "Input.h"
#include "Output.h"
#include "Flag.h"
#include "Belt.h"
#include "RotatingGear.h"

#include <fstream>
using namespace std;

LoadGridAction::LoadGridAction(ApplicationManager* pApp) : Action(pApp)
{
}

void LoadGridAction::ReadActionParameters()
{

}

void LoadGridAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("Enter File Name to Load: ");
	string fileName = pIn->GetString(pOut);   

	ifstream InFile(fileName + ".txt");

	if (!InFile.is_open())
	{
		pGrid->PrintErrorMessage("Error: File cannot be opened!");
		return;
	}


	pGrid->ClearGameObjects();

	int count;

	// ================= Flags =================
	InFile >> count;
	for (int i = 0; i < count; i++)
	{
		int cellNum;
		InFile >> cellNum;

		CellPosition pos = CellPosition::GetCellPositionFromNum(cellNum);
		Flag* pFlag = new Flag(pos);
		pGrid->AddObjectToCell(pFlag);
	}

	// ================= Belts =================
	InFile >> count;
	for (int i = 0; i < count; i++)
	{
		int startCellNum, endCellNum;
		InFile >> startCellNum >> endCellNum;

		CellPosition startPos = CellPosition::GetCellPositionFromNum(startCellNum);
		CellPosition endPos = CellPosition::GetCellPositionFromNum(endCellNum);

		Belt* pBelt = new Belt(startPos, endPos);
		pGrid->AddObjectToCell(pBelt);
	}

	// ================= Rotating Gears =================
	InFile >> count;
	for (int i = 0; i < count; i++)
	{
		int cellNum;
		bool clockwise;
		InFile >> cellNum >> clockwise;

		CellPosition pos = CellPosition::GetCellPositionFromNum(cellNum);
		RotatingGear* pGear = new RotatingGear(pos, clockwise);
		pGrid->AddObjectToCell(pGear);
	}

	InFile.close();

	pManager->UpdateInterface();
	pOut->PrintMessage("Grid Loaded Successfully.");
}

LoadGridAction::~LoadGridAction()
{
}