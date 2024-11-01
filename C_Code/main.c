#include "id3_utils.h"

int main(int argc, char *argv[]) {

    print_header();
    
    if (argc < 2) {
        display_error_com();
        return 1;
    }

    if (strcmp(argv[1], "-h") == 0) {
        display_help();
        return 0;

    } else if (strcmp(argv[1], "-v") == 0 && argc == 3) {

        view_tags(argv[2]);
        
    } else if (strcmp(argv[1], "-e") == 0 && argc == 5) {

        edit_tag( argv[4], argv[2], argv[3] );

    } else {
        display_error_com();
        return 1;
    }

    return 0;
}