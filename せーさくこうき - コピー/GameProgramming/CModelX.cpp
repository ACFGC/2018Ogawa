#include "glut.h"
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <io.h>
#include <string.h> //文字列関数のインクルード

#include "CModelX.h"

void CModelX::Load(char*file){
	//
	//ファイルサイズを取得する
	//
	FILE *fp;	//ファイルポインタ変数の作成
	fp = fopen(file, "rb");	//ファイルをオープンする
	if (fp == NULL) {	//エラーチェック
		printf("fopen error\n");
		return;
	}
	fseek(fp, 0L, SEEK_END);

	int size = ftell(fp);
	char *buf = mpPointer = new char[size + 1];	//ファイルサイズ+1バイト分の領域を確保

	fseek(fp, 0L, SEEK_SET);
	fread(buf, size, 1, fp);	//確保した領域にファイルサイズ分データを読み込む
	buf[size] = '\0';	//最後に\0を設定する（文字列の終端）
	fclose(fp);	//ファイルをクローズする
	//
	//ファイルから3Dモデルのデータを読み込む
	//
	//FILE*fp;   //ファイルポインタ変数の作成
	//fp = fopen(file, "rb"); //ファイルをオープンする
	//if (fp == NULL){ //エラーチェック
	//	printf("fopen error\n");
	//	return;
	//}
	////ファイルサイズ+1バイト分の領域を確保
	//char*buf = mpPointer = new char[size + 1];
	////確保した領域にファイルサイズ分データを読み込む
	//fread(buf, size, 1, fp);
	//buf[size] = '\0'; //最後に\0を設定する(文字列の終端)
	//fclose(fp); //ファイルをクローズする

	//printf(buf);

	//文字列の最後まで繰り返し
	while (*mpPointer != '\0'){
		GetToken(); //単語の取得
		//template 読み飛ばし
		if (strcmp(mToken, "template") == 0){
			SkipNode();
		}
		//Materialの時
		else if (strcmp(mToken, "Material") == 0){
			new CMaterial(this);
		}
		//単語がFrameの場合
		else if (strcmp(mToken, "Frame") == 0){
			//フレームを作成する
			new CModelXFrame(this);
		}
		//単語がAnimationSetの場合
		else if (strcmp(mToken, "AnimationSet") == 0){
			new CAnimationSet(this);
		}
	}

	SAFE_DELETE_ARRAY(buf); //確保した領域を解放する

	//スキンウェイトのフレーム番号設定
	SetSkinWeightFrameIndex();
}

/*
GetToken
文字列データから、単語を1つ取得する
*/
void CModelX::GetToken(){
	char*p = mpPointer;
	char*q = mToken;
	//空白( )タブ(\t)改行(\r)(\n)."以外の文字になるまで読み飛ばす
	while (*p != '\0'&& strchr(" \t\r\n,;\"", *p))p++;
	if (*p == '{' || *p == '}'){
		//｛または}ならmTokenに代入し次の文字へ
		*q++ = *p++;
	}
	else{
		//空白( )タブ(\r)(\n),;"}の文字になるまでmTokenに代入する
		while (*p != '\0'&& !strchr(" \t\r\n,;\"}", *p))
			*q++ = *p++;
	}
	*q = '\0'; //mTokenの最後に￥０を代入
	mpPointer = p; //次の読み込みポイントを更新する
	//もしmTokenが//の場合は,コメントなので改行まで読み飛ばす
	if (!strcmp("//", mToken)){
		//改行まで読み飛ばす
		while (*p != '\0'&& !strchr("\r\n", *p))p++;
		//読み込み位置の更新
		mpPointer = p;
		//単語を取得する(再起呼び出し)
		GetToken();
	}
}

