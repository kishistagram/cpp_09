
### 目的
- 異なったコンテナクラスがプログラム上の同じ関数やアルゴリズムを実行したとき、実行時間が異なるのはなぜか？をアセンブリの観点から検証する

### 今回の比較対象
vector  -> 先頭アドレスとインデックスから直接アクセス
deque   -> ブロック内の位置を計算し、必要ならブロックポインタを取得
共通点	 -> どちらもランダムアクセスはO(1)

### コンパイル方法

どんな命令が存在するかをみる：
```
g++ -Wall -Wextra -Werror -std=c++98 -O2 -S -masm=intel compare.cpp -
o compare.s
```

###　確認できたこと
同じ`operator[]`でも、`vector`と`deque`の内部構造の違いによって生成される機械語の命令列が異なるということ

### まとめ
`std::vector`, `std::deque`は、どちらも添字アクセスの時間計算量がO(1)。
`GCC 11.4.0`, `-O2`の条件ｎでアセンブリを比較してみると、
`vector`はかなり単純なアドレス計算で要素にアクセスをするが、
`deque`はブロック境界の判定やブロックポインタの取得を必要とする場合がある
これは、Ford-Johnson アルゴリズムを同じように適用しても、コンテナによって実行時間が異なる理由の一つとして考えられる。



### vector
- 3命令のみ

rdi :	`vector`オブジェクトのアドレス
rsi	:	インデックス`i`
rax	:	戻り値を格納するレジスタ

1.	`vector`が保持する先頭要素へのポインタを読みだす2/ 2.	address = base + i*4を使って指定されたintを読みだす
3.	関数から戻る
```
	.cfi_startproc
	endbr64
	mov	rax, QWORD PTR [rdi]
	mov	eax, DWORD PTR [rax+rsi*4]
	ret
	.cfi_endproc
```

### deque
```
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
```