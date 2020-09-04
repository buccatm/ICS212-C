/****************************************************************************************************************
//
//  NAME:           Marcos Buccat Jr.
//
//  HOMEWORK:       3b
//
//  CLASS:          ICS 212
//
//  INSTRUCTOR:     Ravi Narayan
//
//  DATE:           February 13, 2020
//
//  FILE:           database.c
//
//  DESCRIPTION:
//    This file contains all of the database function definition.
//    It contains the definition for addRecord, printRecord,
//    printAllRecord, ModifyRecord and deleteRecord.
//
*****************************************************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "database.h"

extern int debugmode;

/*****************************************************************************************************************
//
//   Function Name:               addRecord
//
//   DESCRIPTION:                 This function will add a record to a list. If the list
//                                is empty it will create one. The function will also put the
//                                records inorder.
//
//   PARAMETERS:                  record (struct record **): A record data type that contains account number, name
//                                                          , address and the next record address.
//                                accountno (int)         : The account number of the record
//                                name (char *)           : The name for that record
//                                address (char *)        : The address for the owner of that record
//
//   Return Values:               0  : Success
//                                -1 : Error or Failure
//
**************************************************************************************************************/

int addRecord(struct record ** record, int accountno, char name[], char address[])
{
    struct record * temp;
    struct record * index;
    int result;

    result = -1;
    index = *record;
    if (debugmode == 1)
    {
        printf("\n=============================== Debug Mode ============================\n");
        printf("Entering Add Record\n\tPassing:\n");
        printf("\nStarting ADDRESS: %p\n", (void*)*record);
        printf("Accountno: %d\n", accountno);
        printf("Name: %s\n", name);
        printf("Address: %s\n", address);
    }

    if (accountno > 0)
    {
        temp = (struct record *) malloc(sizeof(struct record));
        temp -> accountno = accountno;
        strcpy(temp -> name, name);
        strcpy(temp -> address, address);
        temp -> next = NULL;

        if (debugmode == 1)
        {
            printf("\n-----------------------------------------------------\n\n");
            printf("Creating Record: \n");
            printf("Record Address: %p\n", (void*)temp);
            printf("Accountno: %d\n", temp -> accountno);
            printf("Name: %s\n", temp -> name);
            printf("Address: %s\n", temp -> address);
            printf("Next: %p\n", (void*)temp -> next);
            printf("\n-----------------------------------------------------\n\n");
        }

        if (*record != NULL)
        {
            if (debugmode == 1)
            {
                printf("Starting Address: %p\n", (void*)*record);
            }
            while (index -> next != NULL)
            {
                if (debugmode == 1)
                {
                    printf("Last Address: %p\n", (void*)index);
                    printf("Next Index: %p\n\n", (void*)index -> next);
                }

                index = index -> next;
                if (debugmode == 1)
                {
                    printf("Current address: %p\n", (void*)index);
                }
            }
            if (debugmode == 1 && index -> next == NULL)
            {
                printf("At the end of list.\n");
                printf("\nAddress of last record in list: %p --> ", (void*)index);
                printf("Next: %p\n", (void*)index -> next);
                printf("Addres of created record: %p\n", (void*)temp);
            }
            temp -> next = index -> next;
            index -> next = temp;
            result = 0;
            if (debugmode == 1)
            {
                printf("\nAdding to the end of record\n");
                printf("Address of last record in list: %p --> ", (void*)index);
                printf("Next: %p\n", (void*)index -> next);
            }
        }

        if (*record == NULL)
        {
            *record = temp;
            index = *record;
            result = 0;
            if (debugmode == 1)
            {
                printf("\nAdding to Empty list\n");
                printf("Address record in list: %p --> ", (void*)index);
                printf("Next: %p\n", (void*)index -> next);
            }
        }
    }

    if (debugmode == 1)
    {
        if (result == 0)
        {
            printf("Result: %d\n\t==== Successfully Added Record ====\n\n", result);
            printf("====================== Exit Add File Functiong ========================\n\n");
        }
    }
    return result;
}

/******************************************************************************************************************
//
//  Function Name:                printRecord
//
//  DESCRIPTION:                  Prints a specific record in the list by inputing an account number.
//
//  PARAMETERS:                   record (struct record *): A record data type that contains the account number, name
//                                                          , address and the next record address.
//                                accountno (int)         : The account number of the account.
//
//  Return Values:                -1: Record not found
//                                 1: Record was found and printed
//
*******************************************************************************************************************/

