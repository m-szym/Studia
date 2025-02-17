; Program linie.asm
; Wy�wietlanie znak�w * w takt przerwa� zegarowych
; Uruchomienie w trybie rzeczywistym procesora x86
; lub na maszynie wirtualnej
; zako�czenie programu po naci�ni�ciu dowolnego klawisza
; asemblacja (MASM 4.0): masm gwiazdki.asm,,,;
; konsolidacja (LINK 3.60): link gwiazdki.obj;
.386
rozkazy SEGMENT use16
ASSUME cs:rozkazy

linia PROC
	; przechowanie rejestr�w
	push ax
	push bx
	push es

	mov ax, 0A000H ; adres pami�ci ekranu dla trybu 13H
	mov es, ax
	mov bx, cs:adres_piksela ; adres bie��cy piksela
	mov al, cs:kolor
	mov es:[bx], al ; wpisanie kodu koloru do pami�ci ekranu

	; przej�cie do nast�pnego wiersza na ekranie
	add bx, 320

	; sprawdzenie czy ca�a linia wykre�lona
	cmp bx, 320*200
	jb dalej ; skok, gdy linia jeszcze nie wykre�lona

	; kre�lenie linii zosta�o zako�czone - nast�pna linia b�dzie
	; kre�lona w innym kolorze o 10 pikseli dalej
	add word PTR cs:przyrost, 10
	mov bx, 10
	add bx, cs:przyrost
	inc cs:kolor ; kolejny kod koloru

	; zapisanie adresu bie��cego piksela
	dalej:
	mov cs:adres_piksela, bx

	; odtworzenie rejestr�w
	pop es
	pop bx
	pop ax

	; skok do oryginalnego podprogramu obs�ugi przerwania
	; zegarowego
	jmp dword PTR cs:wektor8

	; zmienne procedury
	kolor db 1 ; bie��cy numer koloru
	adres_piksela dw 0 ; bie��cy adres piksela
	przyrost dw 0
	wektor8 dd ?
linia ENDP

przek PROC
	; przechowanie rejestr�w
	push ax
	push bx
	push es

	mov ax, 0A000H ; adres pami�ci ekranu dla trybu 13H
	mov es, ax
	mov bx, cs:padres_piksela ; adres bie��cy piksela
	mov al, cs:pkolor
	mov es:[bx], al ; wpisanie kodu koloru do pami�ci ekranu

	; przej�cie do nast�pnego wiersza na ekranie
	mov ax, cs:kier
	add bx, ax
	mov ax, cs:biy

	cmp ax, 0
	je jeden
	mov cs:biy, 0
	add bx, 320
	jmp dal
	jeden:
	mov cs:biy, 1
	dal:

	cmp bx, 320*160
	jae zmien
	;mov cs:kier, 1
	jmp dal2
	zmien:
	mov bx, 320
	mov ax, cs:kier
	neg ax
	mov cs:kier, ax
	inc cs:pkolor
	dal2:

	; sprawdzenie czy ca�a linia wykre�lona
	;cmp bx, 320*200
	;ja pdalej ; skok, gdy linia jeszcze nie wykre�lona
	;
	;; kre�lenie linii zosta�o zako�czone - nast�pna linia b�dzie
	;; kre�lona w innym kolorze o 10 pikseli dalej
	;add word PTR cs:pprzyrost, 10
	;mov bx, 10
	;add bx, cs:pprzyrost
	;inc cs:pkolor ; kolejny kod koloru

	; zapisanie adresu bie��cego piksela
	;pdalej:
	mov cs:padres_piksela, bx

	; odtworzenie rejestr�w
	pop es
	pop bx
	pop ax

	; skok do oryginalnego podprogramu obs�ugi przerwania
	; zegarowego
	jmp dword PTR cs:pwektor8

	; zmienne procedury
	pkolor db 3 ; bie��cy numer koloru
	padres_piksela dw -1 ; bie��cy adres piksela
	pprzyrost dw 0
	pwektor8 dd ?
	biy dw 0
	kier dw 1
przek ENDP

; INT 10H, funkcja nr 0 ustawia tryb sterownika graficznego
zacznij:
mov al, 13H ; nr trybu
mov ah, 0
int 10H

mov bx, 0
mov es, bx ; zerowanie rejestru ES
mov eax, es:[32] ; odczytanie wektora nr 8
mov cs:pwektor8, eax; zapami�tanie wektora nr 8

; adres procedury 'linia' w postaci segment:offset
mov ax, SEG przek
mov bx, OFFSET przek
cli ; zablokowanie przerwa�

; zapisanie adresu procedury 'linia' do wektora nr 8
mov es:[32], bx
mov es:[32+2], ax
sti ; odblokowanie przerwa�

czekaj:
mov ah, 1 ; sprawdzenie czy jest jaki� znak
int 16h ; w buforze klawiatury

jz czekaj
mov ah, 0 ; funkcja nr 0 ustawia tryb sterownika
mov al, 3H ; nr trybu
int 10H

; odtworzenie oryginalnej zawarto�ci wektora nr 8
mov eax, cs:pwektor8
mov es:[32], eax

; zako�czenie wykonywania programu
mov ax, 4C00H
int 21H

rozkazy ENDS

stosik SEGMENT stack
	db 256 dup (?)
stosik ENDS

END zacznij