/*********************************************************************
//
//  NAME:            Marcos Buccat Jr.
//
//  HOMEWORK:        3b
//
//  CLASS:           ICS 212
//
//  INSTRUCTOR:      Ravi Narayan
//
//  DATE:            February 12, 2020
//
//  FILE:            record.h
//
//  DESCRIPTION:
//    This file contains the record file that contains the address
//    accoutn number, name and user address.
//
//
*********************************************************************/

struct record
{
    int                 accountno;
    char                name[25];
    char                address[80];
    struct record*      next;
};
