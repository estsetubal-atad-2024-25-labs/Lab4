#pragma once


/**
 * @brief Describes an Exchange Traded Fund.
 */
typedef struct etf
{
    char ticker[4 + 1];
    char isin[12 + 1];
    char name[80 + 1];
    double ter;
    char distribution[20 + 1];
    char replication[20 + 1];
    int fundSize;
    double var2024;
} ETF;

/**
 * @brief Creates and initializes an ETF structure.
 * 
 * This function initializes an ETF structure with the provided values.
 * It ensures that string parameters are safely copied and properly null-terminated.
 * 
 * @param ticker The ETF's ticker symbol (max 4 characters).
 * @param isin The ETF's ISIN (max 12 characters).
 * @param name The full name of the ETF (max 80 characters).
 * @param ter The total expense ratio (TER) of the ETF.
 * @param distribution The distribution type (e.g., "Distributing", "Accumulating").
 * @param replication The replication method (e.g., "Full replication", "Swap based").
 * @param fundSize The total size of the fund in million of euros.
 * @param var2024 The ETF variation for 2024.
 * 
 * @return A fully initialized ETF structure.
 */
ETF etfCreate(const char ticker[], const char isin[], const char name[], double ter, 
    const char distribution[], const char replication[], int fundSize, double var2024);

/**
 * @brief Prints an ETF's details in a single-line formatted output.
 * 
 * This function displays all fields of an ETF structure in a single line, 
 * using fixed column widths for proper alignment. It ensures that the data 
 * is printed in a structured and readable format.
 * 
 * @param etf The ETF structure to be printed.
 * 
 * @note The function prints directly to the standard output (stdout).
 */
void etfPrint(ETF etf);

/**
 * @brief Prints a table of ETFs with aligned columns.
 * 
 * This function prints multiple ETFs in a structured table format, ensuring 
 * proper column alignment for readability. It prints a header row followed by 
 * the ETF data from the provided array.
 * 
 * @param arr An array of ETF structures to be printed.
 * @param arrLength The number of ETFs in the array.
 * 
 * @note The function prints directly to the standard output (stdout).
 * @warning If `arrLength` is zero or negative, nothing is printed.
 */
void etfPrintTable(ETF arr[], int arrLength);

/**
 * @brief Imports ETF data from a file into an array.
 * 
 * This function reads ETF data from the specified file and stores it in the provided array.
 * The function ensures that no more than `arrLength` elements are read to prevent buffer overflow.
 * 
 * @param filename The name of the file to read ETF data from.
 * @param arr An array of ETF structures where the imported data will be stored.
 * @param arrLength The maximum number of ETFs that can be stored in the array.
 * 
 * @return The number of ETFs successfully imported, or -1 if an error occurs (e.g., file not found).
 */
int etfImport(const char* filename, ETF arr[], int arrLength);

/**
 * @brief Searches for an ETF in the array by its ticker symbol.
 * 
 * @param ticker The ticker symbol to search for (null-terminated string).
 * @param arr The array of ETFs.
 * @param arrLength The number of elements in the array.
 * @return The index of the ETF if found, or -1 if not found.
 */
int etfSearchByTicker(const char ticker[], ETF arr[], int arrLength);

/**
 * @brief Selects the best ETF from the array based on performance.
 * 
 * @param arr The array of ETFs.
 * @param arrLength The number of elements in the array.
 * @return The index of the best ETF in the array.
 */
int etfSelectBest(ETF arr[], int arrLength);

/**
 * @brief Sorts the ETF array in descending order based on performance.
 * 
 * @param arr The array of ETFs to be sorted.
 * @param arrLength The number of elements in the array.
 */
void etfSortByPerformance(ETF arr[], int arrLength);

/**
 * @brief Sorts the ETF array in ascending order (A-Z) based on ticker symbols.
 * 
 * @param arr The array of ETFs to be sorted.
 * @param arrLength The number of elements in the array.
 */
void etfSortByTicker(ETF arr[], int arrLength);

