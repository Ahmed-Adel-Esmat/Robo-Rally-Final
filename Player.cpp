#include "Player.h"
#include "Workshop.h"
#include "GameObject.h"
#include "GameState.h"

Player::Player(Cell* pCell, int playerNum)
	: playerNum(playerNum), health(10), currDirection(RIGHT), savedCommandCount(0)
{
	this->pCell = pCell;

	// Initialise saved commands to NO_COMMAND
	for (int i = 0; i < MaxSavedCommands; i++)
		savedCommands[i] = NO_COMMAND;
}

// ====== Setters and Getters ======

void  Player::SetCell(Cell* cell)   { pCell = cell; }
Cell* Player::GetCell() const       { return pCell; }

void Player::SetHealth(int h)
{
	if (h < 0)
		h = 0;
	else if (h > 10)
		h = 10;

	///TODO: Add validation (e.g. clamp to 0..MaxHealth)
	health = h;
}
int Player::GetHealth() const       { return health; }

Direction Player::GetDirection() const      { return currDirection; }
void      Player::SetDirection(Direction d) { currDirection = d; }

// ====== Saved Commands ======

void Player::AddSavedCommand(Command cmd)
{
	if (savedCommandCount < MaxSavedCommands)
		savedCommands[savedCommandCount++] = cmd;
}

void Player::ClearSavedCommands()
{
	for (int i = 0; i < MaxSavedCommands; i++)
		savedCommands[i] = NO_COMMAND;
	savedCommandCount = 0;
}

int     Player::GetSavedCommandCount() const { return savedCommandCount; }
Command Player::GetSavedCommand(int index) const
{
	if (index >= 0 && index < savedCommandCount)
		return savedCommands[index];
	return NO_COMMAND;
}

// ====== Drawing Functions ======

void Player::Draw(Output* pOut) const
{
	color playerColor = UI.PlayerColors[playerNum];
	CellPosition playerpos = pCell->GetCellPosition();
	pOut->DrawPlayer(playerpos, playerNum, playerColor, currDirection);        // done

	///TODO: Call the appropriate Output function to draw the player token with playerColor
}

void Player::ClearDrawing(Output* pOut) const
{
	///TODO: Determine the correct background colour for this cell
	//       (hint: may differ from UI.CellColor if cell is a WaterPit or DangerZone)
	pCell->DrawCellOrWaterPitOrDangerZone(pOut);
	pCell->DrawGameObject(pOut);
	///TODO: Call the appropriate Output function to draw the token using cellColor (erases it)
}

// ====== Game Logic ======

void Player::Move(Grid* pGrid, GameState* pState)
{
	
	
		Output* pOut = pGrid->GetOutput();
		Input* pIn = pGrid->GetInput();

		Workshop* pWorkshop = NULL;

		for (int i = 0; i < savedCommandCount; i++)
		{
			Command cmd = savedCommands[i];
			CellPosition newPos = pCell->GetCellPosition();

			switch (cmd)
			{
			case MOVE_FORWARD_ONE_STEP:
				newPos.AddCellNum(1, currDirection);
				pGrid->UpdatePlayerCell(this, newPos);
				break;

			case MOVE_FORWARD_TWO_STEPS:
				newPos.AddCellNum(2, currDirection);
				pGrid->UpdatePlayerCell(this, newPos);
				break;

			case MOVE_FORWARD_THREE_STEPS:
				newPos.AddCellNum(3, currDirection);
				pGrid->UpdatePlayerCell(this, newPos);
				break;

			case MOVE_BACKWARD_ONE_STEP:
				if (currDirection == UP)
					newPos.AddCellNum(1, DOWN);
				else if (currDirection == DOWN)
					newPos.AddCellNum(1, UP);
				else if (currDirection == RIGHT)
					newPos.AddCellNum(1, LEFT);
				else
					newPos.AddCellNum(1, RIGHT);

				pGrid->UpdatePlayerCell(this, newPos);
				break;

			case MOVE_BACKWARD_TWO_STEPS:
				if (currDirection == UP)
					newPos.AddCellNum(2, DOWN);
				else if (currDirection == DOWN)
					newPos.AddCellNum(2, UP);
				else if (currDirection == RIGHT)
					newPos.AddCellNum(2, LEFT);
				else
					newPos.AddCellNum(2, RIGHT);

				pGrid->UpdatePlayerCell(this, newPos);
				break;

			case MOVE_BACKWARD_THREE_STEPS:
				if (currDirection == UP)
					newPos.AddCellNum(3, DOWN);
				else if (currDirection == DOWN)
					newPos.AddCellNum(3, UP);
				else if (currDirection == RIGHT)
					newPos.AddCellNum(3, LEFT);
				else
					newPos.AddCellNum(3, RIGHT);

				pGrid->UpdatePlayerCell(this, newPos);
				break;

			case ROTATE_CLOCKWISE:
				if (currDirection == UP)
					currDirection = RIGHT;
				else if (currDirection == RIGHT)
					currDirection = DOWN;
				else if (currDirection == DOWN)
					currDirection = LEFT;
				else
					currDirection = UP;

				pGrid->UpdatePlayerCell(this, pCell->GetCellPosition());
				break;

			case ROTATE_COUNTERCLOCKWISE:
				if (currDirection == UP)
					currDirection = LEFT;
				else if (currDirection == LEFT)
					currDirection = DOWN;
				else if (currDirection == DOWN)
					currDirection = RIGHT;
				else
					currDirection = UP;

				pGrid->UpdatePlayerCell(this, pCell->GetCellPosition());
				break;

			default:
				break;
			}

			GameObject* pObj = pCell->GetGameObject();
			if (pObj != NULL)
			{
				Workshop* ws = dynamic_cast<Workshop*>(pObj);

				if (ws != NULL)
					pWorkshop = ws;
				else
					pObj->Apply(pGrid, pState, this);
			}

			if (pState->GetEndGame())
				return;
		}

		if (pWorkshop != NULL)
			pWorkshop->Apply(pGrid, pState, this);
	
	///TODO: Implement this function
	// - Execute the saved commands one by one, waiting for a mouse click between each
	// - After all commands are executed, apply the game object effect at the final cell (if any)
	// - Use CellPosition and Grid to handle movement and cell updates
}

void Player::AppendPlayerInfo(string& playersInfo) const
{
	string dir;
	if (currDirection == UP)
	{
		dir = "up";
	}
	else if (currDirection == DOWN)
	{
		dir = "down";
	}
	else if (currDirection == LEFT)
	{
		dir = "left";
	}
	else
		dir = "right";



	// TODO: Modify the Info as needed                         // done 
	playersInfo += "P" + to_string(playerNum) + "(";
	playersInfo += dir + ", ";                // 3mlt kda 3shan tban puum(dir,health) w shlt el adem 34an kan enum (currdirection)
	playersInfo += to_string(health) + ")";
}
