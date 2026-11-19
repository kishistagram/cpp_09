	.file	"compare.cpp"
	.intel_syntax noprefix
	.text
	.p2align 4
	.globl	_Z9getVectorRKSt6vectorIiSaIiEEm
	.type	_Z9getVectorRKSt6vectorIiSaIiEEm, @function
_Z9getVectorRKSt6vectorIiSaIiEEm:
.LFB726:
	.cfi_startproc
	endbr64
	mov	rax, QWORD PTR [rdi]
	mov	eax, DWORD PTR [rax+rsi*4]
	ret
	.cfi_endproc
.LFE726:
	.size	_Z9getVectorRKSt6vectorIiSaIiEEm, .-_Z9getVectorRKSt6vectorIiSaIiEEm
	.p2align 4
	.globl	_Z8getDequeRKSt5dequeIiSaIiEEm
	.type	_Z8getDequeRKSt5dequeIiSaIiEEm, @function
_Z8getDequeRKSt5dequeIiSaIiEEm:
.LFB727:
	.cfi_startproc
	endbr64
	mov	rdx, QWORD PTR 16[rdi]
	mov	rcx, QWORD PTR 40[rdi]
	mov	rax, rdx
	sub	rax, QWORD PTR 24[rdi]
	sar	rax, 2
	add	rax, rsi
	js	.L4
	cmp	rax, 127
	jle	.L8
	mov	rdx, rax
	sar	rdx, 7
.L7:
	mov	rsi, rdx
	mov	rdx, QWORD PTR [rcx+rdx*8]
	sal	rsi, 7
	sub	rax, rsi
	lea	rax, [rdx+rax*4]
	mov	eax, DWORD PTR [rax]
	ret
	.p2align 4,,10
	.p2align 3
.L8:
	lea	rax, [rdx+rsi*4]
	mov	eax, DWORD PTR [rax]
	ret
	.p2align 4,,10
	.p2align 3
.L4:
	mov	rdx, rax
	not	rdx
	shr	rdx, 7
	not	rdx
	jmp	.L7
	.cfi_endproc
.LFE727:
	.size	_Z8getDequeRKSt5dequeIiSaIiEEm, .-_Z8getDequeRKSt5dequeIiSaIiEEm
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04.3) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
