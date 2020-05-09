// Jenner Higgins
// CS 240
// 03-19-2019
// Assignment #3
// linkedlist.h


#ifndef history_h
#define history_h

#include <stdio.h>
#include <string.h>

struct HistoryNodeType
{
    int h_num;
    char * h_input;
    struct HistoryNodeType * h_prev;
    struct HistoryNodeType * h_next;
};

struct HistoryNodeType * h_head;
struct HistoryNodeType * h_tail;
struct HistoryNodeType * h_p;         // Current pointer
struct HistoryNodeType * h_trailp;    // Trail pointer

void add_history(int, char *);
void show_history(void);
char * exec_last(void);
char * exec_past_command(int);

struct AliasNodeType
{
    char * a_newcall;
    char * a_input;
    struct AliasNodeType * a_prev;
    struct AliasNodeType * a_next;
};

struct AliasNodeType * a_head;
struct AliasNodeType * a_tail;
struct AliasNodeType * a_p;         // Current pointer
struct AliasNodeType * a_trailp;    // Trail pointer

void add_alias(char *, char *);
void print_list(void);
void _unalias(char *);
char * check_alias(char *);

#endif /* history_h */

