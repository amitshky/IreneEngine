#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

// DON'T FORGET TO CALL Log::Init() IN main()
namespace myo {

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

#define CORE_TRACE(...)			myo::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CORE_INFO(...)			myo::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_WARN(...)			myo::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_ERROR(...)			myo::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_CRITICAL(...)		myo::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define CLIENT_TRACE(...)		myo::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CLIENT_INFO(...)		myo::Log::GetClientLogger()->info(__VA_ARGS__)
#define CLIENT_WARN(...)		myo::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CLIENT_ERROR(...)		myo::Log::GetClientLogger()->error(__VA_ARGS__)
#define CLIENT_CRITICAL(...)	myo::Log::GetClientLogger()->critical(__VA_ARGS__)
