// Jenner Higgins
// CS 240
// 03-19-2019
// Assignment #3
// history.c

#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add_history(int counter, char * input)
{
    h_p = (struct HistoryNodeType*)malloc(sizeof(struct HistoryNodeType));
    h_p -> h_num = counter;
    h_p -> h_input = malloc(strlen(input) + 1);
    strcpy(h_p -> h_input, input);
    h_p -> h_next = NULL;
    h_p -> h_prev = NULL;
    
    if(h_head == NULL)
    {
        h_head = h_p;
        h_tail = h_p;
        h_trailp = h_p;
        h_p = NULL;
    }
    else if(h_trailp -> h_next == NULL)
    {
        h_tail -> h_next = h_p;
        h_tail = h_p;
        h_tail -> h_prev = h_trailp;
        h_p = NULL;
    }
    else
    {
        h_trailp = h_tail;
        h_tail -> h_next = h_p;
        h_tail = h_p;
        h_tail -> h_prev = h_trailp;
    }
}

void show_history(void)
{
    h_p = h_tail;
 
    for(int i = 0; i < 20; i++)
    {
        if(h_p -> h_prev != NULL)
            h_p = h_p -> h_prev;
        else
            break;
    }
    
    for(int i = 0; i < 20; i++)
    {
        if(h_p != NULL)
        {
            printf("%d " " %s \n", h_p -> h_num, h_p -> h_input);
            h_p = h_p -> h_next;
        }
        else
            break;
    }
}

char * exec_last(void)
{
    struct HistoryNodeType * temp = h_tail;
    
    h_p = h_tail;
    
    if(h_p -> h_prev == NULL)
    {
        printf("No command to execute");
        return 0;
    }
    else
    {
        h_p = h_p -> h_prev;
        h_tail = h_p;
        if(h_trailp -> h_prev != NULL)
            h_trailp = h_trailp -> h_prev;
        free(temp);
        temp = NULL;
        h_p -> h_next = NULL;
        return h_p -> h_input;
    }
}

char * exec_past_command(int histnum)
{
    struct HistoryNodeType * temp = h_tail;
    
    h_p = h_tail;

    while(h_p != NULL)
    {
        if(h_p -> h_num == histnum)
        {
            a_tail = a_trailp;
            if(h_trailp -> h_prev != NULL)
                h_trailp = h_trailp -> h_prev;
            free(temp);
            temp = NULL;
            h_tail -> h_next = NULL;
            return h_p -> h_input;
        }
        else if(h_p != NULL)
            h_p = h_p -> h_prev;
    }
    printf("!%d: event not found\n", histnum);
    return 0;
}

