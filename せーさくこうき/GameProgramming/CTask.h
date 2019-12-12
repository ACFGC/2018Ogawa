#ifndef CTASK_H
#define CTASK_H

#include "CMatrix44.h"
#include "CCollider.h"

class CTask;

/*
�^�X�N�Ǘ��N���X�̒�`
*/
class CTaskManager {
private:
	//private�̃����o�́A�����̃N���X�����A�N�Z�X�ł���
	//�C���X�^���X�̃|�C���^
	static CTaskManager *mpInstance;
	//�擪�|�C���^
	CTask *mpHead;
	//�ŏI�|�C���^
	CTask *mpTail;
	CTaskManager()
		: mpHead(0)
		, mpTail(0)
	{}
public:
	//public�̃����o�́A�S�ẴN���X����A�N�Z�X�ł���
	//�C���X�^���X�̎擾
	static CTaskManager* Get();
	//�^�X�N�����X�g�֒ǉ�����
	void Add(CTask *p);
	//�^�X�N�̍X�V
	void Update();
	//�^�X�N�̕`��
	void Render();
	//�j������
	void Destroy();
	//���ڍ폜����
	void Delete();
	//���ڂ����X�g����폜
	void Remove(CTask*);
};


class CTask {
public:
	//�^�X�N�̎��ʒl
	enum ETaskTag {
		EPLAYER,	//�v���C���[
		EOBJECT,
		EGOAL,
		EHAPPY,
		EWIND,
	};
	//�^�X�N�̎���
	ETaskTag mTaskTag;
	//�L���t���O
	bool mEnabled;
	//���̃^�X�N�ւ̃|�C���^
	CTask *mpNext;
	CTask *mpPrev;
	//�����s��
	CMatrix44 mMatrix;
	//�R���X�g���N�^
	CTask()
		: mEnabled(true)
		, mpNext(0)
		, mpPrev(0)
	{
		//�^�X�N���X�g�ɒǉ�
		CTaskManager::Get()->Add(this);
	}
	virtual ~CTask() {
		//�^�X�N���X�g����폜
		CTaskManager::Get()->Remove(this);
	}
	//����������
	virtual void Init() {};
	//�X�V����
	virtual void Update() {};
	//�`�揈��
	virtual void Render() {};
	//�Փˏ���
	virtual void OnCollision(C3DCollider *i, C3DCollider *y) {};
};

#endif
