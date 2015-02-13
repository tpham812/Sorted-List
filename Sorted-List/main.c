/*
 * sorted-list.c
 */

#include	<string.h>
#include	"sorted-list.c"

int compareInts(void *p1, void *p2)
{
	int i1 = *(int*)p1;
	int i2 = *(int*)p2;

	return i1 - i2;
}

int compareDoubles(void *p1, void *p2)
{
	double d1 = *(double*)p1;
	double d2 = *(double*)p2;

	return (d1 < d2) ? -1 : ((d1 > d2) ? 1 : 0);
}

int compareStrings(void *p1, void *p2)
{
	char *s1 = p1;
	char *s2 = p2;

	return strcmp(s1, s2);
}

//Destructor functions
void destroyBasicTypeAlloc(void *p){
	//For pointers to basic data types (int*,char*,double*,...)
	//Use for allocated memory (malloc,calloc,etc.)
	free(p);
}

void destroyBasicTypeNoAlloc(void *p) {
	//For pointers to basic data types (int*,char*,double*,...)
	//Use for memory that has not been allocated (e.g., "int x = 5;SLInsert(mylist,&x);SLRemove(mylist,&x);")
	return;
}

void intTest() {

	void* num;
	int a = 6., b = 3, c = 17, d = 10, e = 13, f = 1, g = 8;
	CompareFuncT compare = &compareInts;
	DestructFuncT destruct = &destroyBasicTypeNoAlloc;
	SortedListPtr sl; SortedListIteratorPtr iterator;
	sl = SLCreate(compare, destruct);
	SLInsert(sl, (void*)&a);
	SLInsert(sl, (void*)&b);
	SLInsert(sl, (void*)&c);
	SLInsert(sl, (void*)&d);
	SLInsert(sl, (void*)&e);
	SLInsert(sl, (void*)&f);
	SLInsert(sl, (void*)&g);
	SLInsert(sl, (void*)&e);
	printList(sl);
	iterator = SLCreateIterator(sl);
	SLRemove(sl, (void*)&c);
	printf("TOKENS: \n");
	while(num = SLNextItem(iterator), num != NULL) 
		printf("%d\n", *((int*)num));
}

void doubleTest() {

	void* num;
	double a = 6.0, b = 3.345, c = 17.65, d = 10.23, e = 13.6, f = 1.9, g = 8.78, h = 8.78;
	CompareFuncT compare = &compareDoubles;
	DestructFuncT destruct = &destroyBasicTypeNoAlloc;
	SortedListPtr sl; SortedListIteratorPtr iterator;
	sl = SLCreate(compare, destruct);
	SLInsert(sl, (void*)&a);
	SLInsert(sl, (void*)&b);
	SLInsert(sl, (void*)&c);
	SLInsert(sl, (void*)&d);
	SLInsert(sl, (void*)&e);
	SLInsert(sl, (void*)&f);
	SLInsert(sl, (void*)&g);
	SLInsert(sl, (void*)&e);
	SLInsert(sl, (void*)&h);
	printList(sl);
	iterator = SLCreateIterator(sl);
	SLRemove(sl, (void*)&d);
	printf("TOKENS: \n");
	while(num = SLNextItem(iterator), num != NULL) 
		printf("%f\n", *((double*)num));
}

void stringTest() {
	
	void* num;
	char *a = "apple", *b = "fox" , *c = "hound", *d = "asus", *e = "horses", *f = "who", *g = "cat", *h = "zebra";
	CompareFuncT compare = &compareStrings;
	DestructFuncT destruct = &destroyBasicTypeNoAlloc;
	SortedListPtr sl; SortedListIteratorPtr iterator;
	sl = SLCreate(compare, destruct);
	SLInsert(sl, (void*)a);
	SLInsert(sl, (void*)b);
	SLInsert(sl, (void*)c);
	SLInsert(sl, (void*)d);
	SLInsert(sl, (void*)e);
	SLInsert(sl, (void*)f);
	SLInsert(sl, (void*)g);
	SLInsert(sl, (void*)e);
	SLInsert(sl, (void*)h);
	printList(sl);
	iterator = SLCreateIterator(sl);
	SLRemove(sl, (void*)d);
	printf("TOKENS: \n");
	while(num = SLNextItem(iterator), num != NULL) 
		printf("%s\n", (char*)num);
}

