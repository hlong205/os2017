#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 10

typedef struct {
char type; // 0=fried chicken, 1=French fries
int amount; // pieces or weight
char unit; // 0=piece, 1=gram
} item;

item buffer[BUFFER_SIZE];
int first = 0;
int last = 0;

void produce(item *i) {
while ((first + 1) % BUFFER_SIZE == last) {
// do nothing -- no free buffer item
}
memcpy(&buffer[first], i, sizeof(item));
first = (first + 1) % BUFFER_SIZE;
}

item *consume() {
item *i = malloc(sizeof(item));
while (first == last) {
// do nothing -- nothing to consume
}
memcpy(i, &buffer[last], sizeof(item));
last = (last + 1) % BUFFER_SIZE;
return i;
}

int main(){
item no1, no2;

no1.type = '0';
no1.amount = 5;
no1.unit = '0';

no2.type = '1';
no2.amount = 9;
no2.unit = '1';

printf("first = %d, last = %d\n\n", first, last);

printf("item no1: %c, %d, %c\n", no1.type, no1.amount, no1.unit);
produce(&no1);
printf("\nAfter produce item no1: \nfirst = %d, \nlast=%d",first,last);

printf("item no2: %c, %d, %c\n", no2.type, no2.amount, no2.unit);
produce(&no2);
printf("\nAfter produce item no2: \nfirst = %d, \nlast=%d",first,last);


item *itemconsumed = consume();
printf("Consumed item: %c, %d, %c \nfirst = %d, \nlast=%d", itemconsumed->type, itemconsumed->amount, itemconsumed->unit, first, last);
return 0;
}

