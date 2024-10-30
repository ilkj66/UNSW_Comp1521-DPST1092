////////////////////////////////////////////////////////////////////////
// DPST1092 --- Assignment 2: `space', a simple file archiver
// 
//
// Written by YIMING HE (z5528914) on 26/7/2024.
//
// 2024-03-08   v1.1    Team DPST1092 

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

#include "space.h"


// ADD ANY extra #defines HERE


// ADD YOUR FUNCTION PROTOTYPES (AND STRUCTS IF ANY) HERE


// print the files & directories stored in galaxy_pathname (subset 0)
//
// if long_listing is non-zero then file/directory permissions, formats & sizes
// are also printed (subset 0)

void list_galaxy(char *galaxy_pathname, int long_listing) {

    // REPLACE THIS CODE WITH YOUR CODE
    FILE *galaxy = fopen(galaxy_pathname, "rb");
    if (galaxy == NULL) {
        perror("fopen");
        exit(1);
    }
    
    if (!long_listing) {
        while(1) {
            int magic_check = fgetc(galaxy);
            if (magic_check == EOF) {                                                   //error checking
                break;
            }
            if (magic_check != 'c') {
                printf("magic number error! Read: 0x%x Expected: 0x63\n", magic_check);         //magic
                exit(1);
            }
            int format_check = fgetc(galaxy);
            if (format_check != '8' && format_check != '7' && format_check != '6') {
                printf("star format error!\n");
                exit(1);
            }
            fseek(galaxy, 10, SEEK_CUR);            //skip the file permission
            uint16_t pathname_length;
            if (fread(&pathname_length, 2, 1, galaxy) != 1) {
                break;
            }
            char *pathname = malloc (pathname_length + 1);
            if (fread(pathname, pathname_length, 1, galaxy) != 1) {
                break;
            }
            pathname[pathname_length] = '\0';
            
            uint8_t content_length_bytes[6];
            if (fread(content_length_bytes, 1, 6, galaxy) != 6) break;
            uint64_t content_length = content_length_bytes[0] |
                                    ((uint64_t)content_length_bytes[1] << 8) |
                                    ((uint64_t)content_length_bytes[2] << 16) |
                                    ((uint64_t)content_length_bytes[3] << 24) |
                                    ((uint64_t)content_length_bytes[4] << 32) |
                                    ((uint64_t)content_length_bytes[5] << 40);
            fseek (galaxy, content_length + 1, SEEK_CUR);
            printf("%s\n", pathname);

            free(pathname);
        }
    } else {
        while(1) {
            int magic_check = fgetc(galaxy);
            if (magic_check == EOF) {
                break;
            }
            if (magic_check != 'c') {
                printf("magic number error! Read: 0x%x Expected: 0x63\n", magic_check);
                exit(1);
            }
            int format_check = fgetc(galaxy);
            if (format_check != '8' && format_check != '7' && format_check != '6') {
                printf("star format error!\n");
                exit(1);
            }
            
            char permissions[11];
            if (fread(permissions, 1, 10, galaxy) != 10) break;
            permissions[10] = '\0';

            uint16_t pathname_length;
            
            if (fread(&pathname_length, 2, 1, galaxy) != 1) {
                break;
            }

            char *pathname = malloc (pathname_length + 1);

            if (fread(pathname, pathname_length, 1, galaxy) != 1) {
                break;
            }

            pathname[pathname_length] = '\0';

            uint8_t content_length_bytes[6];
            if (fread(content_length_bytes, 1, 6, galaxy) != 6) {
                break;
            }
            uint64_t content_length = content_length_bytes[0] |
                                    ((uint64_t)content_length_bytes[1] << 8) |
                                    ((uint64_t)content_length_bytes[2] << 16) |
                                    ((uint64_t)content_length_bytes[3] << 24) |
                                    ((uint64_t)content_length_bytes[4] << 32) |
                                    ((uint64_t)content_length_bytes[5] << 40);
            fseek (galaxy, content_length + 1, SEEK_CUR);
            printf("%s  %c  %5lu  %s\n", permissions, format_check, content_length, pathname);
            
            free(pathname);
        }
    }

    fclose(galaxy);
    //printf("list_galaxy called to list galaxy: '%s'\n", galaxy_pathname);

    //if (long_listing) {
    //    printf("long listing with permissions & sizes specified\n");
    //}
}


