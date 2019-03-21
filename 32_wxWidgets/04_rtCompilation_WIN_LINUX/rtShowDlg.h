///-----------------------------------------------------------------
///
/// @file      rtShowDlg.h
/// @author    Piotr Lenarczyk
/// Created:   21.03.2019 07:35:22
/// @section   DESCRIPTION
///            rtShowDlg class declaration
///
///------------------------------------------------------------------

#ifndef __RTSHOWDLG_H__
#define __RTSHOWDLG_H__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/dialog.h>
#else
	#include <wx/wxprec.h>
#endif

//Do not add custom headers between 
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/richtext/richtextctrl.h>
////Header Include End

////Dialog Style Start
#undef rtShowDlg_STYLE
#define rtShowDlg_STYLE wxCAPTION | wxSYSTEM_MENU | wxDIALOG_NO_PARENT | wxMINIMIZE_BOX | wxCLOSE_BOX
////Dialog Style End

class rtShowDlg : public wxDialog
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		rtShowDlg(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("rtShow"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = rtShowDlg_STYLE);
		virtual ~rtShowDlg();
		void WxButton_PreprocessClick(wxCommandEvent& event);
		void WxButton_AssembleClick(wxCommandEvent& event);
		void WxButton_GoToLineClick(wxCommandEvent& event);
		void WxButton_ChooseFileClick(wxCommandEvent& event);
		void WxButton_CompileClick(wxCommandEvent& event);
		void rtShowDlgActivate(wxActivateEvent& event);
		void WxButton_CompileRunClick(wxCommandEvent& event);
		void WxButton_ElfHexClick(wxCommandEvent& event);
		void WxButton_DisassembleClick(wxCommandEvent& event);
	
	private:
		//Do not add custom control declarations between 
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxButton *WxButton_Disassemble;
		wxButton *WxButton_ElfHex;
		wxStaticText *WxStaticText_CurrentMode;
		wxStaticText *WxStaticText_CurrentStatus;
		wxButton *WxButton_CompileRun;
		wxButton *WxButton_ChooseFile;
		wxButton *WxButton_Assembly;
		wxButton *WxButton_Preprocess;
		wxRichTextCtrl *WxRichTextCtr_Console;
		////GUI Control Declaration End
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_WXBUTTON_DISASSEMBLE = 1011,
			ID_WXBUTTON_ELFHEX = 1010,
			ID_WXSTATICTEXT_CURRENTMODE = 1009,
			ID_WXSTATICTEXT_CURRENTSTATUS = 1008,
			ID_WXBUTTON_COMPILERUN = 1007,
			ID_WXBUTTON_CHOOSEFILE = 1006,
			ID_WXBUTTON_ASSEMBLY = 1003,
			ID_WXBUTTON_PREPROCESS = 1002,
			ID_WXRICHTEXTCTR_CONSOLE = 1001,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
	
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
};

#endif
