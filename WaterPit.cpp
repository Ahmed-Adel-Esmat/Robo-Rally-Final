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
    
        if (pPlayer == NULL || pGrid == NULL)
            return;

        int newHealth = pPlayer->GetHealth() - 3;
        if (newHealth < 0)
            newHealth = 0;

        pPlayer->SetHealth(newHealth);
        pGrid->UpdatePlayerCell(pPlayer, pGrid->GetStartCell()->GetCellPosition());
    
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
