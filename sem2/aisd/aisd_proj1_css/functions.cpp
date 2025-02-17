#include "functions.h"

char* read_command(int& flag)
{
    int current_char = '\0';
    char* command = (char*)malloc(BASE_STRING_BUFFER_SIZE * sizeof(char));
    char* string_buffer = NULL;

    int number_of_chars_read = 0;
    int char_array_size = BASE_STRING_BUFFER_SIZE;
    int not_EOF_chars_read = 0;

    int escape_chars_in_sequence = 0;


    while (current_char != '\n')
    {
        current_char = getchar();

        if (current_char == EOF)
        {
            if (not_EOF_chars_read == 0) flag = FLAG_OTHER;
            break;
        }
        else not_EOF_chars_read++;

        if (!(current_char == '\n' || current_char == NULL || current_char == '\x00' || current_char == '\t')) {

            if (current_char == ENTER_CSS_MODE_SYMBOL)
                escape_chars_in_sequence++;
            else if (current_char != ENTER_CSS_MODE_SYMBOL && escape_chars_in_sequence > 0)
                escape_chars_in_sequence = 0;
            if (escape_chars_in_sequence >= 4 && number_of_chars_read >= 3)
            {
                flag = FLAG_CSS_MODE;
                //free(command);
                return NULL;
            }

            if (current_char) {
                number_of_chars_read++;

                if (number_of_chars_read >= char_array_size) 
                {
                    string_buffer = (char*)realloc(command, 2 * char_array_size * sizeof(char));
                    char_array_size = 2 * char_array_size;

                    if (string_buffer != NULL) 
                    {
                        command = string_buffer;
                        command[number_of_chars_read - 1] = (char) current_char;
                    }
                }
                else 
                {
                    command[number_of_chars_read - 1] = (char)current_char;
                }
            }
        }
    };

    if (command != NULL) command[number_of_chars_read] = '\0';
    return command;
}
char* read_attr(int& flag)
{
    int current_char = '\0';
    char* string_of_attributes = (char*)malloc(BASE_STRING_BUFFER_SIZE * sizeof(char));
    char* string_buffer = NULL;

    int number_of_chars_read = 0;
    int char_array_size = BASE_STRING_BUFFER_SIZE;
    int not_EOF_chars_read = 0;


    while (current_char != STOP_READING_ATTRIBUTES_SYMBOL)
    {

        current_char = getchar();
        if (current_char == EOF)
        {
            if (not_EOF_chars_read == 0) flag = FLAG_OTHER;
            //free(string_of_attributes);
            break;
        }
        else not_EOF_chars_read++;

        if (current_char == STOP_READING_ATTRIBUTES_SYMBOL) 
            break;

        if (!(current_char == STOP_READING_ATTRIBUTES_SYMBOL || current_char == '\n' || current_char == NULL || current_char == '\t' || current_char == '\x00'))
        {
            number_of_chars_read++;

            if (number_of_chars_read >= char_array_size)
            {
                string_buffer = (char*)realloc(string_of_attributes, 2 * char_array_size * sizeof(char));
                char_array_size = 2 * char_array_size;
                if (string_buffer != NULL) {
                    string_of_attributes = string_buffer;
                    string_of_attributes[number_of_chars_read - 1] = (char)current_char;
                }
            }
            else {
                string_of_attributes[number_of_chars_read - 1] = (char)current_char;
            }
        }
    };

    string_of_attributes[number_of_chars_read] = '\0';
    return string_of_attributes;
}
char* read_sel(int& flag)
{
    int current_char = '\n';
    char* string_of_selectors = (char*)malloc(BASE_STRING_BUFFER_SIZE * sizeof(char));
    char* string_buffer = NULL;

    int number_of_chars_read = 0;
    int char_array_size = BASE_STRING_BUFFER_SIZE;
    int escape_chars_in_sequence = 0;

    while (current_char != STOP_READING_SELECTORS_SYMBOL)
    {
        current_char = getchar();
        if (current_char == EOF) 
        {
            flag = FLAG_OTHER;
            //free(string_of_selectors);
            return NULL;
        }

        if (current_char == STOP_READING_SELECTORS_SYMBOL)
            break;

        if (current_char == ENTER_COMMAND_MODE_SYMBOL)
            escape_chars_in_sequence++;
        else if (current_char != ENTER_COMMAND_MODE_SYMBOL && escape_chars_in_sequence > 0)
            escape_chars_in_sequence = 0;

        if (escape_chars_in_sequence >= CHANGE_MODE_SYMBOLS_NUMBER && number_of_chars_read <= CHANGE_MODE_SYMBOLS_NUMBER - 1)
        {
            //free(string_of_selectors);
            flag = FLAG_COMMAND_MODE;
            return NULL;
        }


        if (!(current_char == STOP_READING_ATTRIBUTES_SYMBOL || current_char == '\n' || current_char == NULL || current_char == '\t' || current_char == '\x00' || current_char < ' '))
        {
            number_of_chars_read++;

            if (number_of_chars_read >= char_array_size)
            {
                string_buffer = (char*)realloc(string_of_selectors, 2 * char_array_size * sizeof(char));
                char_array_size = 2 * char_array_size;
                if (string_buffer != NULL) 
                {
                    string_of_selectors = string_buffer;
                    string_of_selectors[number_of_chars_read - 1] = current_char;
                }
            }
            else 
            {
                string_of_selectors[number_of_chars_read - 1] = (char)current_char;
            }
        }


    };

    string_of_selectors[number_of_chars_read] = '\0';


    return string_of_selectors;
}

