#include "WaterPit.h"
#include "Player.h"       
#include "GameState.h"
using namespace std;
#include <fstream>


WaterPit::WaterPit(const CellPosition & waterPitPosition):GameObject(waterPitPosition)
{
}

void WaterPit::Draw(Output * pOut) const
{
	pOut->DrawWaterPit(position);
}

void WaterPit::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{

	///TODO
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

   
    pOut->PrintMessage("You drowned in a water pit! Resetting to start. Click to continue...");
    pIn->GetCellClicked();
    pOut->ClearStatusBar();

 
    pPlayer->SetHealth(pPlayer->GetHealth() - 3);

    
    CellPosition startPos(NumVerticalCells - 1, 0);  
    pGrid->UpdatePlayerCell(pPlayer, startPos);

    
    pGrid->UpdateInterface(pState);
}

void WaterPit::Save(ofstream& OutFile)
{

        OutFile << this->GetPosition().GetCellNum() << endl;
    
}

GameObject * WaterPit::Clone() const
{
    return new WaterPit(position);
}
int WaterPit::GetType() const {
    return 2;
}




WaterPit::~WaterPit()
{
}
