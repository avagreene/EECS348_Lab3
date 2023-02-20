#include <stdio.h>
#include <stdlib.h>

void points(int score, int td_2, int td_1, int touchdowns, int fieldGoals, int safeties, int path[][5], int *numPath)
{
    if (score==0)
    {
        for(int i=0; i<*numPath; i++)
        {
            int *pathy = path[i];
            if (pathy[0]==td_2 && pathy[1]==td_1 && pathy[2]==touchdowns && pathy[3]==fieldGoals && pathy[4]==safeties)
            {
                return;
            }
        }
        path[*numPath][0]=td_2;
        path[*numPath][1]=td_1;
        path[*numPath][2]=touchdowns;
        path[*numPath][3]=fieldGoals;
        path[*numPath][4]=safeties;
        (*numPath)++;

        printf("%d TD + 2pt, %d TD + FG, %d TD, %d 3pt FG, %d Safety", td_2, td_1, touchdowns, fieldGoals, safeties);
        printf("\n");
        return;
    }

    if (score>=8) //touchdown + 2 pt conversion
    {
        points(score-8, td_2+1, td_1, touchdowns, fieldGoals, safeties, path, numPath);
    }

    if (score>=7) //touchdown + 1 pt field goal
    {
        points(score-7, td_2, td_1+1, touchdowns, fieldGoals, safeties, path, numPath);
    }

    if (score>=6) //touchdown
    {
        points(score-6, td_2, td_1, touchdowns+1, fieldGoals, safeties, path, numPath);
    }

    if (score>=3) //field goals
    {
        points(score-3, td_2, td_1, touchdowns, fieldGoals+1, safeties, path, numPath);
    }

    if (score>=2) //safeties
    {
        points(score-2, td_2, td_1, touchdowns, fieldGoals, safeties+1, path, numPath);
    }
}

int main()
{
    int score;

    do
    {
        printf("Enter 1 or 0 to STOP\n");
        printf("Enter the NFL score: ");
        scanf("%d", &score);

        int path[1000][5];
        int numPath=0;

        if (score>1)
        {
            points(score, 0, 0, 0, 0, 0, path, &numPath);
        }

    } while (score>1);
}