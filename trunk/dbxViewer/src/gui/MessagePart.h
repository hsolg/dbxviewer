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

#ifndef MESSAGEPART_H
#define MESSAGEPART_H

#include <afx.h>

#include "DbxUtil.h"

class MessagePart
{
public:
    MessagePart(const char *partStr);
    virtual ~MessagePart();
    bool IsBinary();
    bool IsTextual();
    bool IsAttachment();
    void GetFilename(CString &filename);
    unsigned GetSize();
    void GetAttachment(unsigned char **ppData, unsigned *pDataSize);
protected:
    CString n_header;
    CString m_body;
    CString m_filename;
    CONTENT_TYPE m_contentType;
    ENCODING m_encoding;
    bool m_isAttachment;
    unsigned m_size; // Attachment size.
    unsigned char *m_pData;
};

#endif
