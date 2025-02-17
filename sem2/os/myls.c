#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <sys/sysmacros.h>


int OPTIONS_NUM = 10;
int PERM_BUFFER_SIZE = 10;
int MAX_PATH_SIZE = 1024;
int MAX_FILE_NAME_SIZE = 256;
int OPTION_l = 1;
int OPTION_R = 2;
int OPTION_a = 3;
int OPTION_i = 4;
int OPTION_g = 5;

/*
* 0 - nie ma opcji, 1 jest opcja
* OPTIONS[0] -> podano ścieżkę startową
* OPTIONS[1] -> -l
* OPTIONS[2] -> -R
* OPTIONS[3] -> -a
* OPTIONS[4] -> -i
* OPTIONS[5] -> -g
*/

void read_command(int* options, int argc, char *argv[]);
void recursive_read(char* path, int* options);

void option_i(struct dirent* pDirEnt);
void option_g(struct dirent* pDirEnt);
void option_l(struct dirent* pDirEnt);
void read_permissions(struct stat mystat, char* buffer);
char read_file_type(struct stat mystat);



int main( int argc, char *argv[] ) {
    DIR *pDIR;
    struct dirent *pDirEnt;
    struct stat mystat;


    int used_options[OPTIONS_NUM];
    read_command(used_options, argc, argv);
    // for (int i = 0; i < OPTIONS_NUM; i++)
    // {
    //     printf("%d \n", used_options[i]);
    // }
    

    char current_path[1024];
    if (used_options[0]) {
        strcpy(current_path, argv[1]);
    } else {
        current_path[0] = '.';
        current_path[1] = '\0';
    }
    
    printf("\t%s\n\n", current_path);

    recursive_read(current_path, used_options);

    printf("\n");

    return 0;
}

void read_command(int* options, int argc, char *argv[]) {
    for (int i = 0; i < OPTIONS_NUM; i++)
    {
       options[i] = 0;
    }

    if (argc < 2) 
        return;

    if (argv[1][0] != '-') {
        options[0] = 1;
    }

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-') {
            if (argv[i][1] == 'l') {
                options[OPTION_l] = 1;
            }
            else if (argv[i][1] == 'R') {
                options[OPTION_R] = 1;
            } 
            else if (argv[i][1] == 'a') {
                options[OPTION_a] = 1;
            } 
            else if (argv[i][1] == 'i') {
                options[OPTION_i] = 1;
            } 
            else if (argv[i][1] == 'g') {
                options[OPTION_g] = 1;
            } 
            else {
                printf("unknown option: %s\n", argv[i]);
            }
        } else {
            continue;   
        }
    }
}

void read_permissions(struct stat mystat, char* buffer) {
    int mode = mystat.st_mode;
    int i = 0;
    for (i = 0; i < PERM_BUFFER_SIZE; i++) {
        buffer[i] = '-';
    }
    buffer[PERM_BUFFER_SIZE] = '\0';

    if (mode & S_IRUSR) buffer[0] = 'r';
    if (mode & S_IWUSR) buffer[1] = 'w';
    if (mode & S_IXUSR) buffer[2] = 'x';
    if (mode & S_IRGRP) buffer[3] = 'r';
    if (mode & S_IWGRP) buffer[4] = 'w';
    if (mode & S_IXGRP) buffer[5] = 'x';
    if (mode & S_IROTH) buffer[6] = 'r';
    if (mode & S_IWOTH) buffer[7] = 'w';
    if (mode & S_IXOTH) buffer[8] = 'x';
}

char read_file_type(struct stat mystat) {
    char type = '-';
    if (S_ISDIR(mystat.st_mode)) {
        type = 'd';
    } else if (S_ISCHR(mystat.st_mode)) {
        type = 'c';
    } else if (S_ISBLK(mystat.st_mode)) {
        type = 'b';
    } else if (S_ISFIFO(mystat.st_mode)) {
        type = 'p';
    } else if (S_ISLNK(mystat.st_mode)) {
        type = 'l';
    } else if (S_ISSOCK(mystat.st_mode)) {
        type = 's';
    }
    return type;
}

