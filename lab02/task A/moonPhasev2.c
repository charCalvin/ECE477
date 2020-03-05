/*  moonPhase.c
 *  
 * Authors: 
 *      Calvin Skinner, Susan Hastings
 * 
 * Description: 
 *      Use the curl command with in the function popen() to return a file pointer
 *      to a jason file with weather data; including moon phases. The phase date
 *      needs to be parsed out and written to standard output.
 * 
 * Prototypes:
 *      FILE *popen(const char *command, const char *type);
 * 
 *      int pclose(FILE *stream);
 */

/* COPIED FROM JSON FILE:
    "weather": [
        {
            "astronomy": [
                {
                    "moon_illumination": "7", 
                    "moon_phase": "Waning Crescent", 
                    "moonrise": "05:04 AM", 
                    "moonset": "02:06 PM", 
                    "sunrise": "06:28 AM", 
                    "sunset": "05:09 PM"
                }
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int double_quote_parse(char *str, long int str_size, int pair_num, char * rtn_str);

int main(int argc, char *argv[]){
    FILE *fp = NULL;
    const char *string = "curl http://wttr.in/?format=j1 -s";
    const char *read = "r";
    const char *search = "moon_phase";
    char line[4096];
    char *target_str;
    char Mphase[4096];


    printf("popen used with command: %s\n", string);

    fp = popen(string, read);

    // Check for NULL file pointer
    // if (fp == NULL){
    //     printf("error: popen return NULL\n");
    //     return 0;
    // }

    while(fgets(line, sizeof(line), fp) != NULL){
        target_str = strstr(line, search);   // searching string for specified text

        if (target_str != NULL){
            printf("line: %s\n\n", line);

            if(double_quote_parse(line, sizeof(line), 2, Mphase) != 0){
                printf("error: double_quote_parse returned -1\n");
                return 0;
            }

            int i = 0;
            while(Mphase[i] != "\n"){
                printf("%c", Mphase[i]);
                i++;
            }

            printf("\n\nline: %s", line);
            printf("Moon Phase: %s\n", Mphase);
            break;
        }
    }

    pclose(fp);
    printf("return 0, end od program");
    return 0;
}

int double_quote_parse(char *str, long int str_size, int pair_num, char * rtn_str){
    printf("str: %s\n", str);
    pair_num = (pair_num * 2) - 1;
    printf("1,");

    int i = 0;
    int quote_cnt = 0;

    // Parse string for the second set of quotations.
    // Save all characters between the second set of quotations.
    for(i = 0; i<str_size; i++){
        
        // find quotes
        if(str[i]=="\""){
            quote_cnt++;
            printf("3,");

            if(quote_cnt==pair_num){
                int j = i + 1;
                printf("4,");

                // store characters between quotesa
                while(str[j]!="\""){
                    rtn_str[j-(i+1)] = str[j];
                    j += 1;
                    printf("5,");
                }

                printf("6,");
                return 0;
            }
        }
    }   

    return 0;
    printf("7,");
}