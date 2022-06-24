#pragma warning(disable : 4996)
#include <stdio.h>
#include "linkedList.h"
#include <string.h>
#include <stdlib.h>
#include "function_roots.h"
#include <opencv2\core\core_c.h>
#include <opencv2\highgui\highgui_c.h>
#define CV_IGNORE_DEBUG_BUILD_GUARD

#define _CRT_SECURE_NO_WARNINGS
#define FRAME_DETAIL_SEPERATOR 126
#define FRAME_SEPERATOR 38
#define MAX_NAME 20
#define MAX_PATH 150

/*
the func will print the welcome menu with new prog or load options
input: none
output: user's choice*/
int welcomeMenu()
{
	int opt = 0;
	do
	{
		printf("Enter 0 to start a new video and 1 to load a video: ");
		scanf("%d", &opt);
		getchar();
	} while (opt != 1 && opt != 0);
	return opt;
}

/*
the func will print menu and get user's choice
input: none
output: user's choice*/
int optMenu()
{
	int opt = -1;
	do
	{
		printf("What would you like to do?\n");
		printf("[0] Exit\n");
		printf("[1] Add new Frame\n");
		printf("[2] Remove a Frame\n");
		printf("[3] Change frame index\n");
		printf("[4] Change frame duration\n");
		printf("[5] Change duration of all frames\n");
		printf("[6] List frames\n");
		printf("[7] Play movie!\n");
		printf("[8] Save project\n");
		scanf("%d", &opt);
		getchar();
	} while (opt>8||opt<0);
	return opt;
}

/*
the func will add a frame
input: the pointer to the movie
output: none*/
void insertAtEnd(FrameNode** head, FrameNode *newNode)
{
	FrameNode* curr = *head;
	FrameNode* temp = NULL;
	if (newNode == NULL)
	{
		temp = enterFrame(curr);
		newNode = temp;
	} 
	if (!*head) // empty list!
	{
		*head = newNode;
		(*head)->next = NULL;
	}
	else
	{
		while (curr->next) // while the next is NOT NULL (when next is NULL - that is the last node)
		{
			curr = curr->next;
		}

		curr->next = newNode;
		newNode->next = NULL;
	}
}

/*
the func will start the creation of the frame
input: the list to check the names
output: the frame*/
FrameNode* enterFrame(FrameNode* list)
{
	unsigned int dur = 0;
	char *name = 0;
	char *path = 0;
	int goodPhoto = FALSE;
	int goodName = -1;
	FrameNode* newFrame = (FrameNode*)malloc(sizeof(FrameNode));
	IplImage* image = NULL;
	name = (char*)malloc(sizeof(char)*MAX_NAME);
	path = (char*)malloc(sizeof(char)*MAX_PATH);
	//get duration
	printf("Enter duration: ");
	scanf("%u", &dur);
	getchar();
	do
	{
		//get name
		printf("Enter name: ");
		newFgets(name, MAX_NAME);
		goodName = search(list, name);//check if name was already used
	} while (goodName != -1);
	do
	{
		//get path of the frame
		printf("Enter path: ");
		newFgets(path, MAX_PATH);
		image = cvLoadImage(path, 1);//check if path is empty
		if (image)
		{
			goodPhoto = TRUE;
		}
	} while (goodPhoto == FALSE);
	newFrame->frame = createFrame(dur, name, path);
	newFrame->next = NULL;
	free(name);
	free(path);
	return newFrame;
}

/*
the func will finilaize the creation of the frame
input: the duration, the name and the path
output: the frame*/
Frame* createFrame(unsigned int dur, char* name, char* path)
{
	//entering every variable to its right location in the frame
	Frame* singleFrame = (Frame*)malloc(sizeof(Frame));
	singleFrame->name = (char*)malloc(sizeof(char)*strlen(name));
	singleFrame->path = (char*)malloc(sizeof(char)*strlen(path));
	singleFrame->duration = dur;
	strcpy(singleFrame->name, name);
	strcpy(singleFrame->path, path);
	return singleFrame;
}

/*
the func will do fgets and strcspn
input: pointer to string and maximum length
output: none*/
void newFgets(char str[], int n)
{
	fgets(str, n, stdin);//doing fgets
	str[strcspn(str, "\n")] = 0;//removing the \n
}

