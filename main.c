#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEM 50000
#define GAP_OPEN -2
#define GAP_EXTENDED -4

const char name[] = "ARNDCQEGHILKMFPSTWYVBJZX";
const int matrix[][24] =
    {{4,-1,-2,-2,0,-1,-1,0,-2,-1,-1,-1,-1,-2,-1,1,0,-3,-2,0,-2,-1,-1,-1},
    {-1,5,0,-2,-3,1,0,-2,0,-3,-2,2,-1,-3,-2,-1,-1,-3,-2,-3,-1,-2,0,-1},
    {-2,0,6,1,-3,0,0,0,1,-3,-3,0,-2,-3,-2,1,0,-4,-2,-3,4,-3,0,-1},
    {-2,-2,1,6,-3,0,2,-1,-1,-3,-4,-1,-3,-3,-1,0,-1,-4,-3,-3,4,-3,1,-1},
    {0,-3,-3,-3,9,-3,-4,-3,-3,-1,-1,-3,-1,-2,-3,-1,-1,-2,-2,-1,-3,-1,-3,-1},
    {-1,1,0,0,-3,5,2,-2,0,-3,-2,1,0,-3,-1,0,-1,-2,-1,-2,0,-2,4,-1},
    {-1,0,0,2,-4,2,5,-2,0,-3,-3,1,-2,-3,-1,0,-1,-3,-2,-2,1,-3,4,-1},
    {0,-2,0,-1,-3,-2,-2,6,-2,-4,-4,-2,-3,-3,-2,0,-2,-2,-3,-3,-1,-4,-2,-1},
    {-2,0,1,-1,-3,0,0,-2,8,-3,-3,-1,-2,-1,-2,-1,-2,-2,2,-3,0,-3,0,-1},
    {-1,-3,-3,-3,-1,-3,-3,-4,-3,4,2,-3,1,0,-3,-2,-1,-3,-1,3,-3,3,-3,-1},
    {-1,-2,-3,-4,-1,-2,-3,-4,-3,2,4,-2,2,0,-3,-2,-1,-2,-1,1,-4,3,-3,-1},
    {-1,2,0,-1,-3,1,1,-2,-1,-3,-2,5,-1,-3,-1,0,-1,-3,-2,-2,0,-3,1,-1},
    {-1,-1,-2,-3,-1,0,-2,-3,-2,1,2,-1,5,0,-2,-1,-1,-1,-1,1,-3,2,-1,-1},
    {-2,-3,-3,-3,-2,-3,-3,-3,-1,0,0,-3,0,6,-4,-2,-2,1,3,-1,-3,0,-3,-1},
    {-1,-2,-2,-1,-3,-1,-1,-2,-2,-3,-3,-1,-2,-4,7,-1,-1,-4,-3,-2,-2,-3,-1,-1},
    {1,-1,1,0,-1,0,0,0,-1,-2,-2,0,-1,-2,-1,4,1,-3,-2,-2,0,-2,0,-1},
    {0,-1,0,-1,-1,-1,-1,-2,-2,-1,-1,-1,-1,-2,-1,1,5,-2,-2,0,-1,-1,-1,-1},
    {-3,-3,-4,-4,-2,-2,-3,-2,-2,-3,-2,-3,-1,1,-4,-3,-2,11,2,-3,-4,-2,-2,-1},
    {-2,-2,-2,-3,-2,-1,-2,-3,2,-1,-1,-2,-1,3,-3,-2,-2,2,7,-1,-3,-1,-2,-1},
    {0,-3,-3,-3,-1,-2,-2,-3,-3,3,1,-2,1,-1,-2,-2,0,-3,-1,4,-3,2,-2,-1},
    {-2,-1,4,4,-3,0,1,-1,0,-3,-4,0,-3,-3,-2,0,-1,-4,-3,-3,4,-3,0,-1},
    {-1,-2,-3,-3,-1,-2,-3,-4,-3,3,3,-3,2,0,-3,-2,-1,-2,-1,2,-3,3,-3,-1},
    {-1,0,0,1,-3,4,4,-2,0,-3,-3,1,-1,-3,-1,0,-1,-2,-2,-2,0,-3,4,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}};

typedef struct {
    int score, direction1, direction2, direction3;
} tuple;

typedef struct {
    tuple C, I, D;
} point;

typedef struct {
    int score, direction;
} tuple1;

typedef struct {
    tuple1 C, I, D;
} point1;

char *getString(FILE *file) {
    int mem = 64;
    char *str = malloc(mem);
    fgets(str, mem, file);
    while (str[strlen(str) - 1] != '\n'){
        mem *= 2;
        str = realloc(str, mem);
        fgets(str + mem / 2 - 1, mem / 2 + 1, file);
    }
    return str;
}

