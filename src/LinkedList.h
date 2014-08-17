#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

typedef struct Element_t
{
	struct Element_t *next;
	void *data;
}Element;

typedef struct
{
	Element *head;
	Element *tail;
	int length;
}LinkedList;

LinkedList  *createLinkedList();
void List_Add(Element *newElement , LinkedList *list);
Element *List_removeLast(LinkedList *list);
Element List_addFirst(Element *newElement,LinkedList *list);
Element *List_removeFirst(LinkedList *list);
void List_DestroyList(LinkedList *list);
#endif //__LINKED_LIST_H__