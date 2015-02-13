#include <stdio.h>
#include "sorted-list.h"

/* This function runs in O(n) time. */

/*
This function creates a Sorted List with a compare function and destructer function. Returns SortedListPtr object if successful, NULL if not.
*/
SortedListPtr SLCreate(CompareFuncT cf, DestructFuncT df) {

	SortedListPtr sortedList;
	sortedList = (SortedListPtr)malloc(sizeof(SortedListNode));
	/* Returns NULL if malloc fails */
	if(sortedList == NULL) return NULL;
	sortedList -> headList = NULL;
	sortedList -> compare = cf;	/* Store the comparae function pointer */
	sortedList -> destruct = df;	/* Store the destruct function pointer */
	return sortedList;
}
/*
Thsi function destroys the Data in the list and then destroy the list itself.
 */
void SLDestroy(SortedListPtr list) {
	
	Data *temp, *curr;
	curr = list -> headList;
	/* Traverse the list to free each elements */
	while(curr != NULL) {
		temp = curr -> nextData;
		list -> destruct(curr -> data);
		free(curr);
		curr = temp;	
	}
	list -> headList = NULL;
	free(list);	/* Free the list */
}
 
/* To print out the list if needed. Must change the cast if different data type is used */
void printList(SortedListPtr list) {

	Data *curr;
	curr = list -> headList;
	if(list -> headList == NULL) {printf("No data in list.\n"); return;}
	while(curr != NULL) {
		printf(" %d -> ", *((int*)curr -> data));
		curr = curr -> nextData;			
	}
	printf("\n");
}
/*
This Function initialize the members in the newly created node.
*/
Data *initializeNode(void* newObj, Data* newNode) {

	newNode -> data = newObj;		/* Store the opaque data */
	newNode -> refCount = 1;		/* Set reference count to 1 */
	newNode -> remove = 0;			/* Set remove to false */
	newNode -> nextData = NULL;
	return newNode;
}
/*
This Function inserts a given opaque data and inserts in the list while maintaining sorted order. Returns 1 if successful, 0 if not.
*/
int SLInsert(SortedListPtr list, void *newObj) {
	
	Data *curr, *prev, *newNode;
	curr = list -> headList;

	/* If the list has nothing in it then just insert it, no comparisons needed. */
	if(list -> headList == NULL) {
		newNode = (Data*)malloc(sizeof(Data));
		if(newNode == NULL) return 0;
		newNode = initializeNode(newObj, newNode);
		list -> headList = newNode;
		return 1;
	}	
	/* If the data to be inserted is bigger than than the data in the beginning of list then insert it in the beginning of list. */
	if(list -> compare(newObj, curr -> data) > 0) {
		newNode = (Data*)malloc(sizeof(Data));
		if(newNode == NULL) return 0;
		newNode = initializeNode(newObj, newNode);
		newNode -> nextData = list -> headList;
		list -> headList = newNode;
		return 1;
	}
	prev = curr;
	curr = curr -> nextData;
	/* Inserts data anywhere between front of the list to the end of the list. */
	while(curr != NULL) {
		if(list -> compare(newObj, curr -> data) > 0 || list -> compare(newObj, curr -> data) == 0) {
			newNode = (Data*)malloc(sizeof(Data));
			if(newNode == NULL) return 0;
			newNode = initializeNode(newObj, newNode);
			newNode -> nextData = curr;
			prev -> nextData = newNode;
			return 1;
		}
		prev = curr;	
		curr = curr -> nextData;
	}
	/* Inserts data to the back of the list. */
	newNode = (Data*)malloc(sizeof(Data));
	newNode = initializeNode(newObj, newNode);
	prev -> nextData = newNode;
	return 1;
}
/*
Removes a selected data from the list. If refCount is 0 then destroy the data and free node. Returns 1 if the removal is successful and 0 if not.
*/
int SLRemove(SortedListPtr list, void *newObj) {

	Data *curr, *prev;
	curr = list -> headList;

	/* Nothing in list so cannot remove a data. Returns 0. */
	if(curr == NULL) return 0;
	/* Remove if data is at the front of the sorted list */
	if(list -> compare(newObj, curr -> data) == 0) {
		curr -> refCount--;
		curr -> remove = 1;
		/* Free node if refCount = 0 */
		if(curr -> refCount == 0) {
			list -> destruct(curr -> data); 
			list -> headList = curr -> nextData; 
			free(curr);
		}
		return 1;
	}
	prev = curr;
	curr = curr -> nextData;
	/* Remove if the data is in between the front of the list and the end of the list */
	while(curr -> nextData != NULL) {
		if(list -> compare(newObj, curr -> data) == 0) {
			curr -> refCount--;
			curr -> remove = 1;
			prev -> nextData = curr -> nextData;
			prev -> nextData -> refCount++;
			/* Free node if refCount = 0 */
			if(curr -> refCount == 0) {
				list -> destruct(curr -> data); 
				curr -> nextData -> refCount--; 
				free(curr);
			}
			return 1;
		}
		prev = curr;
		curr = curr -> nextData;
	}
	/* Remove if the data occurs at the end of the list */
	if(list -> compare(newObj, curr -> data) == 0) {
		curr -> refCount--;
		curr -> remove = 1;
		prev -> nextData = curr -> nextData;
		if(curr -> refCount == 0) {list -> destruct(curr -> data); free(curr);}
		return 1;
	}
	return 0;	/* Returns 0 if the data cannot be deleted */
}

