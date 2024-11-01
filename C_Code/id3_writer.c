#include "id3_utils.h"

Status edit_tag(const char *filename, const char *tag, const char *value) {

    TagData *Data = create_tag_data();

    if ( Data == NULL ) {
        display_error("Memmory not allocated.");
        return e_failure;
    }

    if ( validate_mp3( filename, Data ) == e_failure ) 
        display_error("Failed to Vaidate ID3 tags.");

    if ( copy_header( Data->fptr_address, Data->fptr_sample ) == e_failure )
        display_error("Failed to read the Header data.");

    write_id3_tags( tag, value, Data );

    copy_edited_file_data( Data->fptr_address, Data->fptr_sample );
    
    display_data_edited( tag, filename );

    print_line();

    free_tag_data(Data);

}

Status write_id3_tags(const char *tag, const char *value, TagData *data) {

    Status tag_found =  verify_tag( tag, data );

    if ( tag_found == e_failure )
        display_error("Failed to varify the Tag.");

    tag_status = 0;

    while ( tag_status != MAX_TAG ) {

        tag_status = check_id3_tag_presence(data->fptr_address);

        if ( tag_found == tag_status ) {
            copy_new_data( value, data->fptr_address, data->fptr_sample );
            break;
        } else copy_data( data->fptr_address, data->fptr_sample );
    }

}

void copy_new_data( const char *value, FILE *fptr_srce, FILE *fptr_dest ) {

    fseek(fptr_srce, -4, SEEK_CUR);

    for ( i = 0; i < 4; i++ )
        if ( fread(&ch, 1, 1, fptr_srce) == 1 )
            fwrite(&ch, 1, 1, fptr_dest);

    int size = find_size(fptr_srce);
    char data_buf[size];

    fread(data_buf, sizeof(unsigned char), size - 1, fptr_srce );

    int type_of_store = 0;

    for ( i = 0; data_buf[i]; i++ )
        if ( isprint(data_buf[i]))
            type_of_store++;

    if ( type_of_store > 5 ) {

        for (i = 0; i < 3; i++)
            fputc('\0', fptr_dest);

        fprintf(fptr_dest, "%c", (char)( strlen(value) * 2 + 2 ) );

        for (i = 0; i < 3; i++)
            fputc('\0', fptr_dest);

        for (i = 0; value[i] != '\0'; i++) {
            if ( value[i] != '_' ) 
                fputc(value[i], fptr_dest);
            else fputc(' ', fptr_dest); 
            fputc('\0', fptr_dest);
        }

        fputc('\0', fptr_dest);

    } else {

        for (i = 0; i < 3; i++)
            fputc('\0', fptr_dest);

        fprintf(fptr_dest, "%c", (char)( strlen(value) + 1) );

        for (i = 0; i < 3; i++)
            fputc('\0', fptr_dest);

        for (i = 0; value[i] != '\0'; i++)
            if ( value[i] != '_' ) 
                fputc(value[i], fptr_dest);
            else fputc(' ', fptr_dest); 
    }

    copy_leftover_data( fptr_srce, fptr_dest );

}

Status copy_data(FILE *fptr_srce, FILE *fptr_dest) {

    int size = find_size(fptr_srce);

    fseek(fptr_srce, -11, SEEK_CUR);

    for ( i = 0; i < size + 11 - 1; i++ )
        if ( fread(&ch, 1, 1, fptr_srce) == 1 )
            fwrite(&ch, 1, 1, fptr_dest);

}

void copy_edited_file_data( FILE *fptr_srce, FILE *fptr_dest ) {

    rewind(fptr_srce);
    rewind(fptr_dest);

    while (fread(&ch, 1, 1, fptr_dest) == 1) {
        fwrite(&ch, 1, 1, fptr_srce);
    }

}

Status verify_tag( const char *tag, TagData *data ) {

    char *Tags[] = {"-t", "-a", "-A", "-y", "-c", "-C", "-Y", "-o" ,"-T", "-g"};

    for ( i = 0; i < sizeof(Tags) / sizeof(Tags[0]); i++) {
        if ( !strcmp( tag, Tags[i] ) ) {    /* find the right tag and print */
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

Status copy_header(FILE *fptr_srce, FILE *fptr_dest) {

    rewind(fptr_srce);
    rewind(fptr_dest);

    char buffer[11] = "\0";

    if ( fread(buffer, 1, 10, fptr_srce) == 10 )
        fwrite(buffer, 1, 10, fptr_dest);

    return e_success;
}

void copy_leftover_data(FILE *fptr_srce, FILE *fptr_dest) {

    while (fread(&ch, 1, 1, fptr_srce) == 1) {
        fwrite(&ch, 1, 1, fptr_dest);
    }

}

void display_data_edited( const char *tag, const char *filename ) {

    printf("Requested to edit.........\n");
    printf("INFO: Data \"%s\"successfully written\n", filename );
    printf("INFO: Copied left over data\n");
    printf(":::::::  Tag \"%s\" Successfully edited  ::::::::\n", tag );

}