int main(int argc, const char * argv[]) {
    FILE *file = fopen(argv[1], "r");
    char *string1 = getString(file), *string2 = getString(file);
    fclose(file);
    int len1 = (int)strlen(string1) - 1, len2 = (int)strlen(string2) - 1,
        *seq1 = malloc(len1 * sizeof(int)), *seq2 = malloc(len2 * sizeof(int));
    for (int i = 0; i < len1; i++)
        seq1[i] = (int)(strchr(name, string1[i]) - name);
    for (int i = 0; i < len2; i++)
        seq2[i] = (int)(strchr(name, string2[i]) - name);
    point *previousScore = calloc(len2 + 1, sizeof(point)),
          *currentScore = malloc((len2 + 1) * sizeof(point));
    tuple max, zero;
    zero.score = 0;
    zero.direction1 = 0;
    zero.direction2 = 0;
    zero.direction3 = 0;
    max = zero;
    int endi = -1, endj = -1;
    for (int i = 0; i < len1; i++) {
        currentScore[0].C = zero;
        currentScore[0].I = zero;
        currentScore[0].D = zero;
        for (int j = 0; j < len2; j++) {
            int j1 = j + 1;
            tuple score1 = currentScore[j].C, score2 = currentScore[j].I, score3;
            score1.score += GAP_OPEN + GAP_EXTENDED;
            score2.score += GAP_EXTENDED;
            if (score1.score >= score2.score) {
                score1.direction2++;
                currentScore[j1].I = score1;
            } else {
                score2.direction2++;
                currentScore[j1].I = score2;
            }
            score1 = previousScore[j1].C;
            score2 = previousScore[j1].D;
            score1.score += GAP_OPEN + GAP_EXTENDED;
            score2.score += GAP_EXTENDED;
            if (score1.score >= score2.score) {
                score1.direction3++;
                currentScore[j1].D = score1;
            } else {
                score2.direction3++;
                currentScore[j1].D = score2;
            }
            score1 = previousScore[j].C;
            score2 = currentScore[j1].I;
            score3 = currentScore[j1].D;
            score1.score += matrix[seq1[i]][seq2[j]];
            if (score1.score >= score3.score)
                if (score1.score >= score2.score) {
                    score1.direction1++;
                    currentScore[j1].C = score1;
                } else
                    currentScore[j1].C = score2;
            else
                if (score3.score >= score2.score)
                    currentScore[j1].C = score3;
                else
                    currentScore[j1].C = score2;
            if (currentScore[j1].C.score > max.score) {
                max = currentScore[j1].C;
                endi = i;
                endj = j;
            } else if (currentScore[j1].C.score < 0)
                currentScore[j1].C = zero;
            if (currentScore[j1].I.score < 0)
                currentScore[j1].I = zero;
            if (currentScore[j1].D.score < 0)
                currentScore[j1].D = zero;
        }
        point *temp = previousScore;
        previousScore = currentScore;
        currentScore = temp;
    }
    free(previousScore);
    free(currentScore);
    printf("Score: %d\n\n", max.score);
    int starti = endi - max.direction1 - max.direction3 + 1,
        startj = endj - max.direction1 - max.direction2 + 1,
        cut = max.direction1 - 1;
    tuple1 score1, score2a, score2b, score3a, score3b;
    score1.direction = 1;
    score2a.direction = 2;
    score2b.direction = 2;
    score3a.direction = 3;
    score3b.direction = 3;
    printf("(%d, %d) -> (%d, %d)\n", starti, startj, endi, endj);
    while (starti < endi || startj < endj) {
        printf("---\n");
        int leni = endi - starti + 1;
        point1 *score[leni];
        int lenj[leni];
        lenj[0] = endj - cut - startj + 1;
        int used = lenj[0], freed = 0;
        score[0] = malloc(lenj[0] * sizeof(point1));
        score[0][0].C.score = matrix[seq1[starti]][seq2[startj]];
        score[0][0].C.direction = 1;
        score[0][1].I.score = score[0][0].C.score + GAP_OPEN + GAP_EXTENDED;
        score[0][1].I.direction = 2;
        score[0][1].C = score[0][1].I;
        for (int i = 2; i < lenj[0]; i++) {
            score[0][i].I.score = score[0][i - 1].I.score + GAP_EXTENDED;
            score[0][i].I.direction = 2;
            score[0][i].C = score[0][i].I;
        }
        for (int i = 1; i < leni; i++) {
            int seqi = i + starti, i1 = i - 1, left, right, noleft = 0, noright = 0;
            if (i < leni - cut)
                left = startj;
            else {
                left = startj + i - (leni - cut) + 1;
                noleft = 1;
            }
            if (i <= cut) {
                right = endj - (cut - i);
                noright = 1;
            } else
                right = endj;
            lenj[i] = right - left + 1;
            used += lenj[i];
            while (used > MEM) {
                free(score[freed]);
                used -= lenj[freed];
                freed++;
            }
            score[i] = malloc(lenj[i] * sizeof(point1));
            if (noleft) {
                score1.score = score[i1][0].C.score + matrix[seq1[seqi]][seq2[left]];
                score3a.score = score[i1][1].C.score + GAP_OPEN + GAP_EXTENDED;
                score3b.score = score[i1][1].D.score + GAP_EXTENDED;
                if (score3a.score >= score3b.score)
                    score[i][0].D = score3a;
                else
                    score[i][0].D = score3b;
                if (score1.score >= score[i][0].D.score)
                    score[i][0].C = score1;
                else
                    score[i][0].C = score[i][0].D;
            } else {
                score3a.score = score[i1][0].C.score + GAP_OPEN + GAP_EXTENDED;
                score3b.score = score[i1][0].D.score + GAP_EXTENDED;
                if (score3a.score >= score3b.score)
                    score[i][0].D = score3a;
                else
                    score[i][0].D = score3b;
                score[i][0].C = score[i][0].D;
            }
            for (int j = 1; j < lenj[i] - 1; j++) {
                int seqj = j + left, j1 = j - 1, j2 = j + 1;
                score2a.score = score[i][j1].C.score + GAP_OPEN + GAP_EXTENDED;
                score2b.score = score[i][j1].I.score + GAP_EXTENDED;
                if (score2a.score >= score2b.score)
                    score[i][j].I = score2a;
                else
                    score[i][j].I = score2b;
                if (noleft) {
                    score1.score = score[i1][j].C.score + matrix[seq1[seqi]][seq2[seqj]];
                    score3a.score = score[i1][j2].C.score + GAP_OPEN + GAP_EXTENDED;
                    score3b.score = score[i1][j2].D.score + GAP_EXTENDED;
                } else {
                    score1.score = score[i1][j1].C.score + matrix[seq1[seqi]][seq2[seqj]];
                    score3a.score = score[i1][j].C.score + GAP_OPEN + GAP_EXTENDED;
                    score3b.score = score[i1][j].D.score + GAP_EXTENDED;
                }
                if (score3a.score >= score3b.score)
                    score[i][j].D = score3a;
                else
                    score[i][j].D = score3b;
                if (score1.score >= score[i][j].D.score)
                    if (score1.score >= score[i][j].I.score)
                        score[i][j].C = score1;
                    else
                        score[i][j].C = score[i][j].I;
                else
                    if (score[i][j].D.score >= score[i][j].I.score)
                        score[i][j].C = score[i][j].D;
                    else
                        score[i][j].C = score[i][j].I;
            }
            int j = lenj[i] - 1, j1 = j - 1, j2 = lenj[i];
            score2a.score = score[i][j1].C.score + GAP_OPEN + GAP_EXTENDED;
            score2b.score = score[i][j1].I.score + GAP_EXTENDED;
            if (score2a.score >= score2b.score)
                score[i][j].I = score2a;
            else
                score[i][j].I = score2b;
            if (noleft)
                score1.score = score[i1][j].C.score + matrix[seq1[seqi]][seq2[right]];
            else
                score1.score = score[i1][j1].C.score + matrix[seq1[seqi]][seq2[right]];
            if (score1.score >= score[i][j].I.score)
                score[i][j].C = score1;
            else
                score[i][j].C = score[i][j].I;
            if (!noright) {
                if (noleft) {
                    score3a.score = score[i1][j2].C.score + GAP_OPEN + GAP_EXTENDED;
                    score3b.score = score[i1][j2].D.score + GAP_EXTENDED;
                } else {
                    score3a.score = score[i1][j].C.score + GAP_OPEN + GAP_EXTENDED;
                    score3b.score = score[i1][j].D.score + GAP_EXTENDED;
                }
                if (score3a.score >= score3b.score)
                    score[i][j].D = score3a;
                else
                    score[i][j].D = score3b;
                if (score[i][j].D.score > score[i][j].C.score)
                    score[i][j].C = score[i][j].D;
            }
        }
        int total = 0;
        for (int i = leni - 1; i >= freed; i--) {
            int left;
            if (i < leni - cut)
                left = startj;
            else
                left = startj + i - (leni - cut) + 1;
            while (score[i][endj - left].C.direction == 2) {
                printf(". %c\n", string2[endj]);
                endj--;
            }
            if (score[i][endj - left].C.direction == 1) {
                printf("%c %c\n", string1[endi], string2[endj]);
                endj--;
                total++;
            } else
                printf("%c .\n", string1[endi]);
            endi--;
            free(score[i]);
        }
        cut -= total;
    }
    free(string1);
    free(string2);
    free(seq1);
    free(seq2);
    return 0;
}
