#ifndef TYPINGH
#define TYPINGH

char* concatenateWords(char **words, int start, int count);

char** groupWords(const char *words[], int num_words, int words_per_chunk, int *num_chunks);

void freeWords(char ***groups, int groupCount, int n);

void kbPractice();

#endif /* ifndef  */
