## 【题意简述】

在本题当中，你需要设法描述一个表达式的计算过程。这个表达式可能含有四则运算（加、减、乘、除，不会出现负号）、括号、函数调用（普通函数调用和成员函数调用），和一些常量。

例如，`(a+f((b-c+e)*d/c.h(d,d)).g(e)).g(d).h(f(a,c),f(b)/f(c),f(d))`就是一个可能出现的表达式，其中`a`,`b`,`c`,`d`,`e`是常量，`f`是普通函数，`g`,`h`是成员函数。

运算的优先级为：括号>函数调用>乘除法>加减法。注意运算的优先级的大小不代表计算顺序的先后。

你不需要求出这个表达式的具体值，你只需要描述它的计算过程，即将这个表达式分解为若干次四则运算与函数调用，且每次运算或调用的操作数都是常量或之前的运算或调用的结果。

你**可能**需要一些编译原理的相关知识来解决这道题目。

## 【表达式的定义】

首先，一个常量、普通函数、成员函数只可能是一个小写英文字母。在任何一个表达式中，一个字母至多只可能是常量、普通函数、成员函数的一种。

我们用递归的方式定义合法的表达式：

- 单独的一个常量是一个合法的表达式。
- 如果`[EXPR]`是一个合法的表达式，那么`([EXPR])`是一个合法的表达式，其值与`[EXPR]`相同。
- 如果`[EXPR_1]`、`[EXPR_2]`、……、`[EXPR_n]`是$n$个合法的表达式（$n$至少为$1$），`[FUNC]`是一个普通函数，那么`[FUNC]([EXPR_1],[EXPR_2],……,[EXPR_n])`是一个合法的表达式，其值为将`[EXPR_1]`、`[EXPR_2]`、……、`[EXPR_n]`依次作为参数，调用普通函数`[FUNC]`所得的结果。注意同一个函数在不同的调用中可能接受不同个数的参数。
- 如果`[EXPR]`是一个**上述三条规则或本条规则或本条规则**定义的一个合法的表达式，`[EXPR_1]`、`[EXPR_2]`、……、`[EXPR_n]`是$n$个合法的表达式（$n$至少为$1$），`[FUNC]`是一个成员函数，那么`[EXPR].[FUNC]([EXPR_1],[EXPR_2],……,[EXPR_n])`是一个合法的表达式，其值为将`[EXPR_1]`、`[EXPR_2]`、……、`[EXPR_n]`依次作为参数，调用`[EXPR]`的成员函数`[FUNC]`所得的结果。注意同一个函数在不同的调用中可能接受不同个数的参数。
- 如果`[EXPR_0]`、`[EXPR_1]`、……、`[EXPR_n]`是$n+1$个**上述四条规则**定义的合法的表达式（$n$至少为$1$），`[OPR_1]`、`[OPR_2]`、……、`[OPR_n]`是$n$个乘号或除号运算符，那么`[EXPR_0][OPR_1][EXPR_1][OPR_2]……[OPR_n][EXPR_n]`是一个合法的表达式，其值为将`[EXPR_0]`、`[EXPR_1]`、……、`[EXPR_n]`依次进行`[OPR_1]`、`[OPR_2]`、……、`[OPR_n]`运算的结果。
- 如果`[EXPR_0]`、`[EXPR_1]`、……、`[EXPR_n]`是$n+1$个**上述五条规则**定义的合法的表达式（$n$至少为$1$），`[OPR_1]`、`[OPR_2]`、……、`[OPR_n]`是$n$个加号或减号运算符，那么`[EXPR_0][OPR_1][EXPR_1][OPR_2]……[OPR_n][EXPR_n]`是一个合法的表达式，其值为将`[EXPR_0]`、`[EXPR_1]`、……、`[EXPR_n]`依次进行`[OPR_1]`、`[OPR_2]`、……、`[OPR_n]`运算的结果。
- 只有符合以上几条定义的表达式才是合法的。

容易看到，这样定义的每个合法的表达式都有唯一一种解读方式，即不会引起歧义。

