#include "etf.h"
#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a reusable format string
#define ETF_HEADER_FORMAT "%-5s %-12s %-80s %10s %-20s %-20s %10s %10s\n\n"
#define ETF_LINE_FORMAT "%-5s %-12s %-80s %10.2f %-20s %-20s %10d %10.2f\n"

ETF etfCreate(const char ticker[], const char isin[], const char name[], double ter, 
    const char distribution[], const char replication[], int fundSize, double var2024) {
        
    ETF etf;

    strcpy(etf.ticker, ticker);
    strcpy(etf.isin, isin);
    strcpy(etf.name, name);

    etf.ter = ter;

    strcpy(etf.distribution, distribution);
    strcpy(etf.replication, replication);

    etf.fundSize = fundSize;
    etf.var2024 = var2024;
    

    return etf;
}

void etfPrint(ETF etf) {
    //printf("TODO: etfPrint not implemented.\n");
    printf(ETF_LINE_FORMAT, etf.ticker, etf.isin, etf.name, etf.ter, etf.distribution, etf.replication, etf.fundSize, etf.var2024);
}

void etfPrintTable(ETF arr[], int arrLength) {
    if(arrLength <= 0) {
        printf("(Empty ETF data)\n");
        return;
    }

    printf(ETF_HEADER_FORMAT, "TICK", "ISIN", "NAME", "TER (%)", "DISTRIBUTION", "REPLICATION", "FUND SIZE", "2024 %");

    for(int i=0; i < arrLength; i++) {
        etfPrint(arr[i]);
    }
    printf("---\n");
    printf("Total ETF count: %d \n\n", arrLength);
}

int etfImport(const char* filename, ETF arr[], int arrLength) {
    FILE* file = fopen(filename, "r");
    if(file == NULL) {
        perror(filename);
        return -1; // documented error value
    }
    
    int count = 0;
    char line[1024];
    
    // Read and ignore header
    fgets(line, 1024, file);
    
    // Iterate over each line
    while (fgets(line, 1024, file))
    {
        if(count >= arrLength) break; // no more space

        char* tmp = strdup(line);
        
        char** tokens = splitString(tmp, 8, ";");
        
        // 'tokens' is an array[8] of strings, each position containing
        // a column from the CSV file

        double ter = atof(tokens[3]);
        int size = atoi(tokens[6]);
        double var2024 = atof(tokens[7]);

        arr[count++] = etfCreate(tokens[0], tokens[1], tokens[2], ter,
            tokens[4], tokens[5], size, var2024);

	    free(tokens);
        free(tmp);
    }

    fclose(file);

    return count;
}


int etfSearchByTicker(const char ticker[], ETF arr[], int arrLength) {
    
    for(int i=0; i < arrLength; i++) {
        if(strcmp(arr[i].ticker, ticker) == 0) return i;
    }

    return -1;
}

int etfSelectBest(ETF arr[], int arrLength) {
    if(arrLength <= 0) return -1;

    int bestIndex = 0;

    for(int i=1; i < arrLength; i++) {
        if(arr[i].var2024 > arr[bestIndex].var2024) {
            bestIndex = i;
        }
    }

    return bestIndex;
}

void etfSortByPerformance(ETF arr[], int arrLength) {
    // Using bubble sort without optimizations
    for(int i=0; i < arrLength - 1; i++) {
        for(int j=0; j < arrLength - i - 1; j++) {
            if(arr[j].var2024 < arr[j + 1].var2024) {
                ETF temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


void etfSortByTicker(ETF arr[], int arrLength) {
    // Using bubble sort without optimizations
    for(int i=0; i < arrLength - 1; i++) {
        for(int j=0; j < arrLength - i - 1; j++) {
            if(strcmp(arr[j].ticker, arr[j + 1].ticker) > 0) {
                ETF temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