/*
the func will print the list of frames
input: the movie
output: none*/
void printList(FrameNode* movie)
{
	FrameNode* curr = movie;
	printf("The list of frames:\n");
	while (curr) // when curr == NULL, that is the end of the list, and loop will end (NULL is 0)
	{
		printf("Duration is %u name is %s and path is %s\n", curr->frame->duration, curr->frame->name, curr->frame->path);
		curr = curr->next;
	}
}

/*
the func will remove a frame
input: the movie and the name of the frame
output: if the person was removed*/
int removePerson(FrameNode** head, char* name)
{
	FrameNode* temp = NULL;
	FrameNode* curr = *head;
	int removed = 0;
	if (*head)//checking if the list is empty
	{
		if (*head && 0 == strcmp((*head)->frame->name, name))//if list is not empty and we want to remove the first one
		{
			temp = (*head)->next;
			free(*head);
			*head = temp;
			removed = 1;
		}
		else
		{
			while (!removed && curr->next && 0 != strcmp((curr->next)->frame->name, name))//if we didnt remove yet and its not the last element and we didnt find the frame
			{
				curr = curr->next;
			}
			//if we find the name
			if (curr->next && 0 == strcmp(curr->next->frame->name, name))
			{
				temp = curr->next;
				curr->next = temp->next;
				free(temp);
				removed = 1;
			}
		}
	}
	return removed;
}

/*
the func will change ALL of the durations
input: the movie and the new duration
output: none*/
void changeAll(FrameNode** head, int newDur)
{
	FrameNode* curr = *head;
	while (curr)//checking the list is not empty
	{
		curr->frame->duration = newDur;
		curr = curr->next;
	}
}

/*
the func will change duration for on movie
input: the movie, the new duration and the name of the frame
outout: none*/
int changeDur(FrameNode** head, int newDur, char* name)
{
	FrameNode* curr = *head;
	int changed = 0;
	if (*head)//checking that list is not empty
	{
		if (*head && 0 == strcmp((*head)->frame->name, name))//if list is not empty and we want to change the first one
		{
			curr->frame->duration = newDur;
			changed = 1;
		}
		else
		{
			while (!changed && curr->next && 0 != strcmp((curr->next)->frame->name, name))//if we didnt change yet and its not the last element and we didnt find the frame
			{
				curr = curr->next;
			}
			//if we find the name
			if (curr->next && 0 == strcmp(curr->next->frame->name, name))
			{
				curr->frame->duration = newDur;
				changed = 1;
			}
		}
	}
	return changed;
}

/*
the func will count the amount of frames
input: the list of frames
output: the amount of frames*/
int count(FrameNode *list)
{
	int nodes = 0;

	while (list != NULL)//checking list is not NULL
	{
		nodes++;
		list = list->next;
	}

	return nodes;
}

/*
the func will search a name in the frames
input: the movie and the name we search
output: if the name was founf*/
int search(FrameNode* head, char* name)
{
	int index = 0;
	while (head != NULL)//checking list is not NULL
	{
		if (strcmp(head->frame->name, name) == 0)//if we found the name
		{
			return index;
		}
		index++;
		head = head->next;
	}
	return -1;
}

/*
the func will swap 2 frames
input: the movie, list of frames, 2 indexs
output: none*/
void swap(FrameNode** head, int pos1, int pos2, FrameNode* list)
{
	Frame* temp1 = NULL;
	Frame* temp2 = NULL;
	int tempPos1 = pos1;
	int tempPos2 = pos2;
	int len = count(list);
	FrameNode* tempList = list;
	FrameNode* curr = *head;
	if (pos1 == pos2)//if positions are the same
	{
		return;
	}
	if (pos1 > len || pos2 > len)//if any of the positions is bigger than the size of the movie
	{
		return;
	}
	//getting copy of the frame we swap at the first position
	while (pos1 > 0 && tempList->next!=NULL)
	{
		tempList = tempList->next;
		pos1--;
	}
	temp1 = tempList->frame;
	tempList = list;//reseting
	//getting copy of the frame we swap at the second position
	while (pos2 > 0 && tempList->next!=NULL)
	{
		tempList = tempList->next;
		pos2--;
	}
	temp2 = tempList->frame;
	if (tempPos2 > tempPos1)//if the 2nd pos is further away
	{
		while (tempPos1 >= 0)
		{
			if (tempPos1 == 0)//if we got the the right index we replace the frames
			{
				curr->frame = temp2;
			}
			curr = curr->next;
			tempPos1--;
			tempPos2--;
		}
		while (tempPos2 >= 0)//getting to right index on the second pos
		{
			if (tempPos2 == 0)
			{
				curr->frame = temp1;
			}
			curr = curr->next;
			tempPos2--;
		}
	}
	else
	{
		while (tempPos2 >= 0)
		{
			if (tempPos2 == 0)
			{
				curr->frame = temp1;
			}
			curr = curr->next;
			tempPos1--;
			tempPos2--;
		}
		while (tempPos1 >= 0)
		{
			if (tempPos1 == 0)
			{
				curr->frame = temp2;
			}
			curr = curr->next;
			tempPos1--;
		
		}
	}


}

