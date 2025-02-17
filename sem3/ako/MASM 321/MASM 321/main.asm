; 32-Bit Intel Protected Mode Programming
; KIP IRVINE Assembly Language for x86 / Intel-Based Computers. 
;

.386
.model flat,stdcall
.stack 4096

; DEFINE/DECLARE necessary WIN32 constants, functions etc.
;------------------------------------------------------------
; Win32 Console handles
STD_OUTPUT_HANDLE EQU -11       ; predefined Win API constant


; ALIAS  : The following Win32 API functions have an
; extra "A" at the end of their name, 
; so they are redefined here with text macros:
WriteConsole EQU <WriteConsoleA>


;                   FUNCTION PROTOTYPES
; -------------------------------------------------------------
ExitProcess PROTO,          ; exit program
    dwExitCode:DWORD        ; return code


GetStdHandle PROTO,         ; get standard handle
    nStdHandle:DWORD        ; type of console handle


WriteConsole PROTO,                 ; write a buffer to the console
    handle:DWORD,                   ; output handle
    lpBuffer:PTR BYTE,              ; pointer to buffer
    nNumberOfBytesToWrite:DWORD,    ; size of buffer
    lpNumberOfBytesWritten:PTR DWORD,   ; num bytes written
    lpReserved:DWORD                    ; (not used)

; User Defined Data Section
; ---------------------------------------------------------------
.data
mesg1               BYTE    "Hello world!",0dh,0ah,0
sizeMesg1           = ($-mesg1)-1       ; ex-cluding the sign bit
BytesWritten        DWORD   0
ConsoleOutHandle    DWORD   0

.code
main proc
    
    ; Get Standart Output Handle
    INVOKE GetStdHandle, STD_OUTPUT_HANDLE  ; Get a handle to console SCREEN.
    mov ConsoleOutHandle, eax
    
    ; Write Message to the Handle => CONSOLE
    INVOKE WriteConsole, ConsoleOutHandle, ADDR mesg1, (LENGTHOF mesg1)-1, ADDR BytesWritten, 0
    
    
    invoke ExitProcess,0
main endp
;-------------------------------------------------------------------

end main