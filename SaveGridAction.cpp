
#include "SaveGridAction.h"   
#include "Grid.h"           
#include <fstream>            
#include <string>             
using namespace std;

using namespace std;
void SaveGridAction::Execute()

{
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();


    pOut->PrintMessage("Enter File Name to Save: ");
    string fileName = pIn->GetSrting(pOut);


    ofstream OutFile(fileName + ".txt");

    if (OutFile.is_open())
    {


        pGrid->SaveAll(OutFile, 1);
        pGrid->SaveAll(OutFile, 2);
        pGrid->SaveAll(OutFile, 3);

        pOut->PrintMessage("Game Saved Successfully in " + fileName + ".txt");
        OutFile.close();
    }
}