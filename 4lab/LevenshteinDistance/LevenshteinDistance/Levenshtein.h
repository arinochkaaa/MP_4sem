#pragma once
#include <iostream>
// - Levenshtein.h  
// -- ���������   �������e��� (������������ ����������������)
int levenshtein(
	int lx,           // ����� ����� x 
	std::string x,   // ����� ������ lx
	int ly,           // ����� ����� y
	std::string y// ����� y
);
// -- ���������   �������e��� (��������)
int levenshtein_r(
	int lx,           // ����� ������ x 
	std::string x,   // ������ ������ lx
	int ly,           // ����� ������ y
	std::string y    // ������ y
);
