#ifndef ID3_UTILS_H
#define ID3_UTILS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//Structure to hold ID3 tag data.
typedef struct {

    FILE *fptr_address; //creadting file pointer
    FILE *fptr_sample; //to modify the data

    char *version; /**< Version of the ID3 tag */
    char *title;   /**< Title of the song */
    char *artist;  /**< Artist of the song */
    char *album;   /**< Album name */
    char *year;    /**< Year of release */
    char *comment; /**< Comment */
    char *genre;   /**< Genre */
    char *composer; // composer
    char *copyright; //copy right athority
    char *co_artist; // co artist likes actores, playback singers
    char *tarck; // track version
    
    double file_size;//to store size of complete file
    int size; //to store size of character used in each tag

} TagData;

typedef enum
{
    e_success,  //0
    e_failure,  //1
    e_title,    //2
    e_artist,   //3
    e_album,    //4
    e_year,     //5
    e_comment,  //6
    e_composer, //7
    e_copyright,//8
    e_co_artist,//9
    e_tarck,    //10
    e_genre     //11
} Status;

#include "id3_reader.h"
#include "id3_writer.h"

#define MAX_BUF_SIZE 30
#define MAX_TAG 20

//Pointer to the newly created TagData structure.
TagData* create_tag_data();

//to free the flag data memmory
void free_tag_data(TagData *data);

//to display error
void display_error(const char *message);

// to check id3 tag preesent or not
Status check_id3_tag_presence( FILE *fptr );

// to validate the mp3 tags
Status validate_mp3(const char *filename, TagData *data);

// to find the size of the comments
int find_size( FILE *fptr );

// to display the help menu
void display_help();

// if invalid command are passed
void display_error_com();

// to print lines
void print_line();

//to print the header
void print_header();

// global variable declaretion
static int i = 0;
static int index_data = 0, flag = 0, tag_status = 0;
char ch;

#endif // ID3_UTILS_H
