#include "CTask.h"

//�C���X�^���X��static�ϐ�
CTaskManager* CTaskManager::mpInstance = 0;
//�C���X�^���X�̎擾
CTaskManager* CTaskManager::Get() {
	//�C���X�^���X������(0)�̎�
	if (mpInstance == 0) {
		//�C���X�^���X���쐬���đ��
		mpInstance = new CTaskManager();
	}
	//�C���X�^���X�̃|�C���^��Ԃ�
	return mpInstance;
}

//���X�g�֒ǉ�
void CTaskManager::Add(CTask *p) {
	if (mpHead == 0) {
		//���X�g�̍ŏ�
		//���X�g�̐擪�ɂ���
		mpHead = p;
		mpHead->mpPrev = 0;
		//���X�g�̍Ō�ɂ���
		mpTail = p;
		//�Ō�̎��͖����ɂ���
		mpTail->mpNext = 0;
	}
	else {
		//�Ō�ɒǉ�
		mpTail->mpNext = p;
		p->mpPrev = mpTail;
		mpTail = p;
		p->mpNext = 0;
	}
}

//�X�V����
void CTaskManager::Update() {
	//���X�g�̃^�X�N��task�ŎQ�Ƃ��Ă���
	CTask *task = mpHead;
	//task��0�ɂȂ�����I��
	while (task) {
		//�X�V����
		task->Update();
		//���̃��X�g��
		task = task->mpNext;
	}
}

//�`�揈��
void CTaskManager::Render() {
	//���X�g�̃^�X�N��task�ŎQ�Ƃ��Ă���
	CTask *task = mpHead;
	//task��0�ɂȂ�����I��
	while (task) {
		//�`�揈��
		task->Render();
		//���̃��X�g��
		task = task->mpNext;
	}
}

//�j������
void CTaskManager::Destroy() {
	//���X�g��col�ŎQ�Ƃ��Ă���
	CTask *col = mpHead;
	//col��0�ɂȂ�����I��
	while (col) {
		//���̃|�C���^��ޔ�
		CTask *next = col->mpNext;
		//���ڂ��폜
		delete col;
		//���̃��X�g��
		col = next;
	}
	//�ՓˊǗ��̃C���X�^���X�폜
	delete mpInstance;
	//�C���X�^���X�ւ̃|�C���^������
	mpInstance = 0;
}

//���ڍ폜����
void CTaskManager::Delete() {
	//�O�̍��ڂ̃|�C���^
	CTask *prev = 0;
	//���X�g��col�ŎQ�Ƃ��Ă���
	CTask *col = mpHead;
	//col�̏��L�҂������ȍ��ڂ͍폜
	while (col) {
		//����������
		if (!col->mEnabled) {
			CTask *next = col->mpNext;
			delete col;
			col = next;
		}
		else {
			//�L���ȏꍇ�͎���
			prev = col;
			col = col->mpNext;
		}
	}
	//�ŏI�̍��ڂ��X�V
	mpTail = prev;
	if (mpTail)
		mpTail->mpNext = 0;
}

void CTaskManager::Remove(CTask* p) {
	if (p == mpHead) {
		mpHead = p->mpNext;
		if (mpHead)
			mpHead->mpPrev = 0;
		else
			mpTail = 0;
	}
	else if (p == mpTail) {
		mpTail = p->mpPrev;
		if (mpTail)
			mpTail->mpNext = 0;
	}
	else {
		p->mpPrev->mpNext = p->mpNext;
		p->mpNext->mpPrev = p->mpPrev;
	}
}
