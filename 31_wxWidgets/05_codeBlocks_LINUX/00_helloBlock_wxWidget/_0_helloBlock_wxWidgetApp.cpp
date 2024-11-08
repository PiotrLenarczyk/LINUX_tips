/***************************************************************
 * Name:      _0_helloBlock_wxWidgetApp.cpp
 * Purpose:   Code for Application Class
 * Author:    PiotrLenarczyk (piotr.lenarczyk@wat.edu.pl)
 * Created:   2019-03-22
 * Copyright: PiotrLenarczyk (https://www.github.com/PiotrLenarczyk/LINUX_tips.git)
 * License:
 **************************************************************/

#include "_0_helloBlock_wxWidgetApp.h"

//(*AppHeaders
#include "_0_helloBlock_wxWidgetMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(_0_helloBlock_wxWidgetApp);

bool _0_helloBlock_wxWidgetApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	_0_helloBlock_wxWidgetDialog Dlg(0);
    	SetTopWindow(&Dlg);
    	Dlg.ShowModal();
    	wxsOK = false;
    }
    //*)
    return wxsOK;

}
        