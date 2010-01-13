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

#include "EmailMessage.h"

#include "MessagePart.h"
#include "DbxUtil.h"

/*
<message header>

<message content>
--<separator>
<part header>

<content>
--<separator>
<part header>

<content>
--<separator>--
*/

/*
A header line that starts with space or tab is a continuation of the previous line.
*/

EmailMessage::EmailMessage(const char *txt)
{
    const char *p;
    DbxUtil::GetHeader(txt, m_header, &p);
    // Move pointer to start of body.
    p += 2;
    // Create header map.
    DbxUtil::ParseHeader(m_header, m_headerFields);
    CString fieldValue;
    m_contentType = CONTENT_TYPE_TEXT_PLAIN; // Default.
    if (m_headerFields.Lookup("content-type", fieldValue)) {
        if (fieldValue.Find("multipart/alternative") >= 0) {
            m_contentType = CONTENT_TYPE_MULTIPART_ALTERNATIVE;
        } else if (fieldValue.Find("multipart/mixed") >= 0) {
            m_contentType = CONTENT_TYPE_MULTIPART_MIXED;
        }
    }
    if (m_contentType == CONTENT_TYPE_TEXT_PLAIN) {
        m_body = p;
    } else {
        m_body = p;
        // Get boundary.
        CString boundary;
        DbxUtil::GetAttribute(fieldValue, "boundary=", boundary);
        // Read until first boundary.
        boundary = "--" + boundary;
        int boundarySize = boundary.GetLength();
        int ps = m_body.Find(boundary);
        ps += boundarySize;
        // Move to beginning of next line.
        while ((ps < m_body.GetLength()) && (m_body.GetAt(ps) != '\n')) {
            ps++;
        }
        ps++;
        boundary = "\r\n" + boundary;
        boundarySize = boundary.GetLength();
        int pe;
        CString part;
        for(;;) {
            pe = m_body.Find(boundary, ps);
            if (pe >= ps) {
                part = m_body.Mid(ps, pe - ps);
                m_attachmentList.AddTail(new MessagePart(part));
                ps = pe + boundarySize;
                if ((ps + 2) <= m_body.GetLength()) {
                    if ((m_body.GetAt(ps) == '-') && (m_body.GetAt(ps + 1) == '-')) {
                        break;
                    } else {
                        // Move to beginning of next line.
                        while ((ps < m_body.GetLength()) && (m_body.GetAt(ps) != '\n')) {
                            ps++;
                        }
                        ps++;
                    }
                } else {
                    // We should never get here.
                    MessageBox(NULL, "Unexpected error. No linebreak after boundary.", "Error", MB_OK | MB_ICONERROR);
                }
            } else {
                // We should never get here.
                MessageBox(NULL, "Error", "Unexpected error. Last boundary not properly terminated.", MB_OK | MB_ICONERROR);
                break;
            }
        }
    }
}

EmailMessage::~EmailMessage()
{
    MessagePart *pPart;
    POSITION pos = m_attachmentList.GetHeadPosition();
    while (pos) {
        pPart = (MessagePart *)m_attachmentList.GetNext(pos);
        if (pPart) {
            delete pPart;
        }
    }
}

EmailMessage::GetMessageText(CString &text)
{
    text = "";
    CString fieldValue;
    if (m_headerFields.Lookup("subject", fieldValue)) {
        text += "Subject:" + fieldValue + "\r\n";
    }
    if (m_headerFields.Lookup("from", fieldValue)) {
        text += "From:" + fieldValue + "\r\n";
    }
    if (m_headerFields.Lookup("date", fieldValue)) {
        text += "Date:" + fieldValue + "\r\n";
    }
    if (m_headerFields.Lookup("to", fieldValue)) {
        text += "To:" + fieldValue + "\r\n";
    }
    if (! text.IsEmpty()) {
        text += "\r\n";
    }
    if (m_contentType == CONTENT_TYPE_TEXT_PLAIN) {
        text += m_body;
    } else {
        bool foundTextPart = false;
        MessagePart *pPart;
        POSITION pos = m_attachmentList.GetHeadPosition();
        while (pPart = (MessagePart *)m_attachmentList.GetNext(pos)) {
            if (pPart->IsTextual()) {
                unsigned char *pData;
                unsigned dataSize;
                pPart->GetAttachment(&pData, &dataSize);
                text += (const char *)pData;
                foundTextPart = true;
                break;
            }
        }
        if (! foundTextPart) {
            text += m_body;
        }
    }
}

unsigned EmailMessage::GetNumParts()
{
    return m_attachmentList.GetCount();
}

bool EmailMessage::IsPartBinary(unsigned index)
{
    POSITION pos = m_attachmentList.FindIndex(index);
    if (pos == NULL) {
        return false;
    } else {
        return ((MessagePart *)m_attachmentList.GetAt(pos))->IsBinary();
    }
}

bool EmailMessage::IsPartAttachment(unsigned index)
{
    POSITION pos = m_attachmentList.FindIndex(index);
    if (pos == NULL) {
        return false;
    } else {
        return ((MessagePart *)m_attachmentList.GetAt(pos))->IsAttachment();
    }
}

void EmailMessage::GetPartFilename(unsigned index, CString &filename)
{
    POSITION pos = m_attachmentList.FindIndex(index);
    if (pos == NULL) {
        filename = "";
    } else {
        ((MessagePart *)m_attachmentList.GetAt(pos))->GetFilename(filename);
    }
}

void EmailMessage::GetAttachment(unsigned attIndex, unsigned char **ppData, unsigned *pDataSize)
{
    POSITION pos = m_attachmentList.FindIndex(attIndex);
    if (pos) {
        ((MessagePart *)m_attachmentList.GetAt(pos))->GetAttachment(ppData, pDataSize);
    }
}
