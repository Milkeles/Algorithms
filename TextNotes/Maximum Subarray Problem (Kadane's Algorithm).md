2024-08-18 | 16:30 UTC + 3

Written by H. Hristov (Milkeles)

Tags: [[Computer Science]], [[Algorithms]], [[Arrays]], [[Dynamic Programming]]

## Maximum Subarray Problem (Kadane's Algorithm)
The maximum subarray problem revolves around finding a contiguous subarray in an array of integers that has the maximum possible sum. When the original array consists only of positive numbers, the maximum subarray is the array itself. However, when negative numbers are added to the mix, the problem gets a little more difficult to solve. 

### Different Approaches
Because Kadane's algorithm is extremely simple, let's first explore a few solutions of the problem that were proposed before the algorithm was invented. Doing this will show how big of a difference the algorithm makes. Also, some of them use interesting techniques, the learning of which could be useful for solving other problems.

First, obviously, the most intuitive algorithm uses a brute-force approach. It would work, but not so efficiently. Practically, we need two numbers - the start and end of the subarray. To find them, we have to, firstly, loop through the array once to check which number is the optimal beginning of the maximum subarray. Then for each start we also have to loop through all the remaining numbers to check the optimal end. Finally, for each pair of start and end numbers, we have to loop through every number in between to sum them up, and then compare the sums to find the maximum one. The time complexity of such algorithm would be in the order of **O(n³).** 
```cpp
...
int maxSubarr = 0;
int n = sizeof(array) / sizeof(int);

for(int i = 0; i < n; ++i) {
    for(int j = i; j < n; ++j) {
        int sum = 0;
        for(int k = i; k < j; ++k) {
            sum += array[k];
        }
        maxSubarr = max(maxSubarr, sum);
    }
}
...
```

This algorithm can be improved by computing the sum in the innermost loop only once, for every sum is related to the one computer before it - there's only one number difference between them, so we don't have to sum everything all over again. 
```cpp
int maxSubarr = 0;
int n = sizeof(array) / sizeof(int);

for(int i = 0; i < n; ++i) {
    int sum = 0;
    for(int j = i; j < n; ++j) {
        sum += array[j]; //array[i..j] = array[i..j-1] + array[j];
        maxSubarr = max(maxSubarr, sum);
    }
}
```
Alternatively, we can use a prefix array - the I-th element in the prefix array is the sum of the elements in the original array X[1...I]. The prefix array is precalculated outside of the outermost loop, and then we simply use it in the middle loop to get the sum of the elements from the current start and end indexes, Prefix[End] - Prefix[Start]. 
```cpp
int n = sizeof(array) / sizeof(int);
int prefixArr[n];
prefixArr[0] = array[0];

for(int i = 1; i < n; ++i) {
    prefixArr[i] = array[i] + prefixArr[i - 1];
}
    
int maxSubarr = prefixArr[0];
    
for(int i = 0; i < n; ++i) {
    for(int j = i; j < n; ++j) {
        int currentSum;
        if (i == 0) {
            currentSum = prefixArr[j];
        } else {
            currentSum = prefixArr[j] - prefixArr[i - 1];
        }
        maxSubarr = max(maxSubarr, currentSum);
    }
}
```
Both of these approaches have time complexity of **O(n²)**.

We can improve either of the previous two solutions even further to a **O(n log n**) by turning them into a divide-and-conquer algorithm. We'll take the first one because it feels more natural and simple. Instead of checking every possible interval, we'll recursively break down the original problem of size **N** into smaller sub-problems of size **N/2**, which would make total of **log n** recursive calls. For each call we find the maximum subarrays of the left-side problem and the right-side problem in time of **O(n)** using the same approach as we did in the 2nd algorithm. After we find the maximum of the left side and the maximum of the right side, we will add them to also check if the contiguous subarray that is made of the elements of the right max and left max, as well as the elements in the middle, is the largest. Here's how the algorithm looks like:
```cpp
double MaxSum(const vector<int>& X, double L, double U) {
    if (L > U) return 0.0;
    if (L == U) return max(0.0, X[L]);

    int M = ((int)L + (int)U) / 2;
    double Sum = 0.0;
    double MaxToLeft = 0.0;

    for (int I = M; I >= L; --I) { //THE DIRECTION MATTERS!
        Sum += X[I];
        MaxToLeft = max(MaxToLeft, Sum);
    }

    Sum = 0.0;
    double MaxToRight = 0.0;
    
    for (int I = M + 1; I <= U; I++) {
        Sum += X[I];
        MaxToRight = max(MaxToRight, Sum);
    }
    double MaxCrossing = MaxToLeft + MaxToRight;
    
    double MaxInA = MaxSum(X, L, M);
    double MaxInB = MaxSum(X, M + 1, U);

    return max({ MaxCrossing, MaxInA, MaxInB });
}
```

### The Linear Algorithm
After we went through several different ways to solve this problem, it's time to look into Kadane's algorithm - the most efficient and, ironically, the simplest solution. To understand how the algorithm works, we must first understand the following observations: 
1. The maximum subarray cannot start with a negative sum. Eliminating negative number(s) from the beginning of the subarray and starting over will result in a larger overall sum than including them.
2. After eliminating subsequences with a negative sum from the beginning of the subarray, the remaining subsequence must start non-negatively and increase the overall sum. Thus, an optimal maximum subarray must start immediately after the elimination of starting sub-subsequences with negative sums.
Both of these observations are logical and simple to understand. Interestingly, using them we can create two versions of Kadane's algorithm that follow the same logic but their results are slightly different.

The first variation has the following logic: The maximum subarray sum, ending at the current index, is either the current number, or the previously accumulated sum plus the current number:
```cpp
int currentMax = array[0];
int maxSubarr = array[0];
for(int i = 1; i < n; ++i) {
	currentMax = max(array[i], currentMax + array[i]);
	maxSubarr = max(currentMax, maxSubarr);
}
```

The second variation follows the same logic, except, instead of taking the current number as the max so far, when the sum is negative it *resets* the sum and starts over from zero.
```cpp
int currentMax = 0;
int maxSubarr = 0;
for(int i = 0; i < n; ++i) {
	currentMax = max(0, array[i] + currentMax);
	maxSubarr = max(currentMax, maxSubarr);
}
```

The difference between the two versions is that if the array consists **only** of negative numbers, the first algorithm will find the largest negative number as the maximum subarray sum, while the second will return that the maximum subarray sum is zero, which can be interpreted as that there is no maximum subarray, or it is an empty set. The choice which variation to use depends entirely on what we're expected to return for such cases, otherwise, both of these algorithms are linear, or, in other words, their worst case time complexity is **O(n)**.

## REFERENCES
1. Kadane, J. (2023). Two Kadane Algorithms for the Maximum Sum Subarray Problem. Algorithms 2023, Volume 16, Issue 11, 519. Available online: [Algorithms | Free Full-Text | Two Kadane Algorithms for the Maximum Sum Subarray Problem (mdpi.com)](https://www.mdpi.com/1999-4893/16/11/519)
2. Bentley, J. Algorithm Design Techniques. Commun. ACM 1984, 27, 865–871. Available online: [Programming pearls (acm.org)](https://dl.acm.org/doi/pdf/10.1145/358234.381162)
