#ifndef PONG_OPTIONS_H
#define PONG_OPTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Options {
  // to do.
} Options;

Options *initOptions(void);

void updateOptions(Options *const options);

void drawOptions(const Options *const options);

void freeOptions(Options **options);

#ifdef __cplusplus
}
#endif

#endif /* PONG_OPTIONS_H */
