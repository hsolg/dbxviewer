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

#include "MessagePart.h"


char ascii2byte(char a)
{
    if (a < 0x40) {
        return a - 0x30;
    } else {
        return a - 0x37;
    }
}

MessagePart::MessagePart(const char *partStr) :
m_contentType(CONTENT_TYPE_UNKNOWN),
m_encoding(ENCODING_UNKNOWN),
m_isAttachment(false),
m_size(0),
m_pData(NULL)
{
    // We need the same code as for message header probably.
    // Split into header and body and parse header.
    CString header;
    const char *p;
    DbxUtil::GetHeader(partStr, header, &p);
    p += 2; // Skip blank line between header and body.
    CMapStringToString headerFields;
    DbxUtil::ParseHeader(header, headerFields);
    // Delay decoding until part is saved. No because then we dont know the size. Make subclasses?

    CString fieldValue;
    if (headerFields.Lookup("content-type", fieldValue)) {
        if (fieldValue.Find("application/octet-stream") >= 0) {
            m_contentType = CONTENT_TYPE_APPLICATION_OCTET_STREAM;
        } else if (fieldValue.Find("text/plain") >= 0) {
            m_contentType = CONTENT_TYPE_TEXT_PLAIN;
        }
    }
    if (headerFields.Lookup("content-transfer-encoding", fieldValue)) {
        if (fieldValue.Find("base64") >= 0) {
            m_encoding = ENCODING_BASE64;
        } else if (fieldValue.Find("quoted-printable") >= 0) {
            m_encoding = ENCODING_QUOTED_PRINTABLE;
        }
    }
    if (headerFields.Lookup("content-disposition", fieldValue)) {
        if (fieldValue.Find("attachment") >= 0) {
            m_isAttachment = true;
            DbxUtil::GetAttribute(fieldValue, "filename=", m_filename);
        }
    }
//    if (m_isAttachment) {
        CString body = p;
        if (m_encoding == ENCODING_BASE64) {
            const unsigned inputSize = body.GetLength();
            const unsigned outputSize = (inputSize / 4) * 3;
            m_pData = (unsigned char *)malloc(outputSize);
            if (m_pData) {
                DbxUtil::Base64Decode(body, inputSize, m_pData);
                m_size = outputSize;
            }
        } else if (m_encoding == ENCODING_QUOTED_PRINTABLE) {
            const unsigned bodySize = body.GetLength();
            const char *ps = (const char *)body;
            const char *pe = ps + bodySize;
            m_pData = (unsigned char *)malloc(bodySize + 1);
            if (m_pData) {
//                for (int i=0; i<bodySize; i++) {
//                    if (ps[i] == '=') {
//                    } else {
//                    }
//                }
                unsigned char *pt = m_pData;
                while (ps < pe) {
                    if (*ps == '=') {
                        if ((ps + 1) < pe) {
                            if ((*(ps + 1) == '\r') || (*(ps + 1) == '\n')) {
                                ps++;
                                while ((*ps == '\r') || (*ps == '\n')) {
                                    ps++;
                                }
                            } else {
                                if ((ps + 2) < pe) {
                                    *(pt++) = (ascii2byte(*(ps + 1)) << 4) | ascii2byte(*(ps + 2));
                                    ps += 3;
                                } else {
                                    break; // This should never happen.
                                }
                            }
                        } else {
                            break;
                        }
                    } else {
                        *(pt++) = *(ps++);
                    }
                }
                *pt = 0;
                m_size = pt - m_pData;
            }
        } else {
            const unsigned bodySize = body.GetLength();
            m_pData = (unsigned char *)malloc(bodySize + 1);
            if (m_pData) {
                memcpy(m_pData, body, bodySize);
                m_pData[bodySize] = 0;
                m_size = bodySize;
            }
        }
//    }
}

MessagePart::~MessagePart()
{
    if (m_pData) {
        free(m_pData);
        m_pData = NULL;
    }
}

bool MessagePart::IsBinary()
{
    return ! IsTextual();
}

bool MessagePart::IsTextual()
{
    return ((m_contentType == CONTENT_TYPE_UNKNOWN) || (m_contentType == CONTENT_TYPE_TEXT_PLAIN));
}

bool MessagePart::IsAttachment()
{
    return m_isAttachment;
}

void MessagePart::GetFilename(CString &filename)
{
    filename = m_filename;
}

unsigned MessagePart::GetSize()
{
    return m_size;
}

void MessagePart::GetAttachment(unsigned char **ppData, unsigned *pDataSize)
{
    *ppData = m_pData;
    *pDataSize = m_size;
}
