/***************************************************************
 * Name:      _0_helloBlock_wxWidgetMain.h
 * Purpose:   Defines Application Frame
 * Author:    PiotrLenarczyk (piotr.lenarczyk@wat.edu.pl)
 * Created:   2019-03-22
 * Copyright: PiotrLenarczyk (https://www.github.com/PiotrLenarczyk/LINUX_tips.git)
 * License:
 **************************************************************/

#ifndef _0_HELLOBLOCK_WXWIDGETMAIN_H
#define _0_HELLOBLOCK_WXWIDGETMAIN_H

//(*Headers(_0_helloBlock_wxWidgetDialog)
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/stattext.h>
//*)

class _0_helloBlock_wxWidgetDialog: public wxDialog
{
    public:

        _0_helloBlock_wxWidgetDialog(wxWindow* parent,wxWindowID id = -1);
        virtual ~_0_helloBlock_wxWidgetDialog();

    private:

        //(*Handlers(_0_helloBlock_wxWidgetDialog)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        //*)

        //(*Identifiers(_0_helloBlock_wxWidgetDialog)
        static const long ID_STATICTEXT1;
        static const long ID_BUTTON1;
        static const long ID_STATICLINE1;
        static const long ID_BUTTON2;
        //*)

        //(*Declarations(_0_helloBlock_wxWidgetDialog)
        wxBoxSizer* BoxSizer1;
        wxBoxSizer* BoxSizer2;
        wxButton* Button1;
        wxButton* Button2;
        wxStaticLine* StaticLine1;
        wxStaticText* StaticText1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // _0_HELLOBLOCK_WXWIDGETMAIN_H
