#include "id3_utils.h"

Status validate_mp3(const char *filename, TagData *data) {

    data->fptr_address = fopen(filename, "r+");
    data->fptr_sample = fopen( "Write_MP3_file_Auto_delete.mp3" , "w+");

    if (data->fptr_address == NULL)
        display_error("Unable to open file");

    if (data->fptr_sample == NULL)
        display_error("Unable to open file");

    data->version = malloc( 10 * sizeof(char) );

    if (fread( data->version, sizeof(char), 3, data->fptr_address) != 3 )
        display_error("Mp3 file read permission denied");

    if ( strcmp( data->version, "ID3") )
        display_error("ID3 Tag not Found!!");

    char buffer[5];

    if (fread( buffer, sizeof(char), 2, data->fptr_address) != 2)
        return e_failure;

    if (buffer[1] == 0x00) {

        char temp[10];
        sprintf(temp, " v2.%d", buffer[0]);
        strcat(data->version , temp);

    } else {
       display_error("No vaild version found");
    }

    fseek(data->fptr_address, 0, SEEK_END);
    data->file_size = ftell(data->fptr_address);

    return e_success;
}

Status check_id3_tag_presence( FILE *fptr) {

    if ( flag++ == MAX_TAG )
        return MAX_TAG;

    char buffer[5];
    char *Tags[] = {"TIT2", "TPE1", "TALB", "TYER", "COMM", "TCOM", "TCOP", "TPE2" ,"TRCK", "TCON"};

    if (fread(buffer, sizeof(char), 4, fptr) != 4) {
        display_error("Error reading 4 bytes from file.");
    }

    buffer[4] = '\0';

    for ( i = 0; i < sizeof(Tags) / sizeof(Tags[0]); i++) {
        if ( !strcmp( buffer, Tags[i] ) ) {    /* find the right tag and print */
            break;
        }
    }

    switch ( i + 2 ) {
        case e_title: return e_title;
        case e_artist: return e_artist;
        case e_album: return e_album;
        case e_year: return e_year;
        case e_comment: return e_comment;
        case e_composer: return e_composer;
        case e_copyright: return e_copyright;
        case e_co_artist: return e_co_artist;
        case e_tarck: return e_tarck;
        case e_genre: return e_genre;
        default: return e_failure;
    }
    
    return e_failure;
}

int find_size( FILE *fptr ) {

    fseek(fptr, 3, SEEK_CUR); //skip 3 bytes of flag

    unsigned char byte;

    if (fread(&byte, sizeof(unsigned char), 1, fptr) != 1) { // Read 1 byte from the file
        display_error("Error reading byte from file.\n");
    }

    fseek(fptr, 3, SEEK_CUR); //skip 3 bytes of flag

    return (int)byte;
}

void display( const char *title, const char *data ) {

    if ( data != NULL )
        printf("%-10s: %s\n", title ,data );

}

TagData* create_tag_data() {
    TagData *data = (TagData *)malloc(sizeof(TagData));
    if (data) {
        //data->version = NULL;
        data->title = NULL;
        data->artist = NULL;
        data->album = NULL;
        data->year = NULL;
        data->comment = NULL;
        data->genre = NULL;
        data->composer = NULL;
        data->copyright = NULL;
        data->co_artist = NULL;
        data->tarck = NULL;
    }
    return data;
}

void free_tag_data(TagData *data) {
    if (data) {
        free(data->version);
        free(data->title);
        free(data->artist);
        free(data->album);
        free(data->year);
        free(data->comment);
        free(data->genre);
        free(data->composer);
        free(data->copyright);
        free(data->co_artist);
        free(data->tarck);
        free(data);

        if ( data->fptr_sample != NULL ) 
           remove("Write_MP3_file_Auto_delete.mp3");
    }
}


void display_help() {
    printf( "%40s\n\n","HELP MENU");
    printf("Usage     : gcc *.c -o output && ./output [options] filename.mp3\n\n");
    printf("[Options] :\n");
    printf("  1. %-25s: -h\n", "Display help");
    printf("  2. %-25s: -v \n", "View tags");
    printf("  3. %-25s: -e [Tag] [Data]\n", "Edit tags");
    printf("[Tag] :\n");
    printf("  1. %-25s: -t\n", "Title tag");
    printf("  2. %-25s: -T\n", "Track tag");
    printf("  3. %-25s: -a\n", "Artist tag");
    printf("  4. %-25s: -o\n", "Co Artist tag");
    printf("  5. %-25s: -A\n", "Album tag");
    printf("  6. %-25s: -C\n", "Composer tag");
    printf("  7. %-25s: -Y\n", "Copy right tag");
    printf("  8. %-25s: -y\n", "Year tag");
    printf("  9. %-25s: -c\n", "Comment tag");
    printf("  10. %-24s: -g\n", "Genre tag");
    printf("[Data] : Enter the Data to write and use _ instead of space\n");
    print_line();
}

void display_error_com() {
    printf("ERROR: Invaild Command Passed\n");
    printf("Usage:\n");
    printf("\tgcc *.c -o output && ./output [options] filename.mp3\n");
    printf("[Option] :\n");
    printf("  1. %-10s : -v\n", "For View");
    printf("  2. %-10s : -e [Tag] [Data]\n", "For Edit");
    printf("  3. %-10s : -h\n", "For Help");
    printf("For more information check out \"help disk\"\n");
    print_line();
}

void display_error(const char *message) {
    printf("ERROR: %s\n", message );
    print_line();
    exit(0);
}

void print_header() {
    print_line();
    printf("\033[1;37m%43s\033[0m\n", "Mp3 TAG Reader" );
    print_line();
}

void print_line() {
    printf("\033[1;37m");
    for ( i = 0; i < 70; i++ )
        printf("-");
    printf("\033[0m\n");
}