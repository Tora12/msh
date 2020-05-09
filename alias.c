// Jenner Higgins
// CS 240
// 03-19-2019
// Assignment #3
// alias.c

#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add_alias(char * newinput, char * input)
{
    a_p = (struct AliasNodeType*)malloc(sizeof(struct AliasNodeType));
    a_p -> a_input = malloc(strlen(input) + 1);
    strcpy(a_p -> a_input, input);
    a_p -> a_newcall = malloc(strlen(newinput) + 1);
    strcpy(a_p -> a_newcall, newinput);
    a_p -> a_next = NULL;
    a_p -> a_prev = NULL;
    
    if(a_head == NULL)
    {
        a_head = a_p;
        a_tail = a_p;
        a_trailp = a_p;
        a_p = NULL;
    }
    else if(a_trailp -> a_next == NULL)
    {
        a_tail -> a_next = a_p;
        a_tail = a_p;
        a_tail -> a_prev = a_trailp;
        a_p = NULL;
    }
    else
    {
        a_trailp = a_tail;
        a_tail -> a_next = a_p;
        a_tail = a_p;
        a_tail -> a_prev = a_trailp;
    }
}
void print_list(void)
{
    a_p = a_head;
    
    while(a_p != NULL)
    {
        printf("alias %s='%s'\n", a_p -> a_newcall, a_p -> a_input);
        a_p = a_p -> a_next;
    } 
}

void _unalias(char * ninput)
{
    a_p = a_tail;
    
    if(a_head == NULL)
        printf("Unalias %s: not found\n", ninput);
    
    while(a_p != NULL)
    {
        if(strcmp(a_p -> a_newcall, ninput) == 0)
        {
            if(a_p -> a_prev == NULL && a_p -> a_next == NULL)
            {
                a_head = NULL;
                a_tail = NULL;
                a_trailp = NULL;
                free(a_p);
                a_p = NULL;
                break;
            }
            else if(a_p -> a_next == NULL)
            {
                a_tail = a_tail -> a_prev;
                a_trailp = a_trailp -> a_prev;
                free(a_p);
                a_p = NULL;
                break;
            }
            else if(a_p -> a_prev != NULL && a_p -> a_next != NULL)
            {
                a_trailp = a_p;
                a_trailp = a_trailp -> a_prev;
                a_trailp -> a_next = a_tail;
                free(a_p);
                a_p = NULL;
                break;
            }
            else if(a_p -> a_prev == NULL)
            {
                a_head = a_head -> a_next;
                free(a_p);
                a_p = NULL;
                break;
            }
        }
        if(a_p ->a_prev == NULL && strcmp(a_p -> a_newcall, ninput) != 0)
            printf("Unalias %s: not found\n", ninput);
        a_p = a_p -> a_prev;
    }
}

char * check_alias(char * name)
{
    a_p = a_head;
    
    while(a_p != NULL && (strcmp(a_p -> a_newcall, name) != 0))
        a_p = a_p ->a_next;
    if(a_p == NULL)
        return name;
    else
        return a_p -> a_input;
}


