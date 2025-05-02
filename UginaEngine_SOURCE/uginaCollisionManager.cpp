#include "uginaCollisionManager.h"
#include "uginaScene.h"
#include "uginaSceneManager.h"
#include "uginaTransform.h"
namespace ugina
{

	std::bitset<(UINT)eLayerType::Max> 
		CollisionManager::mCollisionLayerMatrix[(UINT)eLayerType::Max] = {};

	std::unordered_map<UINT64, bool> CollisionManager::mCollisionMap = {};
	void CollisionManager::Initialize()
	{
		int a = 1;
		int b = a << 1;
	}
	void CollisionManager::Update()
	{
		Scene* scene = SceneManager::Getactivescene();
		for (UINT row = 0; row < (UINT)eLayerType::Max; row++)
		{
			for (UINT col = 0; col < (UINT)eLayerType::Max; col++)
			{
				if (mCollisionLayerMatrix[row][col] == true)
				{
					LayerCollision(scene, (eLayerType)row, (eLayerType)col);
				}
			}
		}
	}
	void CollisionManager::LateUpdate()
	{
	}
	void CollisionManager::Render(HDC hdc)
	{
	}
	void CollisionManager::Clear()
	{
		mCollisionMap.clear();
		mCollisionLayerMatrix->reset();
	}
	//���̾�� �浹���� ������ �����ϴ� �Լ�
	//left : �浹 üũ�� ���̾�1
	//right : �浹 üũ�� ���̾�1
	//enable : ���� �η��̾�� �浹 üũ�� �Ұ��� �ƴ��� ����
	void CollisionManager::CollisionLayerCheck(eLayerType left, eLayerType right, bool enable)
	{
		//�ݸ��� ����ũ�� ��� ��
		int row = 0;

		int col = 0;

		//������(enum���� �� ������)�� ������ ���Ƴֱ�(�ߺ��� ���ֱ� ����)
		//0 0 0 0 0
		//x 0 0 0 0
		//x x 0 0 0
		//x x x 0 0
		//x x x x 0
		if (left <= right)
		{
			row = (UINT)left;
			col = (UINT)right;
		}
		else
		{
			row = (UINT)right;
			col = (UINT)left;
		}
		mCollisionLayerMatrix[row][col] = enable;
	}
	//���̾�� �浹�� �˻��ϴ� �Լ�
	void CollisionManager::LayerCollision(Scene* scene, eLayerType left, eLayerType right)
	{
		//Ư�� ���̾��� ���ο� �ִ� ���ӿ�����Ʈ ���͸� �������� �ʰ�
		//���� �״�� �����Ͽ� �������� �ϱ��������� ���Ϳ� ������ ����
		const std::vector<GameObject*>& lefts = SceneManager::GetGameObjects(left);
		const std::vector<GameObject*>& rights = SceneManager::GetGameObjects(right);
		
		for (GameObject* left : lefts)
		{
			//Ȱ��ȭ�� ������Ʈ�鸸 üũ
			if (left->IsActive() == false)
			{
				continue;
			}
			Collider* leftCol = left->GetComponent<Collider>();
			//�ݶ��̴��� �����ϴ��� üũ
			if (leftCol == nullptr)
			{
				continue;
			}
			for (GameObject* right: rights)
			{
				if (right->IsActive() == false)
				{
					continue;
				}
				Collider* rightCol = right->GetComponent<Collider>();
				if (rightCol == nullptr)
				{
					continue;
				}
				//�ڱ� �ڽ��� �浹�� ��ŵ
				if (left == right)
				{
					continue;
				}
				ColliderCollision(leftCol, rightCol);
			}
		}
	}
	void CollisionManager::ColliderCollision(Collider* left, Collider* right)
	{
		CollisionID id = {};
		id.left = left->GetID();
		id.right = right->GetID();
		auto iter = mCollisionMap.find(id.id);
		if (iter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(id.id, false));
			iter = mCollisionMap.find(id.id);
		}
		if (Intersect(left, right))
		{
			if (iter->second == false)
			{
				left->OnCollisionEnter(right);
				right->OnCollisionEnter(left);
				iter->second = true;
			}
			else
			{
				left->OnCollisionStay(right);
				right->OnCollisionStay(left);
			}
		}
		else
		{
			if (iter->second == true)
			{
				left->OnCollisionExit(right);
				right->OnCollisionExit(left);

				iter->second = false;
			}
		}
	}
	
	bool CollisionManager::Intersect(Collider* left, Collider* right)
	{
		Transform* leftTr = left->GetOwner()->GetComponent<Transform>();
		Transform* rightTr = right->GetOwner()->GetComponent<Transform>();

		Vector2 leftPos = leftTr->GetPosition() + left->GetOffset();
		Vector2 rightPos = rightTr->GetPosition() + right->GetOffset();

		Vector2 leftSize = left->GetSize() * 100.0f;
		Vector2 rightSize = right->GetSize() * 100.0f;

		////fabs�� �Ǽ��� ������ �������ִ� �Լ�
		//if(fabs(leftPos.x - rightPos.x)<fabs(leftSize.x/2.0f + rightSize.x / 2.0f)
		//	&& fabs(leftPos.y - rightPos.y)<fabs(leftSize.y /2.0f +rightSize.y/ 2.0f))
		//{
		//	return true;
		//}
		enums::eColliderType leftType = left->GetColliderType();
		enums::eColliderType rightType = right->GetColliderType();

		if (leftType == enums::eColliderType::Rect2D&&rightType==enums::eColliderType::Rect2D)
		{
			if (fabs(leftPos.x - rightPos.x) < fabs(leftSize.x / 2.0f + rightSize.x / 2.0f)
				&& fabs(leftPos.y - rightPos.y) < fabs(leftSize.y / 2.0f + rightSize.y / 2.0f))
			{
				return true;
			}
		}
		if (leftType == enums::eColliderType::Circle2D && rightType == enums::eColliderType::Circle2D)
		{
			Vector2 leftCirclePos = leftPos + (leftSize / 2.0f);
			Vector2 rightCirclePos = rightPos + (rightSize / 2.0f);
			float distance = (leftCirclePos - rightCirclePos).length();
			if (distance <= (leftSize.x / 2.0f + rightSize.x / 2.0f))
			{
				return true;
			}
		}
		if ((leftType == enums::eColliderType::Circle2D && rightType == enums::eColliderType::Rect2D)
			|| (leftType == enums::eColliderType::Rect2D && rightType == enums::eColliderType::Circle2D))
		{
			//�����ݶ��̴��� ��
			if (leftType == enums::eColliderType::Circle2D)
			{
				//������Ʈ�� �߽���ǥ +��Ŭ �ݶ��̴��� ������ 
				//�簢���� �ּ� ��ǥ , �ִ� ��ǥ
				int clx = std::clamp(leftPos.x, rightPos.x -(rightSize.x/2),rightPos.x + (rightSize.x/2) );
				int cly = std::clamp(leftPos.y, rightPos.y -(rightSize.y/2),rightPos.y + (rightSize.y/2) );
				//���� ��ǥ���� �簢������ ���� �߽ɱ��� �ִ�� ����� ��ǩ���� ���� ����
				int distX = leftPos.x - clx;
				int distY = leftPos.y - cly;
				int one = distX * distX + distY * distY;
				int two = (leftSize.x / 2) * (leftSize.x / 2) + (leftSize.y / 2) * (leftSize.y / 2);
				
				//���� �������� ������ ���� ��ǩ���� ���̰� �� ū��� �浹�Ѱ����� ����
				if (one <= two)
				{
					return true;
				}
			}
			//������ �ݶ��̴��� ��
			else
			{
				int clx = std::clamp(rightPos.x, leftPos.x - (leftSize.x / 2), leftPos.x + (leftSize.x / 2));
				int cly = std::clamp(rightPos.y, leftPos.y - (leftSize.y / 2), leftPos.y + (leftSize.y / 2));
				int distX = rightPos.x - clx;
				int distY = rightPos.y - cly;
				//TODO
				if (distX * distX + distY * distY <= (rightSize.x / 2) * (rightSize.x / 2) + (rightSize.y / 2) * (rightSize.y / 2))
				{
					return true;
				}
			}
			
			
		}
	return false;
	}
}