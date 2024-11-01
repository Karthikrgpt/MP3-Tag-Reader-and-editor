------------------------------------------------------------------------------------------------------------
                                            MP3 tag Reader and Writer
------------------------------------------------------------------------------------------------------------
Created by "Karthik R."
Last updated on 28th October 2024
------------------------------------------------------------------------------------------------------------

Description :-

    The MP3 Tag Reader and Writer is a application that allows users to read and modify ID3 tags of MP3 audio 
files. This project aims to provide an intuitive command-line interface for users to extract metadata from 
MP3 files and edit existing tags or create new ones. The application supports both ID3v1 and ID3v2 (ID3v2.0, 
ID3v2.1, ID3v2.2, ID3v2.3, ID3v2.4 ... ) tag formats.

    The additional file which is created at the time of editing, is automaticaly deleted. 
 
Here’s a breakdown to its key features :-

1. Reading:
    -> Ability to read and display tags
    -> Usage Example:
        -> If you want to read the tag:

                gcc *.c -o output && ./output -v Manasalaio.mp3                      

        -> -v: Reading command.
        -> Manasalaio.mp3 : Audio file
    -> output:
                ----------------------------------------------------------------------
                                             Mp3 TAG Reader
                ----------------------------------------------------------------------
                Album     : Vettaiyan - (2024)
                Version   : ID3 v2.3                                  Size   : 9.07 MB
                Title     : [iSongs.info] 01 - Manasilaayo            Year   : 2024
                ----------------------------------------------------------------------
                Artist    : Nakash Aziz, Arun Kaundinya, Deepthi Suresh
                Co Artist : Rajinikanth, Amitabh Bachchan, Fahadh Faasil
                Composer  : Anirudh Ravichander
                Copy Right: https://iSongs.info
                Track     : 01
                Comment   : enghttps://iSongs.info
                Genre     : Telugu
                ----------------------------------------------------------------------

2. Writing:
    -> Write tags to enhance metadata storage.
    -> Usage Example:
        -> If you want to write tags,

                    gcc *.c -o output && ./output -e -y 2024 Manasalaio.mp3

        -> -e: Edit requeste.
        -> -y: requested to edit the Year
        -> 2024: Data that need to store.
        -> Manasalaio.mp3: file to edit the tag in Audio file.
    -> Output:
                ----------------------------------------------------------------------
                                             Mp3 TAG Reader
                ----------------------------------------------------------------------
                Requested to edit.........
                INFO: Data "Manasalaio.mp3"successfully written
                INFO: Copied left over data
                :::::::  Tag "-y" Successfully edited  ::::::::
                ----------------------------------------------------------------------

3. help menu:
    -> to display help menu.
    -> Usage Example:
        -> If you want to display help menu,

                            gcc *.c -o output && ./output -h

        -> -h: help menu requeste.
    -> Output:
                ---------------------------------------------------------------------
                                             Mp3 TAG Reader
                ----------------------------------------------------------------------
                                               HELP MENU

                Usage     : gcc *.c -o output && ./output [options] filename.mp3

                [Options] :
                  1. Display help             : -h
                  2. View tags                : -v 
                  3. Edit tags                : -e [Tag] [Data]
                [Tag] :
                  1. Title tag                : -t
                  2. Track tag                : -T
                  3. Artist tag               : -a
                  4. Co Artist tag            : -o
                  5. Album tag                : -A
                  6. Composer tag             : -C
                  7. Copy right tag           : -Y
                  8. Year tag                 : -y
                  9. Comment tag              : -c
                  10. Genre tag               : -g
                [Data] : Enter the Data to write and use _ instead of space
                ----------------------------------------------------------------------   
                
4. If wrong command passed:
    -> it will display error with some basic help menu.
    -> output:
                ----------------------------------------------------------------------
                                             Mp3 TAG Reader
                ----------------------------------------------------------------------
                ERROR: Invaild Command Passed
                Usage:
                        gcc *.c -o output && ./output [options] filename.mp3
                [Option] :
                  1. For View   : -v
                  2. For Edit   : -e [Tag] [Data]
                  3. For Help   : -h
                For more information check out "help disk"
                ----------------------------------------------------------------------

------------------------------------------------------------------------------------------------------------
Files enclosed :-

1. id3_utils.h
2. id3_reader.h
3. id3_writer.h
4. main.c
5. id3_utils.c
6. id3_reader.c
7. id3_writer.c
8. Manasalaio.mp3

------------------------------------------------------------------------------------------------------------
                                                THE END
------------------------------------------------------------------------------------------------------------
