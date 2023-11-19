For Part 2, I chose options 1 and 2: the Birthday Paradox and Probe Rate.

My cpp file is called part2.cpp and contains the code for both problems (they aren't separated).

The cpp file already formats my output and has some comments that explain my work, which I'd also like you to read, but I'll elaborate on some parts of it here:

At the beginning of the program, I set the random seed to the current time. I also wrote a function, generateRandomString(), that generates a string of 28 random letters. Both problems use this function and have debug mode set to "false." Using my code, srand(time(0)), and any custom number of trials (and a custom n for problem 2), you can also replicate my results for both parts.

* PROBLEM 1: BIRTHDAY PARADOX
The paradox states that you only need 23 people for the probability of at least 2 people sharing the same birthday to exceed 50%. In the context of hashtables, this means that with size 365, you only need 23 or fewer insertions for the probability of a collision to exceed 50%. Even if it actually takes more insertions than that, it must be before the hashtable is half full (< 183) and resizes to something bigger than 365. We test this theory below with 1000 trials and print the percentages,expecting around 507 trials to have needed <= 23 insertions.


** Explanation of Major Code:

1. The for loop in lines 24-43 iterates through all the trials, making sure to "reset" the relevant variables for each trial. It also stores a nested while loop, whose purpose I explain below.

(The meat of the testing)
2. The nested while-loop checks whether the number of probes for each insertion is 0 (no collisions), and the hashtable isn't half full yet (otherwise requiring a resize). It breaks as soon as an insertion has a positive number of probes, or the hashtable is half full. Once this happens, each trial stores the total number of insertions this process took and whether it was <= 23 or >= 24, incrementing the appropriate variable of the 2 accordingly.

3. I format the results as a percentage of the total number of iterations (in this case 1000) at the end of the problem. They're generally close to 50.7% for the number of iterations that took 23 or fewer insertions. It may also vary by up to a few percentage points (maximum 2-3%, on average).

Here is my output when I ran the program 5 times:

PART 1: BIRTHDAY PARADOX
% of trials that took <= 23 insertions: 51.6
% of trials that took >= 24 insertions: 48.4

PART 1: BIRTHDAY PARADOX
% of trials that took <= 23 insertions: 50.3
% of trials that took >= 24 insertions: 49.7

PART 1: BIRTHDAY PARADOX
% of trials that took <= 23 insertions: 49.9
% of trials that took >= 24 insertions: 50.1

PART 1: BIRTHDAY PARADOX
% of trials that took <= 23 insertions: 51.2
% of trials that took >= 24 insertions: 48.8

PART 1: BIRTHDAY PARADOX
% of trials that took <= 23 insertions: 52.8
% of trials that took >= 24 insertions: 47.2


-------

* PROBLEM 2: PROBE RATE
This problem is saying that when the hash table is half full, the 1st collision is likely to occur (usually requiring 1 probe), as the 1st m/2 elements will hash to distinct locations if m is prime. The hash table is a quarter full after it resizes (when half the original m indices are filled), as m roughly doubles, so we're now considering the new value of m. You're going back and forth between these 2 processes as the instructions state, resulting in 2n/3 probes on average (66% of n) for n insertions.

Note that this problem might take a couple of seconds, depending on the value of n, and a high number of trials (>= 1000). My runtime otherwise is fine for the hashtable, as seen in part 1.

** Explanation of Major Code:

1. I declare an array of possible prime n's to randomly choose from. They are inspired by the list of sizes required for the resize function of the hashtable in part 1 of the homework.

2. Regarding the outer for loop in lines 70-83
    a. Similar to (1) for the birthday paradox problem above
        
    b. The outer for-loop resets relevant variables for each trial. It creates a hashtable with default size 11 to account for resizing. It also records the total number of probes for each trial (var: probes) and the largest number of probes an insertion required for that trial. These 2 values are used to calculate the average for both values across ALL trials.

3. The largest probe on average and the number of probes on average after inserting n elements is finally calculated across ALL trials. It is formatted accordingly, and usually, the largest probe is 1 or 0 less than log(n), and the number of probes required is very close to 0.667, give or take a few # points.


Here is my output when I ran the program 5 times:

PART 2: PROBE RATE
n is 397.
log(n) = 8.
log(n) -> 7 is the largest number of probes on average.
2n/3 = 264.
2n/3 -> 264 is the number of probes on average. 
0.664987 ≈ 0.667.
These results are in line with our expectations.

PART 2: PROBE RATE
n is 1597.
log(n) = 10.
log(n) -> 9 is the largest number of probes on average.
2n/3 = 1064.
2n/3 -> 1095 is the number of probes on average. 
0.685661 ≈ 0.667.
These results are in line with our expectations.

PART 2: PROBE RATE
n is 397.
log(n) = 8.
log(n) -> 7 is the largest number of probes on average.
2n/3 = 264.
2n/3 -> 265 is the number of probes on average. 
0.667506 ≈ 0.667.
These results are in line with our expectations.

PART 2: PROBE RATE
n is 197.
log(n) = 7.
log(n) -> 6 is the largest number of probes on average.
2n/3 = 131.
2n/3 -> 127 is the number of probes on average. 
0.64467 ≈ 0.667.
These results are in line with our expectations.

PART 2: PROBE RATE
n is 197.
log(n) = 7.
log(n) -> 6 is the largest number of probes on average.
2n/3 = 131.
2n/3 -> 128 is the number of probes on average. 
0.649746 ≈ 0.667.
These results are in line with our expectations.