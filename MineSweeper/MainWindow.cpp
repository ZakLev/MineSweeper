#include "MainWindow.h"

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
//EVT_BUTTON(10001, OnButtonClicked)
wxEND_EVENT_TABLE()

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "MineSweeper", wxPoint(30, 30), wxSize(800, 600))
{
	btn = new wxButton * [nFieldWidth * nFieldHeight];
	wxGridSizer  *grid = new wxGridSizer(nFieldWidth, nFieldHeight, 0, 0);

	nField = new int[nFieldWidth * nFieldHeight];

	wxFont font(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);

	for (int x = 0; x < nFieldWidth; x++)
	{
		for (int y = 0; y < nFieldHeight; y++)
		{
			btn[y * nFieldWidth + x] = new wxButton(this, 10000 + (y * nFieldWidth + x));
			btn[y * nFieldWidth + x]->SetFont(font);
			grid->Add(btn[y * nFieldWidth + x], 1, wxEXPAND | wxALL);

			btn[y * nFieldWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainWindow::OnButtonClicked, this);
			nField[y * nFieldWidth + x] = 0;

		}
	}
	this->SetSizer(grid);
	grid->Layout();
}
MainWindow::~MainWindow()
{
	delete[]btn;
}

void MainWindow::OnButtonClicked(wxCommandEvent &evt)
{
	//Get Coordinate of button in field array
	int x = (evt.GetId() - 10000) % nFieldWidth;
	int y = (evt.GetId() - 10000) / nFieldWidth;

	if (bFirstClick)
	{
		int mines = 30;

		while (mines)
		{
			int rx = rand() % nFieldWidth;
			int ry = rand() % nFieldHeight;

			if (nField[ry * nFieldWidth + rx] == 0 && rx != x && ry != y)
			{
				nField[ry * nFieldWidth + rx] = -1;
				mines--;
			}
		}
		bFirstClick = false;
	}

	//Disable Button
	btn[y*nFieldWidth + x]->Enable(false);

	//Check if Player hits mine
	if (nField[y * nFieldWidth + x] == -1)
	{
		wxMessageBox("BOOOOOOOOM !! - Game Over :(");

		//Reset Game
		bFirstClick = true;
		for (int x = 0; x < nFieldWidth; x++)
		{
			for (int y = 0; y < nFieldHeight; y++)
			{
				nField[y * nFieldWidth + x] = 0;
				btn[y*nFieldWidth + x]->SetLabel("");
				btn[y * nFieldWidth + x]->Enable(true);
			}
		}
	}
	else
	{
		// Count Neighbouring Mines
		int mine_count = 0;
		for(int i = -1; i < 2; i++)
			for (int j = -1; j < 2; j++)
			{
				if (x + i >= 0 && x + i < nFieldWidth && y + j >= 0 && y + j < nFieldHeight)
				{
					if (nField[(y + j) * nFieldWidth + (x + i)] == -1)
						mine_count++;
				}
			}
		//Update buttons label to show mine count if > 0
		if (mine_count > 0)
		{
			btn[y * nFieldWidth + x]->SetLabel(std::to_string(mine_count));
		}
	}
	
	evt.Skip();
}


