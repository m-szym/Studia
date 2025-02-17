.686
.model flat

includelib libcmt.lib

extern _ExitProcess@4 : PROC
extern __write : PROC ; (dwa znaki podkre�lenia)
extern __read : PROC ; (dwa znaki podkre�lenia)
extern _MessageBoxW@16 : PROC
extern _MessageBoxA@16 : PROC

public _main


.data
	tekst_pocz db 10, 'Prosz� napisa� jaki� tekst '
				db 'i nacisnac Enter', 10
	koniec_t db ?

	magazyn db 80 dup (?)

	nowa_linia db 10

	liczba_znakow dd ?

	tytulU dw 'K', 'o', 'm', 'u', 'n', 'i', 'k', 'a', 't', 0
	magazynU dw 80 dup (?) 
	tekstU dw 'A', '=', 0105h, '=', 0
	liczbaU dq ?

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
	;mov edx, 0 ; indeks pocz�tkowy dla magazynU (UTF-16)

	ptl: 
	mov dx, 0
	mov dl, magazyn[ebx] ; pobranie kolejnego znaku
	;tu by�o

	;polskie znaki
	pl_a:
	cmp dl, 0a5h
	jnz pl_c
	mov magazynU[eax], 0104h
	jmp dalej

	pl_c:
	cmp dl, 86h
	jnz pl_e
	mov magazynU[eax], 0106h
	jmp dalej

	pl_e:
	cmp dl, 0a9h
	jnz pl_l
	mov magazynU[eax], 0118h
	jmp dalej

	pl_l:
	cmp dl, 88h
	jnz pl_n
	mov magazynU[eax], 0141h
	jmp dalej

	pl_n:
	cmp dl, 0e4h
	jnz pl_o
	mov magazynU[eax], 0143h
	jmp dalej

	pl_o:
	cmp dl, 0a2h
	jnz pl_s
	mov magazynU[eax], 00d3h
	jmp dalej

	pl_s:
	cmp dl, 98h
	jnz pl_zi
	mov magazynU[eax], 015ah
	jmp dalej

	pl_zi:
	cmp dl, 0abh
	jnz pl_z
	mov magazynU[eax], 0179h
	jmp dalej

	pl_z:
	cmp dl, 0beh
	jnz akoCzystka
	mov magazynU[eax], 017bh
	jmp dalej

	akoCzystka:
	cmp dl, "A"
	jnz latin
	cmp magazyn[ebx+1], "k"
	jnz latin
	cmp magazyn[ebx+2], "o"
	jnz latin
	mov magazynU[eax], 2615h
	add ebx, 2	

	jmp dalej

	;compA:
	;cmp dl, "A"
	;je compK
	;cmp dl, "a"
	;je compK
	;jmp latin

	;angielskie znaki
	latin:
	cmp dl, 'a'
	jb noswap ; skok, gdy znak nie wymaga zamiany
	cmp dl, 'z'
	ja noswap ; skok, gdy znak nie wymaga zamiany

	sub dl, 20H ; zamiana na wielkie litery
	mov magazynU[eax], dx
	; odes�anie znaku do pami�ci
	;mov magazynU[eax], dx

	noswap:
	mov magazynU[eax], dx

	
	dalej: 
	;mov magazynU[eax], dx
	add eax, 2
	inc ebx ; inkrementacja indeksu
	;add edx, 2
	;loop ptl ; sterowanie p�tl�
	dec ecx
	jnz ptl


	; wy�wietlenie przekszta�conego tekstu
	;push liczba_znakow
	;push OFFSET magazyn
	;push 1
	;call __write ; wy�wietlenie przekszta�conego tekstu

	;add esp, 12 ; usuniecie parametr�w ze stosu

	mov magazyn[eax + 2], 0
	;push 0
	;push OFFSET tytul
	;push OFFSET magazyn
	;push 0
	;call _MessageBoxA@16

	push 0
	push OFFSET tytulU
	push OFFSET magazynU	
	push 0
	call _MessageBoxW@16

	push 0
	call _ExitProcess@4 ; zako�czenie programu
_main ENDP
END