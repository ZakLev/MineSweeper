#pragma once

#include "wx/wx.h"

class MainWindow;
class MineSweeper : public wxApp
{
private:
	MainWindow* mainWindow;
public:
	MineSweeper();
	~MineSweeper();
	virtual bool OnInit();

};

