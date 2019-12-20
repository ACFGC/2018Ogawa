#include "CScene.h"

#include "CCharacter.h"
#include "CPlayer.h"
#include "CBreak.h"
#include "CGoal.h"
#include "CHappy.h"
#include "CWind.h"
#include "CTramPoline.h"
#include "CMove.h"
#include "CHammer.h"
#include "CInput.h"
#include <stdio.h>


//���߂�1�񂾂����s���鏈���̒�`
void CScene::Init() {
	//?
	mModelX.Load("���O�i.x");
//	mXPlayer.Init(&mModelX);
//	mXPlayer.mPosition = CVector3(00.0f, 20.0f, 40.0f);

	//������
	new CCharacter(0.0f, 0.0f, 50.0f, 20.0f, 1.0f, 20.0f, 0.0f, 0.0f, 0.0f);
	//������
	new CCharacter(0.0f, 0.0f, -20.0f, 20.0f, 1.0f, 20.0f, 0.0f, 0.0f, 0.0f);
	//������
	new CCharacter(0.0f, 0.0f, -100.0f, 20.0f, 1.0f, 20.0f, 0.0f, 0.0f, 0.0f);
	//������
	new CCharacter(-10.0f, 0.0f, -180.0f, 5.0f, 1.0f, 20.0f, 0.0f, 0.0f, 0.0f);
	//������
	new CCharacter(-10.0f, 0.0f, -240.0f, 5.0f, 1.0f, 20.0f, 0.0f, 0.0f, 0.0f);
	//������
	new CCharacter(-10.0f, 0.0f, -320.0f, 5.0f, 1.0f, 20.0f, 0.0f, 0.0f, 0.0f);

	//�v���C���[����
	CPlayer *player = new CPlayer(0.0f, 50.0f, 50.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	player->mXCharacter.Init(&mModelX);

	 //�S�[������
	//new CGoal(0.0f, 30.0f, -160.0f, 20.0f, 30.0f, 20.0f, 0.0f, 0.0f, 0.0f);

	//�n�b�s�[�]�[������
	new CHappy(-20.0f, 3.0f, 30.0f, 2.0f, 2.0f, 2.0f, 0.0f, 0.0f, 0.0f);

	//�␶��
	new CCharacter(1.0f, 5.0f, 10.0f, 10.0f, 1.0f, 10.0f, 30.0f, 0.0f, 0.0f);
	//�ǐ���
	new CCharacter(20.0f, 10.0f, 0.0f, 20.0f, 1.0f, 10.0f, 90.0f, 90.0f, .0f);

	//�g�����|��������
	new CTrampoline(0.0f, 0.0f, -60.0f, 10.0f, 1.0f, 10.0f, 0.0f, 0.0f, 0.0f);

	//���G���A
	new CWind(0.0f, 00.0f, -140.0f, 10.0f, 1.0f, 10.0f, 0.0f, 0.0f, 0.0f);

	//������
	new CMove(-30.0f, 10.0f, -210.0f, 10.0f, 10.0f, 1.0f, 0.0f, 0.0f, 0.0f);

	//��]��
	new CHammer(0.0f, 10.0f, 30.0f, 10.0f, 10.0f, 1.0f, 0.0f, 90.0f, 0.0f);

	//������u���b�N����
	new CBreak(-10.0f, 0.0f, -280.0f, 5.0f, 1.0f, 20.0f, 0.0f, 0.0f, 0.0f);
	/*	new CBreak(2.0f, 15.0f, -10.0f, 1.0f, 1.0f, 1.0f);
	new CBreak(4.0f, 10.0f, -10.0f, 1.0f, 1.0f, 1.0f);
	*/
}

//�J��Ԃ����s���鏈���̒�`
void CScene::Update() {
	//?
//	mXPlayer.Update();

	//�^�X�N���X�V���Ă���
	CTaskManager::Get()->Update();
	//�Փˏ���
	CCollisionManager::Get()->Update();
	//�����ȃ^�X�N���폜���Ă���
	CTaskManager::Get()->Delete();

	//�}�E�X�̍��{�^��������Ă��邩 
	if (CInput::GetMouseButton(GLFW_MOUSE_BUTTON_LEFT)) {
		//�}�E�X���W�ϐ��쐬 
		float x, y;
		//�}�E�X�J�[�\���̍��W�擾 
		CInput::GetCursorPos(&x, &y);
		//���W���R���\�[���ɕ\�� 
		printf("%10f %10f\n", x, y);
	}

	
	CVector3 eye = CPlayer::spInstance->mBox.mMatrix * CVector3(0.0f, 3.0f, 10.0f);
	//���_�̐ݒ�i�J�����̐ݒ�j
	//gluLookAt(�ڂ̈ʒu(x,y,z)�C�ڕW�̈ʒu(x,y,z)�C�����(x,y,z))
	gluLookAt(eye.x, eye.y, eye.z, CPlayer::spInstance->mPosition.x, CPlayer::spInstance->mPosition.y, CPlayer::spInstance->mPosition.z, 0.0f, 1.0f, 0.0f);

	static GLfloat lightPosition[4] = { 200.0, 200.0, 20.0, 5.0 }; //�����̈ʒu
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition); //�����ʒu�̐ݒ�

	//�^�X�N��`�悵�Ă���
	CTaskManager::Get()->Render();
	CCollisionManager::Get()->Render();
	//?
//	mXPlayer.Render();

	//2D���W��UI��`��
	//�s����v���W�F�N�V�������[�h�֕ύX
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();		//�v���W�F�N�V�����s���ޔ�
	glLoadIdentity();	//�v���W�F�N�V�����s���������
	//�v���W�F�N�V�����s���800�~600�ɐݒ�
	gluOrtho2D(-400, 400, -300, 300);
	//�s������f���r���[���[�h�֕ύX
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();		//���f���r���[�s���ޔ�
	glLoadIdentity();	//���f���r���[�s���������

	glDisable(GL_LIGHTING);	//���C�g����
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);	//�`��F

	char buf[10];
	//������ݒ�
	mText.DrawString("SPACE:Jump W:Front A:< S:Back D:>", -350, 250, 10, 20);	//������`��

	//�S�[���ɐG����
	if (CPlayer::spInstance->Goal <= 0){
		mText.DrawString("Goal!", -220, 0, 60, 60);//������`��
	}

	//�������
	//�S�[���ɐG����
	if (CPlayer::spInstance->Goal >= 2){
		mText.DrawString("Failure", -220, 0, 40, 40);//������`��
	}

	//�n�b�s�[��Ԃ̎���
	mText.DrawString("Happy:", -350, -250, 10, 20);	//������`��
	sprintf(buf, "%d", (CPlayer::spInstance->Happy+59)/60);
	mText.DrawString(buf, -220, -250, 10, 20);	//������`��

	//�^�C���\��
	mText.DrawString("Time:", 240, -250, 10, 20);	//������`��
	sprintf(buf, "%d", (CPlayer::spInstance->Time + 59) / 60);
	mText.DrawString(buf, 350, -250, 10, 20);	//������`��

	glEnable(GL_LIGHTING);	//���C�h�L��

	glPopMatrix();	//���f���r���[�`��s���߂�
	//�s����v���W�F�N�V�������[�h�֕ύX
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();	//�v���W�F�N�V�����s���߂�
	//�s������f���r���[���[�h�֕ύX
	glMatrixMode(GL_MODELVIEW);

}