/*
SkipNode
ノードを読み飛ばす
*/
void CModelX::SkipNode(){
	//文字が終わったら終了
	while (*mpPointer != '\0'){
		GetToken(); //次の単語取得
		//{が見つかったらループ終了
		if (strchr(mToken, '{'))break;
	}
	int count = 1;
	//文字が終わるか、カウントが0になったら終了
	while (*mpPointer != '\0'&& count > 0){
		GetToken(); //次の単語取得
		//{を見つけるとカウントアップ
		if (strchr(mToken, '{'))count++;
		//}を見つけるとカウントダウン
		else if (strchr(mToken, '}'))count--;
	}
}

/*
CModelXFlame
model:CModelXインスタンスへのポインタ
フレームを作成する
読み込み中にFrameが見つかれば、フレームを作成し、
子フレームに追加する
*/
CModelXFrame::CModelXFrame(CModelX*model){
	//現在のフレーム配列の要素数を取得し設定する
	mIndex = model->mFrame.size();
	//CModelXのフレーム配列に追加する
	model->mFrame.push_back(this);
	//変換行列を単位行列にする
	mTransformMatrix.Identity();
	//次の単語(フレーム名の予定)を取得する
	model->GetToken(); //frame name
	//フレーム名分エリアを確保する
	mpName = new char[strlen(model->mToken) + 1];
	//フレーム名をコピーする
	strcpy(mpName, model->mToken);
	//次の単語({の予定)を取得する
	model->GetToken(); //{
	//文字が無くなったら終わり
	while (*model->mpPointer != '\0'){
		//次の単語取得
		model->GetToken();//Frame
		//}かっこの場合は終了
		if (strchr(model->mToken, '}'))break;
		//新なフレームの場合は、子フレームに追加
		if (strcmp(model->mToken, "Frame") == 0){
			//フレームを作成し、子フレームの配列に追加
			mChild.push_back(new CModelXFrame(model));
		}
		else if (strcmp(model->mToken, "FrameTransformMatrix") == 0){
			model->GetToken(); //{
			for (int i = 0; i < ARRAY_SIZE(mTransformMatrix.f); i++){
				mTransformMatrix.f[i] = model->GetFloatToken();
			}
			model->GetFloatToken(); //}
		}
		else if (strcmp(model->mToken, "Mesh") == 0){
			mMesh.Init(model);
		}
		else{
			//上記以外の要素は読み飛ばす
			model->SkipNode();
		}
	}
	/*
	//デバックバージョンのみ有効
	#ifdef _DEBUG
	printf("%s\n", mpName);
	for (int i = 0; i < ARRAY_SIZE(mTransformMatrix.f); i++){
	printf(" %f", mTransformMatrix.f[i]);
	if (i % 4 == 3){
	printf("\n");
	}
	}
	#endif
	*/
}

/*
GetFloatToken
単語を浮動小数点のデータで返す
*/
float CModelX::GetFloatToken(){
	GetToken();
	//atof
	//文字列をfloat型へ変換
	return atof(mToken);
}

/*
GetIntToken
単語を整数のデータで返す
*/
int CModelX::GetIntToken(){
	GetToken();
	return atoi(mToken);
}


