#include "id3_utils.h"

void view_tags(const char *filename) {

    TagData *Data = create_tag_data();

    if ( Data == NULL ) {
        display_error("Memmory not allocated.");
        return;
    }

    if ( validate_mp3( filename, Data ) == e_failure ) 
        display_error("Failed to Vaidate ID3 tags.");

    if ( read_id3_tags(filename, Data ) == e_failure )
        display_error("Failed to read ID3 tags.");

    display_metadata(Data);

    free_tag_data(Data);
}

Status read_id3_tags(const char *filename, TagData *data) {

    tag_status = 0;

    rewind(data->fptr_address);

    fseek(data->fptr_address, 10, SEEK_SET);

    while ( tag_status != MAX_TAG ) {

        tag_status = check_id3_tag_presence(data->fptr_address);

        switch ( tag_status ) {
            case e_album: 
                get_data( "TALB", &data->album, data->fptr_address, &data->size );
                break;
            case e_artist:
                get_data( "TPE1", &data->artist, data->fptr_address, &data->size );
                break;
            case e_co_artist:
                get_data( "TPE2", &data->co_artist, data->fptr_address, &data->size );
                break;
            case e_title:
                get_data( "TIT2", &data->title, data->fptr_address, &data->size );
                break;
            case e_year:
                get_data( "TYER", &data->year, data->fptr_address, &data->size );
                break;
            case e_comment:
                get_data( "COMM", &data->comment, data->fptr_address, &data->size );
                break;
            case e_composer:
                get_data( "TCOM", &data->composer, data->fptr_address, &data->size );
                break;
            case e_copyright:
                get_data( "TCOP", &data->copyright, data->fptr_address, &data->size );
                break;
            case e_tarck:
                get_data( "TRCK", &data->tarck, data->fptr_address, &data->size );
                break;
            case e_genre:
                get_data( "TCON", &data->genre, data->fptr_address, &data->size );
                break;
            default:
                fseek(data->fptr_address, find_size(data->fptr_address) - 1, SEEK_CUR); // Skip (size - 1) bytes
                break;
        }
        
    }

    return e_success;
}

Status get_data(const char *tag, char **data, FILE *fptr, int *size) {

    *size = find_size(fptr);

    *data = (char *)malloc( (*size) * sizeof(char));

    if (fread(*data, sizeof(unsigned char), (*size) - 1, fptr) != (*size) - 1) {
        display_error("Error reading byte from file.\n");
    }

    data_to_char( data, *size );

    return e_success;
}

Status data_to_char( char **data, int size ) {

    char result[size]; // Create a new array to store the result
    for (int i = 0; i < size; i++)
        result[i] = '\0';

    index_data = 0;

    for ( i = 0; i < size; i++)
        if (isprint((*data)[i])) // Check if the character is printable
            result[index_data++] = (*data)[i];

    strcpy(*data, result);

    return e_success;
}

void display_metadata(const TagData *data) {

    display( "Album" , data->album );
    printf("%-10s: %-41s %-7s: %.2lf MB\n", "Version", data->version, "Size", data->file_size / (1024 * 1024) );
    printf("%-10s: %-41s %-7s: %s\n", "Title", data->title, "Year", data->year );
    print_line();

    display( "Artist" , data->artist );
    display( "Co Artist" , data->co_artist );
    display( "Composer" , data->composer );
    display( "Copy Right" , data->copyright );
    display( "Track" , data->tarck );
    display( "Comment" , data->comment );
    display( "Genre" , data->genre );

    print_line();

}