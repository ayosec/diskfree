#include <sys/vfs.h>
#include <stdio.h>
#include <string.h>

int main() {

  FILE *mounts;
  char line[1024];

  mounts = fopen("/proc/mounts", "r");
  if(mounts == NULL) {
    perror("/proc/mounts");
    return 1;
  }

  while(1) {
    char *dirname, *endname;
    struct statfs fs_stat;

    if(fgets(line, sizeof(line), mounts) == NULL)
      break;

    if(strncmp(line, "/dev/", 5) == 0) {
      if((dirname = index(line, ' ')) != NULL) {
        *dirname = '\0';
        dirname++;
        if((endname = index(dirname, ' ')) != NULL) {
          *endname = '\0';

          if(statfs(dirname, &fs_stat) == 0)
            printf("%s\t%d\n", line, 100 - (int)(100 * fs_stat.f_bavail / fs_stat.f_blocks));
        }
      }
    }
  }

  fclose(mounts);

  return 0;
}