int printRecord(struct record * record, int accountno)
{
    struct record * index;
    int result;
    int records_printed;

    result = -1;
    records_printed = 0;
    index = record;

    if (debugmode == 1)
    {
        printf("\n=============================== Debug Mode ==============================\n");
        printf("\tEntering Print a Record\n\n");
        printf("Address starting Record: %p\n", (void*)record);
        printf("Passed in Accountno: %d\n\n", accountno);
    }
    if (accountno > 0 && record != NULL)
    {
        while (index != NULL)
        {
            if (debugmode == 1)
            {
                if (accountno != index -> accountno && debugmode == 1)
                {
                    printf("No Record Found at: %p\n", (void*)index);
                }
                printf("Next: %p\n\n", (void*)index -> next);
            }
            if (accountno == index -> accountno && debugmode != 1)
            {
                printf("Accountno: %d\n", index -> accountno);
                printf("Name: %s\n", index -> name);
                printf("Address: %s\n\n", index -> address);
                records_printed++;
            }
            if (accountno == index -> accountno && debugmode == 1)
            {
                printf("Record Found!\nAddress of Record: %p\n", (void*)index);
                printf("Accountno: %d\n", index -> accountno);
                printf("Name: %s\n", index -> name);
                printf("Address: %s\n", index -> address);
                printf("Next: %p\n", (void*)index -> next);
                records_printed++;
                printf("Number of Records Found: %d\n", records_printed);
            }
            index = index -> next;
            if (debugmode == 1)
            {
                printf("\nCurrent address: %p\n", (void*)index);
            }
        }
        if (debugmode == 1)
        {
            printf("\n===================== Exit Print Functiong =======================\n\n");
        }
    }
    if (records_printed == 0)
    {
        result = -1;
        printf("No such Record Found!\n");
    }
    if (records_printed >= 1)
    {
        result = 0;
        if (debugmode != 1)
        {
            printf("Number of Record Printed with account# %d: %d\n", accountno, records_printed);
        }
    }

    return result;
}

/********************************************************************************************************************
//
//  Function Name:                printAllRecords
//
//  DESCRIPTION:                  prints all of the records in this list.
//
//  PARAMETERS:                   record (struct record *): The record that contains the name, address, account number
//                                                          and the next record address of the list.
//
//  Return Value:                 NONE
//
*********************************************************************************************************************/

void printAllRecords(struct record * record)
{
    struct record * index;
    int counter;
    index = record;
    counter = 0;

    if (debugmode == 1)
    {
        printf("\n=============================== Debug Mode ==================================\n");
        printf("\tEntering Printing All Record Mode\n");
        printf("Address of starting Record: %p\n\n", (void*)index);
    }

    if (record == NULL)
    {
        printf("Record is Empty!\n");
    }

    if (record != NULL)
    {
        while (index -> next != NULL)
        {
            counter++;

            if (debugmode != 1)
            {
                printf("RECORD #%d\n", counter);
                printf("Accountno: %d\n", index -> accountno);
                printf("Name: %s\n", index -> name);
                printf("Address: %s\n\n", index -> address);
            }

            if (debugmode == 1)
            {
                printf("RECORD #%d\n", counter);
                printf("Record Address: %p\n", (void*)index);
                printf("Accountno: %d\n", index -> accountno);
                printf("Name: %s\n", index -> name);
                printf("Address: %s\n", index -> address);
                printf("Next: %p\n\n", (void*) index -> next);
            }

            index = index -> next;
        }

        if (index -> next == NULL)
        {
            counter++;

            if (debugmode != 1)
            {
                printf("RECORD #%d\n", counter);
                printf("Accountno: %d\n", index -> accountno);
                printf("Name: %s\n", index -> name);
                printf("Address: %s\n\n", index -> address);
            }

            if (debugmode == 1)
            {
                printf("RECORD #%d\n", counter);
                printf("Record Address: %p\n", (void*)index);
                printf("Accountno: %d\n", index -> accountno);
                printf("Name: %s\n", index -> name);
                printf("Address: %s\n", index -> address);
                printf("Next: %p\n\n\n", (void*) index -> next);
            }

            index = index -> next;
        }
    }

    if (debugmode == 1)
    {
        printf("size: %d\nIndex: %p\n", counter, (void*)index);
        printf("====================== Exit Print all Functiong ==========================\n\n");
    }
    if (debugmode != 1)
    {
        printf("Number of Records in list: %d\n", counter);
    }
}

