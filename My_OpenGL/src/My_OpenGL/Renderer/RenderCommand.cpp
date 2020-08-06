#include "pch.h"
#include "RenderCommand.h"

namespace myo {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = CreateScope<RendererAPI>();

}