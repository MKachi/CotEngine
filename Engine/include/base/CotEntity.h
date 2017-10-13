#pragma once

#include "CotBroadCastProtocol.h"
#include "CotTime.h"
#include "math/CotMath.h"
#include "CotVectorMap.hpp"

namespace Cot
{
	class COT_API Entity
	{
	protected:
		string		_name;
		bool		_active;
		Vec3		_position;
		Vec3		_rotate;
		Vec3		_scale;
		Entity*		_parent;

		std::vector<Entity*> _children;
		BroadCastProtocol*	 _broadCastProtocol;
		MultiVectorMap<string, class IComponent*> _components;

	public:
		Entity() = delete;
		Entity(const string& name);
		virtual ~Entity();

		template <typename T>
		inline T* AddComponent()
		{
			T* result = new T();
			result->SetOwner(this);
			_components.add(result->GetName(), result);
			return result;
		}

		template <typename T>
		inline void RemoveComponent()
		{
			string key = ComponentType<T>::GetType();
			T* temp = static_cast<T*>(_components.find(key));
			_components.remove(key);
			SafeDelete(temp);
		}

		template <typename T>
		inline T* GetComponent()
		{
			string key = ComponentType<T>::GetType();
			return _components.find<T*>(key);
		}

		template <typename T>
		inline std::vector<T*> GetComponents()
		{
			string key = ComponentType<T>::GetType();
			return _components.finds<T*>(key);
		}

		void CreateBroadCastProtocol();
		void AddBroadCastListener(const string& name, const std::function<void()>& function);
		void SendMsg(const string& function);
		void BroadCastMsg(const string& function);

		void AddChild(Entity* child);
		std::vector<Entity*>& GetChildren() { return _children; }

		void RemoveChild(Entity* child);
		void RemoveChildByName(const string& name);
		void RemoveAllChild();

		void SetName(const string& name);
		string GetName() { return _name; }

		void SetParent(Entity* parent);
		Entity* GetParent() { return _parent; }

		void SetPosition(const Vec3& position);
		void SetPositionX(float x);
		void SetPositionY(float y);
		void SetPositionZ(float z);
		Vec3 GetPosition() { return _position; }

		void SetRotateAxis(float deg, const Vec3& axis);
		Vec3 GetRotate() { return _rotate; }

		void SetScale(const Vec3& scale);
		void SetScaleX(float x);
		void SetScaleY(float y);
		void SetScaleZ(float z);
		Vec3 GetScale() { return _scale; }

		void SetLocalPosition(const Vec3& position);
		void SetLocalPositionX(float x);
		void SetLocalPositionY(float y);
		void SetLocalPositionZ(float z);
		Vec3 GetLocalPosition();

		void SetLocalRotateAxis(float deg, const Vec3& axis);
		Vec3 GetLocalRotate();

		void SetLocalScale(const Vec3& scale);
		void SetLocalScaleX(float x);
		void SetLocalScaleY(float y);
		void SetLocalScaleZ(float z);
		Vec3 GetLocalScale();

		void SetActive(bool active);
		bool IsActive() { return _active; }

		virtual void Update(Time& time);

	};
}