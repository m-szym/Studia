includelib libcmt.lib
includelib libvcruntime.lib
includelib libucrt.lib
includelib legacy_stdio_definitions.lib

        .386
        .model flat, c
        .stack 100h
printf  PROTO arg1:Ptr Byte

        .data
msg1    byte "I hate ASM", 0Ah, 0

        .code
main    proc
        INVOKE printf, ADDR msg1
        ret

main    endp
        end