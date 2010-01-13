/*****************************************************************************

    Copyright 2009 Henrik Solgaard <henrso@ifi.uio.no>

    This file is part of dbxViewer.

    dbxViewer is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    dbxViewer is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with dbxViewer.  If not, see <http://www.gnu.org/licenses/>.

*****************************************************************************/

#if !defined(AFX_DBXVIEWER_H__2C942076_407B_4A36_ABB5_EB49BC36E729__INCLUDED_)
#define AFX_DBXVIEWER_H__2C942076_407B_4A36_ABB5_EB49BC36E729__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDbxViewerApp:
// See dbxViewer.cpp for the implementation of this class
//

class CDbxViewerApp : public CWinApp
{
public:
	CDbxViewerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDbxViewerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDbxViewerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBXVIEWER_H__2C942076_407B_4A36_ABB5_EB49BC36E729__INCLUDED_)
