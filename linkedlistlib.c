#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

int printlist(listelement* pn, char btw[], char after[])
{
	//printf("In printl\n");
	//printf(": %lu\n", pn->length);
	while (pn != NULL)
	{
		long i, len;
		i = 0;
		len = pn->length;
		//printf("In loop %lu;\n", pn->length);
		switch (pn->type)
		{
			case 'f':
				while (i < len)
				{
					printf("%f%s", ((float*)pn->el)[i], btw);
					i++;
				}
				break;
			case 'c':
				while (i < len)
				{
					printf("%c%s", ((char*)pn->el)[i], btw);
					i++;
				}
				break;
			case 'i':
				while (i < len)
				{
					printf("%i%s", ((int*)pn->el)[i], btw);
					i++;
				}
				break;
		}
		printf("%s", after);
		pn = pn->next;
	}
	return 0;
}

listelement* append(void *value, long length, char type, listelement *pn, long pos)
{
	listelement *st = pn;//start of the list
	listelement *bf = NULL;//element before the new element
	listelement *af = NULL;//element that was after bf, and will be after the new element
	
	//create the new element
	listelement *new = malloc(sizeof(listelement));
	if (new == NULL)
		return 0;
	new->type = type;
	new->length = length;
	//printf("In append, length: %lu, new->length: %lu\n", length, new->length);
	void *pvalue;
	switch (type)
	{
			case 'f':
				pvalue = malloc(sizeof(float)*length);
				if (pvalue == NULL)
				{
					free(new);
					return NULL;
				}
				break;
			case 'c':
				pvalue = malloc(sizeof(char)*length);
				if (pvalue == NULL)
				{
					free(new);
					return NULL;
				}
				break;
			case 'i':
				pvalue = malloc(sizeof(int)*length);
				if (pvalue == NULL)
				{
					free(new);
					return NULL;
				}
				break;
	}
	copyarr(pvalue, value, type, length);
	new->el = pvalue;
	new->next = NULL;

	//if you need to create a new list
	if (pn == NULL)
	{
		if (pos != 0 && pos != -1)
		{
			return NULL;
		}
		return new;
	}
	
	//if you heve to put the new element on the begining(0 position)
	if (pos == 0)
	{
		af = pn;
		st = new;
		st->next = af;
		return st;
	}
	//if you need to put the element on position 1
	else if (pos == 1)
	{
		bf = pn;
		if (bf->next == NULL)
		{
			bf->next = new;
		}
		else
		{
			af = bf->next;
			bf->next = new;
			bf->next->next = af;
		}
		return st;
	}
	//else if you need to put element on the last position
	else if (pos == -1)
	{
		listelement *ae;//actual element
		for (ae = pn; ae->next != NULL; ae = ae->next);
		ae->next = new;
		return st;
	}
	//else if you need to put element after position 1
	else if (pos > 1)
	{
		if (pos > len(pn)) return NULL;
		//find bf
		long ap = 0;//actual position
		listelement *ae = pn;//actual element
		while (ap+1 != pos)
		{
			ae = ae->next;
			ap++;
			if (ae == NULL)
			{
				return NULL;
			}	
		}
		bf = ae;
		af = ae->next;
		bf->next = new;
		bf->next->next = af;
		return pn;	
	}
	else
	{
		return NULL;
	}
}

listelement* pop(listelement* pn, long pos)
{
	if (pn == NULL) return NULL;
	if (pos > len(pn)-1) return NULL;

	listelement *st = pn;//start of the list
	listelement *bf;//element before the element to delate
	listelement *td;//element to delate
	listelement *af;//element after the element to delate
	long apos = 0;//actual possion
	
	//if you hove to delate first element
	if (pos == 0 || pos == -1 && st->next == NULL)
	{
		free(st->el);
		if (st->next != NULL)
		{
			af = st->next;
			free(st);
			return af;
		}
		free(st);
		return NULL;
	}
	else if (pos > 0 || pos == -1)
	{
		//printf("In condition\n");
		//find bf
		for (listelement *ae = st; (apos < pos || pos == -1) && ae->next != NULL; apos++)
		{
			bf = ae;
			ae = ae->next;
		}
		if (bf->next->next != NULL)
		{
			af = bf->next->next;
		}
		else
		{
			af = NULL;
		}
		//printf("bf->next == NULL: %d\n", bf->next == NULL);
		free(bf->next->el);
		free(bf->next);
		bf->next = af;
		return st;
	}
	return NULL;
}

int copyarr(void *to, void *from, char type, long length)
{
	while (length > 0)
	{
		switch (type)
		{
			case 'f':
				((float*)to)[length-1] = ((float*)from)[length-1];
				break;
			case 'c':
				((char*)to)[length-1] = ((char*)from)[length-1];
				break;
			case 'i':
				((int*)to)[length-1] = ((int*)from)[length-1];
				break;
		}
		length--;
	}
	return 0;
}

long len(listelement *pn)
{
	long length = 0;
	while (pn != NULL)
	{
		length++;
		pn = pn->next;
	}
	return length;
}

int rmlist(listelement *pn)
{
	listelement *next;
	while(pn != NULL)
	{
		next = pn->next;
		free(pn->el);
		free(pn);
		pn = next;
	}
	return 0;
}

listelement* retel(listelement *st, long pos)
{
	if (st == NULL) return NULL;
	if (pos > (len(st) - 1) || pos < 0) return NULL;
	listelement* act = st;//actual element
	long ap = 0;//actual possion
	while (ap < pos)
	{
		ap++;
		act = act->next;
	}
	return act;
}

int printel(listelement* pn, char btw[])
{
	if (pn == NULL) return 1;
	long i = 0;
	long len = pn->length;
	switch (pn->type)
	{
		case 'f':
			while (i < len)
			{
				printf("%f%s", ((float*)pn->el)[i], btw);
				i++;
			}
			break;
		case 'c':
			while (i < len)
			{
				printf("%c%s", ((char*)pn->el)[i], btw);
				i++;
			}
			break;
		case 'i':
			while (i < len)
			{
				printf("%i%s", ((int*)pn->el)[i], btw);
				i++;
			}
			break;
	}
	return 0;
}
