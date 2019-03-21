///-----------------------------------------------------------------
///
/// @file      rtShowDlg.cpp
/// @author    Piotr Lenarczyk
/// Created:   21.03.2019 07:35:23
/// @section   DESCRIPTION
///            rtShowDlg class implementation
///
///------------------------------------------------------------------

#include "rtShowDlg.h"

//Do not add custom headers
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End
#include "incs.h"
//----------------------------------------------------------------------------
// rtShowDlg
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(rtShowDlg,wxDialog)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(rtShowDlg::OnClose)
	EVT_ACTIVATE(rtShowDlg::rtShowDlgActivate)
	EVT_BUTTON(ID_WXBUTTON_DISASSEMBLE,rtShowDlg::WxButton_DisassembleClick)
	EVT_BUTTON(ID_WXBUTTON_ELFHEX,rtShowDlg::WxButton_ElfHexClick)
	EVT_BUTTON(ID_WXBUTTON_COMPILERUN,rtShowDlg::WxButton_CompileRunClick)
	EVT_BUTTON(ID_WXBUTTON_CHOOSEFILE,rtShowDlg::WxButton_ChooseFileClick)
	EVT_BUTTON(ID_WXBUTTON_ASSEMBLY,rtShowDlg::WxButton_AssembleClick)
	EVT_BUTTON(ID_WXBUTTON_PREPROCESS,rtShowDlg::WxButton_PreprocessClick)
END_EVENT_TABLE()
////Event Table End

rtShowDlg::rtShowDlg(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
	CreateGUIControls();
}

rtShowDlg::~rtShowDlg()
{
} 

void rtShowDlg::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End.
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	WxButton_Disassemble = new wxButton(this, ID_WXBUTTON_DISASSEMBLE, _("Disassembly"), wxPoint(316, 527), wxSize(80, 35), 0, wxDefaultValidator, _("WxButton_Disassemble"));

	WxButton_ElfHex = new wxButton(this, ID_WXBUTTON_ELFHEX, _("ElfHex"), wxPoint(216, 527), wxSize(97, 35), 0, wxDefaultValidator, _("WxButton_ElfHex"));

	WxStaticText_CurrentMode = new wxStaticText(this, ID_WXSTATICTEXT_CURRENTMODE, _("Mode"), wxPoint(453, 527), wxSize(136, 34), wxST_NO_AUTORESIZE, _("WxStaticText_CurrentMode"));

	WxStaticText_CurrentStatus = new wxStaticText(this, ID_WXSTATICTEXT_CURRENTSTATUS, _("Status"), wxPoint(594, 527), wxSize(43, 35), wxST_NO_AUTORESIZE, _("WxStaticText_CurrentStatus"));

	WxButton_CompileRun = new wxButton(this, ID_WXBUTTON_COMPILERUN, _("Compile; Run; Loop;"), wxPoint(636, 527), wxSize(144, 35), 0, wxDefaultValidator, _("WxButton_CompileRun"));

	WxButton_ChooseFile = new wxButton(this, ID_WXBUTTON_CHOOSEFILE, _("File"), wxPoint(397, 526), wxSize(56, 35), 0, wxDefaultValidator, _("WxButton_ChooseFile"));

	WxButton_Assembly = new wxButton(this, ID_WXBUTTON_ASSEMBLY, _("Assembly"), wxPoint(3, 527), wxSize(110, 35), 0, wxDefaultValidator, _("WxButton_Assembly"));

	WxButton_Preprocess = new wxButton(this, ID_WXBUTTON_PREPROCESS, _("Preprocess"), wxPoint(114, 527), wxSize(100, 35), 0, wxDefaultValidator, _("WxButton_Preprocess"));

	WxRichTextCtr_Console = new wxRichTextCtrl(this, ID_WXRICHTEXTCTR_CONSOLE, _(""), wxPoint(1, 1), wxSize(781, 528), 0, wxDefaultValidator, _("WxRichTextCtr_Console"));
	WxRichTextCtr_Console->SetMaxLength(0);
	WxRichTextCtr_Console->AppendText(_("WxRichTextCtrl1"));
	WxRichTextCtr_Console->SetFocus();
	WxRichTextCtr_Console->SetInsertionPointEnd();

	SetTitle(_("rtShow"));
	SetIcon(wxNullIcon);
	SetSize(8,8,800,600);
	Center();
	
	////GUI Items Creation End
}

void rtShowDlg::OnClose(wxCloseEvent& /*event*/)
{
	Destroy();
}

/*
 * WxButton_PreprocessClick
 */
void rtShowDlg::WxButton_PreprocessClick(wxCommandEvent& event)
{
	// insert your code here
}

/*
 * WxButton_AssembleClick
 */
void rtShowDlg::WxButton_AssembleClick(wxCommandEvent& event)
{
    tmp1 = 0x1;
	// insert your code here
}

/*
 * WxButton_GoToLineClick
 */
void rtShowDlg::WxButton_GoToLineClick(wxCommandEvent& event)
{
	// insert your code here
}

/*
 * WxButton_ChooseFileClick
 */
void rtShowDlg::WxButton_ChooseFileClick(wxCommandEvent& event)
{
	// insert your code here
}

/*
 * WxButton_CompileClick
 */
void rtShowDlg::WxButton_CompileClick(wxCommandEvent& event)
{
	// insert your code here
}

/*
 * rtShowDlgActivate
 */
void rtShowDlg::rtShowDlgActivate(wxActivateEvent& event)
{
	// insert your code here
}

/*
 * WxButton_CompileRunClick
 */
void rtShowDlg::WxButton_CompileRunClick(wxCommandEvent& event)
{
	// insert your code here
}

/*
 * WxButton_ElfHexClick
 */
void rtShowDlg::WxButton_ElfHexClick(wxCommandEvent& event)
{
	// insert your code here
}

/*
 * WxButton_DisassembleClick
 */
void rtShowDlg::WxButton_DisassembleClick(wxCommandEvent& event)
{
	// insert your code here
}
