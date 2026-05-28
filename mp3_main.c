/*
Name : T.Pravallika
Regd_No: 25048_038
Project Name: MP3 Tag Reader and Editor
Start Date: 14-04-2026
End Date: 07-05-2026 
*/
#include "mp3_header.h"

int main(int argc, char *argv[])
{
    
    struct MP3 mp3;
    
    int ret = validate_cla(argc,argv,&mp3);
    if(ret == VIEW)
     {
        mp3.mp3_filename = argv[argc-1];
	    view(&mp3);

     }
     else if(ret == EDIT)
     {
        mp3.mp3_filename = argv[argc-1];
        edit(&mp3,argc,argv);
     }

    return 0;

}

/*
DESCRIPTION :
//                                                     MP3 Tag Reader and Editor
Introduction :
*The MP3 Tag Reader and Editor is a C language project developed to read and edit metadata information present in MP3 files using the ID3v2.3 format.
*The project allows users to view and modify details such as Title, Artist, Album, Year, Content, and Comments without affecting the original audio data.

Main Objective :
The main objective of this project is:
*To read MP3 metadata tags.
*To edit selected MP3 tag information.
*To perform metadata operations safely using file handling techniques.


main.c
*The main.c file is the entry point of the program.
Functions Performed :
*Receives command line arguments.
*Creates the MP3 structure variable.
*Calls validate_cla() to validate inputs.
Calls:
*view() function for viewing tags.
*edit() function for editing tags.


view.c
*The view.c file is used to display MP3 metadata information.
Functions Performed :
*Opens the MP3 file in binary read mode.
*Skips the 10-byte ID3 header.
*Reads metadata frames one by one.
Displays:
Title, Artist, Album, Year, Content, Comments
*Uses dynamic memory allocation to store frame data.
*Converts frame size from big-endian to little-endian format.


edit.c
*The edit.c file is responsible for editing MP3 metadata.
Functions Performed :
*Opens the original MP3 file.
*Creates a temporary file.
*Copies the header and remaining data.
Identifies the selected tag option:
-t → Title
-a → Artist
-A → Album
-y → Year
-m → Content
-c → Comment
*Replaces old tag content with new content.
*Renames the temporary file as the original file after editing.


function.c
*The function.c file contains utility and validation functions.
Functions Performed :
*validate_cla()
*Validates command line arguments.
*Checks .mp3 file extension.
*Verifies ID3 format and version.
*toggle_endianess()
*Converts frame size from big-endian to little-endian format.


Concepts Used :
*Structures
*File handling
*Binary file operations
*Dynamic memory allocation
*Command line arguments
*Pointers
*String handling
*Endianness conversion


Conclusion :
*This project successfully reads and edits MP3 metadata tags using C language.
*It demonstrates efficient use of file handling and binary operations while preserving the original audio content of the MP3 file.

*/