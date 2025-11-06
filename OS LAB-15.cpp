/* create_file_safe.c
   Works in Dev C++ / MinGW on Windows and on Linux.
   Tries to create: C:/Users/itssk/OneDrive/Desktop/os/example.txt
   If that fails it will create ./os/example.txt (relative) so the program always succeeds.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>   /* stat, mkdir on POSIX */
#include <errno.h>

#ifdef _WIN32
  #include <direct.h>   /* _mkdir on Windows */
  #define MKDIR(path) _mkdir(path)
#else
  #include <unistd.h>
  #define MKDIR(path) mkdir((path), 0755)
#endif

int dir_exists(const char *path) {
    struct stat st;
    if (stat(path, &st) == 0 && (st.st_mode & S_IFDIR)) return 1;
    return 0;
}

/* Try to create directory; return 0 on success or if already exists, -1 on failure */
int ensure_dir(const char *path) {
    if (dir_exists(path)) return 0;
    if (MKDIR(path) == 0) return 0;
    /* Some systems require creating intermediate dirs — caller can handle fallback */
    return -1;
}

int main(void) {
    const char mainDirectory[] = "C:/Users/itssk/OneDrive/Desktop";
    const char subDirectory[]  = "os";
    const char fileName[]      = "example.txt";
    char fullDirPath[512];
    char fullFilePath[1024];
    FILE *fp = NULL;

    /* Build absolute directory and file path */
    snprintf(fullDirPath, sizeof(fullDirPath), "%s/%s", mainDirectory, subDirectory);
    snprintf(fullFilePath, sizeof(fullFilePath), "%s/%s", fullDirPath, fileName);

    /* 1) Try to ensure the absolute directory exists (won't create parent if missing) */
    if (ensure_dir(fullDirPath) == 0) {
        /* attempt to create the file at absolute path */
        fp = fopen(fullFilePath, "w");
        if (fp != NULL) {
            fprintf(fp, "This is an example file content.\n");
            fclose(fp);
            printf("File created successfully: %s\n", fullFilePath);
            return 0;
        } else {
            /* could not open absolute path file (permissions or other) */
            /* fall through to try relative path */
        }
    }

    /* 2) Fallback: create an 'os' folder in current directory and create file there */
    if (ensure_dir("os") != 0) {
        /* If even creating local 'os' fails, try creating file in current dir directly */
        fp = fopen(fileName, "w");
        if (fp == NULL) {
            fprintf(stderr, "Error: cannot create file anywhere. errno=%d (%s)\n",
                    errno, strerror(errno));
            return 1;
        }
        fprintf(fp, "This is an example file content (created in current directory).\n");
        fclose(fp);
        printf("File created successfully: %s\n", fileName);
        return 0;
    }

    /* create file inside local ./os directory */
    snprintf(fullFilePath, sizeof(fullFilePath), "os/%s", fileName);
    fp = fopen(fullFilePath, "w");
    if (fp == NULL) {
        fprintf(stderr, "Error: could not create fallback file os/%s. errno=%d (%s)\n",
                fileName, errno, strerror(errno));
        return 1;
    }
    fprintf(fp, "This is an example file content (created in ./os).\n");
    fclose(fp);
    printf("File created successfully: %s\n", fullFilePath);
    return 0;
}
