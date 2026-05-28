#include "mp3_header.h"

void edit(struct MP3 *mp3, int argc , char *argv[])
{
    // opening the file in read and write mode
    mp3->org_mp3_fptr = fopen(mp3->mp3_filename,"rb");
    if(mp3->org_mp3_fptr == NULL)
    {
        perror("Error -F");
        return;
    }

    // opening the temperory file
    mp3->dup_mp3_fptr = fopen("temp.mp3","wb");
    if(mp3->dup_mp3_fptr == NULL)
    {
        perror("Error: Opening the File\n");
        fclose(mp3->org_mp3_fptr);
        return ;
    }

    // declaring the buffer space to copying the content and then copying it to the temp file
    char header[11];
    fread(header,1,10,mp3->org_mp3_fptr);
    header[10]='\0';
    fwrite(header,1,10,mp3->dup_mp3_fptr);

    // declaring the tag for comparing with the file 
    char tag[5];
    char tag_name[9];

    if(strcmp(argv[argc-3] ,"-t") == 0)
	{   
        strcpy(tag,"TIT2");
        strcpy(tag_name,"TITLE");
    }
	else if(strcmp(argv[argc-3] , "-a") == 0)
    {
		strcpy(tag,"TPE1");
        strcpy(tag_name,"ARTIST");
    }
	else if(strcmp(argv[argc-3] , "-A") == 0)
    {
		strcpy(tag,"TALB");
        strcpy(tag_name,"ALBUM");
    }
	else if(strcmp(argv[argc-3] , "-y") == 0)
	{	
        strcpy(tag,"TYER");
        strcpy(tag_name,"YEAR");
    }
	else if(strcmp(argv[argc-3] , "-m") == 0)
    {
		strcpy(tag,"TCON");
        strcpy(tag_name,"CONTENT");
    }
	else if(strcmp(argv[argc-3] , "-c") == 0)
    {
		strcpy(tag,"COMM");
        strcpy(tag_name,"COMMENTS");
    }
    else
    {
        validate_cla(1, NULL, NULL);
        fclose(mp3->org_mp3_fptr);
        fclose(mp3->dup_mp3_fptr);
        remove("temp.mp3");
        return;
    }

    int count = 0;
    char tag_buffer[5];
    unsigned int buffer_content_size;
    
    while (count < 6)
    {
   
        fread(tag_buffer,1,4,mp3->org_mp3_fptr);
        tag_buffer[4] = '\0';


        if(strcmp(tag,tag_buffer) == 0)
        {
            //writing the tag into temp file
            fwrite(tag_buffer,1,4,mp3->dup_mp3_fptr);

            // reading the size of the existing tag 
            fread(&buffer_content_size,4,1,mp3->org_mp3_fptr);

            //toogle_endianess
            toggle_endianess(mp3,&buffer_content_size);

            // reading the new content size
            unsigned int buffer_new_content_size = strlen(argv[3])+1;
            
            // writing the size as the character into the temp file
            for(int i = sizeof(buffer_new_content_size) - 1 ; i >= 0 ; i--)
            {
                unsigned char buffer_byte = (buffer_new_content_size >> (i * 8)) & 0xFF; 

                fwrite(&buffer_byte,1,1,mp3->dup_mp3_fptr);
            }

            char frame_flag_buffer[3];

            //reading the frame flag into buffer
            fread(frame_flag_buffer,1,2,mp3->org_mp3_fptr);
            frame_flag_buffer[2] = '\0';

            // writing the flags into the temp file
            fwrite(frame_flag_buffer,1,2,mp3->dup_mp3_fptr);

            //writing the null character after the flag into the size
            fputc('\0', mp3->dup_mp3_fptr);

            // getting the no . of character without null
            int actual_length = strlen(argv[3]);
            // writing the content in the argv[3] into the temp file
            fwrite(argv[3],1,actual_length,mp3->dup_mp3_fptr);

            fseek(mp3->org_mp3_fptr,buffer_content_size,SEEK_CUR);

        }
        else
        {
            //writing the tag into temp file
            fwrite(tag_buffer,1,4,mp3->dup_mp3_fptr);

            
            //reading the size
            fread(&buffer_content_size,4,1,mp3->org_mp3_fptr);

            //writing the size into the temp before toogle_endianess
            fwrite(&buffer_content_size,4,1,mp3->dup_mp3_fptr);

            // converting size into the big to little endian
            toggle_endianess(mp3,&buffer_content_size);

            // read flags separately
            char flag_buf[2];
            fread(flag_buf, 1, 2, mp3->org_mp3_fptr);
            fwrite(flag_buf, 1, 2, mp3->dup_mp3_fptr);

            // read content separately
            char *content = malloc(buffer_content_size);
            fread(content, 1, buffer_content_size, mp3->org_mp3_fptr);
            fwrite(content, 1, buffer_content_size, mp3->dup_mp3_fptr);

            free(content);
        }
        
        count++;

    }

    int ch;
    while ((ch = fgetc(mp3->org_mp3_fptr)) != EOF)
    {
        fputc(ch, mp3->dup_mp3_fptr);
    }

    //printf("Hello\n");

    fclose(mp3->org_mp3_fptr);
    fclose(mp3->dup_mp3_fptr);

    remove("sample.mp3");
    rename("temp.mp3", "sample.mp3");

    printf("--------------------------------------------SELECTED EDIT OPTION-------------------------------------------\n");
    printf("--------------------------------------SELECTED %s CHANGE OPTION-------------------------------------\n",tag_name);
    printf(" %10s\t:\t%s\n",tag_name,argv[3]);
    printf("----------------------------------------%s CHANGED SUCESSFULLY---------------------------------------\n",tag_name);

    return;

}

