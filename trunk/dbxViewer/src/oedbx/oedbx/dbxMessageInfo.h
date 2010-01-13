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
#ifndef dbxMessageInfoH
#define dbxMessageInfoH
//***************************************************************************************
#include <oedbx/dbxIndexedInfo.h>                  
//***************************************************************************************
const int1 miiIndex = 0x00, miiFlags = 0x01, miiMessageAddress = 0x04,   
           miiSubject = 0x08;

class AS_EXPORT DbxMessageInfo : public DbxIndexedInfo   
{ public  : 
            DbxMessageInfo(InStream ins, int4 address) : DbxIndexedInfo(ins, address) { } 

            const char *        GetIndexText    (int1 index) const;  
            IndexedInfoDataType GetIndexDataType(int1 index) const;  
};
//***********************************************  
#endif  dbxMessageInfoH




