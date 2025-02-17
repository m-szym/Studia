#define _CRT_SECURE_NO_WARNINGS

#include "includes.h"
#include "commands.h"

struct m
{
    List2d<Sections_Package> master_list;
    char* main_string;
    char* substring_1;
    char* substring_2;
    char* substring_3;
    int flag;
    List2d<Sections_Package>* current_master_list_node;
    Sections_Package* current_package;
    Section* current_section;
};

void css_mode(m& ma);
void command_mode(m& ma);

int main()
{
    /**/
    List2d<Sections_Package> mlist;
    char* s = NULL;
    char* pch2 = NULL;
    char* pch = NULL;
    char* pch3 = NULL;
    int flag = 0;
    mlist.add_after(new Sections_Package);
    List2d<Sections_Package>* lnode = mlist.next;
    Sections_Package* current_package = mlist.next->cont;
    Section* current_section = mlist.next->cont->get_next_empty_section();

    m ma;
    ma.main_string = NULL;
    ma.substring_1 = NULL;
    ma.substring_2 = NULL;
    ma.substring_3 = NULL;
    ma.flag = 0;

    ma.master_list.add_after(new Sections_Package);
    ma.current_master_list_node = ma.master_list.next;
    ma.current_package = ma.current_master_list_node->cont;
    ma.current_section = ma.current_package->get_next_empty_section();
    
    while (std::cin)
    {
        //if (mlist.next == nullptr)
        //{
        //    mlist.add_after(new Sections_Package);
        //    mlist.add_after(new Sections_Package);
        //    lnode = mlist.next;
        //    current_package = mlist.next->cont;
        //    current_section = mlist.next->cont->get_next_empty_section();
        //}

        //if (lnode == nullptr) {
        //    mlist.add_at_end(new Sections_Package);
        //    lnode = mlist.get_last();
        //    current_package = lnode->cont;
        //    current_section = current_package->get_next_empty_section();
        //}

        if (ma.master_list.next == nullptr)
        {
            ma.master_list.add_after(new Sections_Package);
            ma.master_list.add_after(new Sections_Package);
            ma.current_master_list_node = mlist.next;
            ma.current_package = ma.master_list.next->cont;
            ma.current_section = ma.master_list.next->cont->get_next_empty_section();
        }

        if (ma.current_master_list_node == nullptr) {
            ma.master_list.add_at_end(new Sections_Package);
            ma.current_master_list_node = ma.master_list.get_last();
            ma.current_package = ma.current_master_list_node->cont;
            ma.current_section = ma.current_package->get_next_empty_section();
        }

        //wczytujemy selektory
        if (ma.flag == FLAG_CSS_MODE)  
        {
        //if (flag == FLAG_CSS_MODE)
        //{
        //    
        //    if (current_package != nullptr) {
        //        current_section = current_package->get_next_empty_section();
        //        if (current_section == nullptr)
        //        {
        //            lnode->add_after(new Sections_Package);
        //            if (lnode != nullptr)
        //            {
        //                lnode = lnode->next;
        //                if (lnode != nullptr) {
        //                    current_package = lnode->cont;
        //                    if (current_package != nullptr) {
        //                        current_section = current_package->get_next_empty_section();
        //                    }
        //                }
        //            }
        //        }
        //    }
        //    s = read_sel(flag);
        //        if (flag != FLAG_CSS_MODE)
        //        {
        //            free(s);
        //            continue;
        //        }
        //        //zapisujemy selektory
        //        pch = strtok(s, ",");
        //        if (!(pch == NULL))
        //        {
        //            if (current_section != nullptr) {
        //                if (current_section->add_selector(pch) != nullptr) {
        //                    while (pch != NULL)
        //                    {
        //                        pch = strtok(NULL, ",");
        //                        if (pch == NULL)
        //                            break;
        //                        if (current_section->add_selector(pch) == nullptr) break;
        //                    }
        //                }
        //            }
        //        }
        //    //wczytujemy atrybuty
        //    free(s);
        //    s = read_attr(flag);
        //    if (s == NULL) return 0;
        //    //zapisujemy atrybuty
        //    pch = strtok(s, ":;");
        //    pch2 = strtok(NULL, ":;");
        //    if (pch != NULL && pch2 != NULL)
        //    {
        //        current_section->add_attribute(pch, pch2);
        //        while (pch != NULL)
        //        {
        //            pch = strtok(NULL, ":;");
        //            pch2 = strtok(NULL, ":;");
        //            if (pch != NULL && pch2 != NULL)
        //                current_section->add_attribute(pch, pch2);         
        //        }
        //    }
        //    free(s);
        //    current_package->filled++;
        //    
            css_mode(ma);
        }
        else if (ma.flag == FLAG_COMMAND_MODE)
        {
        /*else if (flag == FLAG_COMMAND_MODE)
        {
            s = read_command(flag);

            if (flag != FLAG_COMMAND_MODE) 
            {
                free(s);
                continue;
            }

            if (s != NULL) 
            {
                char* nss = rl_strip(s);

                pch = strtok(nss, ",");
                pch2 = strtok(NULL, ",");
                pch3 = strtok(NULL, ",");

                if (pch != NULL)
                {
                    if (strcmp("?", pch) == 0)
                    {
                        command_qm(&mlist);
                    }
                    else
                    {
                        if (pch2 != NULL && pch3 != NULL)
                        {
                            if (strcmp(pch2, "A") == 0 && strcmp(pch3, "?") == 0 && is_number(pch) == true)
                                command_iAqm(pch, &mlist);

                            else if (strcmp(pch2, "A") == 0 && strcmp(pch3, "?") == 0)
                                command_nAqm(pch, &mlist);

                            else if (strcmp(pch2, "A") == 0)
                                command_iAn(pch, pch3, &mlist);


                            else if (strcmp(pch2, "S") == 0 && strcmp(pch3, "?") == 0 && is_number(pch) == true)
                                command_iSqm(pch, &mlist);

                            else if (strcmp(pch2, "S") == 0 && is_number(pch3) == true && is_number(pch) == true)
                                command_iSj(pch, pch3, &mlist);

                            else if (strcmp(pch2, "S") == 0 && strcmp(pch3, "?") == 0)
                                command_zSqm(pch, &mlist);


                            else if (strcmp(pch2, "E") == 0)
                                command_zEn(pch, pch3, &mlist);

                            else if (strcmp(pch2, "D") == 0 && strcmp(pch3, "*") == 0 && is_number(pch) == true)
                                command_iDst(pch, &mlist, current_package, current_section, lnode);

                            else if (strcmp(pch2, "D") == 0 && is_number(pch) == true)
                                command_iDn(pch, pch3, &mlist, current_package, current_section, lnode);
                        }                       
                    }
                }
                free(nss);
            }
            free(s);*/
            command_mode(ma);
        }
        else 
            break;
    }

    mlist.root_delete_list();

    return 0;
}