void option_l(struct dirent* pDirEnt) {
    struct stat mystat;
    stat(pDirEnt->d_name, &mystat);

    char type = read_file_type(mystat);

    char permissions[PERM_BUFFER_SIZE];
    read_permissions(mystat, permissions);

    char time_buff[64];
    strftime(time_buff, sizeof(time_buff), "%b %d %H:%M", localtime(&mystat.st_mtime));

    char user_name[32];
    struct passwd *pw = getpwuid(mystat.st_uid);
    if (pw) {
        strcpy(user_name, pw->pw_name);
    } else {
        sprintf(user_name, "%d", mystat.st_uid);
    }

    char group_name[32];
    struct group *gr = getgrgid(mystat.st_gid);
    if (gr) {
        strcpy(group_name, gr->gr_name);
    } else {
        sprintf(group_name, "%d", mystat.st_gid);
    }

    printf("%c", type);
    printf("%s ", permissions);
    printf("%ld ", mystat.st_nlink);
    printf("%s ", user_name);
    printf("%s ", group_name);
    printf("%ld ", mystat.st_size);
    printf("%s ", time_buff);
    printf("%s \n", pDirEnt->d_name);
}

void option_g(struct dirent* pDirEnt) {
    struct stat mystat;
    stat(pDirEnt->d_name, &mystat);

    char type = read_file_type(mystat);

    char permissions[PERM_BUFFER_SIZE];
    read_permissions(mystat, permissions);

    char time_buff[64];
    strftime(time_buff, sizeof(time_buff), "%b %d %H:%M", localtime(&mystat.st_mtime));

    char group_name[32];
    struct group *gr = getgrgid(mystat.st_gid);
    if (gr) {
        strcpy(group_name, gr->gr_name);
    } else {
        sprintf(group_name, "%d", mystat.st_gid);
    }

    printf("%c", type);
    printf("%s ", permissions);
    printf("%ld ", mystat.st_nlink);
    printf("%s ", group_name);
    printf("%ld ", mystat.st_size);
    printf("%s ", time_buff);
    printf("%s \n", pDirEnt->d_name);
}

void option_i(struct dirent* pDirEnt) {
    struct stat mystat;
    stat(pDirEnt->d_name, &mystat);

    printf("%ld ", mystat.st_ino);
}

void recursive_read(char* path, int* options) {
    DIR *pDIR;
    struct dirent *pDirEnt;
    struct stat mystat;
    char c[1024];

    chdir(path);
    
    getcwd(c, sizeof(c));
    
    pDIR = opendir( c );
    if ( pDIR == NULL ) {
        printf( "Cannot open directory '%s'\n", path );
        exit( -1 );
    }

    pDirEnt = readdir( pDIR );
    while ( pDirEnt != NULL ) {
        if (pDirEnt->d_name[0] == '.' && !options[OPTION_a]) {
            pDirEnt = readdir( pDIR );
            continue;
        }

        if (options[OPTION_i]) {
            option_i(pDirEnt);
        }
        
        if (options[OPTION_l]) {
            option_l(pDirEnt);
        } else if (options[OPTION_g]) {
            option_g(pDirEnt);
        } else {
            printf("%s ", pDirEnt->d_name);
        }

        pDirEnt = readdir( pDIR );
    }
    closedir( pDIR );

    pDIR = opendir( c );
    pDirEnt = readdir( pDIR );
    while ( pDirEnt != NULL ) {
        if (pDirEnt->d_name[0] == '.') {
            if (!options[OPTION_a] || 
                (strcmp(pDirEnt->d_name, ".") == 0) ||
                (strcmp(pDirEnt->d_name, "..") == 0)) {
                pDirEnt = readdir( pDIR );
                continue;
            }
        }
        
        stat(pDirEnt->d_name, &mystat);        
        if (S_ISDIR(mystat.st_mode) && options[2]) {
            printf("\n\t%s\n", pDirEnt->d_name);
            recursive_read(pDirEnt->d_name, options);
        }
        
        pDirEnt = readdir( pDIR );
    }
    closedir( pDIR );

    chdir("..");     
}