/*************************************************************************************************
//
//  FUNCTION NAME:                 writefile
//  
//  DESCRIPTION:                   Writes all of the records availabe in the list, into a file.
//
//  PARAMETERS:                    record (struct record *) : The starting address of the first
//                                                            address.
//                                 filename (char[])        : The name of the file to write the
//                                                            records.
//
//  Return Value:                  0  : Success
//                                 -1 : Failure
//
***************************************************************************************************/

int writefile(struct record * record, char filename[])
{
    int result;
    int recs;
    struct record * index;
    FILE *fp;
    index = record;
    recs = 0;
    result = -1;
    fp = fopen(filename, "w");

    if (debugmode == 1)
    {
        printf("\n========================= Enter Write File =======================\n\n");
        printf("Reading from: %p\n", (void*)record);
        printf("Writing data to File: %s\n\n", filename);
    }
    if (fp == NULL)
    {
        result = -1;
    }
    if (fp != NULL && record != NULL)
    {
        while (index -> next != NULL)
        {
            fprintf(fp, "%d\n", index -> accountno);
            fprintf(fp, "%s\n", index -> name);
            fprintf(fp, "%s$\n", index -> address);
            recs++;

            if (debugmode == 1)
            {
                printf("Current Address: %p\n", (void*)index);
                printf("Record# %d\n", recs);
                printf("Accountno: %d\n\n", index -> accountno);
            }
            index = index -> next;
        }
        if (index -> next == NULL)
        {
            fprintf(fp, "%d\n", index -> accountno);
            fprintf(fp, "%s\n", index -> name);
            fprintf(fp, "%s$\n", index -> address);
            recs++;
            if (debugmode == 1)
            {
                printf("Current Address: %p\n", (void*)index);
                printf("Record# %d\n", recs);
                printf("Accountno: %d\n\n", index -> accountno);
                printf("\n========================= Exit Write File =======================\n\n");
            }
            index = index -> next;
        }
        result = 0;
    }
    return result;
}

/****************************************************************************************************
//
//  FUNCTION NAME:                      readfile
//
//  DESCRIPTION:                        Reads data from a file. Then adds the data to the record
//                                      list.
//
//  PARAMETERS:                         record (struct record **) : A record pointer that points to 
//                                      a records that contains account number, name, address and
//                                      the next available record
//                                      filename (char[])         : The name of the file to read 
//                                                                  from
//
//  Return value:                       1  : success
//                                      -1 : Failure
//                                      
******************************************************************************************************/

int readfile(struct record ** record, char filename[])
{
    int result;
    int index;
    int counter;
    int run;
    int account;
    int line;
    int skip_line;

    char input;
    char accountno[10];
    char name[25];
    char address[80];

    FILE *fp;

    counter = 0;
    result = 0;
    index = 0;
    skip_line = 0;
    run = 1;
    account = 0;
    line = 1;

    if (debugmode == 1)
    {
        printf("\n========================== Debug mode ===========================\n");
        printf("\tEnter Read File\n");
        printf("Inputing to Starting address: %p\n", (void*)*record);
        printf("Reading File: %s\n\n", filename);
    }

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        result = -1;
        run = 0;
    }
    if (fp != NULL)
    {
        while (run == 1)
        {
            input = fgetc(fp);
            if (input != EOF)
            {
                if (line == 1 && input != '$')
                {
                    if (input != '\n')
                    {
                        if (debugmode == 1)
                        {
                            printf("Reading line 1, Accountno\n");
                        }
                        accountno[index] = input;
                        if (index < 8)
                        {
                            index++;
                        }
                    }
                    if (input == '\n')
                    {
                        accountno[index] = '\0';
                        account = atoi(accountno);
                        if (debugmode == 1)
                        {
                            printf("Finished reading line 1\n");
                            printf("Accountno: %d\n", account);
                        }
                        line = 4;
                        index = 0;
                    }
                }

                if (line == 2)
                {
                    if (input != '\n')
                    {
                        if (debugmode == 1)
                        {
                            printf("Reading line 2, Name\n");
                        }
                        name[index] = input;
                        if (index < 23)
                        {
                            index++;
                        }
                    }
                    if (input == '\n')
                    {
                        name[index] = '\0';
                        if (debugmode == 1)
                        {
                            printf("Finish Reading line 2\n");
                            printf("Name: %s\n", name);
                        }
                        line = 6;
                        index = 0;
                    }
                }

                if (line == 3)
                {
                    if (input != '$')
                    {
                        if (debugmode == 1)
                        {
                            printf("Reading line 3, Address\n");
                        }
                        address[index] = input;
                        if (index < 78)
                        {
                            index++;
                        }
                    }
                    if (input == '$')
                    {
                        address[index] = '\0';
                        counter++;
                        line = 5;
                        index = 0;
                        if (debugmode == 1)
                        {
                            printf("Finish Reading line 3\n");
                            printf("Address: %s\n", address);
                        }
                        addRecord(record, account, name, address);
                    }
                }

                if (line == 4)
                {
                    if (debugmode == 1)
                    {
                        printf("Skip Char\n");
                    }
                    line = 2;
                }
                if (line == 5)
                {
                    skip_line++;
                    if (debugmode == 1)
                    {
                        printf("Skip Char\n");
                    }
                }
                if (line == 6)
                {
                    if (debugmode == 1)
                    {
                        printf("Skip char\n");
                    }
                    line = 3;
                }
                if (skip_line == 2)
                {
                    line = 1;
                    skip_line = 0;
                    if (debugmode == 1)
                    {
                        printf("Reading line 1 Again\n");
                    }
                }
            }

            if (input == EOF)
            {
                run = 0;
                result = 1;
            }
        }
        fclose(fp);
    }
    if (debugmode == 1)
    {
        if (result == 1)
        {
            printf("\n\tNumber of Records Detected: %d\n", counter);
        }
        printf("\n==================== Exit Read File ===================\n\n");
    }

    return result;
}