void intTest2() {
	
	void* num;
	int a = 6., b = 3, c = 17, d = 10, e = 13, f = 1, g = 8;
	CompareFuncT compare = &compareInts;
	DestructFuncT destruct = &destroyBasicTypeNoAlloc;
	SortedListPtr sl; SortedListIteratorPtr iterator;
	sl = SLCreate(compare, destruct);
	SLInsert(sl, (void*)&a);
	SLInsert(sl, (void*)&b);
	SLInsert(sl, (void*)&c);
	SLInsert(sl, (void*)&d);
	SLInsert(sl, (void*)&e);
	SLInsert(sl, (void*)&f);
	SLInsert(sl, (void*)&g);
	SLInsert(sl, (void*)&e);
	printList(sl);
	iterator = SLCreateIterator(sl);
	SLRemove(sl, (void*)&g);
	printf("TOKENS: \n");
	while(num = SLNextItem(iterator), num != NULL) 
		printf("%d\n", *((int*)num));	
}

void intTest3() {
	
		void* num;
	int a = 6., b = 3, c = 17, d = 10, e = 13, f = 1, g = 8;
	CompareFuncT compare = &compareInts;
	DestructFuncT destruct = &destroyBasicTypeNoAlloc;
	SortedListPtr sl; SortedListIteratorPtr iterator;
	sl = SLCreate(compare, destruct);
	SLInsert(sl, (void*)&a);
	SLInsert(sl, (void*)&b);
	SLInsert(sl, (void*)&c);
	SLInsert(sl, (void*)&d);
	SLInsert(sl, (void*)&e);
	SLInsert(sl, (void*)&f);
	SLInsert(sl, (void*)&g);
	SLInsert(sl, (void*)&e);
	printList(sl);
	iterator = SLCreateIterator(sl);
	SLRemove(sl, (void*)&g);
	SLRemove(sl, (void*)&f);
	printf("TOKENS: \n");
	while(num = SLNextItem(iterator), num != NULL) 
		printf("%d\n", *((int*)num));	
}

void intTest4() {
	
	void* num; int count = 0;
	int a = 6., b = 3, c = 17, d = 10, e = 13, f = 1, g = 8;
	CompareFuncT compare = &compareInts;
	DestructFuncT destruct = &destroyBasicTypeNoAlloc;
	SortedListPtr sl; SortedListIteratorPtr iterator;
	sl = SLCreate(compare, destruct);
	SLInsert(sl, (void*)&a);
	SLInsert(sl, (void*)&b);
	SLInsert(sl, (void*)&c);
	SLInsert(sl, (void*)&d);
	SLInsert(sl, (void*)&e);
	SLInsert(sl, (void*)&f);
	SLInsert(sl, (void*)&g);
	SLInsert(sl, (void*)&e);
	printList(sl);
	iterator = SLCreateIterator(sl);
	SLRemove(sl, (void*)&g);
	SLRemove(sl, (void*)&f);
	printf("TOKENS: \n");
	while(num = SLNextItem(iterator), num != NULL && count != 4) {
		printf("%d\n", *((int*)num));	
		count++;
	}
	SLDestroyIterator(iterator);
}

