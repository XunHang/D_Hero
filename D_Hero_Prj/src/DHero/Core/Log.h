#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace DH {
	class DH_API Log
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger> s_GetCoreLogger() { return s_CoreLogger; }
		static std::shared_ptr<spdlog::logger> s_GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core Log Macro
#define DH_CORE_TRACE(...) ::DH::Log::s_GetCoreLogger()->trace(__VA_ARGS__)
#define DH_CORE_INFO(...)  ::DH::Log::s_GetCoreLogger()->info(__VA_ARGS__)
#define DH_CORE_WARN(...)  ::DH::Log::s_GetCoreLogger()->warn(__VA_ARGS__)
#define DH_CORE_ERROR(...) ::DH::Log::s_GetCoreLogger()->error(__VA_ARGS__)
#define DH_CORE_FATAL(...) ::DH::Log::s_GetCoreLogger()->fatal(__VA_ARGS__)

// Client Log Macro
#define DH_TRACE(...) ::DH::Log::s_GetClientLogger()->trace(__VA_ARGS__)
#define DH_INFO(...)  ::DH::Log::s_GetClientLogger()->info(__VA_ARGS__)
#define DH_WARN(...)  ::DH::Log::s_GetClientLogger()->warn(__VA_ARGS__)
#define DH_ERROR(...) ::DH::Log::s_GetClientLogger()->error(__VA_ARGS__)
#define DH_FATAL(...) ::DH::Log::s_GetClientLogger()->fatal(__VA_ARGS__)
