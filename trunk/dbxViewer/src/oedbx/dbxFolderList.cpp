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

#include <oedbx/dbxFolderList.h>
//***************************************************************************************
DbxFolderList::DbxFolderList(InStream ins, int4 address)
{ Address = address;

  readFolderList(ins);
}

void DbxFolderList::readFolderList(InStream ins)
{ ins.seekg(Address);
  ins.read((char *)Buffer, DbxFolderListSize);
  if(!ins) throw DbxException("Error reading object from input stream !");
  if(Address!=Buffer[0]) throw DbxException("Wrong object marker !");
}
//***************************************************************************************
void DbxFolderList::ShowResults(OutStream outs) const
{ outs << std::endl << "FolderList : " << std::endl
       << " Address : 0x" << std::hex << Address << std::endl;
  rows2File(outs,Address,(int1 *)Buffer, DbxFolderListSize);
}
//***************************************************************************************
