#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/sem.h>

#define READER 5
#define WRITER 2

#define WRITER_INDEX 0
#define MUTEX_INDEX 1
#define READER_INDEX 2

// #define randwait sleep(rand() % 5 + 1)
// #define randwait sleep(5)
#define randwait sleep(1)

int init_sem() {
    const int sem_key = ftok("/home/user", '1');
    if (sem_key < 0) {
        perror("ftok Error");
        exit(1);
    }
    const int sem_id = semget(sem_key, 3, IPC_CREAT | 0666);
    if (sem_id < 0) {
        perror("semget Error");
        exit(1);
    }
    const int ret1 = semctl(sem_id, WRITER_INDEX, SETVAL, 1);
    if (ret1 < 0) {
        perror("semctl Error");
        exit(1);
    }
    const int ret2 = semctl(sem_id, MUTEX_INDEX, SETVAL, 1);
    if (ret2 < 0) {
        perror("semctl Error");
        exit(1);
    }
    // used for counting readers
    const int ret3 = semctl(sem_id, READER_INDEX, SETVAL, 0);
    if (ret3 < 0) {
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

void P(const int sem_id, const int i) {
    struct sembuf sem_buf = {.sem_num = i, .sem_op = -1, .sem_flg = 0};
    const int res = semop(sem_id, &sem_buf, 1);
    if (res < 0) {
        perror("semop Error");
        exit(1);
    }
}

void V(const int sem_id, const int i) {
    struct sembuf sem_buf = {.sem_num = i, .sem_op = 1, .sem_flg = 0};
    const int res = semop(sem_id, &sem_buf, 1);
    if (res < 0) {
        perror("semop Error");
        exit(1);
    }
}

void writer(const int nr, const int sem_id) {
    for (int c = 0; c < 3; c++) {
        P(sem_id, WRITER_INDEX);
        printf("+ WRITER %d write Var\n", nr);
        randwait;
        printf("- Writer %d write Var\n", nr);
        V(sem_id, WRITER_INDEX);

        printf("+ Writer %d Wait\n", nr);
        randwait;
        printf("- Writer %d Wait\n", nr);
    }
    printf("Writer %d finished\n", nr);
}

int getReaders(const int sem_id) {
    return semctl(sem_id, READER_INDEX, GETVAL);
}

void reader(const int nr, const int sem_id) {
    for (int c = 0; c < 4; c++) {
        P(sem_id, MUTEX_INDEX);
        V(sem_id, READER_INDEX);
        if (getReaders(sem_id) == 1) {
            // first reader
            printf("First reader (%d)\n", nr);
            P(sem_id, WRITER_INDEX);
        }
        V(sem_id, MUTEX_INDEX);

        printf("+ Reader %d Read Var\n", nr);
        randwait;
        printf("- Reader %d Read Var\n", nr);


        P(sem_id, MUTEX_INDEX);
        P(sem_id, READER_INDEX);
        if (getReaders(sem_id) == 0) {
            // last reader
            printf("Last reader (%d)\n", nr);
            V(sem_id, WRITER_INDEX);
        }
        V(sem_id, MUTEX_INDEX);

        printf("+ Reader %d Wait\n", nr);
        randwait;
        printf("- Reader %d Wait\n", nr);
    }
    printf("Reader %d finished\n", nr);
}

void main() {
    const int sem_id = init_sem();
    for (int i = 0; i < WRITER; i++) {
        const int pid = fork();
        if (pid == 0) {
            srand(getpid());
            printf("Writer %d with pid %d spawned\n", i, getpid());
            writer(i, sem_id);
            exit(1);
        }
        if (pid == -1) {
            perror("Error forking");
            exit(1);
        }
    }
    for (int i = 0; i < READER; i++) {
        const int pid = fork();
        if (pid == 0) {
            srand(getpid());
            printf("Reader %d with pid %d spawned\n", i, getpid());
            reader(i, sem_id);
            exit(1);
        }
        if (pid == -1) {
            perror("Error forking");
            exit(1);
        }
    }
    // wait for all children to finish
    for (int i = 0; i < READER + WRITER; i++) {
        wait(NULL);
    }
    printf("All children finished\n");

    rem_sem(sem_id);
    exit(0);
}
