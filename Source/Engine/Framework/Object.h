#pragma once
#include "Framework/Factory.h"
#include "Core/Json.h"
#include <string>

#define CLASS_DECLARATION(classname) \
	virtual const char* GetClassName(){return #classname;}\
	virtual void Read(const json_t& value); \
	virtual std::unique_ptr<Object> Clone() { return std::make_unique<classname>(*this); }\
	class Register \
	{ \
	public: \
		Register() \
		{ \
			Factory::Instance().Register<classname>(#classname); \
		} \
	}; 

#define CLASS_DEFINITION(classname) \
	classname::Register register_class;


namespace kiko {

	class Object
	{
	public:
		Object() = default;
		Object(std::string name) : m_name{name} {}
		~Object() { OnDestroy(); }

		CLASS_DECLARATION(Object)

		virtual bool Initialize() { return true; }
		virtual void OnDestroy() {}

		

	public:
		std::string m_name;
		bool active = true;
	};
}