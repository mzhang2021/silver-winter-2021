# Time Complexity

- In USACO, your program must produce the answer in a set amount of time; your program can't run forever!
  - C++ gets 2 seconds per test case
- **Time complexity** measures how fast the running time of your program grows as the input size grows. and it is expressed with **Big O Notation**
- Let's do a basic example:

```c++
int n;
cin >> n;

int count = 0;
for (int i=0; i<n; i++) {
    count++;	// how many times do we increment count? In terms of n
}

cout << count << endl;
```

- We have one input, $n$
- As $n$ grows, the number of operations grows linearly
  - If $n = 10$, our program performs $10$ operations
  - If $n = 100000$, our program performs $100000$ operations
- Therefore, we say the time complexity of this program is $O(n)$

## What counts as an operation?

- Any instruction for the computer to compute or perform, such as adding two numbers or printing a string, can be considered an operation
- There is no strict definition for an operation; you could argue any statement ending in a semicolon counts as one operation
  - In the previous example, you could argue that it makes $n + 4$ operations, so when $n = 10$, the program actually makes $14$ operations instead of $10$
  - As we will soon learn, this distinction doesn't matter

## Back to time complexity...

- Let's try another one!

```c++
int n;
cin >> n;

int count = 0;
for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
        count++;	// how many times do we increment count?
    }
}

cout << cout << endl;
```

- Once again, we have one input, $n$
- As $n$ grows, the number of operations grows quadratically
  - If $n = 10$, our program performs $100$ operations
  - If $n = 100000$, our program performs $10000000000$, or $10^{10}$ operations!
- Therefore, we say the time complexity of this program is $O(n^2)$

- Time complexity may include multiple variables:

```c++
int n, m;
cin >> n >> m;

int count = 0;
for (int i=0; i<n; i++) {
    for (int j=0; j<m; j++) {
        count++;
    }
}

cout << count << endl;
```

- Time complexity: $O(nm)$

- When computing time complexity, we **ignore constant factors**, and we only **include the highest degree** for each variable
- Example:

```c++
int n;
cin >> n;

int count = 0;
for (int i=0; i<2*n; i++) {
    count++;	// 2n times
}

for (int i=0; i<n; i++) {
    for (int j=n-1; j>=i; j--) {
        count++;	// n + (n - 1) + (n - 2) + ... = n * (n + 1) / 2
    }
}

// 2n + n * (n + 1) / 2 = 2n + n^2 / 2 + n / 2 = n^2 / 2 + (5 / 2) * n => O(n^2)
cout << count << endl;
```

- Time complexity: $O(n^2)$

## But wait, why would we ignore these constants? They make our program do more operations!

- You're absolutely right! Time complexity is **not** a measurement of the exact number of operations in a program; it merely describes how fast the running time (or the number of operations) grows **with respect to** the input size
  - Constant factors do not change in response to input size. A program that makes $n$ operations and a program that makes $5n$ operations both grow linearly with respect to $n$
  - Extra terms of lower degree to not matter because the highest degree term **dominates**. This works just like functions in math:
  - $f(x) = x^2 + 3x - 15$
  - The above function is considered quadratic, even though there are extra terms $3x - 15$ at the end
  - Indeed, when $x$ gets really large, the $x^2$ term grows significantly faster than the $3x - 15$ terms, to the point where the $3x - 15$ terms are insignificant compared to the value of the $x^2$ term
  - The same idea applies to evaluating time complexity

## How many operations are we allowed to do?

- There is no exact number, but a good rule of thumb is that C++ can compute $\sim 10^8$, or 100 million operations per second
- For example, if you are solving a problem where $N = 10^5$, then a solution with time complexity $O(N)$ would be acceptable, but a solution with time complexity $O(N^2)$ would likely be too slow

## Beginner's trap: constants still matter!

- Just because time complexity excludes constants doesn't mean we as coders get to ignore constants

```c++
int n;
cin >> n;

for (int i=0; i<1000000000; i++) {	// 9 0's
    cout << "FIRE" << endl;
}
```

- The above program is technically $O(1)$: regardless of the value of $n$, the number of operations it makes is always $\sim 10^9$ operations, so the time complexity is constant with respect to $n$
- However, the constant factor of $10^9$ obviously matters
  - If you submit this program to the USACO server, you will likely get a time limit exceeded verdict

## Time Complexity's Brother: Space Complexity

- Just like with running time, we can also use big O notation to express space complexity
- **Space complexity** measures how much space in memory your program takes up with respect to input size

```c++
int n;
cin >> n;

for (int i=0; i<n; i++) {
    cout << "HELLO" << endl;
}
```

- Time complexity: $O(n)$
- Space complexity: $O(1)$
  - Only two variables are ever declared, $n$ and $i$, and each only take up one unit of space, so ignoring constant factors gives us constant space used regardless of size of $n$

```c++
int n;
cin >> n;

vector<int> a(n);
```

- Time complexity: $O(n)$
- Space complexity: $O(n)$
  - We declare a vector of size $n$, which will take up $n$ units of memory, so our memory usage grows linearly with respect to $n$
  - Note that the time complexity is $O(n)$ even though there are no loops present. This is because declaring a vector of size $n$ takes $O(n)$ time, since we have to reserve $n$ spots in memory, each of which takes one operation

## How many 'units' of memory can we take?

- When talking about computer storage, we use **bytes**

![Computer Science](https://www.fastwebhost.in/blog/wp-content/uploads/2017/04/byes-mb-gb-tb.png)

- USACO rules allow your program to use at most $256$ MB of memory
- For example, an `int` variable takes 4 bytes, so `vector<int> a(n)` would take $4n$ bytes
  - If $n = 10^5$, then our vector would use $4 \cdot 10^5$ bytes, or $0.4$ MB, which is definitely small enough
  - If $n = 10^{10}$, then our vector would use $4 \cdot 10^{10}$ bytes, or $40000$ MB ($40$ GB)! That will definitely exceed the memory limit
    - As a side note, if we declare a vector of size $10^{10}$, we'll probably exceed the time limit anyways

