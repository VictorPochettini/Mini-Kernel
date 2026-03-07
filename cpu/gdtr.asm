gdtr DW 0
     DD 0

setGdt:
    MOV AX, [esp + 4]
    MOV [gdtr], AX
    MOV EAX, [ESP + 8]
    MOV [gdtr + 2], EAX
    LGDT [gdtr]
    RET 