bool is_number(char* string)
{
    int number_characters = 0;

    for (int i = 0; i < strlen(string); ++i) 
    {
        if (isdigit(string[i]) != 0) number_characters++;
    }

    if (number_characters == strlen(string)) return true;
    else return false;
}

Section* get_nth_notempty_section(int n, List2d<Sections_Package>* root) {
    List2d<Sections_Package>* section_package_of_nth_notempty_section = root->next;
    Section* nth_notempty_section_to_return = nullptr;

    while (n > 0) 
    {
        if (section_package_of_nth_notempty_section == nullptr) return nullptr;
        for (int i = 0; i < SECTIONS_PACKAGE_SIZE && n > 0; i++)
        {
            if (section_package_of_nth_notempty_section->cont->sections[i].not_empty)
            {
                nth_notempty_section_to_return = &(section_package_of_nth_notempty_section->cont->sections[i]);
                n--;
            }
        }
        section_package_of_nth_notempty_section = section_package_of_nth_notempty_section->next;
    }
    return nth_notempty_section_to_return;
}
List2d<Sections_Package>* get_sections_package_of_nth_notempty_section(int n, List2d<Sections_Package>* root) {
    List2d<Sections_Package>* sections_package_to_return = root->next;
    Section* nth_not_empty_section = nullptr;

    while (n > 0) 
    {
        if (sections_package_to_return == nullptr) return nullptr;

        for (int i = 0; i < SECTIONS_PACKAGE_SIZE && n > 0; i++)
        {
            if (sections_package_to_return->cont->sections[i].not_empty)
            {
                nth_not_empty_section = &(sections_package_to_return->cont->sections[i]);
                n--;
            }
            if (n == 0) return sections_package_to_return;
        }
        sections_package_to_return = sections_package_to_return->next;
    }
    return sections_package_to_return;
}

int count_all_select_selectors(List2d<Sections_Package>* root, const char* name) {
    int c = 0;
    List2d<Selector>* selnode = nullptr;

    root = root->next;
    
    while (root != nullptr) {
        for (int i = 0; i < SECTIONS_PACKAGE_SIZE; ++i)
        {
            if (root->cont->sections[i].not_empty)
            {
                if (root->cont->sections[i].get_selector_by_name(name) != nullptr) c++;
            }
        }
        root = root->next;
    }
    return c;
}
int count_all_select_attributes(List2d<Sections_Package>* root, const char* name) 
{
    int c = 0;
    Attribute* att = nullptr;

    root = root->next;

    while (root != nullptr) 
    {
        for (int i = 0; i < SECTIONS_PACKAGE_SIZE; ++i)
        {
            if (root->cont->sections[i].not_empty)
            {
                if (root->cont->sections[i].get_attribute_by_name(name)) c++;
            }
        }
        root = root->next;
    }
    return c;
}