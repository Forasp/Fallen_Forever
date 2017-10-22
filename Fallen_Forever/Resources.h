#pragma once
#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>


template<typename Resource, typename Identifier>

class Resources
{
private:
	void AddResource(Identifier _ID, const std::string& _Filename);

	std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;

public:
	void LoadResource(Identifier _ID, const std::string& _Filename);

	template<typename Parameters>
	void LoadResource(Identifier _ID, const std::string& _Filename, const Parameters& secondParam);

	Resource& GetResource(Identifier _ID);
	const Resource& GetResource(Identifier _ID);
};

#include "Resources.inl"
