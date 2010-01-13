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
#ifndef dbxMessageH
#define dbxMessageH
//***************************************************************************************
#include <oedbx/dbxCommon.h>                                           
//***************************************************************************************
class AS_EXPORT DbxMessage   
{ public  :
            DbxMessage(InStream ins, int4 address);                     
            ~DbxMessage();

            int4 GetLength() const { return Length; }                   

            // !!! OE stores the message text with 0x0d 0x0a at  !!!
            // !!! the end of each line                          !!!
            char * GetText() const { return Text; }                     
            void Convert();                                             

            void ShowResults(OutStream outs) const;                     
            void Analyze(int4 & headerLines, int4 & bodyLines) const;   

  private : 
            void init();
            void readMessageText(InStream ins);

            // Stores the address, the length and the text of the message
            int4 Address, Length;
            char * Text;
};
//***************************************************************************************
#endif  dbxMessageH   







