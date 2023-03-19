; This is your structure
struc  my_date
    .day: resw 1
    .month: resw 1
    .year: resd 1
endstruc

section .text
    global ages

section .data
    my_dateArray: times my_date_size * 100 db 0

; void ages(int len, struct my_date* present, struct my_date* dates, int* all_ages);
ages:
    ;; DO NOT MODIFY
    push    ebp
    mov     ebp, esp
    pusha

    mov     edx, [ebp + 8]  ; len
    mov     esi, [ebp + 12] ; present
    mov     edi, [ebp + 16] ; dates
    mov     ecx, [ebp + 20] ; all_ages
    ;; DO NOT MODIFY

    ;; TODO: Implement ages
    ;; FREESTYLE STARTS HERE

    xor eax, eax                                                ; initializam eax pentru a-l folosi drept iterator pentru dates
    
    start:
        mov ebx, dword [esi + my_date.year]                     ; punem in ebx anul curent
        sub ebx, [edi + my_date_size * eax + my_date.year]      ; scadem anul nasterii din anul curent
        mov [ecx + 4 * eax], ebx                                ; punem varsta obtinuta in ages, pe pozitia corespunzatoare

        xor ebx, ebx                                            ; reinitializam ebx
        mov bx, [esi + my_date.month]                           ; punem in bx luna curenta
        cmp bx, [edi + my_date_size * eax + my_date.month]      ; dif intre luna curenta si luna nasterii
        je equal                                                ; suntem in luna nasterii, deci verificam ziua nasterii 
        jl less                                                 ; inca nu a implinit, deci scadem 1
        jg verify                                               ; a implinit, deci lasam asa

        equal:
            xor ebx, ebx                                        ; reinitializam ebx
            mov bx, [esi + my_date.day]                         ; punem in bx ziua curenta
            cmp bx, [edi + my_date_size * eax + my_date.day]    ; dif intre ziua curenta si ziua nasterii
            jge verify                                          ; a implinit, deci lasam asa
                                                                ; daca ziua curenta e mai mica se duce automat in less                   
        less:
            dec dword [ecx + 4 * eax]               

        verify:
            cmp dword [ecx + 4 * eax], -1                       ; se verificam daca data nasterii e dupa data curenta (in cazul asta aveam 0 dar scadem, deci avem -1)
            je add                                              ; daca da, se adauga inapoi 1 
            jg l1                                               ; daca e mai mare, e ok 
                                                                ; mai mic nu are cum sa fie, deci nu tratam cazul
            add:
                inc dword [ecx + 4 * eax]

            l1:
                inc eax                                         ; incrementam indicele iteratiei pentru dates    
                dec edx                                         ; decrementam len
                cmp edx,0                                       ; daca nu am ajuns la final
                jg start                                        ; reluam

    ;; FREESTYLE ENDS HERE
    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY
