#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <pwd.h>

char *whoami() {
    uid_t uid = geteuid();
    struct passwd *pw = getpwuid(uid);
    if (pw) {
        return pw->pw_name;
    }

    return " ";
}

void print() {
    printf("Завершено\n");
    char *group = malloc(sizeof(*group));
    strncpy(group, whoami(), 5);
    printf("Myagkikh %s %s\n", group, whoami());
    free(group);
}

int main() {
    size_t len = 0;
    printf("PID: %d\nSID: %d\nGID: %d\n", getpid(), getsid(getpid()), getpgid(getpid()));
    char *line = NULL;
    printf("Ввeдите команду: ");

    if ((len = getline(&line, &len, stdin)) == -1) {
        return 1;
    }

    if ((strcmp(line, "exit\n") == 0) || (strcmp(line, "\n") == 0)) {
        print();
        return 1;
    }

    line[len - 1] = 0;

    char *argv[255];
    argv[0] = strtok(line, " ");

    for (len = 1; (argv[len] = strtok(NULL, " ")) != NULL;) {
        ++len;
    }

    pid_t child_pid;
    int status;
    child_pid = fork();

    
    if (child_pid == 0) {
        execvp(argv[0], argv);
        exit(0);
    } else if (child_pid > 0)  {
        wait(&status);
        printf("Child exit code: %d / %d\n", WEXITSTATUS(status), status);
        print();
        free(line);
        exit(0);
    } else {
        perror("fork");
        exit(1);
    }
    
}
