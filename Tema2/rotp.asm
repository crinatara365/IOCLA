section .text
    global rotp

section .data
    x dd 0

;; void rotp(char *ciphertext, char *plaintext, char *key, int len);
rotp:
    ;; DO NOT MODIFY
    push    ebp
    mov     ebp, esp
    pusha

    mov     edx, [ebp + 8]  ; ciphertext
    mov     esi, [ebp + 12] ; plaintext
    mov     edi, [ebp + 16] ; key
    mov     ecx, [ebp + 20] ; len
    ;; DO NOT MODIFY

    ;; TODO: Implment rotp
    ;; FREESTYLE STARTS HERE

    xor bl,bl                       ; initializam bl cu 0
    mov bl, [esi]                   ; punem in bl primul caracter din plaintext
    
    label:
        xor bl, [edi + ecx - 1]     ; xor intre primul caracter din plaintext si ultimul din key
                                    ; la urmatorul pas va fi intre al doilea caracter din plaintext si penultimul din key s.a.m.d
        mov eax, [x]                ; punem in eax valoarea din x pentru a o putea folosi mai departe
        mov [edx + eax], bl         ; adaugam caracterul din bl in ciphertext pe pozitia aferenta pasului
        inc DWORD [x]               ; incrementam valoarea din x pentru pasul viitor
        mov eax, [x]  
        mov bl, [esi + eax]         ; punem in bl urmatorul caracter din plaintext
    loop label                      ; loop functioneaza pana cand valoarea din ecx ajunge 0 
    mov dword [x], 0                ; resetam x pentru testul urmator

    ;; FREESTYLE ENDS HERE
    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY