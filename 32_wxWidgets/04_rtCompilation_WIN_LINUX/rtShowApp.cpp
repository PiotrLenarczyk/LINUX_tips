//---------------------------------------------------------------------------
//
// Name:        rtShowApp.cpp
// Author:      Piotr Lenarczyk
// Created:     21.03.2019 07:35:22
// Description: 
//
//---------------------------------------------------------------------------


#ifdef _WIN32
    #include "rtShowApp.h"
    #include "rtShowDlg.h"
#elif   __linux__
    #include "rtShowApp.h"
    #include "rtShowDlg.cpp"
#endif


IMPLEMENT_APP(rtShowDlgApp)

bool rtShowDlgApp::OnInit()
{	mainMain();
	rtShowDlg* dialog = new rtShowDlg(NULL);
	SetTopWindow(dialog);
	dialog->Show(true);		
	return true;
}
 
int rtShowDlgApp::OnExit()
{
	return 0;
}
