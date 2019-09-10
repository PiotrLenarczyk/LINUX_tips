//https://wiki.wxwidgets.org/Catching_key_events_globally
//KeyDown handler
#include "wx/wx.h" 

class MyApp: public wxApp
{
    virtual bool OnInit();
};

class MyFrame: public wxFrame
{
public:

    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

    void OnKeyDown(wxKeyEvent& event);
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame( "Hello World", wxPoint(50,50), wxSize(450,340) );
    frame->Show(TRUE);
    SetTopWindow(frame);
    return TRUE;
} 

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame((wxFrame *)NULL, -1, title, pos, size)
{
    wxPanel* mainPane = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxWANTS_CHARS);
    mainPane->Bind(wxEVT_CHAR_HOOK, &MyFrame::OnKeyDown, this);
}

void MyFrame::OnKeyDown(wxKeyEvent& event)
{
    wxMessageBox(wxString::Format("KeyDown: %i\n", (int)event.GetKeyCode()));
    event.Skip();
}
