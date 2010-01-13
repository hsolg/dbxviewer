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

#if !defined(AFX_DBXVIEWERDLG_H__AFAE92AA_0F56_4BCB_8B60_71F142080D33__INCLUDED_)
#define AFX_DBXVIEWERDLG_H__AFAE92AA_0F56_4BCB_8B60_71F142080D33__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EmailMessage.h"
#include "MessagePart.h"


/////////////////////////////////////////////////////////////////////////////
// CDbxViewerDlg dialog

class CDbxViewerDlg : public CDialog
{
// Construction
public:
	CDbxViewerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDbxViewerDlg)
	enum { IDD = IDD_DBXVIEWER_DIALOG };
	CListBox	m_attachmentList;
	CButton	m_saveButton;
	CButton	m_quitButton;
	CButton	m_aboutButton;
	CButton	m_openButton;
	CEdit	m_messageTextBox;
	CListCtrl	m_messageList;
	CString	m_messageText;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDbxViewerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

    CString m_filename;
    EmailMessage *m_pCurrentMessage;

	// Generated message map functions
	//{{AFX_MSG(CDbxViewerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOpenFile();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnItemchangedMessageList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnAbout();
	afx_msg void OnSave();
	afx_msg void OnSelchangeAttachmentList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    void ReadDbxFile(const char *filename);
    void SaveAttachment(int attIndex, const char *path);
//    void ReadDbxMessage(const char *filename, int index);
    void AdjustLayout();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBXVIEWERDLG_H__AFAE92AA_0F56_4BCB_8B60_71F142080D33__INCLUDED_)
