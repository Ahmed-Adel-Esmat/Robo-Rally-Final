#include "WaterPit.h"
#include "Player.h"       
#include "GameState.h"


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

GameObject * WaterPit::Clone() const
{
    return new WaterPit(position);
}
int WaterPit::GetType() const {
    return 3;
}


WaterPit::~WaterPit()
{
}
