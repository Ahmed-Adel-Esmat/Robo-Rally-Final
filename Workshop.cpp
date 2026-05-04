#include "Workshop.h"
#include "Player.h"        
#include "GameState.h"    
#include "Grid.h"
using namespace std;
#include <fstream>

Workshop::Workshop(const CellPosition & workshopPosition):GameObject( workshopPosition)
{

}


void Workshop::Draw(Output * pOut) const
{
	pOut->DrawWorkshop(position);
}

void Workshop::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{
	///TODO
	
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

   
    pOut->PrintMessage("You have reached a workshop. Repairing... Click to continue...");
    pIn->GetCellClicked();
    pOut->ClearStatusBar();

    
    pPlayer->SetHealth(10);

    
    pGrid->UpdateInterface(pState);
}

GameObject * Workshop::Clone() const
{
    return new Workshop(position);
}
void Workshop::Save(ofstream& OutFile )
{
    OutFile << this->GetPosition().GetCellNum() << endl;
}
int Workshop::GetType() const
{
    return 5;
}
Workshop::~Workshop()
{
}
