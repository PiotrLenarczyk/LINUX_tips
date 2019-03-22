/***************************************************************
 * Name:      _0_helloBlock_wxWidgetApp.h
 * Purpose:   Defines Application Class
 * Author:    PiotrLenarczyk (piotr.lenarczyk@wat.edu.pl)
 * Created:   2019-03-22
 * Copyright: PiotrLenarczyk (https://www.github.com/PiotrLenarczyk/LINUX_tips.git)
 * License:
 **************************************************************/

#ifndef _0_HELLOBLOCK_WXWIDGETAPP_H
#define _0_HELLOBLOCK_WXWIDGETAPP_H

#include <wx/app.h>

class _0_helloBlock_wxWidgetApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // _0_HELLOBLOCK_WXWIDGETAPP_H
