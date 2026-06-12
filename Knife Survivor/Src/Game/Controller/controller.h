#pragma once
class Controller
{
public:
	int m_hndl;			//画像ハンドル
public:

	// 初期化
	void Init();

	// 読み込み
	void Load();

	// 更新
	void Step();

	// 描画
	void Draw();

	// 終了処理
	void Exit();

};

