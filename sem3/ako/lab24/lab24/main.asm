.686
.model flat

includelib libcmt.lib

extern _ExitProcess@4 : PROC
extern __write : PROC ; (dwa znaki podkre�lenia)
extern __read : PROC ; (dwa znaki podkre�lenia)

public _main


.data
	tekst_pocz db 10, 'Prosz� napisa� jaki� tekst '
				db 'i nacisnac Enter', 10
	koniec_t db ?
	magazyn db 80 dup (?)
	Nmagazyn db 320 dup (?)
	nowa_linia db 10
	liczba_znakow dd ?


.code

_main PROC
	; wy�wietlenie tekstu informacyjnego

	; liczba znak�w tekstu
	mov ecx,(OFFSET koniec_t) - (OFFSET tekst_pocz)
	push ecx
	push OFFSET tekst_pocz ; adres tekstu
	push 1 ; nr urz�dzenia (tu: ekran - nr 1)
	call __write ; wy�wietlenie tekstu pocz�tkowego

	add esp, 12 ; usuniecie parametr�w ze stosu


	; czytanie wiersza z klawiatury

	push 80 ; maksymalna liczba znak�w
	push OFFSET magazyn
	push 0 ; nr urz�dzenia (tu: klawiatura - nr 0)
	call __read ; czytanie znak�w z klawiatury

	add esp, 12 ; usuniecie parametr�w ze stosu


	; kody ASCII napisanego tekstu zosta�y wprowadzone
	; do obszaru 'magazyn'
	; funkcja read wpisuje do rejestru EAX liczb�
	; wprowadzonych znak�w

	mov liczba_znakow, eax

	; rejestr ECX pe�ni rol� licznika obieg�w p�tli
	mov ecx, eax
	mov ebx, 0 ; indeks pocz�tkowy
	mov eax, 0

	ptl: 
	mov dl, magazyn[ebx] ; pobranie kolejnego znaku
	;tu by�o

	cmp dl, "\"
	jnz pl_a
	mov Nmagazyn[eax], "1"
	inc eax
	mov Nmagazyn[eax], "2"
	inc eax
	mov Nmagazyn[eax], "3"
	inc eax
	mov Nmagazyn[eax], "4"
	;inc eax
	;czwart raz zostanie zwi�kszony w dalej
	;mov esi, 0
	skipSlash:
	cmp magazyn[ebx+1], "\"
	;inc ebx
	jz skipSlash
	;sub ebx, 1
	jmp dalej



	;polskie znaki
	pl_a:
	cmp dl, 0a5h
	jnz pl_c
	mov Nmagazyn[eax], 0a4h
	jmp dalej

	pl_c:
	cmp dl, 86h
	jnz pl_e
	mov Nmagazyn[eax], 8fh
	jmp dalej

	pl_e:
	cmp dl, 0a9h
	jnz pl_l
	mov Nmagazyn[eax], 0a8h
	jmp dalej

	pl_l:
	cmp dl, 88h
	jnz pl_n
	mov Nmagazyn[eax], 9dh
	jmp dalej

	pl_n:
	cmp dl, 0e4h
	jnz pl_o
	mov Nmagazyn[eax], 0e3h
	jmp dalej

	pl_o:
	cmp dl, 0a2h
	jnz pl_s
	mov Nmagazyn[eax], 0e0h
	jmp dalej

	pl_s:
	cmp dl, 98h
	jnz pl_zi
	mov Nmagazyn[eax], 97h
	jmp dalej

	pl_zi:
	cmp dl, 0abh
	jnz pl_z
	mov Nmagazyn[eax], 8dh
	jmp dalej

	pl_z:
	cmp dl, 0beh
	jnz latin
	mov Nmagazyn[eax], 0bdh
	jmp dalej

	;angielskie znaki
	latin:
	cmp dl, 'a'
	jb dalej ; skok, gdy znak nie wymaga zamiany
	cmp dl, 'z'
	ja dalej ; skok, gdy znak nie wymaga zamiany

	sub dl, 20H ; zamiana na wielkie litery
	; odes�anie znaku do pami�ci
	mov Nmagazyn[eax], dl

	
	dalej: 
	inc ebx ; inkrementacja indeksu
	inc eax
	;loop ptl ; sterowanie p�tl�
	;dec ecx
	cmp ebx, ecx
	;jnz ptl
	jbe ptl


	; wy�wietlenie przekszta�conego tekstu

	push eax
	push OFFSET Nmagazyn
	push 1
	call __write ; wy�wietlenie przekszta�conego tekstu

	add esp, 12 ; usuniecie parametr�w ze stosu

	push 0
	call _ExitProcess@4 ; zako�czenie programu
_main ENDP
END