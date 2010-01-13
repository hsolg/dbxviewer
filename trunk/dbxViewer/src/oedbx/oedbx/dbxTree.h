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
#ifndef dbxTreeH
#define dbxTreeH
//***************************************************************************************
#include <oedbx/dbxCommon.h>                      
//***************************************************************************************
class AS_EXPORT DbxTree   
{ public  : 
            DbxTree(InStream ins, int4 address, int4 values);    
            ~DbxTree();

            int4 GetValue(int4 index) const;                     

            void ShowResults(OutStream outs) const;              

  private : 
            void readValues(InStream ins, int4 parent,   int4 address,  
                                          int4 position, int4 values);
            // data
            int4 Address;
            int4 Values, *Array;
};
//***********************************************  
#endif  dbxTreeH