## 【计算顺序的规定】

上述规定确定了一个表达式的值，接下来我们确定一个表达式的求值顺序。我们用与定义类似的方式规定这个顺序：

- 对于单独的一个常量，不需要计算。
- 对于`([EXPR])`，只需计算`[EXPR]`。
- 对于`[FUNC]([EXPR_1],[EXPR_2],……,[EXPR_n])`，先依次计算`[EXPR_1]`、`[EXPR_2]`、……、`[EXPR_n]`，再调用`[FUNC]`。
- 对于`[EXPR].[FUNC]([EXPR_1],[EXPR_2],……,[EXPR_n])`，先依次计算`[EXPR]`、`[EXPR_1]`、`[EXPR_2]`、……、`[EXPR_n]`，再调用`[FUNC]`。
- 对于`[EXPR_0][OPR_1][EXPR_1][OPR_2]……[OPR_n][EXPR_n]`（其中`[OPR_1]`、`[OPR_2]`、……、`[OPR_n]`全为乘除或全为加减），先计算`[EXPR_0]`，再计算`[EXPR_1]`，再调用`[OPR_1]`得出中间结果，再计算`[EXPR_2]`，再用上述中间结果和`[EXPR_2]`的结果调用`[OPR_2]`……直到计算完毕。

可以看出，除函数外，上述运算顺序均与我们日常使用的顺序相同；函数的运算顺序在不同的标准中不同，这里我们规定为从左至右。

## 【输入格式】

输入文件只有一行（以换行符结束），只包含一个需要处理的表达式。

表达式的长度不超过 $100$，不会出现任何空格等多余字符。

## 【输出格式】

按计算顺序输出每一次的运算符与函数调用。每次调用的参数只能是常量或之前某一次的运算结果，其中运算结果我们用从小到大的正整数依次表示。即：我们用单个英文字母（与输入中的相同）表示一个常量，用一个正整数表示之前某一次的运算结果，设第$i$次的调用产生的结果为$i$。

以下用`[VALUE]`表示一个参数，`[OPR]`表示一个运算符，`[FUNC]`表示一个函数。

如果是运算符调用，设这次要计算的是`[VALUE_1][OPR][VALUE_2]`，则你需要输出一行`[OPR][空格][VALUE_1][空格][VALUE_2]`。

如果是普通函数调用，设这次要计算的是`[FUNC]([VALUE_1],[VALUE_2],……,[VALUE_n])`，则你需要输出一行`[FUNC][空格][VALUE_1][空格][VALUE_2][空格]……[空格][VALUE_n]`。

如果是成员函数调用，设这次要计算的是`[VALUE_0].[FUNC]([VALUE_1],[VALUE_2],……,[VALUE_n])`，则你需要输出一行`[FUNC][空格][VALUE_0][空格][VALUE_1][空格][VALUE_2][空格]……[空格][VALUE_n]`。

## 【样例1】

### 输入

```
(a+f((b-c+e)*d/c.h(d,d)).g(e)).g(d).h(f(a,c),f(b)/f(c),f(d))
```

### 输出

```
- b c
+ 1 e
* 2 d
h c d d
/ 3 4
f 5
g 6 e
+ a 7
g 8 d
f a c
f b
f c
/ 11 12
f d
h 9 10 13 14
```

### 说明

```
- b c         //  1  b-c
+ 1 e         //  2  b-c+e
* 2 d         //  3  (b-c+e)*d
h c d d       //  4  c.h(d,d)
/ 3 4         //  5  (b-c+e)*d/c.h(d,d)
f 5           //  6  f((b-c+e)*d/c.h(d,d))
g 6 e         //  7  f((b-c+e)*d/c.h(d,d)).g(e)
+ a 7         //  8  a+f((b-c+e)*d/c.h(d,d)).g(e)
g 8 d         //  9  (a+f((b-c+e)*d/c.h(d,d)).g(e)).g(d)
f a c         // 10  f(a,c)
f b           // 11  f(b)
f c           // 12  f(c)
/ 11 12       // 13  f(b)/f(c)
f d           // 14  f(d)
h 9 10 13 14  // 15  (a+f((b-c+e)*d/c.h(d,d)).g(e)).g(d).h(f(a,c),f(b)/f(c),f(d))
```

