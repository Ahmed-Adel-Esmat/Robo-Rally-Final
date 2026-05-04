#include "Antenna.h"
#include "GameState.h"
#include "Player.h"
#include "Grid.h"




Antenna::Antenna(const CellPosition & antennaPosition):GameObject(antennaPosition)
{
}

void Antenna::Draw(Output * pOut) const
{
	pOut->DrawAntenna(position);
}

void Antenna::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below

	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "the antenna will decide the turn of players. Click to continue ..." and wait mouse click
	pOut->PrintMessage("The antenna will decide the turn of players. Click to continue...");
	pIn->GetCellClicked();

	// 2- Determine turn order based on each player's distance from the antenna.
	//    Hint: distance = |dV| + |dH|
	//    The player closest to the antenna plays first. Ties are broken by player number.
	//    Use pState to update the turn order accordingly.
	int minDistance = INT_MAX;
	int firstPlayerNum = -1;
	for (int i = 0; i < MaxPlayerCount; i++) {
		Player* player = pState->GetPlayer(i);
		if (player != nullptr) {
			CellPosition playerPos = player->GetCell()->GetCellPosition();
			int distance = abs(playerPos.VCell() - position.VCell()) + abs(playerPos.HCell() - position.HCell());
			if (distance < minDistance) {
				minDistance = distance;
				firstPlayerNum = i;
			}
		}
	}

	// 3- Print a message indicating which player will play first
	if (firstPlayerNum != -1) {
		pOut->PrintMessage("Player " + to_string(firstPlayerNum) + " will play first. Click to continue...");
		pState->SetFirstPlayer(firstPlayerNum);
		
	}
}


GameObject * Antenna::Clone() const
{
	return new Antenna(position);
}
Antenna::~Antenna()
{
}
