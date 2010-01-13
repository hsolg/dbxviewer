/*****************************************************************************

    Copyright 2002 Arne Schloh

    This file is part of the oedbx library.

    oedbx is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    oedbx is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with oedbx.  If not, see <http://www.gnu.org/licenses/>.

*****************************************************************************/

//***************************************************************************************
#define AS_OE_IMPLEMENTATION

#include <oedbx/dbxFolderInfo.h>
//***************************************************************************************
const char * DbxFolderInfo::GetIndexText(int1 index) const
{ const char * text[MaxIndex] = {
     "folder index"                  , "index of the parent folder"              ,
     "folder name (newsgroup name)"  , "dbx file name"                           ,
     "id 04"                         , "registry key of the account"             ,
     "flags"                         , "messages in the folder"                  ,
     "unread messages in the folder" , "index for subfolders of 'local folders'" ,
     "local folder value"            , "id 0b"                                   ,
     "id 0c"                         , "max message index on server"             ,
     "min message index on server"   , "id 0f"                                   ,
     "max message index local"       , "min message index local"                 ,
     "messages to download"          , "id 13"                                   ,
     "id 14"                         , "id 15"                                   ,
     "id 16"                         , "id 17"                                   ,
     "id 18"                         , "id 19"                                   ,
     "id 1a"                         , "id 1b"                                   ,
     "watched messages"              , "id 1d"                                   ,
     "id 1e"                         , "id 1f"                                    };
  if(index<MaxIndex) return text[index];
  throw DbxException("Wrong index !");
}
//***************************************************************************************
IndexedInfoDataType DbxFolderInfo::GetIndexDataType(int1 index) const
{ IndexedInfoDataType dataType[MaxIndex] = {
      dtInt4 , dtInt4 , dtString,dtString,dtInt4 , dtString,dtInt4 , dtInt4 ,
      dtInt4 , dtInt4 , dtInt4 , dtNone , dtNone , dtInt4 , dtInt4 , dtInt4 ,
      dtInt4 , dtInt4 , dtInt4 , dtData , dtNone , dtData , dtNone , dtNone ,
      dtNone , dtNone , dtInt4 , dtNone , dtInt4 , dtNone , dtNone , dtNone  };
  if(index<MaxIndex) return dataType[index];
  throw DbxException("Wrong index !");
}
//***************************************************************************************

