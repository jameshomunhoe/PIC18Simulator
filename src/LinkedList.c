#include "LinkedLIst.h"
#include <stdio.h>
#include <malloc.h>

LinkedList  *createLinkedList()
{

	LinkedList *list = malloc(sizeof(LinkedList));
	list->head = NULL;
	list->tail = NULL;
	list->length = 0;
	return list;
}

void List_Add(Element *newElement , LinkedList *list)
{
	if(list->head == NULL)
	{
		list->head = list->tail = newElement;
	}
	else
	{
		//Get the latest element block by reference to the tail
		list->tail->next = newElement;
		list->tail = newElement;
	}
		list->length++;
		newElement->next = NULL;
		
}

Element *List_removeLast(LinkedList *list)
{
	Element *tempElement =list->tail;
	int i;
	if(list->head == NULL && list->tail == NULL)
	return NULL;
	else if(list->head==list->tail)
	{		
		list->head = NULL;
		list->tail = NULL;
	}
	else
	{
		list->tail = list->head;
		for(i=3;i<=list->length;i++)
		{
			list->tail=list->tail->next;
		}
	}
	list->length--;
	return tempElement;
}

Element List_addFirst(Element *newElement,LinkedList *list)
{
	if(list->head == NULL && list->tail == NULL)
	{
		list->head = list->tail = newElement;
		newElement -> next = NULL;
	}
	else
	{
		newElement->next=list->head;
		list->head=newElement;
	}
	list->length++;
}

Element *List_removeFirst(LinkedList *list)
{
	Element *tempElement;
	
	if(list->head == NULL && list->tail == NULL)
		return NULL;
	if(list->head==list->tail)
	{
		tempElement =list->head;
		list->head=list->tail = NULL;	
	}
	else
	{
		tempElement =list->head ;
		list->head=list->head->next;
	}
	list->length--;
	return tempElement;
}

void List_DestroyList(LinkedList *list)
{
	Element *tempElement;
	int i;
	while(list->head!=NULL)
	{	
		tempElement=List_removeLast(list);
		free(tempElement);
	}
}










