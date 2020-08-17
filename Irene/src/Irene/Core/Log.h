#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

// DON'T FORGET TO CALL Log::Init() IN main()
namespace irene {

	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

#define CORE_TRACE(...)			irene::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CORE_INFO(...)			irene::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_WARN(...)			irene::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_ERROR(...)			irene::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_CRITICAL(...)		irene::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define CLIENT_TRACE(...)		irene::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CLIENT_INFO(...)		irene::Log::GetClientLogger()->info(__VA_ARGS__)
#define CLIENT_WARN(...)		irene::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CLIENT_ERROR(...)		irene::Log::GetClientLogger()->error(__VA_ARGS__)
#define CLIENT_CRITICAL(...)	irene::Log::GetClientLogger()->critical(__VA_ARGS__)
