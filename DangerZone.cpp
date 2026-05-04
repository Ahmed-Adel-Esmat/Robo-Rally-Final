#include "DangerZone.h"
#include "Player.h"
#include "GameState.h"
#include <fstream>

DangerZone::DangerZone(const CellPosition & dangerZonePosition): GameObject(dangerZonePosition)
{
}

void DangerZone::Draw(Output * pOut) const
{
	pOut->DrawDangerZone(position);
}

void DangerZone::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{
	

	//
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

    pOut->PrintMessage("You have reached a danger zone. Click to continue...");
    pIn->GetCellClicked();
    pOut->ClearStatusBar();

  
    pPlayer->SetHealth(pPlayer->GetHealth() - 1);

   
    pGrid->UpdateInterface(pState);
}

GameObject * DangerZone::Clone() const
{
    return new DangerZone(position);
}

int DangerZone::GetType() const
{
    return 3;
}

void DangerZone::Save(ofstream& OutFile)
{
    OutFile << this->GetPosition().GetCellNum() << endl;
}



DangerZone::~DangerZone()
{
}
