/*
CKeyクラス
キーボード入力を取得する
*/
class CKey {
public:
	static bool Flg[256]; //キーが押されている時はtrue
	//Pushはstatic(スタティック)メソッド
	//keyが押されていればtrue
	static bool Push(char key);
	//キーが押された瞬間だけtrueを返す
	static bool Once(char key);
};