// check the files & directories stored in galaxy_pathname (subset 1)
//
// prints the files & directories stored in galaxy_pathname with a message
// either, indicating the hash byte is correct, or indicating the hash byte
// is incorrect, what the incorrect value is and the correct value would be

void check_galaxy(char *galaxy_pathname) {

    // REPLACE THIS PRINTF WITH YOUR CODE
    FILE* galaxy = fopen(galaxy_pathname, "r");
    while (1) {
        int star = fgetc(galaxy);
        
        if (star != 0x63) {
            fprintf(stderr, "error: incorrect first star byte: 0x%x should be 0x63\n", star);
            fclose(galaxy);
            exit(1);
        }
        fseek(galaxy, 11, SEEK_CUR);
        uint16_t pathname_length;
        if (fread(&pathname_length, 2, 1, galaxy) != 1) {
            break;
        }
        char *pathname = malloc (pathname_length + 1);
        if (fread(pathname, pathname_length, 1, galaxy) != 1) {
            break;
        }
        pathname[pathname_length] = '\0';
        uint8_t content_length_bytes[6];
        if (fread(content_length_bytes, 1, 6, galaxy) != 6) break;
        uint64_t content_length = content_length_bytes[0] |  ((uint64_t)content_length_bytes[1] << 8) |
          ((uint64_t)content_length_bytes[2] << 16) |  ((uint64_t)content_length_bytes[3] << 24) |
          ((uint64_t)content_length_bytes[4] << 32) |  ((uint64_t)content_length_bytes[5] << 40);
        
        fseek (galaxy, content_length, SEEK_CUR);
        
        uint8_t computed_hash = 0;
        fseek(galaxy, - 20 - pathname_length - content_length, SEEK_CUR);
        for (int i = 0; i < 20 + pathname_length + content_length; i++) {
            int byte = fgetc(galaxy);
            if (byte == EOF) {
                break;
            }
            if (i == 0) {
                computed_hash = galaxy_hash(0, (uint8_t)byte);
            } else {
                computed_hash = galaxy_hash(computed_hash, (uint8_t)byte);
            }
        }
        uint8_t expected_hash = fgetc(galaxy);
        if (expected_hash == computed_hash) {
            printf("%s - correct hash\n", pathname);
        } else {
            printf("%s - incorrect hash 0x%x should be 0x%x\n", pathname, computed_hash, expected_hash);
        }
        if (fgetc(galaxy) == EOF) {
            break;
        }
        fseek(galaxy, -1, SEEK_CUR);
    }

    //printf("check_galaxy called to check galaxy: '%s'\n", galaxy_pathname);
}


// extract the files/directories stored in galaxy_pathname (subset 1 & 3)

