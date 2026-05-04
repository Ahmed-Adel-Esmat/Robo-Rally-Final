#include "CellPosition.h"
#include "UI_Info.h"

CellPosition::CellPosition()
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1;
	hCell = -1;
}

CellPosition::CellPosition(int v, int h)
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1;
	hCell = -1;

	SetVCell(v);
	SetHCell(h);
}

CellPosition::CellPosition(int cellNum)
{
	(*this) = GetCellPositionFromNum(cellNum); // the function call with build a cell position (vCell and hCell)
	// from the passed (cellNum)
	// (*this) = ... --> this will copy the returned (vCell and hCell)
	//                   to the data members (vCell and hCell)
}

bool CellPosition::SetVCell(int v)
{
	///TODO: Implement this function as described in the .h file (don't forget the validation)
	//

	if (v >= 0 && v < NumVerticalCells)
	{
		vCell = v;
		return true;
	}
	else
	{
		return false;
	}
	//
}

bool CellPosition::SetHCell(int h)
{
	///TODO: Implement this function as described in the .h file (don't forget the validation)

	//

	if (h >= 0 && h < NumHorizontalCells)
	{
		hCell = h;
		return true;
	}
	else
	{
		return false;
	}

}

int CellPosition::VCell() const
{
	return vCell;
}

int CellPosition::HCell() const
{
	return hCell;
}

bool CellPosition::IsValidCell() const
{
	///TODO: Implement this function as described in the .h file

	//

	if (vCell >= 0 && vCell < NumVerticalCells && hCell >= 0 && hCell < NumHorizontalCells)
	{
		return true;
	}
	else
	{
		return false;
	}
	//
}

int CellPosition::GetCellNum() const
{



	return GetCellNumFromPosition(*this); // (*this) is the calling object of GetCellNum
	// which means the object of the current data members (vCell and hCell)
}

int CellPosition::GetCellNumFromPosition(const CellPosition& cellPosition)
{
	// Note:
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)
	// just define an integer that represents cell number and calculate it using the passed cellPosition then return it

	///TODO: Implement this function as described in the .h file

	//

	if (cellPosition.IsValidCell())
	{
		int cellNum = cellPosition.HCell() + 1 + (NumHorizontalCells * (NumVerticalCells - 1 - cellPosition.VCell()));
		return cellNum;
	}
	else
	{
		return -1;
	}

	//

}

CellPosition CellPosition::GetCellPositionFromNum(int cellNum)
{
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)

	CellPosition position;

	/// TODO: Implement this function as described in the .h file

	// Note: use the passed cellNum to set the vCell and hCell of the "position" variable declared inside the function
	//       I mean: position.SetVCell(...) and position.SetHCell(...) then return it

	//

	if (cellNum >= 1 && cellNum <= NumVerticalCells * NumHorizontalCells)
	{
		int v = NumVerticalCells - 1 - ((cellNum - 1) / NumHorizontalCells);
		int h = (cellNum - 1) % NumHorizontalCells;
		position.SetVCell(v);
		position.SetHCell(h);
	}
	else
	{
		position.SetVCell(-1);
		position.SetHCell(-1);
	}

	//


	return position;
}

void CellPosition::AddCellNum(int addedNum, Direction direction)
{

	/// TODO: Implement this function as described in the .h file

	//

	int newV = vCell;
	int newH = hCell;

	switch (direction)
	{
	case UP:
		newV = vCell - addedNum;
		break;

	case DOWN:
		newV = vCell + addedNum;
		break;

	case RIGHT:
		newH = hCell + addedNum;
		break;

	case LEFT:
		newH = hCell - addedNum;
		break;

	}

	if (newV >= 0 && newV < NumVerticalCells && newH >= 0 && newH < NumHorizontalCells)
	{
		vCell = newV;
		hCell = newH;

	}


	//

	// Note: this function updates the data members (vCell and hCell) of the calling object

}