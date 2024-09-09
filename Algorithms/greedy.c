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

/*
Q2: Activity Selection
*/

// Structure to represent an activity
typedef struct {
    int start;
    int finish;
} Activity;

// Function to sort activities based on finish time
void sortActivities(Activity arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].finish > arr[j + 1].finish) {
                Activity temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to select the maximum number of activities
void activitySelection(Activity arr[], int n) {
    sortActivities(arr, n);
    printf("Selected activities are:\n");

    // The first activity is always selected
    int i = 0;
    printf("Activity %d: (%d, %d)\n", i + 1, arr[i].start, arr[i].finish);

    // Consider rest of the activities
    for (int j = 1; j < n; j++) {
        // If this activity has a start time greater than or equal to the
        // finish time of the previously selected activity, then select it
        if (arr[j].start >= arr[i].finish) {
            printf("Activity %d: (%d, %d)\n", j + 1, arr[j].start, arr[j].finish);
            i = j;
        }
    }
}


int main() {
    // Q1
    min_num_coins(159);

    // Q2
    Activity activities[] = {{1, 3}, {2, 5}, {4, 7}, {1, 8}, {5, 9}, {8, 10}};
    int n = sizeof(activities) / sizeof(activities[0]);
    activitySelection(activities, n);


    return 0;
}


