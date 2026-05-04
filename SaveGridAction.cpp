
#include "SaveGridAction.h"   
#include "Grid.h"           
#include <fstream>            
#include <string>             
using namespace std;

SaveGridAction::SaveGridAction(ApplicationManager* pApp) : Action(pApp)
{
}

void SaveGridAction::ReadActionParameters()
{
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

    pOut->PrintMessage("Enter File Name to Save: ");

    fileName = pIn->GetString(pOut);

    pOut->ClearStatusBar();
}
void SaveGridAction::Execute()

{
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();


    pOut->PrintMessage("Enter File Name to Save: ");
    string fileName = pIn->GetString(pOut);


    ofstream OutFile(fileName + ".txt");

    if (OutFile.is_open())
    {


        pGrid->SaveAll(OutFile, 1);
        pGrid->SaveAll(OutFile, 2);
        pGrid->SaveAll(OutFile, 3);
		pGrid->SaveAll(OutFile, 4);
		pGrid->SaveAll(OutFile, 5);
		pGrid->SaveAll(OutFile, 6);
		pGrid->SaveAll(OutFile, 7);

        pOut->PrintMessage("Game Saved Successfully in " + fileName + ".txt");
        OutFile.close();
    }
}