# Input & output

## output

`printf("%d", i);`

`d` repretsent the format specicifier for integers.
using an incorrent specifier for vartiable will print trash.

{%c:char, %d:integer, %f:float, %s:string, %p:address, ...}

`fputs(<result>, <file>);`

write on the output file (can be `stdout`)

## input

`int var; scanf('%d', &var);`

to ask in terminal to user for the input

`fgets(<where>, <size>, <from>)`

for reading for files or stdin

---

# Arrays

- declared and initizilized as `<type> <name>[<size>] = {<values>}`
- accesed by index form 0
- Multidimensional declared/initialized ad `<type> <name>[<rows>][<cols>] = {<values>}` where values can be separated by braces or not. they are read and allocated left to right and up to above

# Pointers

- * used for declaration as `<type> *<name>` and derefecene as <*ptr>
- & is memory operator tog et address from an object
- `int *ptr = NULL` to point to anything of type int
- pointers has their own arithmetic to move among addreses
- `int (*fptr)(int, int)` points to a function with address `&funct` with signature of int return value and two int arguments. calls like this `fptr(x, y)` 
- we can point to other pointers and declare for example `int **ptr2 = &ptr1` to point with a point to other int pointer

# Strings

- are arrays of strings, but simplified to not to write by char. we can directly initialize `char str[] = "some string"` internally is ` { 'G', 'e', 'e', 'k', 's', '\0'}`
- are bassically arrays, so all their operators apply, and the librariers provide functions for easy access to len, copy, concat or other operations of strings.
- in `scanf("%19[^\n]", str);` that specifications is called scanset to read specific things due to limitations of scanf()
- fgets() reads until new line
- string literals are constars char arrays initilized like `const char *str = "some string"`

# User-defined data types

## Structure

- defined as 
```c
struct structure_name {
    data_type member_name1;
    data_type member_name1;
    ....
    ....
};
```
- accesed like `structure_name.member_name1`

## Union

- similar to struct with same syntax but use and internal logic to store in members in the same location. So the size of the union is eqaul to the largets data type between members

## Enums

- set of named constants `enum enum_name {const1, const2, ..., constN};`

## Typedef

- `typedef existing_name alias_name;` used to redfine the data type of data type
