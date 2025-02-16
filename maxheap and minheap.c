#define MAX 1000001
#define full(n) (n==MAX-1)
#define empty(n) (!n)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
	int key;
}element;

element* maxheap;
element* minheap;
int q = 0;
int* n = &q;
FILE* fout;
FILE* fp;

void insert(element, int*);
void ascend(element*, int*);
void descend(element*, int*);

int main(int argc, char* argv[]) {
	char command[255];
	int num;
	element r;
	float count, start=0, end=0;
	maxheap = (element*)malloc(sizeof(element) * MAX);
	if (maxheap == NULL) {
		fprintf(stderr, "메모리 할당 실패");
		return 1;
	}
	minheap = (element*)malloc(sizeof(element) * MAX);
	if (maxheap == NULL) {
		fprintf(stderr, "메모리 할당 실패 (maxheap)");
		return 1;
	}
	
	start = clock();
	if (argc != 2) {
		fprintf(stderr, "usage: %s input_filename\n", argv[0]);
		return 0;
	}
	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		fprintf(stderr,"The input file does not exist.\n");
		return 1;	}

	fout = fopen("hw2_result.txt", "w");
	if (fout == NULL) {
		fprintf(stderr,"파일을 열 수 없습니다");
		return 1;
	}

	

	

	while (fgets(command, sizeof(command), fp) != NULL) {
		if (command[0] == 'I') {
			sscanf(command, "INSERT %d", &num);
			r.key = num;
			insert(r, n);
		}
		else if (command[0] == 'A') {
			ascend(minheap, n);
		}
		else if (command[0] == 'D') {
			descend(maxheap, n);
		}
	}
	
	
	end = clock();
	
	count = (end - start) / CLOCKS_PER_SEC;
	printf("output written to hw2_result.txt.\n");
	printf("running time: %.6f seconds\n", count);

	fclose(fp);
	fclose(fout);
	return 1;
}

void insert(element e, int* k) {
	int m;
	if (full(*k)) {
		fprintf(stderr, "The heap is full.\n");
		exit(1);
	}
	m = ++(*k);
	while ((m != 1) && (maxheap[m/2].key < e.key)) {
		maxheap[m] = maxheap[m / 2];
		m = m / 2;
	}
	maxheap[m] = e;

	m = *k;
	while ((m != 1) && (minheap[m / 2].key > e.key)) {
		minheap[m] = minheap[m / 2];
		m = m / 2;
	}
	minheap[m] = e;
}

void ascend(element *heap,int* p) {
	int pat, ch;
	element e, temp;
	element* copy;
	int k;
	k = *p;
	copy = (element*)malloc(sizeof(element) * MAX);
	if (copy == NULL) {
		fprintf(stderr, "메모리 할당 실패");
		return;
	}
	for (int i = 0; i <= k; i++) {
		copy[i] = heap[i];
	}
	if (empty(k)) {
		fprintf(stderr, "The heap is empty.");
		exit(1);
	}
	while (k > 0) {
		e = copy[1];
		temp = copy[(k)--];
		pat = 1, ch = 2;
		while (ch <= k) {
			if ((ch < k) && (copy[ch].key > copy[ch + 1].key))
				ch++;
			if (temp.key <= copy[ch].key)
				break;
			copy[pat] = copy[ch];
			pat = ch;
			ch = pat * 2;
		}
		copy[pat] = temp;
		fprintf(fout, "%d ", e.key);
	}
	fprintf(fout, "\n");
}

void descend(element* heap, int* p) {
	int pat, ch;
	element e, temp;
	element* copy;
	int k = *p;
	copy = (element*)malloc(sizeof(element) * MAX);
	if (copy == NULL) {
		fprintf(stderr, "메모리 할당 실패");
		return;
	}
	for (int i = 0; i <= k; i++) {
		copy[i] = heap[i];
	}
	if (empty(k)) {
		fprintf(stderr, "The heap is empty.");
		exit(1);
	}
	while (k > 0) {
		e = copy[1];
		temp = copy[(k)--];
		pat = 1, ch = 2;
		while (ch <= k) {
			if ((ch < k) && (copy[ch].key < copy[ch + 1].key))
				ch++;
			if (temp.key >= copy[ch].key)
				break;
			copy[pat] = copy[ch];
			pat = ch;
			ch = pat * 2;
		}
		copy[pat] = temp;
		fprintf(fout, "%d ", e.key);
	}
	fprintf(fout, "\n");
}