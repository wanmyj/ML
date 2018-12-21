#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void deleteSpace(char *str)
{
    char blank[1000];
    int c=0, d=0;
    while (str[c] != '\0')
    {
        if (str[c] == '\n')
        {
            blank[d] = '\0';
            break;
        }
        if (str[c] == ' ')
        {
            c++;
            while(str[c] == ' ')
            {
                c++;
            }
        }
        blank[d] = str[c];
        if (str[c] == '\0')
        {
            break;
        }
        c++;
        d++;
    }
    strcpy(str, blank);
}

int main () {
    FILE * fp;
    fp = fopen ("FT02.plan", "r");
    char str[200] = {'0'};
    double lat_lon_hgh[3][267] = {0.0};
    int i = 0, j = 0;
    while(fgets(str, 100, fp) != NULL) 
    {
        deleteSpace(str);
        if (!strcmp(str, "\"params\":["))
        {
            fgets(str, 100, fp);
            deleteSpace(str);
            char *temp  = (char*)malloc(sizeof(str));
            strcpy(temp, str);            
            if( temp!= NULL && !strcmp(temp, "0,")) 
            {
                fgets(str, 100, fp);
                deleteSpace(str);
                char *temp  = (char*)malloc(sizeof(str));
                strcpy(temp, str);
                if( temp!= NULL && !strcmp(temp, "0,")) 
                {
                    fgets(str, 100, fp);
                    deleteSpace(str);
                    char *temp  = (char*)malloc(sizeof(str));
                    strcpy(temp, str);
                    if( temp!= NULL && !strcmp(temp, "0,")) 
                    {
                        fgets(str, 100, fp);
                        deleteSpace(str);
                        char *temp  = (char*)malloc(sizeof(str));
                        strcpy(temp, str);
                        if( temp!= NULL && !strcmp(temp, "null,")) 
                        {
                            fgets(str, 100, fp);
                            deleteSpace(str);
                            // printf("%s\n", str); getchar();
                            lat_lon_hgh[0][j] = strtod(str, NULL);                            

                            fgets(str, 100, fp);
                            deleteSpace(str);
                            lat_lon_hgh[1][j] = atof(str);

                            fgets(str, 100, fp);
                            deleteSpace(str);
                            lat_lon_hgh[2][j] = atof(str);
                            
                            j++;
                        }
                    }
                }
            }
            free(temp);
            temp = NULL;
        }
    }
    fclose(fp);
    fp = fopen("output.txt", "w");

    i = 0;
    for (j=0; j<(sizeof(lat_lon_hgh[i])/sizeof(lat_lon_hgh[i][0])); j++)
    {
        for (i = 0; i<3; i++)
        {
            printf("%.14f ", lat_lon_hgh[i][j]);
            fprintf(fp, "%.14f ", lat_lon_hgh[i][j]);
        }
        printf("\n");
        fprintf(fp, "\n");
    }
    
    return(0);
}