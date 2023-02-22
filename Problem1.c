#include <stdio.h>
#include <math.h>

int naive_approach(int limit);
int fast_approach(int limit);

int main()
{
    int naive_ans = naive_approach(2025);
    int fast_ans = fast_approach(2025);
    printf("answers:  %d, %d", naive_ans, fast_ans);

    return 0;
}


// not necessarily naive, as this still computes extremely fast
// in terms of the mathematical approach, it is naive
int naive_approach(int limit) {
    int ans = 0;
    int count = 0;
    while (count < limit) {
        if ((count % 5 == 0) || (count % 3 == 0)) {
            ans += count;
        }
        count++;
    }
    
    return ans;
}

/* this is the fast approach, with O(1) time complexity, with n respect to the limit

Explanation Setup:
all factors of 3 from 1, below 1000 looks like...

3,6,9,12,15,18,21,...,999

all factors of 5 from 1 below 100 looks like...

5,10,15,20,25,30,35,40,...,995

both these sums can be written in summation form, so Σ3n, and Σ5n.
because of summation rules, we can factor the 3 and 5 out of both summations, 
giving 3 * Σn, and 5 * Σn. Now, a summation from 1 to N of the function n is just (N(N+1)/2).

so both summations can be rewritten as 3 * (N(N+1)/2), and 5 * (K(K+1)/2), with N and K 
denoting different summation limits for 3 and 5.

Limits:
we have two equations for the 3 and 5 summations, but we dont know the limits N and K.
If we assigned numbers to each divisible number in each 3 and 5 sequence, we would get something
that looked like the following...

1:  2:  3:  4:  5:       333:
3   6   9   12  15  ...  999 

1:  2:  3:  4:  5:      199:   200:
5   10  15  20  25  ... 995    1000

as you can see, limits N and K should be 333 for the three summation, and 200 for the 5 summation 
(dont worry about having the 1000, this is accounted for later)

Now that we have N and K, we can now compute 3 * (N(N+1)/2) + 5 * (K(K+1)/2), but this does not give the final answer

Subtracting the intersection:
Notice how in both the 3 and 5 sequences, there is 15. if we compute 3 * (N(N+1)/2) + 5 * (K(K+1)/2), 
we will also be adding double the factors of 15 so to account for this, we need to subtract off the multiples of 15,
giving a "final" equaiton of 3 * (N(N+1)/2) + 5 * (K(K+1)/2) - 15 * (J(J+1)/2)
(the reason I quoted final was because depending on how exactly the limits are computed, this may not be the final equation)
(in our case, this isn't the final)

Calculating Limits:
lets call the number we want to stay below MAX (in this case 1000)

the calculation for limits is simple, you just divide the number you want to go to with the divisor, and floor the result.
for instance, the limits N for 3 is 1000/3 = 333.3333..., then flooring gives 333 (which is consistent with what we said it should be earlier)


however, there is a slight issue with this. for example, doing the same calculation for 5 gives 200, which will include a 1000 in the summation.
so whenever MAX is a multiple of 3, 5, or 15, we are gonna get +MAX in our final answer. for instance if MAX is a multiple of 3 and 5, then
our answer we get from our "final" equation is actually (answer we want) + 2MAX. if MAX is only a multiple of 3, or 5, our answer is going to be (answer we want)+ MAX.
if MAX is a multiple of 15, we'll get (answer we want) - MAX, subtracted because the 15 summation is negated. We can easily fix this by accumulating all the maxes we get
in some error term (we can accumulate all these maxes through a simple modulo operator to see if MAX is a multiple of 3, 5 or 15), and then subtract the error from our 
"final" eqaution to get the answer we want, yeilding the final equation...

3 * (N(N+1)/2) + 5 * (K(K+1)/2) - 15 * (J(J+1)/2) - error

why go through the trouble to have a general max, leading to general equations for N, K and J? because its legit


*/
int fast_approach(int limit) {
    int limit_three_summation = (int)(limit / 3);
    int limit_five_summation = (int)(limit / 5);
    int limit_fifteen_summation = (int)(limit / 15);

    int error = 0;

    if(limit%3 == 0) error += limit;
    if(limit%5 == 0) error += limit;
    if(limit%15 == 0) error -= limit;

    int three_summation = 3*((limit_three_summation*(limit_three_summation + 1)) / 2);
    int five_summation = 5*((limit_five_summation*(limit_five_summation + 1)) / 2);
    int fifteen_summation = 15*((limit_fifteen_summation*(limit_fifteen_summation + 1)) / 2);

    return three_summation + five_summation - fifteen_summation - error;
}