/*
the func will free the list
input: the list
output: none*/
void freeList(FrameNode** head)
{
	if (*head != NULL) // if list not empty
	{
		if ((*head)->next != NULL) // end condition
		{
			freeList(&((*head)->next));
		}

		free(*head);
	}
}

/*
the func will save the video
input: the list of frames
output: none*/
void save(FrameNode* head)
{
	FrameNode* curr = head;
	FILE* frames = NULL;
	char* path = 0;
	path = (char*)malloc(sizeof(char)*MAX_PATH);
	printf("Enter a path to save: ");
	newFgets(path, MAX_PATH);
	frames = fopen(path, "w");
	if (frames != NULL)
	{
		while (curr != NULL)
		{
			//protocol description: name~path~duration~&name~path~duration~& 
			fprintf(frames, "%s", curr->frame->name);
			fprintf(frames, "%s", "~");
			fprintf(frames, "%s", curr->frame->path);
			fprintf(frames, "%s", "~");
			fprintf(frames, "%d", curr->frame->duration);
			curr = curr->next;
			fprintf(frames, "%s", "~");
			fprintf(frames, "%s", "&");
		}
		printf("Saved\n");
		fclose(frames);
	}
	else
	{
		printf("There was a problem... Please try again\n");
	}
}

/*
the func will load the movie
input: the movie
output: none*/
void loadList(FrameNode ** head)
{
	FILE* source = NULL;
	char * src_path = 0;
	int ascii_code = 0;
	int counter = 0;
	char path[MAX_PATH] = { 0 };
	char name[MAX_NAME] = { 0 };
	char duration_char[MAX_NAME] = { 0 };
	int duration_int = 0;
	int name_counter = 0;
	int path_counter = 0;
	int duration_counter = 0;
	src_path = (char*)malloc(sizeof(char)*MAX_PATH);
	printf("Enter a path to load: ");
	newFgets(src_path, MAX_PATH);
	source = fopen(src_path, "r");
	if (source == NULL)
	{
		printf("Can't open the file\n");
		return;
	}
	while (ascii_code != EOF)
	{
		ascii_code = fgetc(source);//getting ascii code for each char in file
		if (ascii_code == FRAME_DETAIL_SEPERATOR)
		{
			counter++;
		}
		else if (ascii_code == FRAME_SEPERATOR)
		{
			duration_int = atoi(duration_char);//getting duration
			frame_from_file(head, path, name, duration_int);//creating file
			memset(name, 0, strlen(name));//reseting details
			memset(path, 0, strlen(path));
			memset(duration_char, 0, strlen(duration_char));
			path_counter = 0;
			name_counter = 0;
			duration_counter = 0;
			counter = 0;
		}
		else if (counter % 3 == 0)
		{
			name[name_counter] = (char)ascii_code;
			name_counter++;
		}
		else if (counter % 3 == 1)
		{
			path[path_counter] = (char)ascii_code;
			path_counter++;
		}
		else if (counter % 3 == 2)
		{
			duration_char[duration_counter] = (char)ascii_code;
			duration_counter++;
		}
	}
	fclose(source);
}

/*
the func will add a frame with details from file
input: the movie, and frame details
output: none*/
void frame_from_file(FrameNode ** head, char * path, char * name, int duration)
{
	FrameNode * frameList = (FrameNode*)malloc(sizeof(FrameNode));
	frameList->frame = createFrame(duration, name, path);
	insertAtEnd(head, frameList);
}

