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
//  FILE:           database.h
//
//  DESCRIPTION:
//    This file contains all of the database function prototypes.
//    It contains the prototype for addRecord, printRecord,
//    printAllRecord, ModifyRecord, deleteRecord, cleanup,
//    readfile and writefile
//
*****************************************************************************************************************/

#include "record.h"

int addRecord(struct record **, int, char[], char[]);
int printRecord(struct record *, int);
void printAllRecords(struct record *);
int modifyRecord(struct record *, int, char[]);
int deleteRecord(struct record **, int);
int readfile(struct record **, char[]);
int writefile(struct record *, char[]);
void cleanup(struct record **);
