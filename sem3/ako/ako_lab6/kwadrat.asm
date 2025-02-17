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

kwa PROC
	; przechowanie rejestr�w
	push ax
	push bx
	push cx
	push es

	mov ax, cs:timer
	inc ax
	cmp ax, 5
	jb dal
	mov bl, cs:kolor
	cmp bl, 0
	je kol3
	mov cs:kolor, byte ptr 0
	jmp dal
	kol3:
	mov cl, cs:kolor_og
	mov cs:kolor, cl
	dal:
	mov cs:timer, ax


	cmp cs:r_lock, byte ptr 1
	jne ddd
	mov cs:kolor_og, byte ptr 5
	ddd:


	mov ax, 0A000H ; adres pami�ci ekranu dla trybu 13H
	mov es, ax
	mov cl, cs:kolor ; kod koloru


	mov ax, 160
	ptl_1_start:


	mov bx, 0
	ptl_2_start:
	add bx, ax
	mov es:[bx], cl ; wpisanie kodu koloru do pami�ci ekranu
	sub bx, ax
	inc bx

	cmp bx, 20
	jb ptl_2_start

	add ax, 320
	cmp ax, 320*20+160
	jb ptl_1_start



	; odtworzenie rejestr�w
	pop es
	pop cx
	pop bx
	pop ax

	; skok do oryginalnego podprogramu obs�ugi przerwania
	; zegarowego
	jmp dword PTR cs:wektor8

	; zmienne procedury
	kolor_og db 3
	kolor db 3 ; bie��cy numer koloru
	timer dw 0 ; licznik przerwa� zegarowych
	wektor8 dd ?
kwa ENDP

klaw PROC
	; odczytanie kodu ASCII naci�ni�tego klawisza (INT 16H, AH=0)
	; do rejestru AL
	; mov ah, 0
	; int 16H
	push ax
	push bx

	in al, 60H ; odczytanie kodu pozycji z klawiatury

	cmp al, 19d
	jne r_not_down
	mov cs:r_down, 1
	mov bx, cs:timer_r
	inc bx
	mov cs:timer_r, bx
	cmp bx, 36
	jb rr
	mov cs:r_lock, byte ptr 1
	jmp rr
	r_not_down:
	mov cs:timer_r, word ptr 0
	mov cs:r_down, byte ptr 0
	rr:

	
	pop bx
	pop ax

	; skok do oryginalnej procedury obs�ugi przerwania zegarowego
	jmp dword PTR cs:wektor9

	timer_r dw 0 ; licznik przerwa� zegarowych
	r_down db 0
	r_lock db 0
	wektor9 dd ?
klaw ENDP

; INT 10H, funkcja nr 0 ustawia tryb sterownika graficznego
zacznij:
mov al, 13H ; nr trybu
mov ah, 0
int 10H

mov bx, 0
mov es, bx ; zerowanie rejestru ES
mov eax, es:[32] ; odczytanie wektora nr 8
mov cs:wektor8, eax; zapami�tanie wektora nr 8

mov bx, 0
mov es, bx ; zerowanie rejestru ES
mov eax, es:[36] ; odczytanie wektora nr 8
mov cs:wektor9, eax; zapami�tanie wektora nr 8

; adres procedury 'linia' w postaci segment:offset
mov ax, SEG kwa
mov bx, OFFSET kwa
cli ; zablokowanie przerwa�

; zapisanie adresu procedury 'linia' do wektora nr 8
mov es:[32], bx		; <- cz�� offsetowa
mov es:[32+2], ax	; <- cz�� segmentowa
sti ; odblokowanie przerwa�

; adres procedury 'linia' w postaci segment:offset
mov ax, SEG klaw
mov bx, OFFSET klaw
cli ; zablokowanie przerwa�

; zapisanie adresu procedury 'linia' do wektora nr 8
mov es:[36], bx
mov es:[36+2], ax
sti ; odblokowanie przerwa�

; oczekiwanie na naci�ni�cie klawisza 'x'
aktywne_oczekiwanie:
mov ah,1
int 16H

; funkcja INT 16H (AH=1) BIOSu ustawia ZF=1 je�li
; naci�ni�to jaki� klawisz
jz aktywne_oczekiwanie

; odczytanie kodu ASCII naci�ni�tego klawisza (INT 16H, AH=0)
; do rejestru AL
mov ah, 0
int 16H
cmp al, 'x' ; por�wnanie z kodem litery 'x'

jne aktywne_oczekiwanie ; skok, gdy inny znak

mov ah, 0 ; funkcja nr 0 ustawia tryb sterownika
mov al, 3H ; nr trybu
int 10H

; odtworzenie oryginalnej zawarto�ci wektora nr 9
mov eax, cs:wektor8
cli
mov es:[32], eax
sti

; odtworzenie oryginalnej zawarto�ci wektora nr 9
mov eax, cs:wektor9
cli
mov es:[36], eax
sti

; zako�czenie wykonywania programu
mov ax, 4C00H
int 21H

rozkazy ENDS

stosik SEGMENT stack
	db 256 dup (?)
stosik ENDS

END zacznij