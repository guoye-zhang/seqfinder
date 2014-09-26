#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEM 50000
#define NAME_LENGTH 24

const char name[] = "ARNDCQEGHILKMFPSTWYVBJZX";
const int matrix[NAME_LENGTH + 1][NAME_LENGTH + 1] =
    {{5,-2,-1,-2,-1,-1,-1,0,-2,-1,-1,-1,-1,-2,-1,1,0,-2,-2,0,-1,-1,-1,-1,-5},
    {-2,7,0,-1,-3,1,0,-2,0,-3,-2,3,-1,-2,-2,-1,-1,-2,-1,-2,-1,-3,1,-1,-5},
    {-1,0,6,2,-2,0,0,0,1,-2,-3,0,-2,-2,-2,1,0,-4,-2,-3,5,-3,0,-1,-5},
    {-2,-1,2,7,-3,0,2,-1,0,-4,-3,0,-3,-4,-1,0,-1,-4,-2,-3,6,-3,1,-1,-5},
    {-1,-3,-2,-3,12,-3,-3,-3,-3,-3,-2,-3,-2,-2,-4,-1,-1,-5,-3,-1,-2,-2,-3,-1,-5},
    {-1,1,0,0,-3,6,2,-2,1,-2,-2,1,0,-4,-1,0,-1,-2,-1,-3,0,-2,4,-1,-5},
    {-1,0,0,2,-3,2,6,-2,0,-3,-2,1,-2,-3,0,0,-1,-3,-2,-3,1,-3,5,-1,-5},
    {0,-2,0,-1,-3,-2,-2,7,-2,-4,-3,-2,-2,-3,-2,0,-2,-2,-3,-3,-1,-4,-2,-1,-5},
    {-2,0,1,0,-3,1,0,-2,10,-3,-2,-1,0,-2,-2,-1,-2,-3,2,-3,0,-2,0,-1,-5},
    {-1,-3,-2,-4,-3,-2,-3,-4,-3,5,2,-3,2,0,-2,-2,-1,-2,0,3,-3,4,-3,-1,-5},
    {-1,-2,-3,-3,-2,-2,-2,-3,-2,2,5,-3,2,1,-3,-3,-1,-2,0,1,-3,4,-2,-1,-5},
    {-1,3,0,0,-3,1,1,-2,-1,-3,-3,5,-1,-3,-1,-1,-1,-2,-1,-2,0,-3,1,-1,-5},
    {-1,-1,-2,-3,-2,0,-2,-2,0,2,2,-1,6,0,-2,-2,-1,-2,0,1,-2,2,-1,-1,-5},
    {-2,-2,-2,-4,-2,-4,-3,-3,-2,0,1,-3,0,8,-3,-2,-1,1,3,0,-3,1,-3,-1,-5},
    {-1,-2,-2,-1,-4,-1,0,-2,-2,-2,-3,-1,-2,-3,9,-1,-1,-3,-3,-3,-2,-3,-1,-1,-5},
    {1,-1,1,0,-1,0,0,0,-1,-2,-3,-1,-2,-2,-1,4,2,-4,-2,-1,0,-2,0,-1,-5},
    {0,-1,0,-1,-1,-1,-1,-2,-2,-1,-1,-1,-1,-1,-1,2,5,-3,-1,0,0,-1,-1,-1,-5},
    {-2,-2,-4,-4,-5,-2,-3,-2,-3,-2,-2,-2,-2,1,-3,-4,-3,15,3,-3,-4,-2,-2,-1,-5},
    {-2,-1,-2,-2,-3,-1,-2,-3,2,0,0,-1,0,3,-3,-2,-1,3,8,-1,-2,0,-2,-1,-5},
    {0,-2,-3,-3,-1,-3,-3,-3,-3,3,1,-2,1,0,-3,-1,0,-3,-1,5,-3,2,-3,-1,-5},
    {-1,-1,5,6,-2,0,1,-1,0,-3,-3,0,-2,-3,-2,0,0,-4,-2,-3,5,-3,1,-1,-5},
    {-1,-3,-3,-3,-2,-2,-3,-4,-2,4,4,-3,2,1,-3,-2,-1,-2,0,2,-3,4,-2,-1,-5},
    {-1,1,0,1,-3,4,5,-2,0,-3,-2,1,-1,-3,-1,0,-1,-2,-2,-3,1,-2,5,-1,-5},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-5},
    {-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,1}};

typedef struct {
    int score, direction1, direction2, direction3;
} point;

typedef struct {
    int score, direction;
} point1;

