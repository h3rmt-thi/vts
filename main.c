#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/sem.h>

#define FORKS 5

int init_sem() {
    const int sem_key = ftok("/home/user", '1');
    if (sem_key < 0) {
        perror("ftok Error");
        exit(1);
    }
    const int sem_id = semget(sem_key, FORKS, IPC_CREAT | 0666);
    if (sem_id < 0) {
        perror("semget Error");
        exit(1);
    }
    for (int i = 0; i < FORKS; i++) {
        const int ret = semctl(sem_id, i, SETVAL, 1);
        if (ret < 0) {
            perror("semctl Error");
            exit(1);
        }
    }

    return sem_id;
}

int rem_sem(const int sem_id) {
    const int ret = semctl(sem_id, 0, IPC_RMID);
    if (ret < 0) {
        perror("semctl Error");
        exit(1);
    }
    return ret;
}

void P(const int sem_id, const int l, const int r) {
    struct sembuf sem_buf[2] = {{.sem_num = l, .sem_op = -1, .sem_flg = 0}, {.sem_num = r, .sem_op = -1, .sem_flg = 0}};
    const int res = semop(sem_id, sem_buf, 2);
    if (res < 0) {
        perror("semop Error");
        exit(1);
    }
}

void V(const int sem_id, const int l, const int r) {
    struct sembuf sem_buf[2] = {{.sem_num = l, .sem_op = 1, .sem_flg = 0}, {.sem_num = r, .sem_op = 1, .sem_flg = 0}};
    const int res = semop(sem_id, sem_buf, 2);
    if (res < 0) {
        perror("semop Error");
        exit(1);
    }
}

void P2(const int sem_id, const int l, const int r) {
    if (l % 2 == 0) {
        struct sembuf sem_buf = {.sem_num = l, .sem_op = -1, .sem_flg = 0};
        const int res = semop(sem_id, &sem_buf, 1);
        if (res < 0) {
            perror("semop Error");
            exit(1);
        }

        struct sembuf sem_buf_2 = {.sem_num = r, .sem_op = -1, .sem_flg = 0};
        const int res_2 = semop(sem_id, &sem_buf_2, 1);
        if (res_2 < 0) {
            perror("semop Error");
            exit(1);
        }
    } else {
        struct sembuf sem_buf = {.sem_num = r, .sem_op = -1, .sem_flg = 0};
        const int res = semop(sem_id, &sem_buf, 1);
        if (res < 0) {
            perror("semop Error");
            exit(1);
        }

        struct sembuf sem_buf_2 = {.sem_num = l, .sem_op = -1, .sem_flg = 0};
        const int res_2 = semop(sem_id, &sem_buf_2, 1);
        if (res_2 < 0) {
            perror("semop Error");
            exit(1);
        }
    }
}

void think(const int nr, const int l, const int r) {
    printf("+ %d (%d, %d) %s\n", nr, l, r, "started thinking...");
    sleep(rand() % 10 + 1);
    // sleep(3);
    printf("- %d (%d, %d) %s\n", nr, l, r, "stopped thinking...");
}

void eat(const int nr, const int l, const int r) {
    printf("+ %d (%d, %d) %s\n", nr, l, r, "started eating...");
    sleep(rand() % 10 + 1);
    // sleep(3);
    printf("- %d (%d, %d) %s\n", nr, l, r, "stopped eating...");
}

void child(const int nr, const int sem_id) {
    const int l = nr;
    const int r = (nr + 1) % FORKS;
    while (true) {
        think(nr, l, r);
        P(sem_id, l, r);
        // P2(sem_id, l, r);
        eat(nr, l, r);
        V(sem_id, l, r);
    }
}

void main() {
    const int sem_id = init_sem();
    for (int i = 0; i < FORKS; i++) {
        const int pid = fork();
        if (pid == 0) {
            srand(getpid());
            printf("Child %d with pid %d spawned\n", i, getpid());
            child(i, sem_id);
        }
        if (pid == -1) {
            perror("Error forking");
            exit(1);
        }
    }
    // wait for all children to finish
    for (int i = 0; i < FORKS; i++) {
        wait(NULL);
    }
    printf("All children finished\n");

    rem_sem(sem_id);
    exit(0);
}
