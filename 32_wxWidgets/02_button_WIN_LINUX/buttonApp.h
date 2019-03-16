//---------------------------------------------------------------------------
//
// Name:        buttonApp.h
// Author:      Piotr
// Created:     3/16/2019 11:25:22 PM
// Description: 
//
//---------------------------------------------------------------------------

#ifndef __BUTTONDLGApp_h__
#define __BUTTONDLGApp_h__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#else
	#include <wx/wxprec.h>
#endif

class buttonDlgApp : public wxApp
{
	public:
		bool OnInit();
		int OnExit();
};

#endif
