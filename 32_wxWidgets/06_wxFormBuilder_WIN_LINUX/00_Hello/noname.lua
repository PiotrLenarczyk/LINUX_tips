----------------------------------------------------------------------------
-- Lua code generated with wxFormBuilder (version Feb 16 2016)
-- http://www.wxformbuilder.org/
----------------------------------------------------------------------------

-- Load the wxLua module, does nothing if running from wxLua, wxLuaFreeze, or wxLuaEdit
package.cpath = package.cpath..";./?.dll;./?.so;../lib/?.so;../lib/vc_dll/?.dll;../lib/bcc_dll/?.dll;../lib/mingw_dll/?.dll;"
require("wx")

UI = {}


-- create MyFrame1
UI.MyFrame1 = wx.wxFrame (wx.NULL, wx.wxID_ANY, "", wx.wxDefaultPosition, wx.wxSize( 800,600 ), wx.wxDEFAULT_FRAME_STYLE+wx.wxTAB_TRAVERSAL )
	UI.MyFrame1:SetSizeHints( wx.wxDefaultSize, wx.wxDefaultSize )
	
	UI.bSizer1 = wx.wxBoxSizer( wx.wxVERTICAL )
	
	UI.m_notebook1 = wx.wxNotebook( UI.MyFrame1, wx.wxID_ANY, wx.wxDefaultPosition, wx.wxDefaultSize, 0 )
	
	UI.bSizer1:Add( UI.m_notebook1, 1, wx.wxEXPAND  + wx. wxALL, 5 )
	
	
	UI.MyFrame1:SetSizer( UI.bSizer1 )
	UI.MyFrame1:Layout()
	UI.m_menubar2 = wx.wxMenuBar( 0 )
	UI. = wx.wxMenu()
	UI.m_menubar2:Append( UI., "" ) 
	
	UI.MyFrame1:SetMenuBar( UI.m_menubar2 )
	
	
	UI.MyFrame1:Centre( wx.wxBOTH )


--wx.wxGetApp():MainLoop()
