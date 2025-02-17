#pragma once
#include "includes.h"
#include "functions.h"

void command_iAqm(const char* pch, List2d<Sections_Package>* root);
void command_iSqm(const char* pch, List2d<Sections_Package>* root);
void command_iSj(const char* pch, const char* pch3, List2d<Sections_Package>* root);
void command_iAn(const char* pch, const char* pch3, List2d<Sections_Package>* root);
void command_nAqm(const char* pch, List2d<Sections_Package>* root);
void command_zSqm(const char* pch, List2d<Sections_Package>* root);
void command_zEn(const char* pch, const char* pch3, List2d<Sections_Package>* root);
void command_qm(List2d<Sections_Package>* root);
void command_iDst(const char* pch, List2d<Sections_Package>* root, Sections_Package*& cusecpack, Section*& cusec, List2d<Sections_Package>*& lnode);
void command_iDn(const char* pch, const char* pch3, List2d<Sections_Package>* root, Sections_Package*& cusecpack, Section*& cusec, List2d<Sections_Package>*& lnode);