/*******************************************************************************************************
//
//  FUNCTION NAME:                     cleanup
//
//  DESCRIPTION:                       Before exiting the program, this function will cleanup
//                                     the heap. It will be releasing all of the spaces used
//                                     in the heap.
//
//  PARAMETERS:                        start (struct record**) : A struct record pointer that points
//                                     to a struct record that contains the accountno, name, address
//                                     and the next available record.
//
//  RETURN VALUE:                      void
//
*********************************************************************************************************/

void cleanup(struct record ** start)
{
    struct record * index;
    struct record * remove;
    int counter;
    index = *start;
    remove = *start;
    counter = 0;
    if (debugmode == 1)
    {
        printf("\n========================= Debug Mode ===========================\n\n");
        printf("\tEnter cleanup Function\n\n");
        printf("Starting address: %p\n\n", (void*)index);
    }
    if (*start != NULL)
    {
        while (index -> next != NULL)
        {
            if (debugmode == 1)
            {
                printf("Current Index: %p -->", (void*)index);
                printf("Next: %p\n", (void*)index -> next);
                printf("To Remove: %p\n\n", (void*)remove);
            }
            index = index -> next;
            free(remove);
            counter++;
            *start = index;
            remove = *start;
        }
        if (index -> next == NULL)
        {
            if (debugmode == 1)
            {
                printf("Current Index: %p -->", (void*)index);
                printf("Next: %p\n", (void*)index -> next);
                printf("To Remove: %p\n\n", (void*)remove);
            }

            index = index -> next;
            free(remove);
            counter++;
            remove = index;
            *start = index;
        }
    }
    if (debugmode == 1)
    {
        printf("amount removed: %d\n", counter);
        printf("\n======================= Exit Clean up =========================\n\n");
    }
}

/*********************************************************************************************************************
//  
//  Function Name:               modifyRecord
//
//  DESCRIPTION:                 This will modify an existing account in the record. The function will modify the 
//                               inputed account number's address.
//
//  PARAMETERS:                  record (struct record *): The record that contains the name, address, account number
//                                                          and the next record address of the list.
//                               accountno (int)         : The account number of the record
//                               address (char *)        : The address of the owner of this reccord
//
//  Return Value:                -1: Record not found and failed to modify record
//                                1: Successfully modified the record
//
**********************************************************************************************************************/

