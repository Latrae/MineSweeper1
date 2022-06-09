#pragma once


#include "wx/wx.h"
#include "cMain.h"




class cApp : public wxApp
{
	bool OnInit();

private:
	cMain* m_frame1 = nullptr;

public:
	cApp();
	~cApp();
};
