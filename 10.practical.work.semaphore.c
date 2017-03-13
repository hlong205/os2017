#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>	
#include <semaphore.h>
#define BUFFER_SIZE 10

typedef struct {
char type; // 0=fried chicken, 1=French fries
int amount; // pieces or weight
char unit; // 0=piece, 1=gram
} item;

item buffer[BUFFER_SIZE];
int first = 0;
int last = 0;
sem_t s;

void produce(item *i) {
while ((first + 1) % BUFFER_SIZE == last) {
// do nothing -- no free buffer item
}
sem_wait(&s);
memcpy(&buffer[first], i, sizeof(item));
first = (first + 1) % BUFFER_SIZE;
sem_post(&s);
}

item *consume() {
item *i = malloc(sizeof(item));
while (first == last) {
// do nothing -- nothing to consume
}
sem_wait(&s);
memcpy(i, &buffer[last], sizeof(item));
last = (last + 1) % BUFFER_SIZE;
sem_post(&s);
return i;
}


int main(){

item no1,no2,no3;

no1.type = '0';
no1.amount = 5;
no1.unit = '0';

no2.type = '1';
no2.amount = 9;
no2.unit = '1';

no3.type = '2';
no3.amount = 8;
no3.unit = '1';

printf("\nfirst = %d, \nlast = %d", first, last);

printf("Item no1:%c,%d,%c\n", no1.type, no1.amount, no1.unit);
produce(&no1);
printf("\nAfter produce item no1: \nfirst = %d, \nlast=%d",first, last);

printf("Item no2:%c,%d,%c\n", no2.type, no2.amount, no2.unit);
produce(&no2);
printf("\nAfter produce item no2: \nfirst = %d, \nlast=%d",first, last);

printf("Item no3:%c,%d,%c\n", no3.type, no3.amount, no3.unit);
produce(&no2);
printf("\nAfter produce item no3: \nfirst = %d, \nlast=%d",first, last);

pthread_t id1, id2;
pthread_create(&id1,NULL,produce,NULL);

pthread_create(&id2,NULL,&consume,NULL);
pthread_join(&id2,NULL);
printf("After consume: \nfirst = %d, last = %d\n\n", first, last);
return 0;

	
}

