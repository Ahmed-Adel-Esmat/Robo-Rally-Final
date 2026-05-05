#include "GameState.h"

#include "Grid.h"
#include "Player.h"
#include "Cell.h"
#include "Output.h"

GameState::GameState(Grid* pGrid)
{
	// Create all Player objects starting at the board's designated start cell.
	// The Grid provides the start cell position; the GameState owns the Player objects.
	Cell* startCell = pGrid->GetStartCell();
	Output* pOut = pGrid->GetOutput();

	for (int i = 0; i < MaxPlayerCount; i++)
	{
		PlayerList[i] = new Player(startCell, i);
		PlayerList[i]->Draw(pOut); // draw initial position
	}

	currPlayerNumber = 0;         // Player 0 goes first by default
	currentPhase = PHASE_MOVEMENT;
	endGame = false;
}

GameState::~GameState()
{
	for (int i = 0; i < MaxPlayerCount; i++)
		delete PlayerList[i];
}

// ========== Player Access ==========

Player* GameState::GetCurrentPlayer() const
{
	///TODO: Return the player whose turn it is                  // done 
	return PlayerList[currPlayerNumber]; // wrong -- update this
}

Player* GameState::GetPlayer(int playerNum) const
{
	///TODO: Return the player with the given player number
	if (playerNum < 0 || playerNum >= MaxPlayerCount)               //doneee 
	{
		return NULL;                                               // 3shan el function de btrg3 pointer fa lazem n3mlha null fa el pointer kda m4 beshawer 3la haga
	}
	return PlayerList[playerNum]; // wrong -- update this
	
}

// ========== Turn Management ==========

void GameState::AdvanceCurrentPlayer()
{
	currPlayerNumber = (currPlayerNumber + 1) % MaxPlayerCount;
}

void GameState::SetFirstPlayer(int playerNum)
{
	if (playerNum < 0 || playerNum >= MaxPlayerCount)
		return;

	currPlayerNumber = playerNum;
	///TODO: Implement this function to set which player goes first this round
}

// ========== Phase Management ==========

PhaseType GameState::GetCurrentPhase() const
{
	return currentPhase;
}

void GameState::SetCurrentPhase(PhaseType phase)
{
	currentPhase = phase;
}

void GameState::AdvancePhase()
{
	// Currently only PHASE_MOVEMENT exists.
	// [OPTIONAL BONUS] If you add PHASE_SHOOTING to the PhaseType enum (DEFS.h),
	// update this to cycle:  MOVEMENT --> SHOOTING --> MOVEMENT
	currentPhase = PHASE_MOVEMENT;
}

// ========== End-Game ==========

bool GameState::GetEndGame() const
{
	return endGame;
}

void GameState::SetEndGame(bool end)
{
	endGame = end;
}

// ========== Drawing Helpers ==========

void GameState::DrawAllPlayers(Output* pOut) const
{
	///TODO: Draw all players
	for (int i = 0; i < MaxPlayerCount;i++)                  // donee 
	{
		PlayerList[i]->Draw(pOut);     // draw function in player classs                        
	}
}

void GameState::AppendPlayersInfo(string& info) const
{
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		PlayerList[i]->AppendPlayerInfo(info);
		if (i < MaxPlayerCount - 1)
			info += ", ";
	}
	info += " | Curr = " + to_string(currPlayerNumber);
}
