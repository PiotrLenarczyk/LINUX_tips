//---------------------------------------------------------------------------
//
// Name:        buttonApp.cpp
// Author:      Piotr
// Created:     3/16/2019 11:25:22 PM
// Description: 
//
//---------------------------------------------------------------------------
#include "buttonApp.h"
#include "buttonDlg.cpp"


IMPLEMENT_APP(buttonDlgApp)

bool buttonDlgApp::OnInit()
{
	buttonDlg* dialog = new buttonDlg(NULL);
	SetTopWindow(dialog);
	dialog->Show(true);
	return true;
}
 
int buttonDlgApp::OnExit()
{
	return 0;
}
