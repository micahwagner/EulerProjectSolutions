#include <stdio.h>

int first_approach(int limit);
int fast_approach(int limit);

int main()
{
    int ans = first_approach(4000000);
    printf("%d", ans);
    return 0;
}



int first_approach(int limit) {
    int prev = 1;
    int current = 1;
    int sum = 0;
    while (current < limit) {
        if(current % 2 == 0) sum += current;
        current += prev;
        prev = current - prev;
    }
    return sum;
}


int fast_approach(int limit) {

}