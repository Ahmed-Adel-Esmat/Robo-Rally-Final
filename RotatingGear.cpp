#include "RotatingGear.h"
#include "Player.h"        
#include "GameState.h"    




RotatingGear::RotatingGear(const CellPosition & gearposition,bool clockwise) : GameObject(gearposition)
{
	isClockWise = clockwise;
}

void RotatingGear::Draw(Output* pOut) const
{
	pOut->DrawRotatingGear(position, isClockWise);
}



	///TODO: 
void RotatingGear::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

    if (isClockWise)
        pOut->PrintMessage("Rotating gear: rotating clockwise. Click to continue...");
    else
        pOut->PrintMessage("Rotating gear: rotating anti-clockwise. Click to continue...");
    pIn->GetCellClicked();
    pOut->ClearStatusBar();

    Direction d = pPlayer->GetDirection();
    Direction newDir;

    if (isClockWise)
    {
        if (d == UP)    newDir = RIGHT;
        else if (d == RIGHT) newDir = DOWN;
        else if (d == DOWN)  newDir = LEFT;
        else                 newDir = UP;
    }
    else
    {
        if (d == UP)    newDir = LEFT;
        else if (d == LEFT)  newDir = DOWN;
        else if (d == DOWN)  newDir = RIGHT;
        else                 newDir = UP;
    }
    pPlayer->SetDirection(newDir);

    pGrid->UpdateInterface(pState);
}
bool RotatingGear::GetisClockWise() const
{
	return isClockWise;
}

GameObject * RotatingGear::Clone() const
{
    return new RotatingGear(position, isClockWise); 
}

RotatingGear::~RotatingGear()
{
}
