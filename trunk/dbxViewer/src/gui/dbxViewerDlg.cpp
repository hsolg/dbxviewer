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

#include "stdafx.h"
#include "dbxViewer.h"
#include "dbxViewerDlg.h"

#include "oedbx/dbxFileHeader.h"
#include "oedbx/dbxTree.h"
#include "oedbx/dbxFolderInfo.h"
#include "oedbx/dbxMessageInfo.h"
#include "oedbx/dbxMessage.h"

#include <iostream.h>
#include <fstream.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static LPCSTR szLicense =
_T("Copyright 2009 Henrik Solgaard. Based on the oedbx library, copyright 2002 Arne Schloh.\r\n\r\n"
"This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.\r\n\r\n"
"This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.\r\n\r\n"
"You should have received a copy of the GNU General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>.\r\n");

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CString	m_license;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	m_license = szLicense;
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Text(pDX, IDC_LICENSE, m_license);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDbxViewerDlg dialog

CDbxViewerDlg::CDbxViewerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDbxViewerDlg::IDD, pParent),
    m_pCurrentMessage(NULL)
{
	//{{AFX_DATA_INIT(CDbxViewerDlg)
	m_messageText = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDbxViewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDbxViewerDlg)
	DDX_Control(pDX, IDC_ATTACHMENT_LIST, m_attachmentList);
	DDX_Control(pDX, IDC_SAVE, m_saveButton);
	DDX_Control(pDX, IDCANCEL, m_quitButton);
	DDX_Control(pDX, IDC_ABOUT, m_aboutButton);
	DDX_Control(pDX, IDC_OPEN_FILE, m_openButton);
	DDX_Control(pDX, IDC_MESSAGE_TEXT, m_messageTextBox);
	DDX_Control(pDX, IDC_MESSAGE_LIST, m_messageList);
	DDX_Text(pDX, IDC_MESSAGE_TEXT, m_messageText);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDbxViewerDlg, CDialog)
	//{{AFX_MSG_MAP(CDbxViewerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN_FILE, OnOpenFile)
	ON_WM_SIZE()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_MESSAGE_LIST, OnItemchangedMessageList)
	ON_BN_CLICKED(IDC_ABOUT, OnAbout)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_LBN_SELCHANGE(IDC_ATTACHMENT_LIST, OnSelchangeAttachmentList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDbxViewerDlg message handlers

BOOL CDbxViewerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
    m_messageList.InsertColumn(0, "Time", LVCFMT_LEFT, 130);
    m_messageList.InsertColumn(1, "From", LVCFMT_LEFT, 180, 1);
    m_messageList.InsertColumn(2, "Subject", LVCFMT_LEFT, 200, 2);

    AdjustLayout();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDbxViewerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDbxViewerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDbxViewerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDbxViewerDlg::OnOpenFile() 
{
    CFileDialog openDialog(TRUE, "dbx", NULL, OFN_FILEMUSTEXIST, "Outlook express mailbox file (*.dbx)|*.dbx||", this);
    if (openDialog.DoModal() == IDOK) {
        CString path = openDialog.GetPathName();
        ReadDbxFile(path);
        // TODO Verify that reading succeeded.
        m_filename = path;
    }
    UpdateData(FALSE);
}

void format_time(const unsigned char *fileTime, char *buf, int bufSize)
{
    FILETIME fileTimeLocal;
    SYSTEMTIME systemTime;
    FileTimeToLocalFileTime((const FILETIME *)fileTime, &fileTimeLocal);
    FileTimeToSystemTime(&fileTimeLocal, &systemTime);
    int n = GetDateFormat(LOCALE_USER_DEFAULT, 0, &systemTime, NULL, buf, bufSize);
    if (n) {
        buf[n - 1] = ' ';
        GetTimeFormat(LOCALE_USER_DEFAULT, 0, &systemTime, NULL, buf + n, bufSize - n);
    }
}

void CDbxViewerDlg::ReadDbxFile(const char *filename) 
{
    m_messageList.DeleteAllItems();
    m_messageText = "";
    // The dbx file has to be opened in binary mode.
    std::ifstream ins(filename, std::ios::binary);

    DbxFileHeader fileHeader(ins);

    // Some const values like fhTreeRootNodePtr or fhEntries are defined
    // to allow easy access to the values stored in the DbxFileHeader
    int4 address = fileHeader.GetValue(fhTreeRootNodePtr),
         entries = fileHeader.GetValue(fhEntries        );

    if(address && entries) // if everything is OK
    { // The tree in the message dbx file stores the pointers to
        // all message infos objects
        // Read in the tree with all pointers
        DbxTree tree(ins,address,entries);

        // cycle through all values
        for(int4 j=0; j<entries; ++j)
        { // Get the address of the folder info
            address = tree.GetValue(j);
            // Read in the message info
            DbxMessageInfo messageInfo(ins,address);

            // Which indexes are used in the message info object
            int4 indexes = messageInfo.GetIndexes();

            if(indexes&(1<<miiMessageAddress)) // Only if a message is stored
            {
                const char *sender = messageInfo.GetString(9);
                if (sender == NULL) {
                    sender = messageInfo.GetString(14);
                }
                int4 length;
                const int timeBufSize = 64;
                char timeBuf[timeBufSize];
                format_time(messageInfo.GetValue(2, &length), timeBuf, timeBufSize);
                m_messageList.InsertItem(j, timeBuf);
                m_messageList.SetItemText(j, 1, sender);
                m_messageList.SetItemText(j, 2, messageInfo.GetString(8));
            }
        }
    }

    ins.close();
}

void CDbxViewerDlg::SaveAttachment(int attIndex, const char *path) {
    if (m_pCurrentMessage) {
        unsigned char *pData;
        unsigned dataSize;
        m_pCurrentMessage->GetAttachment(attIndex, &pData, &dataSize);
        HANDLE h = CreateFile(path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
        if (h != INVALID_HANDLE_VALUE) {
            DWORD bytesWritten;
            WriteFile(h, pData, dataSize, &bytesWritten, NULL);
            if (bytesWritten != dataSize) {
                MessageBox("Saving failed", "Save error", MB_OK | MB_ICONERROR);
            }
            CloseHandle(h);
        }
    }
}

void /*CDbxViewerDlg::*/ReadDbxMessage(const char *filename, int index, CString &msg) 
{
    // The dbx file has to be opened in binary mode.
    std::ifstream ins(filename, std::ios::binary);

    DbxFileHeader fileHeader(ins);

    // Some const values like fhTreeRootNodePtr or fhEntries are defined
    // to allow easy access to the values stored in the DbxFileHeader
    int4 address = fileHeader.GetValue(fhTreeRootNodePtr),
         entries = fileHeader.GetValue(fhEntries        );

    if(address && entries) // if everything is OK
    { // The tree in the message dbx file stores the pointers to
        // all message infos objects
        // Read in the tree with all pointers
        DbxTree tree(ins,address,entries);
        address = tree.GetValue(index);
        // Read in the message info
        DbxMessageInfo messageInfo(ins,address);

        // Which indexes are used in the message info object
        int4 indexes = messageInfo.GetIndexes();

        if(indexes&(1<<miiMessageAddress)) // Only if a message is stored
        {
            // Get the address of the message
            int4 messageAddress = messageInfo.GetValue(miiMessageAddress);
            // Extract the message
            DbxMessage message(ins, messageAddress);
            msg = message.GetText();
        }
    }

    ins.close();
}

void CDbxViewerDlg::AdjustLayout()
{
    CRect rect;
    GetClientRect(&rect);
    const int padding = 10;
    const int spacing = 10;
    const int buttonPanelHeight = 50;
    CRect buttonRect;
    m_openButton.GetWindowRect(&buttonRect);
    const int buttonWidth = buttonRect.right - buttonRect.left;
    const int listWidth = ((rect.right - rect.left) - padding - (spacing * 2)) / 2;
    const int listHeight = (rect.bottom - rect.top) - (2 * padding);
    const int msgWidth = ((rect.right - rect.left) - padding - (spacing * 2)) / 2;
    const int msgHeight = ((rect.bottom - rect.top) - buttonPanelHeight - (2 * padding) - spacing) * 0.75;
    const int attWidth = msgWidth - buttonWidth - spacing;
    const int attHeight = (rect.bottom - rect.top) - buttonPanelHeight - (2 * padding) - (2 * spacing) - msgHeight;
    m_messageList.SetWindowPos(&m_messageList, padding, padding, listWidth, listHeight, SWP_NOZORDER | SWP_SHOWWINDOW);
    m_messageTextBox.SetWindowPos(&m_messageList, padding + listWidth + spacing, padding + buttonPanelHeight + spacing, msgWidth, msgHeight, SWP_NOZORDER | SWP_SHOWWINDOW);
    m_attachmentList.SetWindowPos(&m_messageList, padding + listWidth + spacing, padding + buttonPanelHeight + spacing + msgHeight + spacing, attWidth, attHeight, SWP_NOZORDER | SWP_SHOWWINDOW);

    m_openButton.SetWindowPos(&m_openButton, padding + listWidth + spacing, padding, 0, 0, SWP_NOZORDER | SWP_SHOWWINDOW | SWP_NOSIZE);
    m_aboutButton.SetWindowPos(&m_aboutButton, padding + listWidth + spacing + buttonWidth + spacing, padding, 0, 0, SWP_NOZORDER | SWP_SHOWWINDOW | SWP_NOSIZE);
    m_quitButton.SetWindowPos(&m_quitButton, padding + listWidth + spacing + (2 * (buttonWidth + spacing)), padding, 0, 0, SWP_NOZORDER | SWP_SHOWWINDOW | SWP_NOSIZE);
    m_saveButton.SetWindowPos(&m_saveButton, padding + listWidth + spacing + attWidth + spacing, padding + buttonPanelHeight + spacing + msgHeight + spacing, 0, 0, SWP_NOZORDER | SWP_SHOWWINDOW | SWP_NOSIZE);

    m_openButton.Invalidate();
    m_aboutButton.Invalidate();
    m_quitButton.Invalidate();
    m_saveButton.Invalidate();
}

void CDbxViewerDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
    if (IsWindowVisible()) {
        AdjustLayout();
    }
}

void CDbxViewerDlg::OnItemchangedMessageList(NMHDR* pNMHDR, LRESULT* pResult) 
{
    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    if (pNMListView->uNewState & LVIS_SELECTED) {
        // Reset other controls.
        GetDlgItem(IDC_SAVE)->EnableWindow(FALSE);
        m_attachmentList.ResetContent();
        // Read the selected message.
        if (! m_filename.IsEmpty()) {
            CString msgTxt;
            ReadDbxMessage(m_filename, pNMListView->iItem, msgTxt);
            if (m_pCurrentMessage) {
                delete m_pCurrentMessage;
            }
            m_pCurrentMessage = new EmailMessage(msgTxt);
            m_pCurrentMessage->GetMessageText(m_messageText);
//m_messageText = msgTxt;
            // Read the attachments.
            unsigned numParts = m_pCurrentMessage->GetNumParts();
            for (int i=0; i<numParts; i++) {
                if (m_pCurrentMessage->IsPartAttachment(i)) {
                    CString filename;
                    m_pCurrentMessage->GetPartFilename(i, filename);
                    const int newIndex = m_attachmentList.AddString(filename);
                    m_attachmentList.SetItemData(newIndex, i);
                }
            }
        } else {
            MessageBox("Mailbox could not be opened", "Mailbox error", MB_OK | MB_ICONERROR);
        }
    } else {
        m_messageText = "";
    }
	*pResult = 0;
    UpdateData(FALSE);
}

void CDbxViewerDlg::OnAbout() 
{
    CAboutDlg dlgAbout;
    dlgAbout.DoModal();
}

void CDbxViewerDlg::OnSave() 
{
    CString attName;
    const int selIndex = m_attachmentList.GetCurSel();
    m_attachmentList.GetText(selIndex, attName);
    const int attIndex = m_attachmentList.GetItemData(selIndex);
    CFileDialog saveDialog(FALSE, NULL, attName, OFN_OVERWRITEPROMPT, "", this);
    if (saveDialog.DoModal() == IDOK) {
        CString path = saveDialog.GetPathName();
        SaveAttachment(attIndex, path);
        // TODO Verify that saving succeeded.
    }
    UpdateData(FALSE);
}

void CDbxViewerDlg::OnSelchangeAttachmentList() 
{
    if (m_attachmentList.GetCurSel() == LB_ERR) {
        GetDlgItem(IDC_SAVE)->EnableWindow(FALSE);
    } else {
        GetDlgItem(IDC_SAVE)->EnableWindow(TRUE);
    }
}
