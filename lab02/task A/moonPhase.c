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

int main(int argc, char *argv[]){
    FILE *fp = NULL;
    const char *string = "curl http://wttr.in/?format=j1 -s";
    const char *read = "r";
    const char *search = "moon_phase";
    char line[4096];
    char *target_str;
    char Mphase[64];


    printf("popen used with command: %s\n\n", string);

    fp = popen(string, read);

    if (fp == NULL){
        printf("error: popen return NULL\n");
        return 0;   
    }

    while(fgets(line, sizeof(line), fp) != NULL){
        target_str = strstr(line, search);   // searching string for specified text

        if (target_str != NULL){
            int i = 0;
            int quote_cnt = 0;

            // Parse string for the second set of quotations.
            // Save all characters between the second set of quotations.
            for(i = 0; i<sizeof(line); i++){
                if(line[i]=='\"'){
                    quote_cnt++;

                    if(quote_cnt==3){
                        int j = i + 1;
                        
                        while(line[j]!='\"'){
                            Mphase[j-(i+1)] = line[j];
                            j++;
                        }
                    }
                }
            }

            printf("line: %s\n", line);
            printf("Moon Phase: %s\n", Mphase);
            break;
        }
    }

    pclose(fp);

    printf("return 0 at end of program\n");
    return 0;
}