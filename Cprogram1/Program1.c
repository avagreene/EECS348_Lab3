#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//prints the sales report
void salesReport(float *data, char** months) //maybe edit so the values actually line up
{
    printf("Monthly Sales Report for 2022:\n");
    printf("Month       Sales\n");
    for (int i = 0; i < 12; i++) 
    {
        printf("%s", months[i]);
        printf("    $");
        printf("%.2f\n", data[i]); //prints data to the first 2 decimal places
    }

}

//prints the min, max, and average of the monthly sales
void minMaxAvg(float *data, char** months)
{
    float min = data[0];
    char* minMonth = months[0];
    float max = data[0];
    char* maxMonth = months[0];
    float average = data[0];

    for (int i=1; i < 12; i++)
    {
        if (data[i]<min)
        {
            min=data[i];
            minMonth=months[i];
        }
        if (data[i]>max)
        {
            max=data[i];
            maxMonth=months[i];
        }

        average+=data[i];
    }

    average/=12;


    printf("\nSales summary:\n");

    printf("Minimum sales:   $");
    printf("%.2f", min);
    printf("    (");
    printf("%s", minMonth);
    printf(")\n");

    printf("Maximum sales:   $");
    printf("%.2f", max);
    printf("    (");
    printf("%s", maxMonth);
    printf(")\n");

    printf("Average sales:    $");
    printf("%.2f\n", average);

}

void sixMonths(float *data, char** months)
{

    printf("\nSix-Month Moving Average Report: \n");

    for (int i=0; i<7; i++)
    {
        float average=0;

        printf("%s", months[i]); 
        printf("   -  "); 
        printf("%s", months[i+5]);
        printf("    $");

        for (int j=0; j<6; j++)
        {
            average+=data[j+i];
        }
        average/=6;
        printf("%.2f\n", average);
    }

}

void highLow(float *data, char** months)
{
    printf("\nSales Report (Highest to Lowest): \n");
    printf(" Month      Sales \n");
    
    float *sortedData = data;
    char** sortedMonths = months;

    for (int i=0; i<11; i++)
    {
        for (int j = i + 1; j<12; j++)
        {
            if (sortedData[i]<sortedData[j])
            {
                float temp = sortedData[i];
                char *temp2 = sortedMonths[i];
                sortedData[i] = sortedData[j];
                sortedMonths[i] = sortedMonths[j];
                sortedData[j] = temp;
                sortedMonths[j] = temp2;
            }
        }
    }

    for (int i = 0; i < 12; i++) 
    {
        printf("%s", sortedMonths[i]);
        printf("    $");
        printf("%.2f\n", sortedData[i]); //prints data to the first 2 decimal places
    }
}

char** monthArray()
{

    char** months = malloc(12 * sizeof(char*)); //allocate memory for an array of 12 char pointers
    char* names[12]={"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    for (int i=0; i<12; i++)
    {
        months[i] = malloc((strlen(names[i]) + 1) * sizeof(char)); //copy each month name into a new dynamically allocated string
        strcpy(months[i], names[i]);
    }

    return months;
}

float* getData(char *fileName)
{
    FILE *fptr;

    fptr = fopen(fileName, "r"); //opens file for reading

    //if statement in case the file doesn't exist
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return NULL;
    }

    char data[12][100]={}; //creates an array of 12 elements, each element has a maximum length of 100 characters
    int i = 0;

    //for loop for the 12 lines of data for each month in the file
    for (i = 0; i < 12; i++) {
        if (fgets(data[i], 100, fptr) == NULL) //stores the data for each line in each element in the array
        { 
            break; //if the line doesn't exist the loop breaks
        }
    }

    float *numData = (float *)malloc(12 * sizeof(float)); // allocate memory for an array of 12 floating-point values
    if (numData == NULL) {
        printf("Error allocating memory!\n");
        return NULL;
    }

    //loop through each element of the data array and store it as a floating-point value in the `numData` array
    //doing this because the other array is not float type
    for (i = 0; i < 12; i++) {
        sscanf(data[i], "%f", &numData[i]);
    }

    fclose(fptr); //close the file
    return numData;
}


int main()
{
    //get data from file by calling the getData function
    float *data = getData("filename.txt");
    if (data == NULL) 
    {
        return 1;
    }
    
    char** months = monthArray(); //get an array of months by calling the monthArray function

    //calling functions for the programs output:
    salesReport(data, months);
    minMaxAvg(data, months);
    sixMonths(data, months);
    highLow(data, months);



    //freeing allocated memory
    free(data);
    for (int i = 0; i < 12; i++) {
        free(months[i]);
    }
    free(months);

    return 0;
}