int main(int argc, const char * argv[]) {
    char string1[10000], string2[10000];
    scanf("%s%s", string1, string2);
    int len1 = (int)strlen(string1), len2 = (int)strlen(string2), seq1[len1], seq2[len2];
    for (int i = 0; i < len1; i++) {
        seq1[i] = (int)(strchr(name, string1[i]) - name);
    }
    for (int i = 0; i < len2; i++) {
        seq2[i] = (int)(strchr(name, string2[i]) - name);
    }
    point *previousScore = calloc(len2 + 1, sizeof(point)),
          *currentScore = malloc((len2 + 1) * sizeof(point)),
          max;
    max.score = 0;
    int endi = -1, endj = -1;
    for (int i = 0; i < len1; i++) {
        currentScore[0].score = 0;
        for (int j = 0; j < len2; j++) {
            int j1 = j + 1;
            point score1 = previousScore[j], score2 = currentScore[j], score3 = previousScore[j1];
            score1.score += matrix[seq1[i]][seq2[j]];
            score2.score += matrix[NAME_LENGTH][seq2[j]],
            score3.score += matrix[seq1[i]][NAME_LENGTH];
            if (score1.score >= score3.score)
                if (score1.score >= score2.score) {
                    score1.direction1++;
                    currentScore[j1] = score1;
                } else {
                    score2.direction2++;
                    currentScore[j1] = score2;
                }
            else
                if (score3.score >= score2.score) {
                    score3.direction3++;
                    currentScore[j1] = score3;
                } else {
                    score2.direction2++;
                    currentScore[j1] = score2;
                }
            if (currentScore[j1].score > max.score) {
                max = currentScore[j1];
                endi = i;
                endj = j;
            } else if (currentScore[j1].score < 0) {
                currentScore[j1].score = 0;
                currentScore[j1].direction1 = 0;
                currentScore[j1].direction2 = 0;
                currentScore[j1].direction3 = 0;
            }
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
    point1 score1, score2, score3;
    score1.direction = 1;
    score2.direction = 2;
    score3.direction = 3;
    printf("(%d, %d) -> (%d, %d)\n", starti, startj, endi, endj);
    while (starti < endi || startj < endj) {
        printf("---\n");
        int leni = endi - starti + 1;
        point1 *score[leni];
        int lenj[leni];
        lenj[0] = endj - cut - startj + 1;
        int used = lenj[0], freed = 0;
        score[0] = malloc(lenj[0] * sizeof(point1));
        score[0][0].score = matrix[seq1[starti]][seq2[startj]];
        score[0][0].direction = 1;
        for (int i = 1; i < lenj[0]; i++) {
            score[0][i].score = score[0][i - 1].score + matrix[NAME_LENGTH][seq2[i + startj]];
            score[0][i].direction = 2;
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
                score1.score = score[i1][0].score + matrix[seq1[seqi]][seq2[left]];
                score3.score = score[i1][1].score + matrix[seq1[seqi]][NAME_LENGTH];
                if (score1.score >= score3.score)
                    score[i][0] = score1;
                else
                    score[i][0] = score3;
            } else {
                score[i][0].score = score[i1][0].score + matrix[seq1[seqi]][NAME_LENGTH];
                score[i][0].direction = 3;
            }
            for (int j = 1; j < lenj[i] - 1; j++) {
                int seqj = j + left, j1 = j - 1;
                score2.score = score[i][j1].score + matrix[NAME_LENGTH][seq2[seqj]];
                if (noleft) {
                    score1.score = score[i1][j].score + matrix[seq1[seqi]][seq2[seqj]];
                    score3.score = score[i1][j + 1].score + matrix[seq1[seqi]][NAME_LENGTH];
                } else {
                    score1.score = score[i1][j1].score + matrix[seq1[seqi]][seq2[seqj]];
                    score3.score = score[i1][j].score + matrix[seq1[seqi]][NAME_LENGTH];
                }
                if (score1.score >= score3.score)
                    if (score1.score >= score2.score)
                        score[i][j] = score1;
                    else
                        score[i][j] = score2;
                else
                    if (score3.score >= score2.score)
                        score[i][j] = score3;
                    else
                        score[i][j] = score2;
            }
            int j = lenj[i] - 1, j1 = j - 1;
            if (noright) {
                score2.score = score[i][j1].score + matrix[NAME_LENGTH][seq2[right]];
                if (noleft)
                    score1.score = score[i1][j].score + matrix[seq1[seqi]][seq2[right]];
                else
                    score1.score = score[i1][j1].score + matrix[seq1[seqi]][seq2[right]];
                if (score1.score >= score2.score)
                    score[i][j] = score1;
                else
                    score[i][j] = score2;
            } else {
                score2.score = score[i][j1].score + matrix[NAME_LENGTH][seq2[right]];
                if (noleft) {
                    score1.score = score[i1][j].score + matrix[seq1[seqi]][seq2[right]];
                    score3.score = score[i1][j + 1].score + matrix[seq1[seqi]][NAME_LENGTH];
                } else {
                    score1.score = score[i1][j1].score + matrix[seq1[seqi]][seq2[right]];
                    score3.score = score[i1][j].score + matrix[seq1[seqi]][NAME_LENGTH];
                }
                if (score1.score >= score3.score)
                    if (score1.score >= score2.score)
                        score[i][j] = score1;
                    else
                        score[i][j] = score2;
                else
                    if (score3.score >= score2.score)
                        score[i][j] = score3;
                    else
                        score[i][j] = score2;
            }
            /*for (int j = 0; j < lenj[i]; j++) {
                printf("%d:%d ", score[i][j].score, score[i][j].direction);
            }
            printf("\n");*/
        }
        int total = 0;
        for (int i = leni - 1; i >= freed; i--) {
            int left;
            if (i < leni - cut)
                left = startj;
            else
                left = startj + i - (leni - cut) + 1;
            while (score[i][endj - left].direction == 2) {
                printf(". %c\n", string2[endj]);
                endj--;
            }
            if (score[i][endj - left].direction == 1) {
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
    return 0;
}
