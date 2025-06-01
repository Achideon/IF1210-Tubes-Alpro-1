#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#ifdef _WIN32
#include <windows.h>
#define SLEEP_MS(ms) Sleep(ms)
#else
#include <unistd.h>
#define SLEEP_MS(ms) usleep((ms) * 1000)
#endif

#define TARGET_FPS 24
#define FRAME_DELAY_MS (1000 / TARGET_FPS)
#define FRAME_DELIMITER "---FRAME---"
#define DISPLAY_ROW 2
#define FRAMEBUFFER_MAX (8192 * 10)

static volatile int interrupted = 0;

void HandleInterrupt(int signal) {
    interrupted = 1;
}

void MoveCursorTo(int row, int col) {
    printf("\033[%d;%dH", row, col);
}

char **LoadFramesFromFile(const char *filename, int *frameCount) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open %s\n", filename);
        return NULL;
    }

    int capacity = 10;
    *frameCount = 0;
    char **frames = malloc(capacity * sizeof(char *));
    char *buffer = malloc(8192 * sizeof(char));
    char *frameBuffer = malloc(8192 * 10);
    frameBuffer[0] = '\0';

    while (fgets(buffer, 8192, file)) {
        if (strncmp(buffer, FRAME_DELIMITER, strlen(FRAME_DELIMITER)) == 0) {
            if (*frameCount >= capacity) {
                capacity *= 2;
                frames = realloc(frames, capacity * sizeof(char *));
            }
            frames[*frameCount] = malloc(strlen(frameBuffer) + 1);
            strcpy(frames[*frameCount], frameBuffer);
            (*frameCount)++;
            frameBuffer[0] = '\0';
        } else {
            if (strlen(frameBuffer) + strlen(buffer) + 1 >= FRAMEBUFFER_MAX) {
                if (*frameCount >= capacity) {
                    capacity *= 2;
                    frames = realloc(frames, capacity * sizeof(char *));
                }
                frames[*frameCount] = malloc(strlen(frameBuffer) + 1);
                strcpy(frames[*frameCount], frameBuffer);
                (*frameCount)++;
                frameBuffer[0] = '\0';
            }
            strcat(frameBuffer, buffer);
        }
    }

    if (strlen(frameBuffer) > 0) {
        if (*frameCount >= capacity) {
            capacity *= 2;
            frames = realloc(frames, capacity * sizeof(char *));
        }
        frames[*frameCount] = malloc(strlen(frameBuffer) + 1);
        strcpy(frames[*frameCount], frameBuffer);
        (*frameCount)++;
    }
    free(buffer);
    free(frameBuffer);
    fclose(file);
    return frames;
}

void DisplayFrame(char *frame) {
    char *line = strtok(frame, "\n");
    int row = DISPLAY_ROW;
    while (line != NULL) {
        MoveCursorTo(row, 1);  
        printf("%s", line);
        line = strtok(NULL, "\n");
        row++;
    }
}

void PlayCirno() {
    interrupted = 0;
    signal(SIGINT, HandleInterrupt);
    
    int frameCount = 0;
    char **frames = LoadFramesFromFile("../data/cirno.txt", &frameCount);
    if (!frames || frameCount == 0) {
        printf("No frames loaded.\n");
        return;
    }

    printf("\033[2J");  
    printf("\033[?25l");

    for (int i = 0; i < frameCount && !interrupted; i++) {
        char *frameCopy = strdup(frames[i]);
        DisplayFrame(frameCopy);
        free(frameCopy);

        fflush(stdout);
        SLEEP_MS(FRAME_DELAY_MS);
    }  
    printf("\033[?25h");  
    printf("\033[2J");    
    printf("\033[H");     
    
    signal(SIGINT, SIG_DFL);
    
    for (int i = 0; i < frameCount; i++) {
        free(frames[i]);
    }
    free(frames);
}