void css_mode(m &ma)
{
    if (ma.current_package != nullptr) {
        ma.current_section = ma.current_package->get_next_empty_section();
        if (ma.current_section == nullptr)
        {
            ma.current_master_list_node->add_after(new Sections_Package);
            if (ma.current_master_list_node != nullptr)
            {
                ma.current_master_list_node = ma.current_master_list_node->next;
                if (ma.current_master_list_node != nullptr) {
                    ma.current_package = ma.current_master_list_node->cont;
                    if (ma.current_package != nullptr) {
                        ma.current_section = ma.current_package->get_next_empty_section();
                    }
                }
            }
        }
    }


    ma.main_string = read_sel(ma.flag);

    if (ma.flag != 0)
    {
        free(ma.main_string);
        //continue;
        return;
    }

    //zapisujemy selektory

    ma.substring_1 = strtok(ma.main_string, ",");
    if (!(ma.substring_1 == NULL))
    {
        if (ma.current_section != nullptr) {

            if (ma.current_section->add_selector(ma.substring_1) != nullptr) {
                while (ma.substring_1 != NULL)
                {
                    ma.substring_1 = strtok(NULL, ",");
                    if (ma.substring_1 == NULL)
                        break;
                    if (ma.current_section->add_selector(ma.substring_1) == nullptr) 
                        break;//return;//było break;
                }
            }
        }
    }


    //wczytujemy atrybuty
    free(ma.main_string);

    ma.main_string = read_attr(ma.flag);
    if (ma.main_string == NULL) return;      

    //zapisujemy atrybuty
    ma.substring_1 = strtok(ma.main_string, ":;");
    ma.substring_2 = strtok(NULL, ":;");
    if (ma.substring_1 != NULL && ma.substring_2 != NULL)
    {
        ma.current_section->add_attribute(ma.substring_1, ma.substring_2);

        while (ma.substring_1 != NULL)
        {
            ma.substring_1 = strtok(NULL, ":;");
            ma.substring_2 = strtok(NULL, ":;");
            if (ma.substring_1 != NULL && ma.substring_2 != NULL)
                ma.current_section->add_attribute(ma.substring_1, ma.substring_2);
        }
    }
    free(ma.main_string);
    ma.current_package->filled++;
}

