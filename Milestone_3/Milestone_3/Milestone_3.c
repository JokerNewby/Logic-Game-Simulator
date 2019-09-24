#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

//queue for storing info read from a file
typedef struct list_tag {
	int id;
	char gates;
	int input1;
	int input2;
	int output;
	struct list_tag*next;
}ListNode;

typedef struct {
	ListNode*first;
	ListNode*last;
}queue;

//gates
int And(int a, int b) {
	return(a&&b);
}
int Or(int a, int b) {
	return(a || b);
}
int Xor(int a, int b) {
	if ((a&&b) == 1) {
		return 0;
	}
	else {
		return 1;
	}
}
int Not(int a) {
	if (a == 1) {
		return 0;
	}
	else
		return 1;
}


//functions for working with the queue
void queueInsert(queue *qp, int t, char a, int b, int c) {
	ListNode * n = (ListNode *)malloc(sizeof(ListNode));
	if (n == NULL) {
		printf("Out of memory \n");
		exit(1);
	}
	n->id = t;
	n->gates = a;
	n->input1 = b;
	n->input2 = c;
	n->next = NULL;
	if (qp->last == NULL) {
		qp->first = qp->last = n;
	}
	else {
		qp->last->next = n;
		qp->last = n;
	}
}

void queueInit(queue*qp) {
	qp->first = NULL;
	qp->last = NULL;
}

void queuePrint(queue q) {
	int h,a,b,c,d;
	printf("Now I will print the queue\n"); 
	ListNode * n;
	ListNode * e;
	for (n = q.first; n != NULL; n = n->next) {
		switch (n->gates) {
		case 'I':
			printf("please enter either 0 or 1 \n");
			scanf("%d", &h);
			n->output = h;
			break;
		case 'A':
			c = n->input1;
			e = q.first;
			while (e->id != c) {
				e = e->next;
			}
			a = e->output;
			d = n->input2;
			e = q.first;
			while (e->id != d) {
				e = e->next;
			}
			b = e->output;
			n->output = And(a, b);
			break;
		case 'O':
			c = n->input1;
			e = q.first;
			while (e->id != c) {
				e = e->next;
			}
			a = e->output;
			d = n->input2;
			e = q.first;
			while (e->id != d) {
				e = e->next;
			}
			b = e->output;
			n->output = Or(a, b);
			break;
		case 'X':
			c = n->input1;
			e = q.first;
			while (e->id != c) {
				e = e->next;
			}
			a = e->output;
			d = n->input2;
			e = q.first;
			while (e->id != d) {
				e = e->next;
			}
			b = e->output;
			n->output = Xor(a, b);
			break;
		case 'N':
			c = n->input1;
			e = q.first;
			while (e->id != c) {
				e = e->next;
			}
			a = e->output;
			n->output = Not(a);
			break;
		case 'Q':
			c = n->input1;
			e = q.first;
			while (e->id != c) {
				e = e->next;
			}
			a = e->output;
			n->output = a;
			break;
		}
	}
	for (n = q.first; n != NULL; n = n->next) {
		printf("id: %d gate: %c input1: %d input2: %d output: %d \n", n->id, n->gates, n->input1, n->input2, n->output);
	}
	n = q.last;
	printf("the result of the circuit is: %d \n", n->output);
}






int main() {
	int id, in1, in2, n,i;
	char gate;
	FILE *fp;
	queue my_q;
	fp = fopen("test.txt", "r");
	queueInit(&my_q);
	fscanf(fp, "%d", &n);
	//printf("%d \n", n);
	for (i = 0; i < n; i++) {
		//grabs id
		fscanf(fp, "%d", &id);
		//printf("%d \n", id);
		//grabs gate
		fscanf(fp, "%c", &gate);
		fscanf(fp, "%c", &gate);
		fscanf(fp, "%c", &gate);
		//printf("%c \n", gate);
		//grabs first input
		fscanf(fp, "%d", &in1);
		//printf("%d \n", in1);
		//grabs second input
		fscanf(fp, "%d", &in2);
		//printf("%d \n", in2);
		//put info into a node of the queue
		queueInsert(&my_q, id, gate, in1, in2);
	}
	queuePrint(my_q);
	fclose(fp);
	system("pause");
	return 0;
}