/*
Init
Meshのデータを取り込む
*/
void CMesh::Init(CModelX*model){
	model->GetToken(); //{ or 名前
	if (!strchr(model->mToken, '{')){
		//名前の場合、次が{
		model->GetToken(); //{
	}
	//頂点数の取得
	mVertexNum = model->GetIntToken();
	//頂点数分エリア確保
	mpVertex = new CVector3[mVertexNum];
	mpAnimateVertex = new CVector3[mVertexNum];
	//頂点数分データを取り込む
	for (int i = 0; i < mVertexNum; i++){
		mpVertex[i].x = model->GetFloatToken();
		mpVertex[i].y = model->GetFloatToken();
		mpVertex[i].z = model->GetFloatToken();
	}
	mFaceNum = model->GetIntToken(); //面数読み込み
	//超点数は一面に3頂点
	mpVertexIndex = new int[mFaceNum * 3];
	for (int i = 0; i < mFaceNum * 3; i += 3){
		model->GetToken(); //超点数読み飛ばし
		mpVertexIndex[i] = model->GetIntToken();
		mpVertexIndex[i + 1] = model->GetIntToken();
		mpVertexIndex[i + 2] = model->GetIntToken();
	}
	//文字が無くなったら終わり
	while (model->mpPointer != '\0'){
		model->GetToken(); //MeshNormals
		//}かっこの場合は終了
		if (strchr(model->mToken, '}'))
			break;
		if (strcmp(model->mToken, "MeshNormals") == 0){
			model->GetToken(); //{
			//法線データ数を取得
			mNormalNum = model->GetIntToken();
			//法線のデータを配列に取り込む
			CVector3*pNormal = new CVector3[mNormalNum];
			for (int i = 0; i < mNormalNum; i++){
				pNormal[i].x = model->GetFloatToken();
				pNormal[i].y = model->GetFloatToken();
				pNormal[i].z = model->GetFloatToken();
			}
			//法線数=面数x3
			mNormalNum = model->GetIntToken() * 3; //FaceNum
			int ni;
			//頂点毎に法線データを設定する
			mpNormal = new CVector3[mNormalNum];
			mpAnimateNormal = new CVector3[mNormalNum];
			for (int i = 0; i < mNormalNum; i += 3){
				model->GetToken(); //3
				ni = model->GetIntToken();
				mpNormal[i] = pNormal[ni];

				ni = model->GetIntToken();
				mpNormal[i + 1] = pNormal[ni];

				ni = model->GetIntToken();
				mpNormal[i + 2] = pNormal[ni];
			}
			delete[]pNormal;
			model->GetToken(); //}
		}
		else if (strcmp(model->mToken, "MeshMaterialList") == 0){
			model->GetToken(); //{
			//Materialの数
			mMaterialNum = model->GetIntToken();
			//FaceNum
			mMaterialIndexNum = model->GetIntToken();
			//マテリアルインデックスの作成
			mpMaterialIndex = new int[mMaterialIndexNum];
			for (int i = 0; i < mMaterialIndexNum; i++){
				mpMaterialIndex[i] = model->GetIntToken();
			}
			//マテリアルデータの作成
			for (int i = 0; i < mMaterialNum; i++){
				model->GetToken(); //Material
				if (strcmp(model->mToken, "Material") == 0){
					mMaterial.push_back(new CMaterial(model));
				}
				else{
					//{既出
					model->GetToken(); //MaterialName
					mMaterial.push_back(model->FindMaterial(model->mToken));
					model->GetToken(); //}
				}
			}
			model->GetToken(); //}//End of MeshMaterialList
		}
		//SkinWeigfhtsのとき
		else if (strcmp(model->mToken, "SkinWeights") == 0){
			//CSkinWeightsクラスのインスタンスを作成し、配列に追加
			mSkinWeights.push_back(new CSkinWeights(model));
		}
		else if (strcmp(model->mToken, "MeshTextureCoords") == 0){
			model->GetToken();  //{
			//テクスチャ座標数を取得
			int textureCoordsNum = model->GetIntToken();
			mpTextureCoords = new CVector2[textureCoordsNum];
			for (int i = 0; i < textureCoordsNum; i++){
				mpTextureCoords[i].x = model->GetFloatToken();
				mpTextureCoords[i].y = model->GetFloatToken();
			}
			model->GetToken(); //}
		}
		else{
			//以外のノードは読み飛ばし
			model->SkipNode();
		}

		//デバックバージョンのみ有効
#ifdef _DEBUG
		/*
		printf("NormalNum:%d", mNormalNum);
		for (int i = 0; i < mNormalNum; i++){
		if (i % 1 == 0){
		printf("\n");
		}
		printf("%10f", mpNormal[i].x);
		printf("%10f", mpNormal[i].y);
		printf("%10f", mpNormal[i].z);
		}
		*/
#endif
	}
}

