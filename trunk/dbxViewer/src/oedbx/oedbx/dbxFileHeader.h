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
#ifndef DbxFileHeaderH
#define DbxFileHeaderH
//***************************************************************************************
#include <oedbx/dbxCommon.h>   
//***************************************************************************************
const int4 FileHeaderSize    = 0x24bc;
const int4 FileHeaderEntries = FileHeaderSize>>2;

const int4 fhFileInfoLength       = 0x07,                              
           fhFirstFolderListNode  = 0x1b, fhLastFolderListNode  = 0x1c,
           fhMessageConditionsPtr = 0x22, fhFolderConditionsPtr = 0x23,
           fhEntries              = 0x31, fhTreeRootNodePtr     = 0x39 ;

class AS_EXPORT DbxFileHeader   
{ public  : 
            DbxFileHeader(InStream ins);        

            int4 GetValue(int4 index) const{return Buffer[index];    }  

            bool isFolders() const { return (Buffer && (Buffer[1]==0x6f74fdc6)); }  

            void ShowResults(OutStream outs) const;              

  private : 
            // this function is called from the constructor
            void readFileHeader(InStream ins);

            // stores the data
            int4 Buffer[FileHeaderEntries];
};
//***********************************************  
#endif DbxFileHeaderH 





