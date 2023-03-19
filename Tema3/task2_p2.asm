section .text
	global par

;; int par(int str_length, char* str)
;
; check for balanced brackets in an expression
par:
	xor ecx, ecx					; contor pentru numarul de paranteze de pe stiva

	start:
		cmp byte [eax], 40			; verificam ce fel de paranteza este caracterul curent
		je put_on_stack				; este paranteza deschisa
		jl remove_from_stack			; este paranteza inchisa
		jg remove_from_stack
		put_on_stack:
			push 40				; daca gasim o paranteza deschisa, o punem pe stiva
			inc ecx				; incrementam numarul de paranteze de pe stiva
			jmp next_step			; mergem catre pasul urmator

		remove_from_stack:			; am citit o paranteza inchisa
			cmp ecx, 0 			; ne asiguram ca avem ce sa scoatem de pe stiva
			jg remove_safe
			je break			; trebuie sa scoatem de pe stiva, dar nu mai avem ce
							; deci stim sigur ca sirul nu este corect

			remove_safe:
				pop esi			; scoatem o paranteza deschisa de pe stiva
				dec ecx			; nu uitam sa decrementam contorul
				jmp next_step

			break:
				xor edx, edx		; punem 0 in edx pentru a iesi din loop
				inc edx			; il incrementam pt ca este decrementat in next_step si vrem sa fie 0 
				dec ecx			; punem -1 in ecx ca sa stim la final ca sirul nu este corect

		next_step:
			inc byte eax			; trecem la caracterul urmator din sirul dat
			dec edx				; decrementam numarul de pasi ramasi
			jnz start			; reluam procesul daca edx != 0
	
	cmp ecx, 0					; stabilim ce fel de sir avem
	je correct
	jl incorrect

	correct: 					; punem 1 in eax
		xor eax, eax
		inc eax
		jmp finish

	incorrect:					; punem 0 in eax
		xor eax, eax

	finish:
	ret
