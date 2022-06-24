#define CV_IGNORE_DEBUG_BUILD_GUARD
#pragma warning(disable : 4996)
#include <stdio.h>
#include "function_roots.h"
#include <stdlib.h>
#include "view.h"
#include "linkedList.h"
#include <string.h>
#define MAX_NAME 20
int main(void)
{ 
	FrameNode * movie = NULL;
	char name[MAX_NAME] = { 0 };
	int removed = 0;
	int opt = -1;
	int newDur = 0;
	int pos1 = 0;
	int pos2 = 0;
	int changed = 0;
	int firstOpt = 0;
	firstOpt = welcomeMenu();
	if (firstOpt == 1)
	{
		loadList(&movie);
	}
	while (opt != 0) 
	{
		opt = optMenu();
		switch (opt)
		{
			case 0:
				printf("Goodbye");
				break;
			case 1:
				insertAtEnd(&movie, NULL);
				break;
			case 2:
				printf("Enter name of frame to remove:\n");
				newFgets(name, MAX_NAME);
				printf("%s ", name);
				removed = removePerson(&movie, name);
				if (removed == 1)
				{
					printf("removed from movie\n");
				}
				else
				{
					printf("not in movie\n");
				}
				break;
			case 3:
				printf("Enter name of frame swap remove:\n");
				newFgets(name, MAX_NAME);
				printf("Enter new location: ");
				scanf("%d", &pos2);
				getchar();
				pos1 = search(movie, name);
				if (pos1 != -1)
				{
					swap(&movie, pos1, pos2 - 1, movie);
				}
				else
				{
					printf("Name wasnt found");
				}
				break;
			case 4:
				do
				{
					printf("Enter name of frame to change:\n");
					newFgets(name, MAX_NAME);
				} while (search(movie, name) == -1);
				printf("Enter new duration: ");
				scanf("%d", &newDur);
				changed = changeDur(&movie, newDur, name);
				if (changed == 1)
				{
					printf("Changed\n");
				}
				else
				{
					printf("Name wasnt found\n");
				}
				break;
			case 5:
				printf("Enter new duration: ");
				scanf("%d", &newDur);
				changeAll(&movie, newDur);
				break;
			case 6:
				printList(movie);
				break;
			case 7:
				play(movie);
				break;
			case 8:
				save(movie);
				break;
		}
	}
	freeList(&movie);
	getchar();
	return 0;
}