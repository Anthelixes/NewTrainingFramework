#pragma once
#include <string>

struct TextureResource
{
	std::string	type;
	std::string	path;
	std::string	min_filter;
	std::string	mag_filter;
	std::string	wrap_s;
	std::string	wrap_t;
};