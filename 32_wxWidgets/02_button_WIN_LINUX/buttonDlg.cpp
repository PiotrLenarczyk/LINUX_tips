///-----------------------------------------------------------------
///
/// @file      buttonDlg.cpp
/// @author    Piotr
/// Created:   3/16/2019 11:25:22 PM
/// @section   DESCRIPTION
///            buttonDlg class implementation
///
///------------------------------------------------------------------

#include "buttonDlg.h"

//Do not add custom headers
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// buttonDlg
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(buttonDlg,wxDialog)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(buttonDlg::OnClose)
	EVT_BUTTON(ID_WXBUTTON1,buttonDlg::WxButton1Click)
END_EVENT_TABLE()
////Event Table End

buttonDlg::buttonDlg(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
	CreateGUIControls();
}

buttonDlg::~buttonDlg()
{
} 

void buttonDlg::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End.
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	WxRichTextCtrl1 = new wxRichTextCtrl(this, ID_WXRICHTEXTCTRL1, _(""), wxPoint(50, 38), wxSize(172, 114), wxRE_MULTILINE, wxDefaultValidator, _("WxRichTextCtrl1"));
	WxRichTextCtrl1->SetMaxLength(0);
	WxRichTextCtrl1->AppendText(_("WxRichTextCtrl1"));
	WxRichTextCtrl1->SetFocus();
	WxRichTextCtrl1->SetInsertionPointEnd();

	WxButton1 = new wxButton(this, ID_WXBUTTON1, _("clear"), wxPoint(155, 222), wxSize(113, 42), 0, wxDefaultValidator, _("WxButton1"));

	SetTitle(_("button"));
	SetIcon(wxNullIcon);
	SetSize(8,8,320,334);
	Center();
	
	////GUI Items Creation End
}

void buttonDlg::OnClose(wxCloseEvent& /*event*/)
{
	Destroy();
}

void clearRichText(wxRichTextCtrl& wxRText)
{   wxRText.SetValue("");
};

/*
 * WxButton1Click
 */
void buttonDlg::WxButton1Click(wxCommandEvent& event)
{   clearRichText(*WxRichTextCtrl1);
	// insert your code here
}

