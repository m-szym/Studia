#define _CRT_SECURE_NO_WARNINGS
#pragma once

const int SECTIONS_PACKAGE_SIZE = 13;
const int BASE_STRING_BUFFER_SIZE = 5;

const int FLAG_CSS_MODE = 0;
const int FLAG_COMMAND_MODE = 1;
const int FLAG_OTHER = 3;

const int CHANGE_MODE_SYMBOLS_NUMBER = 4;
const char ENTER_CSS_MODE_SYMBOL = '*';
const char ENTER_COMMAND_MODE_SYMBOL = '?';

const char STOP_READING_SELECTORS_SYMBOL = '{';
const char STOP_READING_ATTRIBUTES_SYMBOL = '}';