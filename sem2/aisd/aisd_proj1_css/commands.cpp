#include "commands.h"

void command_iAqm(const char* pch, List2d<Sections_Package>* root)
{
    Section* s = get_nth_notempty_section(atoi(pch), root);

    if (s != nullptr) std::cout << atoi(pch) << ",A,? == " << s->count_attributes() - 1 << std::endl;
    else return;
}

void command_iSqm(const char* pch, List2d<Sections_Package>* root)
{
    Section* s = get_nth_notempty_section(atoi(pch), root);

    if (s != nullptr && s->not_empty == true) std::cout << pch << ",S,? == " << s->count_selectors() - 1 << std::endl;
    else return;
}

void command_iSj(const char* pch, const char* pch3, List2d<Sections_Package>* root)
{
    Section* s = get_nth_notempty_section(atoi(pch), root);

    if (s != nullptr)
    {
        Selector* sel = s->get_nth_selector(atoi(pch3) - 1);

        if (sel != nullptr) std::cout << pch << ",S," << pch3 << " == " << sel->name << std::endl;
    }
    else return;
}

void command_iAn(const char* pch, const char* pch3, List2d<Sections_Package>* root)
{
    Section* s = get_nth_notempty_section(atoi(pch), root);

    if (s != nullptr)
    {
        Attribute* a = s->get_attribute_by_name(pch3);

        if (a != nullptr) std::cout << pch << ",A," << pch3 << " == " << a->value << std::endl;
    }
    else return;
}

void command_nAqm(const char* pch, List2d<Sections_Package>* root)
{
    int c = count_all_select_attributes(root, pch);

    if (c >= 0) std::cout << pch << ",A,? == " << c << std::endl;
    else return;
}

void command_zSqm(const char* pch, List2d<Sections_Package>* root)
{
    int c = count_all_select_selectors(root, pch);

    if (c >= 0) std::cout << pch << ",S,? == " << c << std::endl;
    else return;
}

void command_zEn(const char* pch, const char* pch3, List2d<Sections_Package>* root)
{
    if (root != nullptr)
    {   
        root = root->get_last();

        bool found_sel = false;
        bool found_att = false;
        char* name = nullptr;
        Attribute* att = nullptr;
        Selector* sel = nullptr;

        while (root != nullptr && !(found_sel))
        {
            if (root->cont != nullptr)
            {
                if (root->cont->sections != nullptr)
                {
                    for (int i = SECTIONS_PACKAGE_SIZE - 1; i >= 0; i--)
                    {
                        if (root->cont->sections[i].not_empty == true)
                        {
                            sel = root->cont->sections[i].get_selector_by_name(pch);
                            if (sel != nullptr)
                            {
                                found_sel = true;
                                att = root->cont->sections[i].get_attribute_by_name(pch3);
                                if (att != nullptr)
                                {
                                    found_att = true;
                                    if (att->value != nullptr)
                                    {
                                        name = att->name;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            root = root->prev;
        }
        if (found_att == 1) std::cout << pch << ",E," << pch3 << " == " << att->value << std::endl;
    }
}   

void command_qm(List2d<Sections_Package>* root)
{
    int c = 0;

    root = root->next;

    while (root != nullptr)
    {
        for (int i = 0; i < SECTIONS_PACKAGE_SIZE; i++)
        {
            if (root->cont->sections[i].not_empty == true) c++;
        }
        root = root->next;
    }
    std::cout << "? == " << c << std::endl;
}

void command_iDst(const char* pch, List2d<Sections_Package>* root, Sections_Package*& cusecpack, Section*& cusec, List2d<Sections_Package>*& lnode)
{
    Section* s = get_nth_notempty_section(atoi(pch), root);
    List2d<Sections_Package>* sp = get_sections_package_of_nth_notempty_section(atoi(pch), root);

    if (sp != nullptr && s != nullptr) 
    {
        s->clear_self();
        sp->cont->filled--;

        if (sp->cont->filled == 0)
        {
            sp->remove_self();
            cusecpack = nullptr;
            cusec = nullptr;
            lnode = nullptr;
        }

        std::cout << pch << ",D,* == deleted" << std::endl;
    }
    else return;
}

void command_iDn(const char* pch, const char* pch3, List2d<Sections_Package>* root, Sections_Package*& cusecpack, Section*& cusec, List2d<Sections_Package>*& lnode)
{
    Section* s = get_nth_notempty_section(atoi(pch), root);
    List2d<Sections_Package>* sp = get_sections_package_of_nth_notempty_section(atoi(pch), root);

    if (s != nullptr && sp != nullptr) 
    {
        if (s->get_attribute_by_name(pch3) != nullptr)
        {
            s->remove_attribute_by_name(pch3);
            if (s->attributes->next == nullptr) 
            {
                s->clear_self();
                sp->cont->filled--;
            }

            if (sp->cont->filled == 0)
            {
                sp->remove_self();
                cusec = nullptr;
                cusecpack = nullptr;
                lnode = nullptr;
            }
            std::cout << pch << ",D," << pch3 << " == deleted" << std::endl;
        }
    }
    else return;
}