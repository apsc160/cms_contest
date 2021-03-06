A common task in Engineering applications is two determine the relationship between two variables.  After plotting the data, if the relationship appears to be linear, then we can compute a *line of best fit*, or *trend-line* between them.

<div style="text-align:center;width=100%;">
<img alt="Simple Linear Regression" 
    src="https://upload.wikimedia.org/wikipedia/commons/thumb/3/3a/Linear_regression.svg/438px-Linear_regression.svg.png" 
    style="margin-left: auto; margin-right:auto; display:block; maxwidth=100%;"  />
<strong>Simple Linear Regression (source: <a href="https://commons.wikimedia.org/wiki/File:Linear_regression.svg">[wikimedia]</a>)</strong></div>
<br/>

A linear relationship between two variables $x$ and $y$ has the form

$$ y = mx + b, $$

where $m$ is the slope of the line, and $b$ is the $y$-intercept.  Given a collection of $n$ 2D points $\\{(x_i, y_i)\\}_{i=1}^n$, we wish to compute $m$ and $b$ to minimize the sum-of-squared errors across all the datapoints:

$$\text{minimize } E = \sum_i \\|y_i - mx_i - b\\|^2.$$

Using a bit of calculus, it can be shown that the minimizing parameters satisfy

$$ \begin{aligned} m & = \frac{\sum_{i=1}^n(x_i - \bar{x})(y_i - \bar{y})}{\sum_{i=1}^n(x_i-\bar{x})^2},\\\\ b & = \bar{y} - m \bar{x},\end{aligned} $$

where

$$ \begin{aligned} \bar{x} & = \frac{1}{n}\sum_{i=1}^n x_i,\\\\ \bar{y} & = \frac{1}{n}\sum_{i=1}^n y_i. \end{aligned} $$

## Task

Write a program that reads pairs of $x$ and $y$ values from a file named `data.txt`, computes the trend-line using simple linear regression, and prints the slope and intercept to standard output (i.e. the console or terminal).

### Input Format

The input file `data.txt` consists of pairs of floating-point values, with each pair on a new line.  Continue reading values until the end of the file.

### Output Format

The slope and intercept should be printed on a single line, separated by a space, with a precision of two decimal places.

---
### Sample Input

`data.txt`:
```default
0.655596 0.78162
0.180574 0.0929678
0.777239 0.739358
0.983658 0.957803
0.272991 0.353709
```

### Sample Output

```default
1.00 0.01
```
---

### Hint:

You may need to make multiple passes through the file.