void extract_galaxy(char *galaxy_pathname) {

    // REPLACE THIS PRINTF WITH YOUR CODE
    FILE* galaxy = fopen(galaxy_pathname, "r");
    if (galaxy == NULL) {
        perror("fopen");
        exit(1);
    }

    while(1) {
        int magic_check = fgetc(galaxy);
        if (magic_check == EOF) {
            break;
        }
        if (magic_check != 'c') {
            printf("magic number error! Read: 0x%x Expected: 0x63\n", magic_check);
            exit(1);
        }
        int format_check = fgetc(galaxy);
        if (format_check != '8' && format_check != '7' && format_check != '6') {
            printf("star format error!\n");
            exit(1);
        }
        
        char permissions[11];
        if (fread(permissions, 1, 10, galaxy) != 10) {
            break;
        }
        permissions[10] = '\0';
        
        uint16_t pathname_length;
        if (fread(&pathname_length, 2, 1, galaxy) != 1) {
            break;
        }

        //fseek(galaxy, pathname_length, SEEK_CUR); // get pathname and print format like : "Extracting: hello.txt"
        char *pathname = malloc(pathname_length + 1);
        fread(pathname, pathname_length, 1, galaxy);
        pathname[pathname_length] = '\0';

        uint8_t content_length_bytes[6];
        if (fread(content_length_bytes, 1, 6, galaxy) != 6) {
            break;
        }

        uint64_t content_length = content_length_bytes[0] |  ((uint64_t)content_length_bytes[1] << 8) |
          ((uint64_t)content_length_bytes[2] << 16) |  ((uint64_t)content_length_bytes[3] << 24) |
          ((uint64_t)content_length_bytes[4] << 32) |  ((uint64_t)content_length_bytes[5] << 40);

        FILE* write_in_file = fopen(pathname, "w");
        if (write_in_file == NULL) {
            perror("fopen");
            exit(1);
        }

        int p;                 
        for(int i = 0; i < content_length; i++) {
            if ((p = fgetc(galaxy)) != EOF) {
                fputc(p, write_in_file);
            } else{
                exit (1);
            }
        }
        mode_t mode = 0;
        if (permissions[1] == 'r') mode |= S_IRUSR;
        if (permissions[2] == 'w') mode |= S_IWUSR;
        if (permissions[3] == 'x') mode |= S_IXUSR;
        if (permissions[4] == 'r') mode |= S_IRGRP;
        if (permissions[5] == 'w') mode |= S_IWGRP;
        if (permissions[6] == 'x') mode |= S_IXGRP;
        if (permissions[7] == 'r') mode |= S_IROTH;
        if (permissions[8] == 'w') mode |= S_IWOTH;
        if (permissions[9] == 'x') mode |= S_IXOTH;

        if (chmod(pathname, mode) != 0) {
            perror("chmod");
            free(pathname);
            fclose(galaxy);
            exit(1);
        }

        fseek (galaxy, 1, SEEK_CUR);

        printf("Extracting: %s\n", pathname);
        
    }
    
    //printf("extract_galaxy called to extract galaxy: '%s'\n", galaxy_pathname);
}


// create galaxy_pathname containing the files or directories specified in
// pathnames (subset 2 & 3)
//
// if append is zero galaxy_pathname should be over-written if it exists
// if append is non-zero galaxys should be instead appended to galaxy_pathname
//                       if it exists
//
// format specifies the galaxy format to use, it must be one STAR_FMT_6,
// STAR_FMT_7 or STAR_FMT_8

