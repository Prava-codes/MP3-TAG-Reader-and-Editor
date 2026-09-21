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
