#pragma once
//#include "../Users/non original orgasm/Desktop/sdks/wxWidgets-3.1.6/include/wx/wx.h"
#include "wx/wx.h"




class cMain : public wxFrame
{

public:
	cMain();
	~cMain();
	void OnButtonClicked(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();

public:
	int FieldWidth = 10;
	int FieldHeight = 10;
	wxButton** btn;
	int* nField = nullptr;
	bool bFirstClick = true;


};