int modifyRecord(struct record * record, int accountno, char address[])
{
    struct record * index;
    int result;
    int records_modified;

    result = -1;
    records_modified = 0;
    index = record;

    if (debugmode == 1)
    {
        printf("\n============================= Debug Mode ================================\n");
        printf("\nEnter modify Record mode\n");
        printf("Starting Record Address: %p\n", (void*)record);
        printf("Modify Address of all accounts whit: %d\n", accountno);
        printf("New Address: %s\n", address);
    }
    if (record != NULL && accountno > 0)
    {
        while (index != NULL)
        {
            if (accountno == index -> accountno)
            {
                if (debugmode == 1)
                {
                    printf("\nModifying the follwing record:\n");
                    printf("Record Address: %p\n", (void*) index);
                    printf("Accountno: %d\n", index -> accountno);
                    printf("Name: %s\n", index -> name);
                    printf("Old Address: %s\n", index -> address);
                    printf("Next: %p\n\n", (void*)index -> next);
                }
                if (debugmode != 1)
                {
                    printf("\nModifying the follwing record:\n");
                    printf("Accountno: %d\n", index -> accountno);
                    printf("Name: %s\n", index -> name);
                    printf("Address: %s\n", index -> address);
                }
                strcpy(index -> address, address);
                printf("\n\tNew Address: \n%s\n", index -> address);
                records_modified++;
            }
            index = index -> next;
        }
    }
    if (record == NULL)
    {
        printf("Warning the list is empty!\n");
        result = 0;
    }
    if (records_modified <= 0)
    {
        printf("No such File Detected!\n");
        result = 0;
    }
    if (records_modified >= 1)
    {
        result = 1;
    }
    if (debugmode == 1)
    {
        printf("\n===================== Exit Modify =======================\n");
    }
    return result;
}

/**********************************************************************************************************************
//
//  Function Name:              deleteRecord
//
//  DESCRIPTION:                This will delete an exisiting record from the list by removing the inputed account number
//
//  PARAMETERS:                 record (struct record *) : The record that contains the name, address, account number and
//                                                         name.
//                              accountno (int)          : The account number of the record to be removed.
//
//  Return Value:               -1: That account was not removed
//                               1: Successfully removed
//
************************************************************************************************************************/

int deleteRecord(struct record ** record, int accountno)
{
    struct record * index;
    struct record * remove;
    struct record * next_to_index;
    int result;
    int records_removed;

    result = -1;
    records_removed = 0;
    index = *record;

    if (debugmode == 1)
    {
        printf("\n=============================== Debug Mode ==================================\n");
        printf("\tEnter delete Record Mode\n");
        printf("\nStarting Address Record: %p\n", (void*)index);
        printf("Remove all accounts with Accountno: %d\n\n", accountno);
    }

    if (accountno > 0 && index != NULL)
    {
        do
        {
            if (accountno == index -> accountno)
            {
                if (debugmode == 1)
                {
                    printf("Account Found!\nRemoving the first record of the list.\n");
                    printf("Before current start: %p\n", (void*)index);
                    printf("Next: %p\n", (void*)index -> next);
                }
                remove = index;
                index = remove -> next;
                *record = index;
                if (debugmode == 1)
                {
                    printf("To Remove: %p\n", (void*)remove);
                    printf("New Starting Record: %p\n\n", (void*)*record);
                }
                free(remove);
                remove = NULL;
                records_removed++;
            }

            if (index != NULL)
            {
                if (accountno != index -> accountno)
                {
                    next_to_index = index -> next;
                    if (debugmode == 1)
                    {
                        printf("Current: %p\n", (void*)index);
                        printf("Current Next: %p\n", (void*)next_to_index);
                    }

                    if (next_to_index != NULL)
                    {
                         if (accountno == next_to_index -> accountno)
                         {
                             remove = next_to_index;
                             next_to_index = remove -> next;
                             index -> next = remove -> next;
                             if (debugmode == 1)
                             {
                                 printf("Account found!\n");
                                 printf("Remove: %p\n", (void*)remove);
                                 printf("New Next: %p\n\n", (void*)next_to_index);
                             }
                             free(remove);
                             remove = NULL;
                             records_removed++;
                         }
                    }
                    if (next_to_index != NULL)
                    {
                        if (accountno != next_to_index -> accountno)
                        {
                            index = index -> next;
                            if (debugmode == 1)
                            {
                                printf("New Current: %p\n\n", (void*)index);
                            }
                        }
                    }
                    if (next_to_index == NULL)
                    {
                        index = NULL;
                    }
                }
            }
            remove = NULL;
        }
        while (index != NULL);
    }

    printf("Records Removed: %d\n", records_removed);
    if (records_removed >= 1)
    {
        result = 0;
    }
    if (result == -1)
    {
        printf("No such Record Found!\n");
    }
    if (debugmode == 1)
    {
        printf("\n================= Exit Delete ======================\n\n");
    }
    return result;
}
