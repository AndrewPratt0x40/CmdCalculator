# CmdCalculator
A command-line calculator written in C++

## Command-line arguments
- `-e <value>`: The expression to calculate. If this is omitted, the user will be prompted to enter an expression instead.
- `-p <value>`: The maximum amount of digits to display after the decimal point.
- `-d`: Prefer decimals over integers in output. Incompatible with `-D`.
- `-D`: Prefer integers over decimals in output. Incompatible with `-d`.
- `-s`: Prefix positive values with a sign operator in output. Incompatible with `-S`.
- `-S`: Don't prefix positive values with a sign operator in output. Incompatible with `-s`.
- `-l`: Prefer a leading zero over nothing to the left of the decimal point in output. Incompatible with `-L`.
- `-l`: Prefer nothing over a leading zero to the left of the decimal point in output. Incompatible with `-l`.
- `-t`: Prefer a trailing zero over nothing to the right of the decimal point in output. Incompatible with `-T`.
- `-T`: Prefer nothing over a trailing zero to the right of the decimal point in output. Incompatible with `-t`.


## Expression syntax
Numbers may be written as integers or decimals.
Leading and trailing zeros are optional.
All whitespace in the expression will be ignored.

The following operators are available:
|Operator|Name|Example|Evaluation of Example|
|-|-|-|-|
|`+`|Addition|`7+3`|$7+3=10$|
|`-`|Subtraction|`7-3`|$7-3=-4$|
|`*`|Multiplication|`7*3`|$7*3=21$|
|`/`|Division|`7/3`|$\frac{7}{3}=2.333...$|
|`^`|Exponentiation|`7^3`|$7^3=343$|
|`_`|Nth Root|`7_3`|$\sqrt[7]{3}=3\approx 1.17$|
|`sqrt`|Square Root|`sqrt 64`|$\sqrt{64}=8$|
|`%`|Modulo|`7%3`|$7\mod 3=1$|