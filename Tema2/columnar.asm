section .data
    extern len_cheie, len_haystack
    x dd 0
    y dd 0
    z dd 0
    q dd 0
    w dd 0
    j dd 0
    k dd 0
    g dd 0
    t dd 0

section .text
    global columnar_transposition

;; void columnar_transposition(int key[], char *haystack, char *ciphertext);
columnar_transposition:
    ;; DO NOT MODIFY
    push    ebp
    mov     ebp, esp
    pusha 

    mov edi, [ebp + 8]   ;key
    mov esi, [ebp + 12]  ;haystack
    mov ebx, [ebp + 16]  ;ciphertext
    ;; DO NOT MODIFY

    ;; TODO: Implment columnar_transposition
    ;; FREESTYLE STARTS HERE

    mov edx, [len_cheie]
    mov [k], edx                        ; punem in k lungimea cheii
    mov [t], edx                        ; punem in t lungimea cheii
    xor ecx, ecx                        ; initializam ecx cu 0 

    start:
        mov eax, [len_haystack]
        cdq                             ; punem in edx:eax deimpartitul
        idiv dword [len_cheie]          ; impartim la lungimea cheii
        inc eax                         
        mov dword [x], eax              ; in x avem numarul de caractere de pe o coloana (catul+1)
        mov dword [y], edx              ; in y avem cate pozitii de pe ultima linie sunt ocupate (restul impartirii)

        mov eax, [edi+4*ecx]
        mov [w], eax                    ; punem in w indicele coloanei de adaugat
        mov [q], eax                    ; punem in q indicele coloanei de adaugat
        mov [z], ecx                    ; pastram in z pozitia pe care ne aflam din key
        xor ecx, ecx
        mov eax, esi                    ; punem in eax inputul dat pentru a-l prelucra
        cmp dword [w], 0                ; comparam indicele coloanei de adaugat cu 0
        je l2                           ; daca este 0 mergem direct in l2 
        jg l1                           ; daca este mai mare mergem in l1 
       
        l1: 
            inc eax                     ; stergem din eax atatea caractere de la inceput egale cu numarul pozitiei coloanei
            dec dword [q]
            cmp dword [q], 0
            jg l1
      
        l2:
            mov edx, [y]                    ; punem in edx numarul de pozitii ocupate de pe ultima linie
            cmp [w], edx                    ; il comparam cu indicele coloanei de adaugat 
            jge one_step_less               ; daca indicele coloanei este mai mare sau egal, adaugam in ebx x-1 caractere
            jl x_steps                      ; daca indicele coloanei este mai mic, avem x caractere

            one_step_less: 
                mov dl, [eax]                
                mov ecx, [j]
                mov [ebx + ecx], dl         ; se adauga in ebx primul caracter din eax

                count_len_key_chars:        ; se sare peste [len_cheie] caractere
                    inc eax 
                    dec dword [t]
                    cmp dword [t], 0
                    jg count_len_key_chars

                add_char:                   ; se adauga in ebx primul caracter din eax dupa salt
                    mov dl, [eax]
                    inc ecx
                    mov [ebx + ecx], dl
                    mov edx, [len_cheie]
                    mov [t], edx            ; se reinitializeaza t cu lungimea cheii pentru a fi folosit la urmatorul salt
                    xor edx, edx
                    dec dword [x]
                    cmp dword [x], 1        ; se verifica daca s-au parcurs toate liniile unei coloane
                    jg count_len_key_chars
                    je final                ; se compara cu 1 pt ca se fac x-1 pasi 

            x_steps:                        ; este identic cu one_step_less
                mov dl, [eax]
                mov ecx, [j]
                mov [ebx + ecx], dl

                pass_len_key_chars:
                    inc eax 
                    dec dword [t]
                    cmp dword [t], 0
                    jg pass_len_key_chars
                add:
                    mov dl, [eax]
                    inc ecx
                    mov [ebx+ecx], dl
                    mov edx, [len_cheie]
                    mov [t], edx
                    xor edx, edx
                    dec dword [x]
                    cmp dword [x], 0        ; se parcurg x pasi
                    jg pass_len_key_chars

        final:
            mov [j], ecx
            mov ecx, [z]
            inc ecx
            dec dword [k]
            cmp dword [k], 0                ; se verifica daca mai sunt coloane de adaugat
            jg start
    mov dword [j], 0                        ; se initializeaza pentru testul urmator (j este pozitia pe care se adauga in ebx)

    ;; FREESTYLE ENDS HERE
    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY