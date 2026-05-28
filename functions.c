#include "mp3_header.h"

int validate_cla(int argc, char *argv[], struct MP3 *mp3)
{
    if( argc == 1 )
    {
	label:
	printf("------------------------------------------------------------------------------\n");
	printf("ERROR: ./a.out : INVALID ARGUMENTS\n");
	printf("USAGE : To view please pass like: ./a.out -v mp3filename\n");
	printf("To edit please pass like: ./a.out -e -t/-a/-A/-m/-y/-c changing_text mp3filename\n");
	printf("To get help pass like : ./a.out --help\n");
	printf("------------------------------------------------------------------------------\n");
	return 0;
    }

    if( (strcmp(argv[1], "--help") == 0) )
    {
	printf("------------------------------->HELP<-----------------------------------------\n");
	printf("1. -v -> to view mp3 file contents\n");
	printf("2. -e -> to edit mp3 file contents\n");
	printf("\t\t2.1. -t -> to edit song title\n");
	printf("\t\t2.2. -a -> to edit artist name\n");
	printf("\t\t2.3. -A -> to edit album name\n");
	printf("\t\t2.4. -y -> to edit year\n");
	printf("\t\t2.5. -m -> to edit content\n");
	printf("\t\t2.6. -c -> to edit comment\n");
	printf("------------------------------------------------------------------------------\n");
	return 0; 
    }

	if(argc < 3)
	{
		printf("Error: File name not given!!\n");
		return 0;
	}
    if(!strcmp(argv[1], "-v"))
    {
	// Do the necessary validation
		char *ext = strrchr(argv[argc - 1], '.');  // getting the address of . in the file name if not found NULL is return
		if (!ext || strcmp(ext, ".mp3") != 0) //!ext checkes if the NULL is returned it turns into 1 and s.ckt happens and becomes true and strcmp doest execute.
		{
			printf("Invalid file\n");
        	return 0;
		}
		
		// opening the file
		FILE *fp =fopen(argv[argc - 1] ,"rb");

		if(fp == NULL)
		{
			perror("Error");
			return 0;
		}

		char tag[4];
		//reading the ID3 into the tag
		fread(tag,1,3,fp);
		tag[3]= '\0';
		if(strcmp(tag , "ID3") != 0)
		{
			printf("The file Doesn't support ID3 format!!\n");
			fclose(fp);
			return 0;
		}
		// checking version is 03 00
		unsigned char version[2];
		fread(version,1,2,fp);

		if(version[0] != 3 || version[1] != 0 )
		{
			printf("Version Of the file is not 03 00");
			fclose(fp);
			return 0;
		}
		fclose(fp);

	return VIEW;
    }
    
    if(!strcmp(argv[1], "-e"))
    {
	// Do the necessary validation

	char *ext = strrchr(argv[argc - 1], '.');  // getting the address of . in the file name if not found NULL is return
		if (!ext || strcmp(ext, ".mp3") != 0) //!ext checkes if the NULL is returned it turns into 1 and s.ckt happens and becomes true and strcmp doest execute.
		{
			printf("Invalid file\n");
        	return 0;
		}
	
	// opening the file
		FILE *fp =fopen(argv[argc - 1] ,"rb");

		if(fp == NULL)
		{
			perror("Error");
			return 0;
		}
	char tag[4];
		//reading the ID3 into the tag
		fread(tag,1,3,fp);
		tag[3]= '\0';
		if(strcmp(tag, "ID3") != 0)
		{
			printf("The file Doesn't support ID3 format!!\n");
			fclose(fp);
			return 0;
		}
	// checking version is 03 00
		unsigned char version[2];
		fread(version,1,2,fp);

		if(version[0] != 3 || version[1] != 0 )
		{
			printf("Version Of the file is not 03 00");
			fclose(fp);
			return 0;
		}

	
	
	return EDIT;
    }

}


void toggle_endianess(struct MP3 *mp3, int *size)
{

	*size = ((* size & 0x000000FF) << 24) | ((* size & 0x0000FF00) << 8)  | ((* size & 0x00FF0000) >> 8)  |((* size & 0xFF000000) >> 24);

}