## 【样例2】

### 输入

```
a+b+c+d+e*f*g*h*i*(j-k-l-m-n)
```

### 输出

```
+ a b
+ 1 c
+ 2 d
* e f
* 4 g
* 5 h
* 6 i
- j k
- 8 l
- 9 m
- 10 n
* 7 11
+ 3 12
```

## 【样例3】

### 输入

```
(a+a+a)+a+a+a+(a+a+a)
```

### 输出

```
+ a a
+ 1 a
+ 2 a
+ 3 a
+ 4 a
+ a a
+ 6 a
+ 5 7
```

## 【测试点】

测试点1：包含常量、加减号

测试点2：包含常量、四则运算符

测试点3：包含常量、加减号、括号

测试点4：包含常量、四则运算符、括号

测试点5：包含常量、普通函数调用

测试点6：包含常量、成员函数调用

测试点7：包含常量、普通函数调用、成员函数调用、括号

测试点8：包含常量、四则运算符、普通函数调用、括号

测试点9：包含常量、四则运算符、成员函数调用、括号

测试点10：包含常量、四则运算符、普通函数调用、成员函数调用、括号

| 我    |      |      |
| ---- | ---- | ---- |
| 是    |      |      |
| 一    |      |      |
| 个    | 表    | 格    |

```c++
#include <iostream>
struct Point{
  double x, y;
}point;
int main(){
  std::cin >> point.x >> point.y;
  return 0;
}
```

