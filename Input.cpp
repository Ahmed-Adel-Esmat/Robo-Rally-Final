#include "Input.h"

#include "Output.h"

//======================================================================================//
//								General Functions									    //
//======================================================================================//

Input::Input(window* pW)
{
	pWind = pW; // point to the passed window
}

////////////////////////////////////////////////////////////////////////////////////////// 

void Input::GetPointClicked(int& x, int& y) const
{
	pWind->WaitMouseClick(x, y); // Note: x and y of WaitMouseClick are sent by reference
}

////////////////////////////////////////////////////////////////////////////////////////// 

string Input::GetSrting(Output* pO) const
{
	string Label;
	char Key;
	while (1)
	{
		pWind->WaitKeyPress(Key);
		if (Key == 27)	// ESCAPE key is pressed
			return "";	// returns nothing as user has cancelled label
		if (Key == 13)	// ENTER key is pressed
			return Label;
		if ((Key == 8) && (Label.size() >= 1))	// BackSpace is pressed
			Label.resize(Label.size() - 1);
		else
			Label += Key;
		if (pO)
			pO->PrintMessage(Label);
	}
}

////////////////////////////////////////////////////////////////////////////////////////// 

int Input::GetInteger(Output* pO) const
{

	///TODO: implement the GetInteger function as described in Input.h file 
	//       using function GetString() defined above and function stoi()
	string s = GetSrting(pO);
	if (s == "" || s.find_first_not_of(' ') == string::npos)
	{
		return -1;
	}

	for (int i = 0; i < s.length(); i++)
	{
		// Allow a negative sign '-' ONLY at the very beginning
		if (i == 0 && s[i] == '-')
		{
			if (s.length() == 1) return -1; // Just a dash is not a number
			continue;
		}

		// If any character is not a digit (0-9), the whole thing is invalid
		if (isdigit(s[i]) == false)
		{
			return -1;
		}
	}

	return stoi(s);




	// Note: stoi(s) converts string s into its equivalent integer (for example, "55" is converted to 55)
}

//======================================================================================//
//								Game  Functions									        //
//======================================================================================//

ActionType Input::GetUserAction() const
{
	int x = -1, y = -1;
	GetPointClicked(x, y);

	//  ============ GUI in the Design mode ============
	if (UI.InterfaceMode == MODE_DESIGN)
	{
		// [1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			// Check which Menu item was clicked
			// ==> This assumes that menu items are lined up horizontally <==

			int clickedItemOrder = (x / UI.MenuItemWidth);

			// Divide x coord of the point clicked by the menu item width (integer division)
			// If division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (clickedItemOrder)
			{
			case ITM_SET_FLAG_CELL: return SET_FLAG_CELL;


				///TODO: Add cases for the other items of Design Mode
			case ITM_ADD_ANTENNA: return ADD_ANTENNA;
			case ITM_ADD_BELT: return ADD_BELT;
			case ITM_ADD_WATER_PIT: return ADD_WATER_PIT;
			case ITM_ADD_DANGER_ZONE: return ADD_DANGER_ZONE;
			case ITM_ADD_WORKSHOP: return ADD_WORKSHOP;
			case ITM_ADD_ROTATING_GEAR: return ADD_ROTATING_GEAR;
			case ITM_COPY: return COPY_ITEM;
			case ITM_CUT: return CUT_ITEM;
			case ITM_PASTE: return PASTE_ITEM;
			case ITM_DELETE: return DEL_ITEM;
			case ITM_SAVE: return SAVE_GRID;
			case ITM_LOAD: return LOAD_GRID;
			case ITM_SWITCH_TO_PLAY_MODE: return TO_PLAY_MODE;
			case ITM_EXIT: return EXIT;






			default: return EMPTY;	// A click on empty place in toolbar
			}
		}

		// [2] User clicks on the grid area
		if ((y >= UI.ToolBarHeight) && (y < UI.height - UI.StatusBarHeight))
		{
			return GRID_AREA;
		}

		// [3] User clicks on the status bar
		return STATUS;
	}

	// ============ GUI in the Play mode ============
	else
	{
		///TODO:
		// perform checks similar to Design mode checks above for the Play Mode
		// and return the corresponding ActionType

		//

		if (y >= 0 && y < UI.ToolBarHeight)
		{
			// Calculate which Play Mode icon was clicked
			int clickedItemOrder = (x / UI.MenuItemWidth);

			switch (clickedItemOrder)
			{
			case ITM_SELECT_COMMAND:   return SELECT_COMMAND;
			case ITM_EXECUTE_COMMANDS: return EXECUTE_COMMANDS;
			case ITM_REBOOT_REPAIR:    return REBOOT_REPAIR;
			case ITM_NEW_GAME:         return NEW_GAME;
			case ITM_SWITCH_TO_DESIGN_MODE: return TO_DESIGN_MODE;
			case ITM_EXIT_PLAY:        return EXIT;



			default: return EMPTY;
			}
		}
		if ((y >= UI.ToolBarHeight) && (y < UI.height - UI.StatusBarHeight))
		{
			return GRID_AREA;
		}

		return STATUS;

		//





	}

}

////////////////////////////////////////////////////////////////////////////////////////// 

CellPosition Input::GetCellClicked() const
{
	int x, y;
	pWind->WaitMouseClick(x, y);	// Get the coordinates of the user click

	CellPosition cellPos(-1, -1);

	if (UI.InterfaceMode == MODE_DESIGN)
	{
		if (y >= UI.ToolBarHeight && y < (UI.height - UI.StatusBarHeight))
		{
			///TODO: SetHCell and SetVCell of the object cellPost appropriately
			//       using the coordinates x, y and the appropriate variables of the UI_Info Object (UI)
			int h = x / UI.CellWidth;
			int v = (y - UI.ToolBarHeight) / UI.CellHeight;

			cellPos.SetHCell(h);
			cellPos.SetVCell(v);



		}
	}

	return cellPos;
}

//////////////////////////////////////////////////////////////////////////////////////////

int Input::GetSelectedCommandIndex() const
{
	int x = -1, y = -1;
	GetPointClicked(x, y);

	if ((y >= UI.height - UI.StatusBarHeight - UI.CommandsBarHeight - UI.AvailableCommandsYOffset) && (y < UI.height - UI.StatusBarHeight))
	{
		if (x < UI.AvailableCommandsXOffset || x > UI.AvailableCommandsXOffset + (UI.CommandItemWidth / 2) * MaxAvailableCommands)
			return -1;

		return (x - UI.AvailableCommandsXOffset) / (UI.CommandItemWidth / 2);;
	}

	return -1;
}

////////////////////////////////////////////////////////////////////////////////////////// 
