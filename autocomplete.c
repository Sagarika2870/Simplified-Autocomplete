#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "autocomplete.h"
#include <ctype.h>

void removeChar(char *str, char delete) {

    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != delete) dst++;
    }
    *dst = '\0';
}

char *substring(char *string, int position, int length) 
{
   char *pointer;
   int ind;
 
   pointer = malloc(length+1);
 
   for (ind = 0 ; ind < length ; ind++)
   {
      *(pointer+ind) = *string;      
      string++;   
   }
 
   *(pointer+ind) = '\0';
 
   return pointer;
}

int compare(const void *p1, const void *p2)
{
    struct term *ip1 = (struct term *)p1;
    struct term *ip2 = (struct term *)p2;
    // const char* a = (const char*)p1;
    // const char* b = (const char*)p2;
    //strcmp(((ptr)p1)->term, ((ptr)p2)->term);
    return strcmp(ip1->term,ip2->term);
}
int compare1(const void * a, const void * b) {
    struct term *ip1 = (struct term *)a;
    struct term *ip2 = (struct term *)b;
    // const char* a = (const char*)p1;
    // const char* b = (const char*)p2;
    //strcmp(((ptr)p1)->term, ((ptr)p2)->term);
    return (ip2->weight-ip1->weight);
}

void read_in_terms(struct term **terms, int *pnterms, char *filename){
    //Defining variables
    int n = 0;
    char *first;
    struct term *ptr = *terms;
    char line[200];
    FILE *fp; 
    fp = fopen(filename, "r");
    first = fgets(line, sizeof(line), fp);
    fprintf(stderr, "hello");
    double a;
    n = atoi(first);
    *pnterms = n;
    char delim[] = "\t";
    char *line_weight; 
    char *line_term;

    //Allocating memory 
    ptr =(struct term *)malloc(n * sizeof(struct term));
    char new = '\n';
    char *null = "\0";
    //Reading File and Sending to *terms 
    for(int i = 0; i < n; i++){
        fgets(line, sizeof(line), fp); //read in at most sizeof(line) characters
        line_weight = strtok(line,delim);
        line_term = strtok(NULL,delim);
        removeChar(line_term, new);
        // for(int j = 0; line_term[j]; j++){
        //     line_term[j] = tolower(line_term[j]);
        // }
        a = atof(line_weight);
        strcpy(ptr[i].term, line_term); 
        ptr[i].weight = a;
    }
    
    //size_t structs_len = sizeof(ptr) / sizeof(struct term);
   // printf("%s\n",ptr); 
    qsort(ptr, *pnterms, sizeof(struct term),compare);
    *terms = ptr;
    // for(int i = 0; i<7; i++){
    //     printf("%s\n",ptr+i);
    // }
    
    //printf("%s\n",*terms);
    //free(ptr);  //why is term empty when we free ptr?
    //fflush(stdout);
}

int lowest_match(struct term *terms, int nterms, char *substr){ // test if substring is not in terms
    int low = 0;
    int high = nterms;
    int mid;
    char *mid_sub;
    char *subs;
    char *sub_low;
    char *sub_high;
    int size = strlen(substr);
    char *a = (char *)malloc(sizeof(nterms));
    char *b= (char *)malloc(sizeof(nterms));
    char *c=(char *)malloc(sizeof(nterms));
    char *d=(char *)malloc(sizeof(nterms));
    while(high -low >= 2){
        mid = (low+high)/2;
        strcpy(a,terms[mid-1].term);
         
        mid_sub = substring(a,0,size);
        if(strcmp(mid_sub,substr)> 0){
            high = mid -1;
        }else if(strcmp(mid_sub,substr)< 0){
            low = mid+1;
        }else if(strcmp(mid_sub,substr)== 0){
            for(int i = 0;i<=mid; i++){ //does not return lowest (make temp variable and compare with new subs(min ind))
                strcpy(b,terms[i].term);
                subs = substring(b, 0, size);
                if(strcmp(subs,substr) == 0){
                    return i;
                // }else{
                //     return mid;
                }
            }
        }
        }
        strcpy(c,terms[low-1].term);
        sub_low = substring(c,0,size);
        strcpy(d,terms[high-1].term);
        sub_high = substring(c,0,size);
            
    
        // for(int i =0; i<=mid; i++){
        //     strcpy(b,terms[i].term);
        //     subs = substring(b, 0, size);
        //     if(strcmp(subs,substr) == 0){
        //         return i;
        // }
        if (strcmp(sub_low,substr) == 0){
            //printf("%d\n",low);
            return low;
        }else if (strcmp(sub_high,substr) == 0){
            //printf("%d\n",high);
            return high;
    }
}

    int highest_match(struct term *terms, int nterms, char *substr){
        int low = 0;
        int high = nterms;
        int mid;
        char *mid_sub;
        char *subs;
        char *sub_high;
        char *sub_low;
        int size = strlen(substr);
        char *a = (char *)malloc(sizeof(nterms));
        char *b= (char *)malloc(sizeof(nterms));
        char *c=(char *)malloc(sizeof(nterms));
        char *d=(char *)malloc(sizeof(nterms));
        while(high -low >= 2){
            mid = (low+high)/2;
            strcpy(a,terms[mid-1].term);
            
            mid_sub = substring(a,0,size);
            if(strcmp(mid_sub,substr)> 0){
                high = mid -1;
            }else if(strcmp(mid_sub,substr)< 0){
                low = mid+1;
            }else if(strcmp(mid_sub,substr)== 0){
                for(int i = nterms-1;i>mid; i--){//does not actually return highest
                    strcpy(b,terms[i].term);
                    subs = substring(b, 0, size);
                    if(strcmp(subs,substr) == 0){
                        return i;
                    // }else{
                    //     return mid;
                    }
                }
            }
            }
               strcpy(c,terms[low-1].term);
        sub_low = substring(c,0,size);
        strcpy(d,terms[high-1].term);
        sub_high = substring(c,0,size);           

        if (strcmp(sub_low,substr) == 0){
            //printf("%d",low);
            return low;
        }else if (strcmp(sub_high,substr) == 0){
            //printf("%d",high);
            return high;
    }
    }
    
// use binary search to find when the substring is in a element and then compare the vlaues around it to determine 
// the lowest 
void autocomplete(struct term **answer, int *n_answer, struct term *terms, int nterms, char *substr){
//     //call lowest and highest match
//     //Extract terms from struct term *terms
//     //use malloc to allocate memory for **answer
//     //Qsort by weight in a for loop and count number of answers (nanswers)
    int low_ind = lowest_match(terms,nterms, substr);
    int high_ind = highest_match(terms, nterms,substr);
    int num;
    if(low_ind == -1 && high_ind ==-1){
        num = 0;
    }else{
        num = high_ind-low_ind+1;
    }
    
    *n_answer = num;
    struct term *pointer = *answer;
    pointer =(struct term *)malloc(num * sizeof(struct term));
    for(int i = 0; i < num; i++){
        //printf("%s\n",terms[low_ind-1+i].term);
        strcpy(pointer[i].term, terms[low_ind-1+i].term); 
        pointer[i].weight = terms[low_ind-1+i].weight;
    }
    if(num != 0){
        qsort(pointer, *n_answer, sizeof(struct term),compare1);
    }
    
    *answer = pointer;
    for(int i = 0; i<num;i++){
        printf("%s\n", *answer+i);
    }
    

}