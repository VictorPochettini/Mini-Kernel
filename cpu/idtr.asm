section .data
     idtr DW 0    ; 16-bit Limit
          DD 0    ; 32-bit Base Address
section .text
global setIdt
setIdt:
    MOV AX, [esp + 4]      ; First parameter: 16-bit limit
    MOV [idtr], AX
    MOV EAX, [ESP + 8]     ; Second parameter: 32-bit base address
    MOV [idtr + 2], EAX
    
    LIDT [idtr]            ; Load IDT pointer register
    RET