void CMesh::Render(){
	/*頂点データ、法線データの配列を有効にする*/
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	/*頂点データ、法線データの配列を指定する*/
	glVertexPointer(3, GL_FLOAT, 0, mpAnimateVertex);
	glNormalPointer(GL_FLOAT, 0, mpAnimateNormal);
	glTexCoordPointer(2, GL_FLOAT, 0, mpTextureCoords);

	/*頂点のインデックスの場所を指定して図形を描画する*/
	//	glDrawElements(GL_TRIANGLES, 3 * mFaceNum, GL_UNSIGNED_INT, mpVertexIndex);


	/*頂点のインデックスの場所を指定して図形を描画する*/
	for (int i = 0; i < mFaceNum; i++){
		//マテリアルを適用する
		mMaterial[mpMaterialIndex[i]]->SetMaterial();
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (mpVertexIndex + i * 3));
		//マテリアルを解除する
		mMaterial[mpMaterialIndex[i]]->UnSetMaterial();
	}

	/*頂点データ、法線データの配列を無効にする*/
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

/*
AnimateVertex
頂点にアニメーションを適用
*/
void CMesh::AnimateVertex(CModelX*model){
	//アニメーション用の頂点エリアクリア
	memset(mpAnimateVertex, 0, sizeof(CVector3)*mVertexNum);
	memset(mpAnimateNormal, 0, sizeof(CVector3)*mNormalNum);
	//スキンウェイト分繰り返し
	for (int i = 0; i < mSkinWeights.size(); i++){
		//フレーム番号取得
		int frameIndex = mSkinWeights[i]->mFrameIndex;
		//フレーム合成行列にオフセット行列を合成
		CMatrix44 mSkinningMatrix = mSkinWeights[i]->mOffset * model->mFrame[frameIndex]->mCombinedMatrix;
		//超点数分繰り返し
		for (int j = 0; j < mSkinWeights[i]->mIndexNum; j++){
			//頂点番号取得
			int index = mSkinWeights[i]->mpIndex[j];
			//重み取得
			float weight = mSkinWeights[i]->mpWeight[j];
			//頂点と法線を更新する
			mpAnimateVertex[index] += mpVertex[index] * mSkinningMatrix*weight;
			mpAnimateNormal[index] += mpNormal[index] * mSkinningMatrix*weight;
		}
	}
	//法線を正規化する
	for (int i = 0; i < mNormalNum; i++){
		mpAnimateNormal[i] = mpAnimateNormal[i].normalize();
	}
}

/*
Render
メッシュの面数が0以上なら描画する
*/
void CModelXFrame::Render(){
	if (mMesh.mFaceNum != 0)
		mMesh.Render();
}

/*
Render
全てのフレームの描画処理を呼び出す
*/
void CModelX::Render(){
	for (int i = 0; i < mFrame.size(); i++){
		mFrame[i]->Render();
	}
}

/*
SetMaterial
マテリアルを適用する
*/
void CMaterial::SetMaterial(){
	glMaterialfv(GL_FRONT, GL_EMISSION, mEmissive);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &mPower);
	//テクスチャが有る場合
	if (mTextureID > 0){
		//テクスチャを使用可能にする
		glEnable(GL_TEXTURE_2D);
		//テクスチャをバインドする
		glBindTexture(GL_TEXTURE_2D, mTextureID);
		//テクスチャマッピングのデータを有効にする
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}

