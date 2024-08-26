/*
Traits: 
1) Greedy Choice Property: Achieve global optimum by selecting locally best option
2) Optimal Substructure: The global problem can be solved by independent subproblems
In short, at each step, there is an optimal solution, 
after all the steps, we combine solutions to reach the global optimum
WARNING: ONLY use it when the problem guarantees that a local optimum leads to a global optimum.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/*
Q1: Coin Change Problem
*/


// Given 4 types of coins, find the min # of coins that sum up to amount cents
void min_num_coins(int amount) {
    int coins[] = {25, 10, 5, 1};
    int count[] = {0, 0, 0, 0};
    int old_amt = amount;
    // We start with coins with the biggest value to lowest
    for (int i = 0; i < 4; i++) {
        while(amount - coins[i] >= 0) {
            amount -= coins[i];
            count[i] += 1;
        }
    }

    printf("We need %d quarters, %d dimes, %d nickels, %d pennies for %d cents\n",
            count[0], count[1], count[2], count[3], old_amt);
}

int main() {
    min_num_coins(159);
    return 0;
}