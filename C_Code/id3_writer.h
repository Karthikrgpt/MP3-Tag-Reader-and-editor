#ifndef ID3_WRITER_H
#define ID3_WRITER_H

// Writes the ID3 tags to an MP3 file
Status write_id3_tags(const char *tag, const char *value, TagData *data);

//to edit the tag of id3 tag
Status edit_tag(const char *filename, const char *tag, const char *value);

//to verify user enterd tag
Status verify_tag( const char *tag, TagData *data );

//to copy header
Status copy_header(FILE *fptr_srce, FILE *fptr_dest);

//to copy the data, if tag not match
Status copy_data(FILE *fptr_srce, FILE *fptr_dest);

//copy the new tag to the sample file
void copy_new_data( const char *value, FILE *fptr_srce, FILE *fptr_dest );

// to copy the left over data to sample file
void copy_leftover_data(FILE *fptr_srce, FILE *fptr_dest);

// to copy the data from sample to original file
void copy_edited_file_data( FILE *fptr_srce, FILE *fptr_dest );

// to display the output
void display_data_edited( const char *tag, const char *filename );

#endif // ID3_WRITER_H
