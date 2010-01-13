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

#include "DbxUtil.h"


void DbxUtil::GetHeader(const char *msg, CString &header, const char **ppEnd)
{
    // Find the end of the header.
    const char *p = msg;
    while (*p != '\0') {
        if ((*p == '\r') && (*(p+1) == '\n')) {
            p += 2;
            if ((*p == '\r') && (*(p+1) == '\n')) {
                break;
            }
        } else {
            p++;
        }
    }
    // Save header as string.
    const int headerLength = p - msg;
    LPTSTR pBuffer = header.GetBufferSetLength(headerLength);
    memcpy(pBuffer, msg, headerLength);
    header.ReleaseBuffer(headerLength);
    *ppEnd = p;
}

void DbxUtil::ParseHeader(const CString header, CMapStringToString &map)
{
    const int headerLength = header.GetLength();
    int pos = 0;
    for(;;) {
        int endPos = header.Find("\r\n", pos);
        if (endPos > pos) {
            CString line = header.Mid(pos, endPos - pos);
            pos = endPos + 2;
            while ((pos < headerLength) && ((header.GetAt(pos) == ' ') || (header.GetAt(pos) == '\t'))) {
                endPos = header.Find("\r\n", pos);
                line += header.Mid(pos, endPos - pos);
                pos = endPos + 2;
            }
            int nameEnd = line.Find(':');
            if (nameEnd > 0) {
                CString key = line.Mid(0, nameEnd);
                CString value = line.Mid(nameEnd + 1, line.GetLength() - nameEnd);
                key.MakeLower();
                map.SetAt(key, value);
            }
        } else {
            // This should never happen.
            break;
        }
    }
}

void DbxUtil::GetAttribute(const CString fieldValue, const char *attrName, CString &value) {
    int bpos = fieldValue.Find(attrName);
    if (bpos >= 0) {
        bpos += strlen(attrName);
        if (fieldValue.GetAt(bpos) == '"') {
            bpos++;
            int bend = fieldValue.Find('"', bpos);
            if (bend > bpos) {
                value = fieldValue.Mid(bpos, bend - bpos);
            }
        } else {
            int bend = bpos;
            while (bend < fieldValue.GetLength()) {
                if ((fieldValue.GetAt(bend) == ' ') || (fieldValue.GetAt(bend) == '\t')) {
                    break;
                }
                bend++;
            }
            if (bend > bpos) {
                value = fieldValue.Mid(bpos, bend - bpos);
            }
        }
    }
}

void DbxUtil::GetDecodedBody()
{
}

static unsigned char lookupTable[] = {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3e, 0xff, 0xff, 0xff, 0x3f,
    0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e,
    0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
    0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

void DbxUtil::Base64Decode(const char *pSource, unsigned dataSize, unsigned char *pTarget)
{
    // The data size will always be a multiple of four.
    // Four characters are translated into three bytes.
    const char *pCurrentSource = pSource;
    unsigned char *pCurrentTarget = pTarget;
    const char *pEnd = pSource + dataSize;
    unsigned buf;
    while (pCurrentSource < pEnd) {
        while ((*pCurrentSource == '\r') || (*pCurrentSource == '\n')) {
            pCurrentSource++;
        }
        buf = 0;
        buf |= (lookupTable[pCurrentSource[0]] << 18);
        buf |= (lookupTable[pCurrentSource[1]] << 12);
        buf |= (lookupTable[pCurrentSource[2]] << 6);
        buf |= (lookupTable[pCurrentSource[3]]);
        *(pCurrentTarget++) = ((unsigned char *)&buf)[2];
        *(pCurrentTarget++) = ((unsigned char *)&buf)[1];
        *(pCurrentTarget++) = ((unsigned char *)&buf)[0];
        pCurrentSource += 4;
    }
}
