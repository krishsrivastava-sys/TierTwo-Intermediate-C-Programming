# The Comma Operator in C

> The Comma operator in C evaluates both the sides, but returns only right hand of it.

### ✅ **Definition of the Comma Operator**

In C, the **comma operator** evaluates *both* of its operands **from left to right**, but **returns the value of the right-hand operand**.

So:

```c
a = (b = 10, c = b + 5);
```

is treated like:

1. Evaluate `b = 10` → result: `10` (but we don't use this value)
2. Then evaluate `c = b + 5` → result: `15` (this becomes the value of the whole comma expression)
3. Assign the result (`15`) to `a`

---

### 🔁 So why not return `b = 10`?

Because the comma operator **always returns the last (rightmost) expression**.

This is built into the language design. In a general expression:

```c
X = (expr1, expr2, expr3, ..., exprN);
```

The value assigned to `X` is the **value of `exprN`** — the last expression — regardless of what the earlier expressions are.

---

### 📌 Example:

```c
int x, y, z;
x = (y = 1, z = 2);  // x = 2, because z = 2 is the final value
```

Even though `y = 1` happens, only `z = 2` is the value returned from the whole comma expression.

---

### 🤓 Side Note:

If you wanted `a` to get the value of `b` instead, you'd write:

```c
a = (c = (b = 10) + 5, b);
```

Then:

* `b = 10`
* `c = b + 5 = 15`
* `(c = ..., b)` → evaluates to `b`, which is 10
* `a = 10`

---

Let me know if you want more examples or want to try rewriting it more readably.
