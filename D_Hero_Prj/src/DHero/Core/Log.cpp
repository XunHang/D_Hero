#include "dhpch.h"
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace DH {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init() {
		spdlog::set_pattern("%^[%T] %n:\t%v%$");

		s_CoreLogger = spdlog::stdout_color_mt("DH");
		s_CoreLogger->set_level(spdlog::level::trace);
		
		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}