/*
UnSetMaterial
テクスチャマッピングを無効にする
*/
void CMaterial::UnSetMaterial(){
	//テクスチャが有る場合
	if (mTextureID > 0){
		//テクスチャのバインドを解く
		glBindTexture(GL_TEXTURE_2D, 0);
		//テクスチャを無効にする
		glDisable(GL_TEXTURE_2D);
		//テクスチャマッピングのデータを無効にする
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}

/*
Materialデータの読み込みと設定
*/
CMaterial::CMaterial(CModelX*model)
:mpName(0)
, mpTextureFilename(0)
, mTextureID(0)
{
	//CModelXにマテリアlを追加する
	model->mMaterial.push_back(this);
	model->GetToken(); //{?Name
	if (strcmp(model->mToken, "{") != 0){
		//{でないときはマテリアル名
		mpName = new char[strlen(model->mToken) + 1];
		strcpy(mpName, model->mToken);
		model->GetToken(); //{
	}
	mDiffuse[0] = model->GetFloatToken();
	mDiffuse[1] = model->GetFloatToken();
	mDiffuse[2] = model->GetFloatToken();
	mDiffuse[3] = model->GetFloatToken();

	mPower = model->GetFloatToken();

	mSpecular[0] = model->GetFloatToken();
	mSpecular[1] = model->GetFloatToken();
	mSpecular[2] = model->GetFloatToken();

	mEmissive[0] = model->GetFloatToken();
	mEmissive[1] = model->GetFloatToken();
	mEmissive[2] = model->GetFloatToken();

	model->GetToken(); //TextureFilename or }

	if (strcmp(model->mToken, "TextureFilename") == 0){
		//テクスチャありの場合、テクスチャファイル名取得
		model->GetToken(); //{
		model->GetToken(); //filename
		mpTextureFilename = new char[strlen(model->mToken) + 1];
		strcpy(mpTextureFilename, model->mToken);
		//テクスチャファイル名でテクスチャを検索する
		CTexture*p = model->FindTexture(model->mToken);
		//テクスチャが在る時
		if (p){
			//テクスチャIDを取得
			mTextureID = p->mId;
		}
		else{
			//無い場合、テクスチャ読み込み
			p = new CTexture(model->mToken);
			if (p->mpName){
				//テクスチャ配列に追加
				model->mTexture.push_back(p);
				//テクスチャIDを取得
				mTextureID = p->mId;
			}
		}
		model->GetToken(); //}
		model->GetToken(); //}
	}
	/*
	#ifdef _DEBUG
	printf("%s\n", mpName);
	printf("mDiffuse:");
	printf("%10f ", mDiffuse[0]);
	printf("%10f ", mDiffuse[1]);
	printf("%10f ", mDiffuse[2]);
	printf("%10f\n", mDiffuse[3]);
	printf("mPower:");
	printf("%10f\n", mPower);
	printf("mSpecular:");
	printf("%10f ", mSpecular[0]);
	printf("%10f ", mSpecular[1]);
	printf("%10f ", mSpecular[2]);
	printf("%10f\n", mSpecular[3]);
	printf("mEmissive:");
	printf("%10f ", mEmissive[0]);
	printf("%10f ", mEmissive[1]);
	printf("%10f ", mEmissive[2]);
	printf("%10f\n", mEmissive[3]);
	#endif
	*/
}

/*
FindMaterial
マテリアル名に該当するマテリアルを返却する
*/
CMaterial*CModelX::FindMaterial(char*name){
	//マテリアル配列のイテレータ作成
	std::vector <CMaterial*>::iterator itr;
	//マテリアル配列を先頭から順に検索
	for (itr = mMaterial.begin(); itr != mMaterial.end(); itr++){
		//名前が一致すればマテリアルのポインタを返却
		if (strcmp(name, (*itr)->mpName) == 0){
			return*itr;
		}
	}
	//無いときはNULLを返却
	return NULL;
}

/*
FindTexture
nameに該当するファイル名を持つテクスチャを検索して返却する
*/
CTexture*CModelX::FindTexture(char*name){
	//テクスチャ配列のイテレータ作成
	std::vector<CTexture*>::iterator itr;
	//テクスチャ配列の先頭から順に検索
	for (itr = mTexture.begin(); itr != mTexture.end(); itr++){
		//名前が一致すればテクスチャのポインタを返却
		if (strcmp(name, (*itr)->mpName) == 0){
			return *itr;
		}
	}
	//無いときはNULLを返却
	return NULL;
}


/*
CSkinWeights
スキンウェイトの読み込み
*/
CSkinWeights::CSkinWeights(CModelX*model)
:mpFrameName(0)
, mFrameIndex(0)
, mIndexNum(0)
, mpIndex(0)
, mpWeight(0)
{
	model->GetToken(); //{
	model->GetToken(); //FrameName
	//フレーム名エリア確保、設定
	mpFrameName = new char[strlen(model->mToken) + 1];
	strcpy(mpFrameName, model->mToken);
	//頂点番号数取得
	mIndexNum = model->GetIntToken();
	//頂点番号数が0を超える
	if (mIndexNum > 0){
		//頂点番号と頂点ウェイトのエリア確保
		mpIndex = new int[mIndexNum];
		mpWeight = new float[mIndexNum];
		//頂点番号取得
		for (int i = 0; i < mIndexNum; i++)
			mpIndex[i] = model->GetIntToken();
		//頂点ウェイト取得
		for (int i = 0; i < mIndexNum; i++)
			mpWeight[i] = model->GetFloatToken();
	}
	//オフセット行列取得
	for (int i = 0; i < 16; i++){
		mOffset.f[i] = model->GetFloatToken();
	}
	model->GetToken(); //}
#ifdef _DEBUG
	/*
	printf("SkinWeights %s\n", mpFrameName);
	if (mIndexNum > 0){
	for (int i = 0; i < mIndexNum; i++){
	printf("%d ", mpIndex[i]);
	printf("%f\n", mpWeight[i]);
	}
	}
	for (int i = 0; i < 16; i++){
	printf("%9f ", mOffset.f[i]);
	if (i % 4 == 3){
	printf("\n");
	}
	}
	*/
#endif
}

/*
CAnimationSet
*/
CAnimationSet::CAnimationSet(CModelX*model)
:mpName(0)
, mTime(0)
, mWeight(0)
, mMaxTime(0)
{
	model->mAnimationSet.push_back(this);
	model->GetToken(); //Animation Name
	//アニメーションの名前を退避
	mpName = new char[strlen(model->mToken) + 1];
	strcpy(mpName, model->mToken);
	model->GetToken(); //{
	while (*model->mpPointer != '\0'){
		model->GetToken(); //}orAnimation
		if (strchr(model->mToken, '}'))break;
		if (strcmp(model->mToken, "Animation") == 0){
			//Animation要素読み込み
			mAnimation.push_back(new CAnimation(model));
		}
	}
	//終了時間設定
	mMaxTime = mAnimation[0]->mpKey[mAnimation[0]->mKeyNum - 1].mTime;
#ifdef _DEBUG
	//printf("AnimationSet:%s\n", mpName);
#endif
}

CAnimation::CAnimation(CModelX*model)
:mpFrameName(0)
, mFrameIndex(0)
, mKeyNum(0)
, mpKey(0)
{
	model->GetToken(); //{ or Animation Name
	if (strchr(model->mToken, '{')){
		model->GetToken(); //{
	}
	else{
		model->GetToken(); //{
		model->GetToken(); //{
	}

	model->GetToken(); //FrameName
	mpFrameName = new char[strlen(model->mToken) + 1];
	strcpy(mpFrameName, model->mToken);
	mFrameIndex =
		model->FindFrame(model->mToken)->mIndex;
	model->GetToken(); //}
	//キーの配列を保存しておく配列
	CMatrix44*Key[4] = { 0, 0, 0, 0 };
	//時間の配列を保存しておく配列
	float*time[4] = { 0, 0, 0, 0 };
	while (*model->mpPointer != '\0'){
		model->GetToken(); //} or AnimationKey
		if (strchr(model->mToken, '}'))break;
		if (strcmp(model->mToken, "AnimationKey") == 0){
			model->GetToken(); //{
			//データのタイプ取得
			int type = model->GetIntToken();
			//時間数取得
			mKeyNum = model->GetIntToken();
			switch (type){
			case 0: //Rotation Quaternion
				//行列の配列を時間数分確保
				Key[type] = new CMatrix44[mKeyNum];
				//時間の配列を時間数分確保
				time[type] = new float[mKeyNum];
				//時間数分繰り返す
				for (int i = 0; i < mKeyNum; i++){
					time[type][i] = model->GetFloatToken();
					model->GetToken(); //4を読み飛ばし
					//w,x,y,zを取得
					float w = model->GetFloatToken();
					float x = model->GetFloatToken();
					float y = model->GetFloatToken();
					float z = model->GetFloatToken();
					//クォータニオンから回転行列に変換
					Key[type][i].SetQuaternion(x, y, z, w);
				}
				break;
			case 1: //拡大・縮小の行列作成
				Key[type] = new CMatrix44[mKeyNum];
				time[type] = new float[mKeyNum];
				for (int i = 0; i < mKeyNum; i++){
					time[type][i] = model->GetFloatToken();
					model->GetToken(); //3
					float x = model->GetFloatToken();
					float y = model->GetFloatToken();
					float z = model->GetFloatToken();
					Key[type][i].m00 = x;
					Key[type][i].m11 = y;
					Key[type][i].m22 = z;
				}
				break;
			case 2: //移動の行列作成
				Key[type] = new CMatrix44[mKeyNum];
				time[type] = new float[mKeyNum];
				for (int i = 0; i < mKeyNum; i++){
					time[type][i] = model->GetFloatToken();
					model->GetToken(); //3
					float x = model->GetFloatToken();
					float y = model->GetFloatToken();
					float z = model->GetFloatToken();
					CVector3 vec(x, y, z);
					Key[type][i].SetTranslate(vec);

				}
				break;
			case 4: //行列データの取得
				mpKey = new CAnimationKey[mKeyNum];
				for (int i = 0; i < mKeyNum; i++){
					mpKey[i].mTime = model->GetFloatToken(); //Time
					model->GetToken(); //16
					for (int j = 0; j < 16; j++){
						mpKey[i].mMatrix.f[j] = model->GetFloatToken();
					}
				}
				break;
			}
			model->GetToken(); //}
		}
		else{
			model->SkipNode();
		}
	} //Whileの終わり
	//行列データではない時
	if (mpKey == 0){
		//時間数分キーを作成
		mpKey = new CAnimationKey[mKeyNum];
		for (int i = 0; i<mKeyNum; i++){
			//時間設定
			mpKey[i].mTime = time[2][i]; //Time
			//行列作成 Position*Rotation*Size
			mpKey[i].mMatrix = Key[1][i] * Key[0][i] * Key[2][i];
		}
	}
	//確保したエリア解放
	for (int i = 0; i < ARRAY_SIZE(Key); i++){
		SAFE_DELETE_ARRAY(time[i]);
		SAFE_DELETE_ARRAY(Key[i]);
	}
	/*
	#ifdef _DEBUG
	printf("Animation:%s\n", mpFrameName);
	for (int i = 0; i < 16; i++){
	printf("%9f ", mpKey[0].mMatrix.f[i]);

	if (i % 4 == 3){
	printf("\n");
	}
	}
	#endif
	*/
}

/*
AnimationFrame
フレームの変換行列をアニメーションデータで更新する
*/
void CModelX::AnimateFrame(){
	//アニメーションで適用されるフレームの変換行列をゼロクリアにする
	for (int i = 0; i<mAnimationSet.size(); i++){
		CAnimationSet*anim = mAnimationSet[i];
		//重みが0は飛ばす
		if (anim->mWeight == 0)continue;
		//フレーム分(Animation分)繰り返す
		for (int j = 0; j<anim->mAnimation.size(); j++){
			CAnimation*animation = anim->mAnimation[j];
			//該当するフレームの変換行列をゼロクリアする
			memset(&mFrame[animation->mFrameIndex]->mTransformMatrix, 0, sizeof(CMatrix44));
		}
	}
	//アニメーションに該当するフレームの変換行列をアニメーションのデータで設定する
	for (int i = 0; i < mAnimationSet.size(); i++){
		CAnimationSet*anim = mAnimationSet[i];
		//重みが0は飛ばす
		if (anim->mWeight == 0)continue;
		//フレーム分(Animation分)繰り返す
		for (int j = 0; j < anim->mAnimation.size(); j++){
			//フレームを取得する
			CAnimation*animation = anim->mAnimation[j];
			CModelXFrame*frame = mFrame[animation->mFrameIndex];
			//キーが無い場合は飛ばす
			if (animation->mpKey == 0)continue;
			//時間を取得
			float time = anim->mTime;
			//最初の時間より小さい場合
			if (time < animation->mpKey[0].mTime){
				//変換行列を0コマ目の行列で更新
				frame->mTransformMatrix += animation->mpKey[0].mMatrix*anim->mWeight;
			}
			//最後の時間より大きい場合
			else if (time >= animation->mpKey[animation->mKeyNum - 1].mTime){
				//変換行列を最後のコマの行列で更新
				frame->mTransformMatrix += animation->mpKey[animation->mKeyNum - 1].mMatrix*anim->mWeight;
			}
			else{
				//時間の途中の場合
				for (int k = 1; k < animation->mKeyNum; k++){
					//変換行列を、線形補間にて更新
					if (time < animation->mpKey[k].mTime &&  animation->mpKey[k - 1].mTime != animation->mpKey[k].mTime){
						float r = (animation->mpKey[k].mTime - time) / (animation->mpKey[k].mTime - animation->mpKey[k - 1].mTime);
						frame->mTransformMatrix += (animation->mpKey[k - 1].mMatrix*r + animation->mpKey[k].mMatrix*(1 - r))*anim->mWeight;
						break;
					}
				}
			}
		}
	}
#ifdef _DEBUG
	/*
	for (int i = 0; i < mFrame.size(); i++){
	printf("Frame:%s\n", mFrame[i]->mpName);
	for (int j = 0; j < 16; j++){
	printf("%9f ", mFrame[i]->mTransformMatrix.f[j]);
	if (j % 4 == 3)
	printf("\n");
	}
	}
	*/
#endif
}

/*
AnimateVertex
頂点にアニメーションを適用する
*/
void CModelX::AnimateVertex(){
	//フレーム数分繰り返し
	for (int i = 0; i < mFrame.size(); i++){
		//メッシュに面があれば
		if (mFrame[i]->mMesh.mFaceNum>0){
			//頂点をアニメーションで更新する
			mFrame[i]->mMesh.AnimateVertex(this);
		}
	}
}



/*
AnimateCombined
合成行列の作成
*/
void CModelXFrame::AnimateCombined(CMatrix44*parent){
	//親からの変換行列に、自分の変換行列を掛ける
	mCombinedMatrix = mTransformMatrix * (*parent);
	//子フレームの合成行列を作成する
	for (int i = 0; i < mChild.size(); i++){
		mChild[i]->AnimateCombined(&mCombinedMatrix);
	}
}

/*
SetSkinWeightFrameIndex
スキンウェイトのフレーム番号を設定する
*/
void CModelX::SetSkinWeightFrameIndex(){
	//フレーム数分繰り返し
	for (int i = 0; i < mFrame.size(); i++){
		//メッシュに面があれば
		if (mFrame[i]->mMesh.mFaceNum>0){
			//スキンウェイト分繰り返し
			for (int j = 0; j < mFrame[i]->mMesh.mSkinWeights.size(); j++){
				//フレーム名のフレームを取得する
				CModelXFrame*frame = FindFrame(mFrame[i]->mMesh.mSkinWeights[j]->mpFrameName);
				//フレーム番号を設定する
				mFrame[i]->mMesh.mSkinWeights[j]->mFrameIndex = frame->mIndex;
			}
		}
	}
}

