We have already covered converting numbers between binary (base-2), hexadecimal (base-16), and decimal (base-10) numbers.  In this exercise, we will write a program to convert numbers to base-7.

A base-7 number has digits in the range [0 - 6], where each digit represents an increasing power of 7.  For example, the number $15424_7$ represents the decimal number

$$ \begin{aligned} 15424_7 & = 1\times(7^4) + 5\times(7^3) + 4\times(7^2) + 2\times(7^1) + 4\times(7^0)\\\\ & = 4330. \end{aligned} $$

To convert from decimal to base-7, we need to perform the reverse process: given the number 4330 in decimal, we want to determine the digits in base 7.  We can do this by noting that the least-significant digit, 4, is the remainder of 4330 when dividing by 7:

$$ \begin{aligned} 4330 \\% 7 & = 1\times(7^4) \\% 7 + 5\times(7^3) \\% 7 + 4\times(7^2) \\% 7 + 2\times(7^1) \\% 7 + 4\times(7^0) \\% 7\\\\ & = 1\times 0 + 5 \times 0 + 4 \times 0 + 2 \times 0 + 4 \times 1\\\\ & = 4. \end{aligned} $$

To get the next digit, note that if we divide 4330 by 7 using integer division, we get
$$ \begin{aligned} 4330 / 7 & = 1\times(7^4) / 7 + 5\times(7^3) / 7 + 4\times(7^2) / 7 + 2\times(7^1) / 7 + 4\times(7^0) / 7\\\\ & = 1\times(7^3) + 5\times(7^2) + 4\times(7^1) + 2\times(7^0)\\\\ & = 1542_7, \end{aligned} $$
which has the same digits at the original 4330, but with the least-significant digit removed.

Write a program that reads positive decimal integers from standard input (i.e. using `scanf(...)`), and prints their corresponding base-7 representations to standard output.  Your program should stop if it fails to read a valid integer (i.e. `scanf(...)` returns something other than `1`).

### Input Format

The input will consist of positive integers in the range [0 - 5764800], each separated by a newline.

### Output Format

Print the corresponding base-7 representations, each on a new line.  Do not print any leading-zeroes unless the input number is exactly `0`, in which case you should print `"0"`.

---

### Sample Input

```default
4330
7
23
1
16806
```

### Sample Output

```default
15424
10
32
1
66666
```

### Explanation

$$ \begin{aligned} 4330_{10} & = 15474_{7}\\\\ 	7_{10} & = 10_{7}\\\\ 23_{10} & = 32_{7}\\\\ 1_{10} & = 1_{7}\\\\ 16806_{10} & = 66666_{7} \end{aligned} $$

