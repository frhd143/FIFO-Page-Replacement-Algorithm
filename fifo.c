
/*
    Written by Farhd Asadi
    First In First Out Page Replacement Algorithm
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main (int argc, char *argv[]) {
    int page_size = atoi(argv[2]);
    int nu_phys_pages = atoi(argv[1]);
    char *filename = argv[3];
    
    FILE *file = fopen(filename, "r");
    char line[12];
    int page_numbers[100000]; // Our page reference
    int a = 0; // page number
    int i = 0; // keeps track of where in our array should we put our page number(a).
    
    // Open the file and save every line into our array(page_numbers)
    while(fgets(line, 13, file)) {
        a = atoi(line)/(page_size);
        page_numbers[i] = a;
        i++;        
    }
    
    fclose(file);
    
    int frames = nu_phys_pages; 
    int pages = sizeof(page_numbers)/sizeof(page_numbers[0]);
    
    // Create a table 
    int temp[frames];
    for (int i = 0; i < frames; i++) {
        // pages cannot have negative number so it is ok to till the table with -1s.
        temp[i] = -1;
    }

    int miss = 0; // number of page faults
    int index = 0; // keeps track of where we are and where we should add new pages in our table(temp)

    // Go through every page
    for (int i = 0; i < pages; i++) {
        // helper help oss to skip some parts of we get a hit!
        // if helper is 1 it means that we get a hit!
        int helper = 0;
        for (int j = 0; j < frames; j++) {
            if (page_numbers[i] == temp[j]) {
                helper++;
                // We substract one from miss because even when we get a hit the program increaments miss by 1
                // to avoid this we simply subtract one so when the program increaments one nothing will change
                miss--;
            }
        }
        miss++;

        // If we get a hit (helper = 1), the we skip these two if statements
        if (index == frames && helper == 0) {
            index = index % frames;
            temp[index] = page_numbers[i];
            index++;
        } else if (index < frames && helper == 0) {
            temp[index] = page_numbers[i];
            index++;
        }
    }

    printf("Number of physical pages = %d, page size = %d\n", nu_phys_pages, page_size);
    printf("Reading memory trace from %s...  Read %d memory references\n", filename, pages);
    printf("Results:  %d page faults\n", miss);
    // printf("------------------------------------------------------------------------\n");
    //printf("%d\n", miss);

    return 0;
}



