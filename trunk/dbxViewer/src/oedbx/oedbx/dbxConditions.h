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
#ifndef dbxConditionsH
#define dbxConditionsH
//***************************************************************************************
#include <oedbx/dbxCommon.h>           
//***************************************************************************************
class AS_EXPORT DbxConditions   
{ public  : 
            DbxConditions(InStream ins, int4 address);           
            ~DbxConditions();
            
            const char * GetText() const { return Text; }        
            
            void ShowResults(OutStream outs) const;              

  private : 
            void init();
            void readConditions(InStream ins);

            //data
            int4 Address, Length;
            char * Text;
};
//***********************************************  
#endif dbxConditionsH




