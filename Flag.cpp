#include "Flag.h"
#include "GameState.h" 

Flag::Flag(const CellPosition & flagposition) : GameObject(flagposition)
{

}

void Flag::Draw(Output* pOut) const
{
	pOut->DrawFlag(position);
}

void Flag::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{

	///TODO: 
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	
	pOut->PrintMessage("You have reached the flag! You win! Click to continue...");
	pIn->GetCellClicked();
	pOut->ClearStatusBar();

	
	pState->SetEndGame(true);
}
GameObject* Flag::Clone() const
{
	return new Flag(position);
}

Flag::~Flag()
{

}