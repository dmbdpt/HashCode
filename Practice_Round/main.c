#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define MAX_CHARS 512

typedef struct
{
    char name[16];
    int score;
} ld;

typedef struct
{
    ld likes[5];
    int likes;
    ld dlikes[5];
    int dlikes;
    char yn;
} cli;

static int nr_clients;
ld *likes;
cli *clients;
int total_lds;

int cmpname(const void *a, const void *b)
{
    ld *lda = (ld *)a;
    ld *ldb = (ld *)b;

    return (strcmp(lda->name, ldb->name));
}

int cmpscore(const void *a, const void *b)
{
    ld *lda = (ld *)a;
    ld *ldb = (ld *)b;

    return (strcmp(lda->score, ldb->score));
}

void print_info()
{
    printf("Nr. Clients: %d\n", nr_clients);
    for (size_t i = 0; i < total_lds; i++)
    {
        printf("%s %d\n", likes[i].name, likes[i].score);
    }
}

ld init_ld(char name[])
{
    ld new;
    strcpy(new.name, name);
    new.score = 0;
    return new;
}

void ld_increase_size()
{
    total_lds++;
    likes = realloc(likes, sizeof(ld) * total_lds);
}

cli init_cli(ld dorlike[]){
    
}

void superscretalg(){

}



int main(int argc, char *argv[])
{
    likes = malloc(sizeof(ld));

    char line[MAX_CHARS];
    FILE *fp = fopen(argv[1], "r");
    fgets(line, MAX_CHARS, fp);

    nr_clients = atoi(line);

    while (!feof(fp))
    {
        int tmp;
        ld *tmp2;
        fscanf(fp, "%d", &tmp);

        for (size_t i = 0; i < tmp; i++)
        {
            char name[16];
            fscanf(fp, "%s", name);
            tmp2 = (ld *)bsearch(name, likes, total_lds, sizeof(ld), cmpname);
            if (tmp2 != NULL)
            {
                tmp2->score++;
            }
            else
            {
                ld_increase_size();
                ld new = init_ld(name);
                new.score++;
                likes[total_lds - 1] = new;
                qsort((void *)likes, total_lds, sizeof(ld), cmpname);
            }
        }

        fscanf(fp, "%d", &tmp);

        for (size_t i = 0; i < tmp; i++)
        {
            char name[16] = "\0";
            fscanf(fp, "%s", name);
            tmp2 = (ld *)bsearch(name, likes, total_lds, sizeof(ld), cmpname);
            if (tmp2 != NULL)
            {
                tmp2->score--;
            }
            else
            {
                ld_increase_size();
                ld new = init_ld(name);
                new.score--;
                likes[total_lds - 1] = new;
                qsort((void *)likes, total_lds, sizeof(ld), cmpname);
            }
        }
    }

    print_info();

    return 0;
}