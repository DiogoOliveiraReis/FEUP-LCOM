#include <db.h>

unsigned int day = 0, month = 0, year = 0, hours = 0, minutes = 0, seconds = 0;
int topScores[10];
Date topDates[10];

int writeScore()
{
    FILE *fptr = fopen("/home/lcom/labs/proj/src/db/scores.txt", "a");
    if (fptr == NULL)
    {
        printf("Error writting to scores.txt\n");
        return 1;
    }
    fprintf(fptr, "%d ", score);
    if (getDate(&day, &month, &year) == 0 && getTime(&hours, &minutes, &seconds) == 0)
    {
        fprintf(fptr, "- %d", day);
        fprintf(fptr, "/%d", month);
        fprintf(fptr, "/%d @ ", year);
        fprintf(fptr, "%d", hours);
        fprintf(fptr, ":%d", minutes);
        fprintf(fptr, ":%d\n", seconds);
    }
    else
        fprintf(fptr, "RTC Error\n");
    fclose(fptr);
    return 0;
}

int writeHighscore()
{
    FILE *fptr = fopen("/home/lcom/labs/proj/src/db/highscores.txt", "r+");
    if (fptr == NULL)
    {
        printf("Error writting to scores.txt\n");
        return 1;
    }
    //create current top10, from file
    int i = 0;
    for (int j = 0; j < 10; j++)
    {
        fscanf(fptr, "%i", &i);
        topScores[j] = i;
    }
    fclose(fptr);

    //create current top10 dates, from file
    Date topDates[10];
    int dayT = 0, monthT = 0, yearT = 0;
    fptr = fopen("/home/lcom/labs/proj/src/db/scores.txt", "r+");
    for (int j = 0; j < 10; j++)
    {
        Date date;
        topDates[i] = date;
        topDates[i].day = 0;
        topDates[i].month = 0;
        topDates[i].year = 0;
        fscanf(fptr, "%i"
                     "%i"
                     "%i",
               &dayT, &monthT, &yearT);
        topDates[i].day = dayT;
        topDates[i].month = monthT;
        topDates[i].year = yearT;
    }
    fclose(fptr);

    fptr = fopen("/home/lcom/labs/proj/src/db/highscores.txt", "r+");
    if (getDate(&day, &month, &year) == 0 && getTime(&hours, &minutes, &seconds) == 0)
    {
        /*
        fprintf(fptr, "- %d", day);
        fprintf(fptr, "/%d", month);
        fprintf(fptr, "/%d @ ", year);
        fprintf(fptr, "%d", hours);
        fprintf(fptr, ":%d", minutes);
        fprintf(fptr, ":%d\n", seconds);
        fprintf(fptr, "\n");
        */
    }
    else
        fprintf(fptr, "RTC Error\n");

    //update top10 with current score
    bool found = false;
    int temp = 0;
    int temp2 = 0;
    // char *tempDate[1000];
    // char *tempDate2[1000];
    for (int i = 0; i < 10; i++)
    {
        if (found)
        {
            temp = topScores[i];
            //*tempDate = topDates[i].dateInfo;

            topScores[i] = temp2;
            //strcpy(topDates[i].dateInfo, *tempDate2);

            temp2 = temp;
            //*tempDate2 = *tempDate;
        }
        if (score > topScores[i] && !found)
        {
            temp2 = topScores[i];
            //*tempDate2 = topDates[i].dateInfo;

            topScores[i] = score;
            //strcpy(topDates[i].dateInfo, "today");
            found = true;
        }
    }
    //write new top10 to file
    for (int i = 0; i < 10; i++)
    {
        fprintf(fptr, "%d ", topScores[i]);
        fprintf(fptr, "\n");
    }
    fclose(fptr);

/*
    fptr = fopen("/home/lcom/labs/proj/src/db/scores.txt", "w+");
    // //write new top10dates to file
    for (int i = 0; i < 10; i++)
    {
        fprintf(fptr, "%d ", topDates[i].day);
        fprintf(fptr, "%d ", topDates[i].month);
        fprintf(fptr, "%d ", topDates[i].year);
        fprintf(fptr, "\n");
    }
    fclose(fptr);
    */
    return 0;
}

int displayScores()
{
    // char c;
    FILE *fptr = fopen("/home/lcom/labs/proj/src/db/highscores.txt", "r");
    if (fptr == NULL)
    {
        printf("Error reading scores.txt\n");
        return 1;
    }
    int i = 0;
    int y = 350;
    int counter = 1;

    fscanf(fptr, "%d", &i);
    while (!feof(fptr))
    {
        drawInt(counter, 5, y);
        drawInt(i, 55, y);
        y += 30;
        fscanf(fptr, "%d", &i);
        counter++;
    }
    fclose(fptr);
    return 0;
}

int clearScores()
{
    FILE *fptr = fopen("/home/lcom/labs/proj/src/db/highscores.txt", "w");
    if (!fptr)
    {
        printf("Error clearing scores.txt\n");
        return 1;
    }
    fclose(fptr);
    return 0;
}

int drawDate(unsigned day, unsigned month, unsigned year, unsigned hours, unsigned minutes, unsigned seconds, int x, int y)
{
    x += 10;
    drawInt(day, x, y);

    xpm_map_t xpm_slash = slash;
    xpm_image_t img_slash;
    uint8_t *sprite_slash = vg_create_sprite(xpm_slash, &img_slash);

    vg_draw_sprite(sprite_slash, img_slash, x + 20, y);

    drawInt(month, x + 30, y);

    vg_draw_sprite(sprite_slash, img_slash, x + 50, y);

    drawInt(year, x + 60, y);

    y += 30;

    drawInt(hours, x, y);
    xpm_map_t xpm_doubledot = doubledot;
    xpm_image_t img_doubledot;
    uint8_t *sprite_doubledot = vg_create_sprite(xpm_doubledot, &img_doubledot);
    vg_draw_sprite(sprite_doubledot, img_doubledot, x + 34, y);
    drawInt(minutes, x + 44, y);
    vg_draw_sprite(sprite_doubledot, img_doubledot, x + 78, y);
    drawInt(seconds, x + 88, y);
    return 0;
}

int drawTopScores()
{
    return 0;
}
