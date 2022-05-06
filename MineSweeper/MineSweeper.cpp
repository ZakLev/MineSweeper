#include "MineSweeper.h"
#include "MainWindow.h"

wxIMPLEMENT_APP(MineSweeper);

MineSweeper::MineSweeper()
{
}

MineSweeper::~MineSweeper()
{
}

bool MineSweeper::OnInit()
{
	mainWindow = new MainWindow();
	mainWindow->Show();
	return true;
}