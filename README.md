# cpp_09
Milestone05, Common Core, 42 Tokyo
# cpp_09
Milestone05, Common Core, 42 Tokyo


### ex00
### map
assosiative container　連想コンテナ

連想コンテナ
キーに基づいた手探索機能を提供
1. 順序付き連想今手間
2. 非順序連想コンテナ

map群: {key, value}ぺあの名が美


### ex01
→ std::stackを使った式評価、LIFO構造をアルゴリズムに結び付ける

### コンテナアダプタ std::stack
std::stackはLIFO(Last in, First out)なので、RPNの手法に合う

基本アルゴリズムはこんなかんじ：
```
for each token:
	if token is a number:
		stackにpushする
	
	else if token is an operator:
		stackから2つpopする
		計算する
		結果をpushする
```

やること
・RPN->std::stackを使用
・stackの不変条件の管理
	->演算子処理の時には少なくとも２つの値が必要
・入力が正しい式を検証できるか
	-> 最後にstackへ２個以上残っていたら式として不完全
・演算の境界条件を扱う
	-> 数字がふそく
	-> 最終結果が１つではない
	-> 0除算
	-> 不正な文字
	-> 演算子だけの入力
	-> 空文字列
	
