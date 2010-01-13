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
#ifndef dbxFolderListH
#define dbxFolderListH

#include <oedbx/dbxCommon.h>                    
//***************************************************************************************
const int1 DbxFolderListSize    = 0x68,            
           DbxFolderListEntries = DbxFolderListSize >> 2;
const int1 flFolderInfo         = 0x15,
           flNextFolderListNode = 0x17, flPreviousFolderListNode = 0x18;

class AS_EXPORT DbxFolderList   
{ public  : 
            DbxFolderList(InStream ins, int4 address);   

            int4 GetValue(int1 index) const { if(index>=DbxFolderListEntries)            
                                                    throw DbxException("Index to big !");
                                              return Buffer[index];
                                            }
            void ShowResults(OutStream outs) const;              

  private : 
            void readFolderList(InStream ins);

            //data
            int4 Address;
            int4 Buffer[DbxFolderListEntries];
};
//***********************************************  
#endif dbxFolderListH 




