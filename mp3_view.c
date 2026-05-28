#include "mp3_header.h"

void view(struct MP3 *mp3)
{
    printf("\n                                   SELECTED VIEW DETAILS                                  \n");
    printf("\v");
    printf("-----------------------------------------------------------------------------------------------\n");
    printf("                                    MP3 TAG READER AND EDITOR FOR ID3v2                     \n");
    printf("-----------------------------------------------------------------------------------------------\n");
    // opening the file in read mode binary
    mp3->org_mp3_fptr = fopen(mp3->mp3_filename,"rb");
    if(mp3->org_mp3_fptr == NULL)
    {
        perror("Error -F");
        return;
    }

    // skiping Header of 10 bytes
    fseek(mp3->org_mp3_fptr,10,SEEK_SET);
    int count = 0;
    // make to run the loop 6 times to read the data
    do{
        char tag[5];
        fread(tag,1,4,mp3->org_mp3_fptr);
        tag[4]='\0';

        // trying to check each tag in each cycle of data fetching
        switch (count)
        {
        case 0 :
            if(strcmp("TIT2",tag) != 0)
            {
                printf("Tag mismatch\n");
                return;
            }
            printf("Title   : ");
            break;
        case 1:
            if(strcmp("TPE1",tag) != 0)
            {
                printf("Tag mismatch\n");
                return;
            }
            printf("Artist  : ");
            break;
        case 2:
            if(strcmp("TALB",tag) != 0)
                {
                    printf("Tag mismatch\n");
                    return;
                }
            printf("Album   : ");
            break;
        case 3:
            if(strcmp("TYER",tag) != 0)
            {
                printf("Tag mismatch\n");
                return;
            }
            printf("Year    : ");
            break;
        case 4:
            if(strcmp("TCON",tag) != 0)
            {
                printf("Tag mismatch\n");
                return;
            }
            printf("Content : ");
            break;
        case 5:
            if(strcmp("COMM",tag) != 0)
            {
                printf("Tag mismatch\n");
                return;
            }
            printf("Comment : ");
            break;
        default:
            break;
        }
        unsigned int content_size;
        //reading the size
        fread(&content_size,4,1,mp3->org_mp3_fptr);

        // converting into the big to little endian
        toggle_endianess(mp3,&content_size);

        // skipping the flag and first null characters 
        fseek(mp3->org_mp3_fptr,3,SEEK_CUR);

        // creating the variable to store the conent dynamically
        char * content = malloc(content_size);

        if(content == NULL)
        {
            perror("ERROR -M");
            return;
        }

        // reading the char to the content
        fread(content,1,content_size - 1,mp3->org_mp3_fptr);
        content[content_size-1] = '\0';

        // displaying the detail of the tags
        for(int i = 0 ; i < content_size - 1; i++)
        {
            printf("%c",content[i]);
        }
        printf("\n");
        free(content);

        count++ ;

    }while(count < 6);
    fclose(mp3->org_mp3_fptr);

    printf("-----------------------------------------------------------------------------------------------\n");
    printf("\n");
    printf("                                 DETAILS DISPLAYED SUCESSFULLY                                  \n\n");
}

// void print_tag_data()
// {

// }