void intTest5() {
	
	void* num; int count = 0;
	int a = 6, b = 3, c = 17, d = 10, e = 13, f = 1, g = 8;
	CompareFuncT compare = &compareInts;
	DestructFuncT destruct = &destroyBasicTypeNoAlloc;
	SortedListPtr sl; SortedListIteratorPtr iterator, iterator2;
	sl = SLCreate(compare, destruct);
	SLInsert(sl, (void*)&a);
	SLInsert(sl, (void*)&b);
	SLInsert(sl, (void*)&c);
	SLInsert(sl, (void*)&d);
	SLInsert(sl, (void*)&e);
	SLInsert(sl, (void*)&f);
	SLInsert(sl, (void*)&g);
	SLInsert(sl, (void*)&e);
	printList(sl);
	iterator2 = SLCreateIterator(sl);
	iterator = SLCreateIterator(sl);
	while(num = SLNextItem(iterator), num != NULL) {
		printf("Iterator 1: %d\n", *((int*)num));
		count++;
		if(count == 2) break;
	}
	count = 0;	
	while(num = SLNextItem(iterator2), num != NULL) {
		printf("Iterator 2: %d\n", *((int*)num));
		count++;
		if(count == 5) break;
	}
	SLRemove(sl, (void*)&a);
	SLRemove(sl, (void*)&b);
		while(num = SLNextItem(iterator), num != NULL) 
		printf("Iterator 1: %d\n", *((int*)num));

	while(num = SLNextItem(iterator2), num != NULL) 
		printf("Iterator 2: %d\n", *((int*)num));
}
void intTest6() {
	
	void* num; int count = 0;
	int a = 6, b = 3, c = 17, d = 10, e = 13, f = 1, g = 8;
	CompareFuncT compare = &compareInts;
	DestructFuncT destruct = &destroyBasicTypeNoAlloc;
	SortedListPtr sl; SortedListIteratorPtr iterator, iterator2;
	sl = SLCreate(compare, destruct);
	SLInsert(sl, (void*)&a);
	SLInsert(sl, (void*)&b);
	SLInsert(sl, (void*)&c);
	SLInsert(sl, (void*)&d);
	SLInsert(sl, (void*)&e);
	SLInsert(sl, (void*)&f);
	SLInsert(sl, (void*)&g);
	SLInsert(sl, (void*)&e);
	printList(sl);
	iterator2 = SLCreateIterator(sl);
	iterator = SLCreateIterator(sl);
	while(num = SLNextItem(iterator), num != NULL) {
		printf("Iterator 1: %d\n", *((int*)num));
		count++;
		if(count == 2) break;
	}
	count = 0;	
	while(num = SLNextItem(iterator2), num != NULL) {
		printf("Iterator 2: %d\n", *((int*)num));
		count++;
		if(count == 4) break;
	}
	SLRemove(sl, (void*)&a);
	SLRemove(sl, (void*)&b);
	SLRemove(sl, (void*)&g);
	SLRemove(sl, (void*)&d);
	while(num = SLNextItem(iterator), num != NULL) 
		printf("Iterator 1: %d\n", *((int*)num));
	while(num = SLNextItem(iterator2), num != NULL) 
		printf("Iterator 2: %d\n", *((int*)num));
}
void intTest7() {
 
	int a = 6., b = 3, c = 17, d = 10, e = 13, f = 1, g = 8;
	CompareFuncT compare = &compareInts;
	DestructFuncT destruct = &destroyBasicTypeNoAlloc;
	SortedListPtr sl;
	sl = SLCreate(compare, destruct);
	SLInsert(sl, (void*)&a);
	SLInsert(sl, (void*)&b);
	SLInsert(sl, (void*)&c);
	SLInsert(sl, (void*)&d);
	SLInsert(sl, (void*)&e);
	SLInsert(sl, (void*)&f);
	SLInsert(sl, (void*)&g);
	SLInsert(sl, (void*)&e);
	printList(sl);
	SLDestroy(sl);
	printList(sl);
}

void intTest8() {
	
	void* num; int count = 0;
	int a = 6., b = 3, c = 17, d = 10, e = 13, f = 1, g = 8, h = 7;
	CompareFuncT compare = &compareInts;
	DestructFuncT destruct = &destroyBasicTypeNoAlloc;
	SortedListPtr sl; SortedListIteratorPtr iterator;
	sl = SLCreate(compare, destruct);
	SLInsert(sl, (void*)&a);
	SLInsert(sl, (void*)&b);
	SLInsert(sl, (void*)&c);
	SLInsert(sl, (void*)&d);
	SLInsert(sl, (void*)&e);
	SLInsert(sl, (void*)&f);
	SLInsert(sl, (void*)&g);
	SLInsert(sl, (void*)&e);
	printList(sl);
	iterator = SLCreateIterator(sl);
	printf("TOKENS: \n");
	while(num = SLNextItem(iterator), num != NULL) {
		printf("%d\n", *((int*)num));	
		count++;
		if(count == 4) SLInsert(sl, (void*)&h);
	}	
}
int main()
{
	//intTest();
	//doubleTest();
	//stringTest();
	//intTest2();
	//intTest3();
	//intTest4();
	//intTest5();
	//intTest6();
	//intTest7();
	intTest8();
	return 0;
}
