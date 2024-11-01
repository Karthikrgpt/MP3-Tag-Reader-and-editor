#ifndef ID3_READER_H
#define ID3_READER_H

//to read id 3 tags
Status read_id3_tags(const char *filename, TagData *data);

//to display stored stored data in the structure
void display_metadata(const TagData *data);

//to view tags of mp3 files
void view_tags(const char *filename);

//to store the data to the structure for respective flag
Status get_data( const char *tag, char **data, FILE *fptr, int *size);

// to extract the data from file to structure
Status data_to_char( char **data, int size );

// to display the perticular tags stored in the structure
void display( const char *title, const char *data );

#endif // ID3_READER_H