/*
This function creates an Iterator object. Returns SortedListPtr object if successful, NULL if not.
*/
SortedListIteratorPtr SLCreateIterator(SortedListPtr list) {
	
	if(list == NULL) return NULL;	/* If sorted list is NULL, then don't create iterator and return NULL. */
	SortedListIteratorPtr iterator = (SortedListIteratorPtr)malloc(sizeof(SortedListIterate));
	if(iterator == NULL) return NULL;	/* Returns NULL if malloc fails. */
	iterator -> headData = list -> headList;
	/* Increment the iterator reference count of the first data in the iterator */
	if(iterator -> headData != NULL) iterator -> headData -> refCount++;
	iterator -> list = list;
	return iterator; 
}

/*
This function destroys the iterator. While destroying data with that has a reference count of 0.
 */
void SLDestroyIterator(SortedListIteratorPtr iter) {
	
	Data *curr, *temp;
	curr = iter -> headData;
	/* Traverse thought the nodes to find any removed nodes and then free it */
	while(curr != NULL && curr -> remove == 1) {			
		temp = curr -> nextData;
		curr -> refCount--;
		if(curr -> refCount == 0) {		
			iter -> list -> destruct(curr -> data);
			curr -> nextData -> refCount--;
			free(curr);	/* Free Node */
		}
		curr = temp;
	}
	free(iter); /* Free iterator */
}
/*
Finds the next data in the list hasn't been removed. Free the data and node if the data has been removed.
 */
Data *findNextItem(Data *current, SortedListPtr list) {
	
	Data *temp;

	/* Find the next closest data that has not been removed */
	while(current != NULL && current -> remove == 1) {
		temp = current -> nextData;
		current -> refCount--;
		if(temp != NULL)
			temp -> refCount++;
		/* Free the data and node if the reference count is 0 */
		if(current -> refCount == 0 && current -> remove == 1) {
			list -> destruct(current -> data);
			free(current);
		}
		current = temp;	
	}
	return current;	/* Return the unremoved node containing the data */
}
/*
This function returns the next opaque data in the list. Returns NULL if there are no more elements to return. 
*/
void *SLNextItem(SortedListIteratorPtr iter){
	
	Data *curr; void *data;

	curr = iter -> headData;
	if(curr == NULL) return NULL; 			/* Returns NULL if no more element exists */
	if(curr -> remove == 0) data = curr -> data;	/* Store data to return if remove count is 0 */
	else {
		curr = findNextItem(curr, iter -> list);
		if(curr == NULL) return NULL;
		data = curr -> data;
	}
	iter -> headData = curr -> nextData;		/* Set iterator to the next data in the list */
	/* Increment the next data's reference count */
	if(iter -> headData != NULL) iter -> headData -> refCount++;	
	return data;
}
