section .text
	global cmmmc

;; int cmmmc(int a, int b)
;
;; calculate least common multiple fow 2 numbers, a and b
cmmmc:						; pentru a calcula cmmmc o sa folosim algoritmul lui euclid
	push eax
	push edx
	imul eax, edx
	push eax
	pop ecx					; rezultatul inmultirii numerelor
	pop ebx					; al doilea numar
	pop eax					; primul numar
	cmmdc:					; calculam cmmdc pentru a-l imparti la produsul numerelor
		cmp eax, ebx			; comparam cele 2 numere
		jg minus_first
		jl minus_second
		minus_first:			; daca primul e mai mare
			sub eax, ebx		; se scade din el valorea celui de-al doilea
			jmp check
		minus_second:			; daca al doilea e mai mare
			sub ebx, eax		; se scade din el valoarea primului
		check:				; se repeta doar daca cele 2 numere sunt diferite
			cmp eax, ebx 	
			jl cmmdc
			jg cmmdc		
	push ecx				; idiv imparte edx:eax deci punem deimpartitul ecx in eax 
	pop eax
	cdq
	idiv ebx				; impartim la cmmdc si rezultatul se pune direct in eax

	ret
