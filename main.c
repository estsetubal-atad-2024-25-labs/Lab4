#include <stdio.h> 
#include <stdlib.h>
#include "input.h"
#include "etf.h"

#define MAX_ETF 100

int main() {

    //ETF etf = {"SXR8", "IE00B5BMR087", "iShares Core S&P 500 UCITS ETF USD (Acc)", 0.07, "Accumulating", "Full replication", 104545, 32.62};
    //ETF etf = etfCreate("SXR8", "IE00B5BMR087", "iShares Core S&P 500 UCITS ETF USD (Acc)", 0.07, "Accumulating", "Full replication", 104545, 32.62);
    //etfPrint(etf);
    
    ETF etfs[MAX_ETF];
    int dataLength = etfImport("etfs.csv", etfs, MAX_ETF);
    etfPrintTable(etfs, dataLength);
    

    int find = etfSearchByTicker("H4ZJ", etfs, dataLength);
    find > -1 ? etfPrint(etfs[find]) : printf("Not found.\n");

    int best = etfSelectBest(etfs, dataLength);
    best > -1 ? etfPrint(etfs[best]) : printf("Not found.\n");

    etfSortByPerformance(etfs, dataLength);
    etfPrintTable(etfs, dataLength);

    etfSortByTicker(etfs, dataLength);
    etfPrintTable(etfs, dataLength);

    return EXIT_SUCCESS;
}