void create_galaxy(char *galaxy_pathname, int append, int format,
                   int n_pathnames, char *pathnames[n_pathnames]) {

    // REPLACE THIS CODE PRINTFS WITH YOUR CODE
    //FILE *galaxy = fopen(galaxy_pathname, "w");
    FILE *galaxy = fopen(galaxy_pathname, append ? "ab" : "wb");
    if (galaxy == NULL) {
        perror("file open failed");
        exit(1);
    }
    for (int i = 0; i < n_pathnames; i++) {

        char *file_name = pathnames[i];
        FILE* file = fopen(file_name, "rb");
        if (file == NULL) {
            perror("fopen");
            exit(1);
        }

        uint8_t computed_hash = 0x00;

        fputc('c', galaxy);                       //magic number 'c'
        fputc('8', galaxy);                       //star format

        uint8_t c = 'c';
        uint8_t eight = '8';

        computed_hash = galaxy_hash(computed_hash, c);
        computed_hash = galaxy_hash(computed_hash, eight);
        
        struct stat st;
        if (stat(file_name, &st) != 0) {
            perror("stat");
            fclose(file);
            exit(1);
        }

        uint16_t pathname_length = strlen(file_name);
        fprintf(galaxy, "%s", (st.st_mode & S_IFDIR) ? "d" : "-");              // file permission
        fprintf(galaxy, "%s", (st.st_mode & S_IRUSR) ? "r" : "-");
        fprintf(galaxy, "%s", (st.st_mode & S_IWUSR) ? "w" : "-");
        fprintf(galaxy, "%s", (st.st_mode & S_IXUSR) ? "x" : "-");
        fprintf(galaxy, "%s", (st.st_mode & S_IRGRP) ? "r" : "-");
        fprintf(galaxy, "%s", (st.st_mode & S_IWGRP) ? "w" : "-");
        fprintf(galaxy, "%s", (st.st_mode & S_IXGRP) ? "x" : "-");
        fprintf(galaxy, "%s", (st.st_mode & S_IROTH) ? "r" : "-");
        fprintf(galaxy, "%s", (st.st_mode & S_IWOTH) ? "w" : "-");
        fprintf(galaxy, "%s", (st.st_mode & S_IXOTH) ? "x" : "-");

        char permissions[10];
        permissions[0] = (st.st_mode & S_IFDIR) ? 'd' : '-';
        permissions[1] = (st.st_mode & S_IRUSR) ? 'r' : '-';
        permissions[2] = (st.st_mode & S_IWUSR) ? 'w' : '-';
        permissions[3] = (st.st_mode & S_IXUSR) ? 'x' : '-';
        permissions[4] = (st.st_mode & S_IRGRP) ? 'r' : '-';
        permissions[5] = (st.st_mode & S_IWGRP) ? 'w' : '-';
        permissions[6] = (st.st_mode & S_IXGRP) ? 'x' : '-';
        permissions[7] = (st.st_mode & S_IROTH) ? 'r' : '-';
        permissions[8] = (st.st_mode & S_IWOTH) ? 'w' : '-';
        permissions[9] = (st.st_mode & S_IXOTH) ? 'x' : '-';

        for (int permission_count = 0; permission_count < 10; permission_count++) {
            computed_hash = galaxy_hash(computed_hash, (uint8_t)permissions[permission_count]);
        }
        
        fwrite(&pathname_length, 2, 1, galaxy);                                    // pathname length
        uint8_t high, low;
        low = pathname_length & 0xFF;           
        high = (pathname_length >> 8) & 0xFF;
        //printf("%x, %x\n", high, low);
        computed_hash = galaxy_hash(computed_hash, low);
        computed_hash = galaxy_hash(computed_hash, high);

        fwrite(file_name, 1, pathname_length, galaxy);                             //pathname

        for (int j = 0; j < pathname_length; j++) {
            computed_hash = galaxy_hash(computed_hash, (uint8_t)file_name[j]);
        }

        fwrite(&st.st_size, 6, 1, galaxy);                                         // size of file

        uint8_t *size_ptr = (uint8_t *)&st.st_size;
        for (int j = 0; j < 6; j++) {
            computed_hash = galaxy_hash(computed_hash, size_ptr[j]);
        }
    
        //fseek(galaxy, - pathname_length - 8, SEEK_CUR);
        //for(int k = 0; k < pathname_length + 8; k++) {
        //    int f = fgetc(galaxy);
        //    computed_hash = galaxy_hash(computed_hash, (uint8_t)f);
        //}

        for (long j = 0; j < st.st_size; j++) {
            int byte = fgetc(file);
            fputc(byte, galaxy);
            if (byte != EOF) {
                computed_hash = galaxy_hash(computed_hash, (uint8_t)byte);
            }
        }

        //fseek(galaxy, - 20 - pathname_length - st.st_size, SEEK_CUR);

        
        //for (long j = 0; j < st.st_size + 20 + pathname_length; j++) {
        //    int byte = fgetc(file);
        //    computed_hash = galaxy_hash(computed_hash, (uint8_t)byte);
        //}
        fseek(galaxy, 0, SEEK_END);

        fputc(computed_hash, galaxy);
        
        printf("Adding: %s\n", pathnames[i]);
        fclose(file);
    }
    fclose(galaxy);

}

// ADD YOUR EXTRA FUNCTIONS HERE
