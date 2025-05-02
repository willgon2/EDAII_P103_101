#include "document.h"

void get_files(char *directory) {
    struct dirent *de;

    DIR *dr = opendir(directory);

    if (dr == NULL) {
        printf("The directory %s could not be oppened!\n", directory);
        // return;


    }

    while ((de = readdir(dr)) != NULL) 
            printf("%s\n", de->d_name); 
  
    closedir(dr);
}
