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

#ifndef DBXUTIL_H
#define DBXUTIL_H

#include <afx.h>


typedef enum {
    CONTENT_TYPE_UNKNOWN,
    CONTENT_TYPE_TEXT_PLAIN,
    CONTENT_TYPE_APPLICATION_OCTET_STREAM,
    CONTENT_TYPE_MULTIPART_ALTERNATIVE,
    CONTENT_TYPE_MULTIPART_MIXED
} CONTENT_TYPE;

typedef enum {
    ENCODING_UNKNOWN,
    ENCODING_BASE64,
    ENCODING_QUOTED_PRINTABLE
} ENCODING;

class DbxUtil
{
public:
    static void GetHeader(const char *msg, CString &header, const char **ppEnd);
    static void ParseHeader(const CString header, CMapStringToString &map);
    static void GetAttribute(const CString fieldValue, const char *attrName, CString &value);
    static void GetDecodedBody();
    static void Base64Decode(const char *pSource, unsigned dataSize, unsigned char *pTarget);
protected:
};

#endif
