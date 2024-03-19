# Mockup For Program Execution

## Basic usage

Entering a number:
```
> CmdCalculator.exe
Enter an expression: 0
= 0
> _
```

Calculating 2 + 2:
```
> CmdCalculator.exe
Enter an expression: 2+2
= 4
> _
```

Calculating 2 + 2 with extra whitespace:
```
> CmdCalculator.exe
Enter an expression:    2 +   2  
= 4
> _
```

Calculating a complicated expression:
```
> CmdCalculator.exe
Enter an expression: 1 + 98.76 + (4^(-3/4))_2 * 3(12 % 5 - sqrt 4) / (2.0 + (15 / 2)) + 12. * 6_5 - .3
= 116.631628973
> _
```

## Command-line arguments

Given expression:
```
> CmdCalculator.exe -e "2 + 2"
= 4
> _
```

Specific precision:
```
> CmdCalculator.exe -p 3 -e ".123456789"
= 0.123
> _
```

Prefer decimals over integers:
```
> CmdCalculator.exe -d -e "2 + 2"
= 4.0
> _
```

Prefer integers over decimals:
```
> CmdCalculator.exe -D -e "2 + 2"
= 4
> _
```

Prefer signed expressions for positive values:
```
> CmdCalculator.exe -s -e "2 + 2"
= +4
> _
```

Prefer unsigned expressions for positive values:
```
> CmdCalculator.exe -S -e "2 + 2"
= 4
> _
```

Include leading zero for numbers who's absolute value is between zero and one, exclusive:
```
> CmdCalculator.exe -l -e "1 / 2"
= 0.2
> _
```

Exclude leading zero for numbers who's absolute value is between zero and one, exclusive:
```
> CmdCalculator.exe -L -e "1 / 2"
= .2
> _
```

Include trailing zero for integers:
```
> CmdCalculator.exe -d -t -e "2 + 2"
= 4.0
> _
```

Exclude trailing zero for integers:
```
> CmdCalculator.exe -d -T -e "2 + 2"
= 4.
> _
```

## Errors

Unrecognized command-line argument:
```
> CmdCalculator.exe -d -e "a" helloWorld -S
Unrecognized command-line argument "helloWorld"
> _
```

Invalid precision:
```
> CmdCalculator.exe -p hi -e "2 + 2"
Invalid precision value "hi", must be a non-negative integer
> _
```

Missing argument:
```
> CmdCalculator.exe -e
Expected a value for parameter "-e"
> _
```

Invalid expression followed by valid expression:
```
> CmdCalculator.exe
Enter an expression: a
Unexpected character "a" at column 1

Enter an expression: 2 + 2
= 4
> _
```

Divide by zero:
```
> CmdCalculator.exe -e "1 / 0 + 6"
Cannot divide by zero at column 3
	After: "1 "
	Before: " 0 + 6"
> _
```

Overflow:
```
> CmdCalculator.exe -e "10^999999"
Overflow
> _
```

Underflow:
```
> CmdCalculator.exe -e "10_999999"
Underflow
> _
```

Invalid given expression:
```
> CmdCalculator.exe -e "a"
Unexpected character "a" at column 1
> _
```

Unexpected characters:
```
> CmdCalculator.exe
Enter an expression: a
Unexpected character "a" at column 1

Enter an expression: abc
Unexpected character "a" at column 1
	Before: "bc"

Enter an expression: 12a
Unexpected character "a" at column 3
	After: "12"

Enter an expression: 12a34
Unexpected character "a" at column 3
	After: "12"
	Before: "34"

Enter an expression: 1 + 2 - 3 * 4 / a + 6 - 7 * 8 / 9
Unexpected character "a" at column 17
	After: "...3 * 4 / "
	Before: " + 6 - 7..."

Enter an expression: 
```

Empty Expression:
```
> CmdCalculator.exe
Enter an expression: 
Expression cannot be empty

Enter an expression: 
```

Missing operator:
```
> CmdCalculator.exe
Enter an expression: 1 +
Expected a right operand for the "+" operator at column 3
	After: "1 "

Enter an expression: 
```

Missing closing bracket:
```
> CmdCalculator.exe
Enter an expression: 1 + ( 2 + 3
Expected a closing ")" for the group started by the "(" at column 5
	After: "1 + "
	Before: " 2 + 3"

Enter an expression: 1 + | 2 + 3
Expected a closing "|" for the absolute value operation started by the "|" at column 5
	After: "1 + "
	Before: " 2 + 3"

Enter an expression: 
```

Unexpected closing bracket:
```
> CmdCalculator.exe
Enter an expression: 1 + 2 ) + 3
Unexpected closing ")" at column 7
	After: "1 + 2 "
	Before: " + 3"
```