#include <stdio.h>
#include <dirent.h>

int main() {
  DIR *dir;
  struct dirent *ent;
  char *dir_path = "./messages/";

  if ((dir = opendir(dir_path)) != NULL) {
    while ((ent = readdir(dir)) != NULL) {
      if (ent->d_type == DT_REG) { // check if it is a regular file
        char file_path[100];
        sprintf(file_path, "%s%s", dir_path, ent->d_name); // create file path
        FILE *file = fopen(file_path, "r");
        if (file) {
          printf("Content of %s:\t", ent->d_name);
          char line[100];
          while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
          }
          fclose(file);
          printf("\n");
        }
      }
    }
    closedir(dir);
  } else {
    perror("Unable to open directory");
    return 1;
  }

  FILE *file = fopen("./body", "r");
  if (file) {
    printf("\nBody:\n");
    char line[100];
    while (fgets(line, sizeof(line), file)) {
      printf("%s", line);
    }
    fclose(file);
    printf("\n");
  } else {
    perror("Unable to open body");
    return 1;
  }

  return 0;
}
