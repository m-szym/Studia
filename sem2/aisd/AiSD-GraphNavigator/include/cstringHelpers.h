#pragma once

#include <cstring>
#include <cctype>
#include <cstdio>
#include <cstdlib>

// This file contains various helper functions for working with cstrings used in the program.

const int BASE_STRING_BUFFER_SIZE = 32; // The base size of the buffer used to read strings from the standard input.

// Checks if the given (null terminated) cstring represents a number (i.e. contains only digits and possibly a newline character at the end)
// Used in checking the validity of input.
bool isNumber(char* string);

// Reads a string from the standard input and returns pointer to the null terminated array of chars, with all non-ASCII characters omitted.
// Used in reading the input from the user.
// For speed reasons getchar() is used to read 1 char at a time.
// Only ASCII characters are supported and others are omitted from in the otuput cstring.
// Uses dynamically resized buffer, with the beginning size of BASE_STRING_BUFFER_SIZE.
// The buffer is resized by doubling its size when it's full.
// The buffer is freed by the caller.
// Many intricacies of this function are a result of the project requirements and are not the best way to implement this function.
char* readString();

// Splits the (null terminated) cstring into tokens using the given delimiter and returns array of tokens.
// Used in parsing the input from the user.
// Simply a convenience wrapper around strtok() function.
char** tokenizeString(char* string, char* delimiter, int& tokens);