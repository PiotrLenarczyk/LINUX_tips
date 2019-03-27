//---------------------------------------------------------------------------
//
// Name:        rtShowApp.h
// Author:      Piotr Lenarczyk
// Created:     21.03.2019 07:35:22
// Description: 
//
//---------------------------------------------------------------------------

#ifndef __RTSHOWDLGApp_h__
#define __RTSHOWDLGApp_h__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#else
	#include <wx/wxprec.h>
#endif

class rtShowDlgApp : public wxApp
{
	public:
		bool OnInit();
		int OnExit();
};

#endif
