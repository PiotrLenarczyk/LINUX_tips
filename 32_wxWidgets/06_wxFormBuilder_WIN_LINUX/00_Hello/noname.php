<?php

/*
* PHP code generated with wxFormBuilder (version Feb 16 2016)
* http://www.wxformbuilder.org/
*
* PLEASE DO "NOT" EDIT THIS FILE!
*/

/*
 * Class MyFrame1
 */

class MyFrame1 extends wxFrame {
	
	function __construct( $parent=null ){
		parent::__construct ( $parent, wxID_ANY, wxEmptyString, wxDefaultPosition, new wxSize( 800,600 ), wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		$this->SetSizeHints( wxDefaultSize, wxDefaultSize );
		
		$bSizer1 = new wxBoxSizer( wxVERTICAL );
		
		$this->m_notebook1 = new wxNotebook( $this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
		
		$bSizer1->Add( $this->m_notebook1, 1, wxEXPAND | wxALL, 5 );
		
		
		$this->SetSizer( $bSizer1 );
		$this->Layout();
		$this->m_menubar2 = new wxMenuBar( 0 );
		$this-> = new wxMenu();
		$this->m_menubar2->Append( $this->, wxEmptyString ); 
		
		$this->SetMenuBar( $this->m_menubar2 );
		
		
		$this->Centre( wxBOTH );
	}
	
	
	function __destruct( ){
	}
	
}

?>
