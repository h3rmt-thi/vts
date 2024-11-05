#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/sem.h>

const int CHILDREN = 3;
const int SLEEP_TIME = 1;
const int SIMULATIONS = 3;

int init_sem() {
    const int sem_key = ftok("/home/user", '1');
    if (sem_key < 0) {
        perror("ftok Error");
        exit(1);
    }
    const int sem_id = semget(sem_key, 1, IPC_CREAT | 0666);
    if (sem_id < 0) {
        perror("semget Error");
        exit(1);
    }
    const int ret = semctl(sem_id, 0, SETVAL, 1);
    if (ret < 0) {
        perror("semctl Error");
        exit(1);
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

void P(const int sem_id) {
    struct sembuf sem_buf = {.sem_num = 0, .sem_op = -1, .sem_flg = 0};
    const int res = semop(sem_id, &sem_buf, 1);
    if (res < 0) {
        perror("semop Error");
        exit(1);
    }
}

void V(const int sem_id) {
    struct sembuf sem_buf = {.sem_num = 0, .sem_op = 1, .sem_flg = 0};
    const int res = semop(sem_id, &sem_buf, 1);
    if (res < 0) {
        perror("semop Error");
        exit(1);
    }
}

void sim(const int nr, const int sem_id) {
    for (int i = 0; i < SIMULATIONS; i++) {
        P(sem_id);
        printf("Prozess %d betritt kritischen Bereich zum %d.mal\n", nr, i);
        sleep(SLEEP_TIME);
        printf("Prozess %d verlässt kritischen Bereich zum %d.mal\n", nr, i);
        V(sem_id);
    }

    printf("Prozess %d betritt unkritischen Bereich\n", nr);
    sleep(SLEEP_TIME);
    printf("Prozess %d verlässt unkritischen Bereich\n", nr);
    exit(0);
}

void main(void) {
    const int sem_id = init_sem();
    for (int i = 0; i < CHILDREN; i++) {
        const int pid = fork();
        if (pid == 0) {
            printf("Child %d with pid %d\n", i, getpid());
            sim(i, sem_id);
        }
        if (pid == -1) {
            perror("Error forking");
            exit(1);
        }
    }
    // wait for all children to finish
    for (int i = 0; i < CHILDREN; i++) {
        wait(NULL);
    }
    printf("All children finished\n");

    rem_sem(sem_id);
    exit(0);
}
