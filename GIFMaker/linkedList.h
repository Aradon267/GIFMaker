#pragma once
#ifndef LINKEDLISTH
#define LINKEDLISTH

#define FALSE 0
#define TRUE !FALSE

// Frame struct
typedef struct Frame
{
	char*		name;
	unsigned int	duration;
	char*		path;
} Frame;
// Link (node) struct
typedef struct FrameNode
{
	Frame* frame;
	struct FrameNode* next;
} FrameNode;

void loadList(FrameNode ** head);
void freeList(FrameNode** head);
int removePerson(FrameNode** head, char* name);
void printList(FrameNode* movie);
Frame* createFrame(unsigned int dur, char* name, char* path);
void insertAtEnd(FrameNode** head, FrameNode *newNode);
FrameNode* enterFrame(FrameNode* list);
void changeAll(FrameNode** head, int newDur);
int changeDur(FrameNode** head, int newDur, char* name);
int count(FrameNode *list);
int search(FrameNode* head, char* name);
void swap(FrameNode** head, int pos1, int pos2, FrameNode* list);
void save(FrameNode* head);
void frame_from_file(FrameNode ** head, char path[], char name[], int duration);
void loadList(FrameNode ** head);
#endif