section .text
	global sort

; struct node {
;     	int val;
;    	struct node* next;
; };

;; struct node* sort(int n, struct node* node);
; 	The function will link the nodes in the array
;	in ascending order and will return the address
;	of the new found head of the list
; @params:
;	n -> the number of nodes in the array
;	node -> a pointer to the beginning in the array
; @returns:
;	the address of the head of the sorted list
sort:
	enter 0, 0

	xor ecx, ecx
	add ecx, eax
	xor ebx, ebx
	add ebx, eax
	xor eax, eax
	start:
		mov esi, [edx + eax]			; obtinem valoarea din nod 
		push ecx				; punem pe stiva nr de pasi ramasi
		check_if_max:				; verificam daca valoarea din nod este egala cu maximul 
			cmp esi, ebx 
			je next_step			; daca da, nu-i mai cautam succesorul
	 		
		inc esi					; crestem cu 1 valoarea
		xor edi, edi
		xor ecx, ecx 
		add ecx, -8
		find_next:
			add ecx, 8
			mov edi, [edx + ecx]		; parcurgem tot vectorul
			cmp esi, edi			; cautam succesorul valorii din nod
			je set_next			; l-am gasit, deci setam legatura
			jg find_next 			; reapelam "find_next" pana il gasim
			jl find_next

		set_next:
			xor edi, edi
			mov edi, edx
			add edi, ecx			; punem in edi adresa succesorului
			mov [edx+eax+4], edi		; punem in campul next adresa succesorului
							; campurile next sunt din 8 in 8 incepand de la [edx+4]
		next_step:
			add eax, 8			; crestem eax pentru a obtine urmatoarea valoare din vector
			pop ecx				; scoatem de pe stiva valoarea pasilor ramasi 
			dec ecx
			jnz start		

	xor eax, eax
	find_min:					; tot ce ne mai ramane de facut este punem in eax adresa valorii 1 
		mov esi, [edx+eax]			; parcurgem tot vectorul
		cmp esi, 1
		je set_min						
		add eax, 8
		jmp find_min

	set_min:					; cand l-am gasit punem in eax adresa lui 1
		mov ebx, edx
		add ebx, eax
		mov eax, ebx

	leave
	ret
