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

#include <oedbx/dbxFileHeader.h>
//***************************************************************************************
DbxFileHeader::DbxFileHeader(InStream ins) { readFileHeader(ins); }
//***************************************************************************************
void DbxFileHeader::readFileHeader(InStream ins)
{ ins.seekg(0);
  ins.read((char *)Buffer, FileHeaderSize);
  if(!ins) throw DbxException("Error reading object from input stream !");
}
//***************************************************************************************
struct Entry  { int4 index; char * text; };
const int1 HeaderValues = 31;
const Entry entries[HeaderValues] =
  { { fhFileInfoLength,       "file info length"                                       },
    { 0x09,                   "pointer to the last variable segment"                   },
    { 0x0a,                   "length of a variable segment"                           },
    { 0x0b,                   "used space of the last variable segment"                },
    { 0x0c,                   "pointer to the last tree segment"                       },
    { 0x0d,                   "length of a tree segment"                               },
    { 0x0e,                   "used space of the last tree segment"                    },
    { 0x0f,                   "pointer to the last message segment"                    },
    { 0x10,                   "length of a message segment"                            },
    { 0x11,                   "used space of the last message segment"                 },
    { 0x12,                   "root pointer to the deleted message list"               },
    { 0x13,                   "root pointer to the deleted tree list"                  },
    { 0x15,                   "used space in the middle sector of the file"            },
    { 0x16,                   "reusable space in the middle sector of the file"        },
    { 0x17,                   "index of the last entry in the tree"                    },
    { fhFirstFolderListNode,  "pointer to the first folder list node"                  },
    { fhLastFolderListNode,   "pointer to the last folder list node"                   },
    { 0x1f,                   "used space of the file"                                 },
    { fhMessageConditionsPtr, "pointer to the message conditions object"               },
    { fhFolderConditionsPtr,  "pointer to the folder conditions object"                },
    { fhEntries,              "entries in the tree"                                    },
    { fhEntries+1,            "entries in the 2.nd tree"                               },
    { fhEntries+2,            "entries in the 3.rd tree"                               },
    { fhTreeRootNodePtr,      "pointer to the root node of the tree"                   },
    { fhTreeRootNodePtr+1,    "pointer to the root node of the 2.nd tree"              },
    { fhTreeRootNodePtr+2,    "pointer to the root node of the 3.rd tree"              },
    { 0x9f,                   "used space for indexed info objects"                    },
    { 0xa0,                   "used space for conditions objects"                      },
    { 0xa2,                   "used space for folder list objects"                     },
    { 0xa3,                   "used space for tree objects"                            },
    { 0xa4,                   "used space for message objects"                         }
  };

void DbxFileHeader::ShowResults(OutStream outs) const
{ int4 temp[FileHeaderEntries], i, *ptr;
  for(i=0; i<FileHeaderEntries; ++i) temp[i] = Buffer[i];
  outs << std::endl << "file header : " << std::endl;
  for(i=0; i<HeaderValues; ++i)
    { ptr = temp + entries[i].index;
      if(*ptr) { outs << std::left << std::setw(50) << (entries[i].text) << " : 0x"
                      << std::hex << (*ptr) << std::endl;
                 *ptr = 0;
               }
    }
  outs << std::endl << "Show the rest ..." << std::endl;
  rows2File(outs,0,(int1 *)temp,FileHeaderSize);
}
