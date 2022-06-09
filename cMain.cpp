#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
EVT_BUTTON(10001, OnButtonClicked)
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "MineSweeper.com - wxWidgets!", wxPoint(30, 30), wxSize(800, 600))
{
	btn = new wxButton * [FieldWidth * FieldHeight];
	wxGridSizer* grid = new wxGridSizer(FieldWidth, FieldHeight, 0, 0);

	nField = new int[FieldWidth * FieldHeight];

	for (int x = 0; x < FieldWidth; x++)
	{
		for (int y = 0; y < FieldHeight; y++)
		{
			btn[y * FieldWidth + x] = new wxButton(this, 10000 + (y * FieldWidth + x));
			grid->Add(btn[y * FieldWidth + x], 1, wxEXPAND | wxALL);

			btn[y * FieldWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnButtonClicked, this);
			nField[y * FieldWidth + x] = 0;
		}
	}

	this->SetSizer(grid);
	grid->Layout();
}

cMain::~cMain()
{
	delete[]btn;

}


void cMain::OnButtonClicked(wxCommandEvent& evt)
{
	int x = (evt.GetId() - 10000) % FieldWidth;
	int y = (evt.GetId() - 10000) / FieldWidth;

	if (bFirstClick)
	{

		int mines = 30;

		while (mines)
		{
			int rx = rand() % FieldWidth;
			int ry = rand() % FieldHeight;

			if (nField[ry * FieldWidth + rx] == 0 && rx != x && ry != y)
			{
				nField[ry * FieldWidth + rx] = -1;
				mines--;
			}
		}


		bFirstClick = false;
	}

	//Disables the clicked button so it cannot be clicked again
	btn[y * FieldWidth + x]->Enable(false);

	if (nField[y * FieldWidth + x] == -1)
	{
		wxMessageBox("Boom! - Game Over");

		bFirstClick = true;
		for (int x = 0; x < FieldWidth; x++)
		{
			for (int y = 0; y < FieldHeight; y++)
			{
				nField[y * FieldWidth + x] = 0;
				btn[y * FieldWidth + x]->SetLabel("");
				btn[y * FieldWidth + x]->Enable(true);
			}
		}
	}
	else
	{
		int mine_count = 0;
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (x + i >= 0 && x + i < FieldWidth && y + j >= 0 && y + j < FieldHeight)
				{
					if (nField[(y + j) * FieldWidth + (x + i)] == -1)
						mine_count++;
				}
			}
		}

		if (mine_count > 0)
		{
			btn[y * FieldWidth + x]->SetLabel(std::to_string(mine_count));
		}
	}
	evt.Skip();
}