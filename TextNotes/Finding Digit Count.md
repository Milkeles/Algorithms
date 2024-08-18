2024-08-18 | 00:42 UTC +3

by H. Hristov

Tags: [[Computer Science]], [[Mathematics]], [[Algorithms]], [[Competitive Programming]]

# Finding Digit Count
Suppose that we have a random integer, such as 4321. If we have to find how many digits it has, we would simply count them by dividing the number by ten and incrementing a counter until the number reaches zero. However, there is an alternative way to achieve this. Let's look at the number once again:

$$
4321
$$

This is a decimal number, therefore each place value in it is a power of ten. So we can break it down to:

$$
\begin{aligned}
4 \cdot1000 + 3\cdot 100 + 2\cdot 10 + 1 \text{ or } \newline 4\cdot 10^3 + 3\cdot 10^2 + 2\cdot 10^1 +1\cdot10^0 \end{aligned}
$$

By doing this, we can see that, in order for a number to have 4 digits, it must be equal or greater than 1,000 or 10³ and less than the next place value, which is 10⁴ or 10,000, which is quite obvious. But, if we have to generalize this, we can say that any positive integer **P** with **d** digits must satisfy:

$$
10^{d-1}\leq P < 10^{d} 
$$

By expressing it this way, we now have two variables - an integer **P** and an unknown exponent **d**, which is also directly related to the digit count of **P**. So, if we wish to find the number of digits our integer has, we have to find **d**. Doing this is incredibly simple, all we have to do is apply a tiny bit of high school math knowledge – logarithms. The base 10 logarithm $$\log_{10}(P) = k$$
tells us that, in order to get P, we must raise 10 to the power of k. Deriving from this and our previous inequality, we can now easily find d:

$$
\log_{10}{(10^{d-1})} \leq log_{10}{(P)} < log_{10}{(10^{d})}
$$

Simplify.

$$
d-1 \leq log_{10}{(P)} < d 
$$

This tells us that **d**, the number of digits of **P**, is base 10 logarithm of **P** rounded up.

$$
d = \lceil log_{10}(P)\rceil = 1 + \lfloor log_{10}(P)\rfloor 
$$

You may now wonder **"But what's the point of knowing this?"**. There are several benefits. For starters, it can be done in just one line of code, instead of a whole loop. Pretty cool, huh? Jokes aside, there are two situations when knowing this is actually useful. 

The first is when we have to find the number of digits of a number in a non-decimal system, such as binary. This can be done the exact same way we did it with a decimal integer, all we have to do is change the base of the logarithm, for its base tells us how many digits the number has in that system. For example, the number 19 is 10011 in binary. All we have to do to find its digit count is to calculate base 2 logarithm of 19 and then round it up (or round it down and add 1). 

Another application of this is if we have to find the digit count of a large product. A good example of this would be to find the number of digits a large factorial has. Doing this the most straightforward way - by multiplying every single number to get the product and then dividing that product to count its digits would be extremely inefficient and difficult – multiple multiplication and division operations will be performed, and the product will be so large that we won't be able to store it in a built-in data type. Instead, we can use what we learned so far and apply a very convenient property of logarithms:

$$
\log{(x \cdot y)}=\log{(x)} \cdot \log{(y)}
$$

We know that

$$
\begin{gathered}
n! = n\cdot n-1 \cdot n-2 ... \cdot 1 \text{ or }\newline
n! = \prod_{{i=1}}^{{n}}i
\end{gathered}
$$

Therefore the logarithm of n! is simply the sum of logarithms of all the numbers:

$$
\begin{gathered}
\log{(n!)} = \log(n)+\log{(n-1)}+...+1  
\newline
\text{or}\newline
\log{(n!)} = \sum_{{i=0}}^{{n}}log{(i)}
\end{gathered}
$$

And by finding this, we have essentially found the digit count of **n!**, without actually calculating it. The factorial was merely an example, though, the same technique can be utilized with any product. Here's a C++ code snippet of this:
```cpp
 main() {
    int n = 50; //65 digits
    double sum = 0;
    for(int i = 1; i <= n; ++i) {
        sum += log10(i);
    }
    cout << (int)sum + 1; 

    return 0;
}
```

### REFERENCES

Nakov, P., Dobrinkov, P. (2015). Programming=++Algorithms. Software University.