![UOJ_small](http://uoj.ac/pictures/UOJ_small.png)

<table class="table table-bordered table-hover table-striped table-text-center"><thead><tr><th>ID</th><th>题目</th><th>提交者</th><th>结果</th><th>用时</th><th>内存</th><th>语言</th><th>文件大小</th><th>提交时间</th></tr></thead><tbody><tr><td><a href="/submission/109670">#109670</a></td><td><a href="/problem/149">#149. 【NOIP2015】子串</a></td><td><a class="uoj-username" href="http://uoj.ac/user/profile/DraZxlNDDt" style="color:rgb(75,175,178)">DraZxlNDDt</a></td><td><a href="/submission/109670" class="uoj-score" style="color: rgb(230, 207, 0);">40</a></td><td>112ms</td><td>3284kb</td><td><a href="/submission/109670">C++</a></td><td>814b</td><td><small>2016-11-17 21:49:25</small></td></tr><tr><td><a href="/submission/109669">#109669</a></td><td><a href="/problem/17">#17. 【NOIP2014】飞扬的小鸟</a></td><td><a class="uoj-username" href="http://uoj.ac/user/profile/rabbit_lb" style="color:rgb(71,185,157)">rabbit_lb</a></td><td><a href="/submission/109669" class="uoj-score" style="color: rgb(218, 230, 0);">55</a></td><td>78ms</td><td>27768kb</td><td><a href="/submission/109669">C++</a></td><td>1.4kb</td><td><small>2016-11-17 21:47:47</small></td></tr><tr><td><a href="/submission/109668">#109668</a></td><td><a href="/problem/146">#146. 【NOIP2015】信息传递</a></td><td><a class="uoj-username" href="http://uoj.ac/user/profile/cytusbox" style="color:rgb(75,175,178)">cytusbox</a></td><td><a href="/submission/109668" class="uoj-score" style="color: rgb(0, 204, 0);">100</a></td><td>182ms</td><td>7544kb</td><td><a href="/submission/109668">C++</a></td><td>1005b</td><td><small>2016-11-17 21:44:02</small></td></tr><tr><td><a href="/submission/109667">#109667</a></td><td><a href="/problem/145">#145. 【NOIP2015】神奇的幻方</a></td><td><a class="uoj-username" href="http://uoj.ac/user/profile/cytusbox" style="color:rgb(75,175,178)">cytusbox</a></td><td><a href="/submission/109667" class="uoj-score" style="color: rgb(0, 204, 0);">100</a></td><td>2ms</td><td>1240kb</td><td><a href="/submission/109667">C++</a></td><td>470b</td><td><small>2016-11-17 21:39:26</small></td></tr><tr><td><a href="/submission/109666">#109666</a></td><td><a href="/problem/147">#147. 【NOIP2015】斗地主</a></td><td><a class="uoj-username" href="http://uoj.ac/user/profile/cytusbox" style="color:rgb(75,175,178)">cytusbox</a></td><td><a href="/submission/109666" class="uoj-score" style="color: rgb(0, 204, 0);">100</a></td><td>114ms</td><td>516kb</td><td><a href="/submission/109666">C++</a></td><td>2.8kb</td><td><small>2016-11-17 21:37:30</small></td></tr><tr><td><a href="/submission/109665">#109665</a></td><td><a href="/problem/148">#148. 【NOIP2015】跳石头</a></td><td><a class="uoj-username" href="http://uoj.ac/user/profile/cytusbox" style="color:rgb(75,175,178)">cytusbox</a></td><td><a href="/submission/109665" class="uoj-score" style="color: rgb(0, 204, 0);">100</a></td><td>110ms</td><td>1376kb</td><td><a href="/submission/109665">C++</a></td><td>510b</td><td><small>2016-11-17 21:34:30</small></td></tr><tr><td><a href="/submission/109664">#109664</a></td><td><a href="/problem/150">#150. 【NOIP2015】运输计划</a></td><td><a class="uoj-username" href="http://uoj.ac/user/profile/cytusbox" style="color:rgb(75,175,178)">cytusbox</a></td><td><a href="/submission/109664" class="uoj-score" style="color: rgb(122, 230, 0);">97</a></td><td>1445ms</td><td>73416kb</td><td><a href="/submission/109664">C++</a></td><td>3.0kb</td><td><small>2016-11-17 21:29:06</small></td></tr><tr><td><a href="/submission/109663">#109663</a></td><td><a href="/problem/1">#1. A + B Problem</a></td><td><a class="uoj-username" href="http://uoj.ac/user/profile/cytusbox" style="color:rgb(75,175,178)">cytusbox</a></td><td><a href="/submission/109663" class="uoj-score" style="color: rgb(0, 204, 0);">100</a></td><td>3ms</td><td>1196kb</td><td><a href="/submission/109663">C++</a></td><td>113b</td><td><small>2016-11-17 21:28:46</small></td></tr><tr><td><a href="/submission/109662">#109662</a></td><td><a href="/problem/150">#150. 【NOIP2015】运输计划</a></td><td><a class="uoj-username" href="http://uoj.ac/user/profile/orzNanoApe" style="color:rgb(65,194,114)">orzNanoApe</a></td><td><a href="/submission/109662" class="uoj-score" style="color: rgb(0, 204, 0);">100</a></td><td>1299ms</td><td>51516kb</td><td><a href="/submission/109662">C++</a></td><td>2.3kb</td><td><small>2016-11-17 21:24:50</small></td></tr><tr><td><a href="/submission/109661">#109661</a></td><td><a href="/problem/17">#17. 【NOIP2014】飞扬的小鸟</a></td><td><a class="uoj-username" href="http://uoj.ac/user/profile/zrnlkc" style="color:rgb(64,195,110)">zrnlkc</a></td><td><a href="/submission/109661" class="uoj-score" style="color: rgb(172, 230, 0);">75</a></td><td>283ms</td><td>40848kb</td><td><a href="/submission/109661">C++</a></td><td>1.0kb</td><td><small>2016-11-17 21:22:14</small></td></tr></tbody></table>

<a href="www.baidu.com">百度一下，你就中毒</a>
$$
\frac{-b\pm\sqrt{b^2-4ac}}{2a} \\
O\left( n^{\sqrt{\log n}} \right) \\
\left|
\begin{matrix}
 2& -1&  0 \\
-1&  3& -1 \\
-1& -1&  3
\end{matrix}
\right| = 12
$$