void command_mode(m& ma)
{
    ma.main_string = read_command(ma.flag);

    if (ma.flag != 1)
    {
        free(ma.main_string);
        //continue;
        return;
    }

    if (ma.main_string != NULL)
    {
        char* nss = rl_strip(ma.main_string);

        ma.substring_1 = strtok(nss, ",");
        ma.substring_2 = strtok(NULL, ",");
        ma.substring_3 = strtok(NULL, ",");

        if (ma.substring_1 != NULL)
        {
            if (strcmp("?", ma.substring_1) == 0)
            {
                command_qm(&ma.master_list);
            }
            else
            {
                if (ma.substring_2 != NULL && ma.substring_3 != NULL)
                {
                    if (strcmp(ma.substring_2, "A") == 0 && strcmp(ma.substring_3, "?") == 0 && is_number(ma.substring_1) == true)
                        command_iAqm(ma.substring_1, &ma.master_list);

                    else if (strcmp(ma.substring_2, "A") == 0 && strcmp(ma.substring_3, "?") == 0)
                        command_nAqm(ma.substring_1, &ma.master_list);

                    else if (strcmp(ma.substring_2, "A") == 0)
                        command_iAn(ma.substring_1, ma.substring_3, &ma.master_list);


                    else if (strcmp(ma.substring_2, "S") == 0 && strcmp(ma.substring_3, "?") == 0 && is_number(ma.substring_1) == true)
                        command_iSqm(ma.substring_1, &ma.master_list);

                    else if (strcmp(ma.substring_2, "S") == 0 && is_number(ma.substring_3) == true && is_number(ma.substring_1) == true)
                        command_iSj(ma.substring_1, ma.substring_3, &ma.master_list);

                    else if (strcmp(ma.substring_2, "S") == 0 && strcmp(ma.substring_3, "?") == 0)
                        command_zSqm(ma.substring_1, &ma.master_list);


                    else if (strcmp(ma.substring_2, "E") == 0)
                        command_zEn(ma.substring_1, ma.substring_3, &ma.master_list);

                    else if (strcmp(ma.substring_2, "D") == 0 && strcmp(ma.substring_3, "*") == 0 && is_number(ma.substring_1) == true)
                        command_iDst(ma.substring_1, &ma.master_list, ma.current_package, ma.current_section, ma.current_master_list_node);

                    else if (strcmp(ma.substring_2, "D") == 0 && is_number(ma.substring_1) == true)
                        command_iDn(ma.substring_1, ma.substring_3, &ma.master_list, ma.current_package, ma.current_section, ma.current_master_list_node);
                }
            }
        }
        free(nss);
    }
    free(ma.main_string);
}