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

#ifndef EMAILMESSAGE_H
#define EMAILMESSAGE_H

#include <afx.h>

#include "DbxUtil.h"


class EmailMessage
{
public:
    EmailMessage(const char *txt);
    virtual ~EmailMessage();
    GetMessageText(CString &text);
    unsigned GetNumParts();
    bool IsPartBinary(unsigned index);
    bool IsPartAttachment(unsigned index);
    void GetPartFilename(unsigned index, CString &filename);
    void GetAttachment(unsigned attIndex, unsigned char **ppData, unsigned *pDataSize);
protected:
    CONTENT_TYPE m_contentType;
    CString m_header;
    CString m_body;
    CMapStringToString m_headerFields;
    CPtrList m_attachmentList;
};

#endif
