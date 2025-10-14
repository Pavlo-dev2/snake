#ifndef LINKEDLISTLIB_H
#define LINKEDLISTLIB_H

typedef struct listelement
{
	long length;//length of the array
	void *el;//pointer on the array
	char type;//type of the array, i - int, f - float, c - char
	struct listelement *next;
} listelement;

listelement* append(void *value, long length, char type, listelement *pn, long pos);//add element(array) to possion pos, -1 for add to the end, NULL if list is new
listelement* pop(listelement *pn, long pos);//delate element on possion pos, -1 for delate the last element, NULL if list is new
int printlist(listelement* pn, char btw[], char after[]);//prints all of arrays in the list with string btw bitwin elements and after bitwin arrays
int copyarr(void *to, void *from, char type, long length);//copy arrays
long len(listelement *pn);//returns  length of the list
int rmlist(listelement *pn);//free all of memory the list is using
listelement* retel(listelement *st, long pos);//returns element on possion pos
int printel(listelement* pn, char btw[]);//prints all of arrays in the single elemnt with string btw bitwin elements and after bitwin arrays

#endif
