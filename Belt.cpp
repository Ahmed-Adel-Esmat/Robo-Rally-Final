#include "Belt.h"
#include <fstream>


Belt::Belt(const CellPosition & startCellPos, const CellPosition & endCellPos) : GameObject(startCellPos)
{
	this->endCellPos = endCellPos;

	///TODO: Do the needed validation

}
void Belt::Draw(Output* pOut) const
{
	pOut->DrawBelt(position, endCellPos);
}

void Belt::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{


	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "You have reached a belt. Click to continue ..." and wait mouse click
	pOut->PrintMessage("You have reached a belt. Click to continue...");
	pIn->GetCellClicked();
	pOut->ClearStatusBar();

	// 2- Apply the belt's effect by moving the player to the endCellPos
	//    Review the "pGrid" functions and decide which function can be used for that
	pGrid->UpdatePlayerCell(pPlayer, endCellPos);
}
CellPosition Belt::GetEndPosition() const
{
	return endCellPos;
}
GameObject * Belt::Clone() const
{
	return new Belt(position, endCellPos);
}
void Belt::Save(ofstream& OutFile)
{
	OutFile << position.GetCellNum() << " " << endCellPos.GetCellNum() << endl;
}
int Belt::GetType() const {
	return 2;
}


Belt::~Belt()
{
}
