#ifndef MP3_HEADER_H
#define MP3_HEADER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define VIEW 	1
#define EDIT 	2


struct MP3
{
    char *mp3_filename;
    FILE *org_mp3_fptr;
    FILE *dup_mp3_fptr;
};

int validate_cla(int argc, char *argv[], struct MP3 *mp3);
void view(struct MP3 *mp3);
void edit(struct MP3 *mp3, int argc , char *argv[]);
void toggle_endianess(struct MP3 *mp3, int *size);
//void print_tag_data(FILE * org_mp3_fptr);
void tag_to_name(char *);

#endif
