
### 目的
- 異なったコンテナクラスがプログラム上の同じ関数やアルゴリズムを実行したとき、実行時間が異なるのはなぜか？をアセンブリの観点から検証する



## 実行前のもの

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



## 実行時の命令追跡（GDB）

### 目的

`compare.cpp` から生成したアセンブリには、`getDeque()` の複数の分岐経路（`.L4`、`.L7`、`.L8`）が含まれていた。

しかし、生成されたアセンブリは実行履歴ではない。実行時には条件に応じて必要な経路だけが選択される。

そこで、GDBを使用して実際に実行される命令を観察することにした。

### 実験方法

`compare_main.cpp` を作成し、`getVector()` と `getDeque()` を呼び出した。

300個の整数をコンテナに格納し、異なるインデックスの要素にアクセスすることで、実行時の処理を確認する。

コンパイル：

```bash
g++ -std=c++98 -O2 -g -fno-inline \
    compare.cpp compare_main.cpp -o compare
```

GDBで実行：

```bash
gdb ./compare
```

以下のコマンドを順番に実行した。

```gdb
set disassembly-flavor intel
break getDeque
run
display/i $pc
si
```

### 観察結果

`getDeque(d, 3)` の呼び出し時に、設定したブレークポイントで停止した。

```text
Breakpoint 1, getDeque
(d=std::deque with 300 elements = {...}, i=i@entry=3)
```

続いて、プログラムカウンタ `$pc` の位置にある命令を表示した。

```asm
endbr64
```

`si` を実行すると、次の命令に進んだ。

```asm
sub rsp, 0x8
```

これにより、GDBを使って実行中の機械語命令を1命令ずつ観察できることを確認した。

なお、今回の実行ファイルでは、先に生成した `compare.s` と一部異なる命令列が確認された。コンパイル条件が異なるため、同じ関数でも生成される命令が変化し得る。

今回は、分岐先までの完全な追跡は行っていない。

### 考察

今回の実験から、次の点を整理できた。

1. `vector` と `deque` は、どちらも `operator[]` の時間計算量が `O(1)` である。
2. `vector` は連続したメモリに要素を保持するため、要素のアドレス計算が比較的単純である。
3. `deque` は複数のメモリブロックで構成されるため、ブロック位置の計算やブロックポインタの取得が必要になる場合がある。
4. GCC 11.4.0で生成したアセンブリでは、この構造の違いが命令列の違いとして確認できた。
5. アセンブリファイルには複数の実行経路が記述されており、すべての命令が毎回実行されるわけではない。

### 結論

**同じアルゴリズムと同じ時間計算量であっても、データ構造の違いによって機械語レベルの処理は異なる。**

これは、CPP09 ex02で `std::vector` と `std::deque` に同じFord–Johnsonアルゴリズムを適用した際、実行時間に差が生じ得る理由の一つである。

ただし、今回確認したのは要素アクセスの機械語命令の違いであり、Ford–Johnson全体の実行時間差を直接測定・説明したわけではない。実行時間には、キャッシュ、要素の移動、コンパイラ最適化なども影響する。

今回の実験では、GDBによる詳細な命令追跡よりも、コンテナの内部構造と機械語命令の関係を理解することを主な成果とした。