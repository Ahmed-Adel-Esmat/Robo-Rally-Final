#include "ExitAction.h"
#include "Grid.h"

ExitAction::ExitAction(ApplicationManager* pApp) : Action(pApp)
{
}

void ExitAction::ReadActionParameters()
{

}


void ExitAction::Execute()
{
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    pGrid->PrintErrorMessage("Exiting Robo Rally... Goodbye! Click to close.");

}

ExitAction::~ExitAction()
{
}
