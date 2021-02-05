#pragma once

#include "Irene/Core/Core.h"

namespace irene {

	struct FramebufferSpecification
	{
		uint32_t Width, Height;
		// FramebufferFormat Format = 
		uint32_t Samples = 1;

		bool SwapChainTarget = false;

		bool Multisample = false;
		bool Bloom = false;
	};

	class Framebuffer
	{
	public:
		virtual ~Framebuffer() = default;

		virtual void Bind() = 0;
		virtual void BindPingPongFramebuffer(uint32_t index) = 0; // for Bloom
		virtual void Blit() = 0;	// for MSAA
		virtual void Unbind() = 0;
		virtual void BindColorAttachment(uint32_t slot = 0) = 0;
		virtual void BindColorAttachmentArray(uint32_t index, uint32_t slot = 0) = 0; // for Bloom
		virtual void BindPingPongColorAttachment(uint32_t index, uint32_t slot = 0) = 0; // for Bloom

		virtual void Resize(uint32_t width, uint32_t height) = 0;

		virtual uint32_t GetScreenTextureID() const = 0;
		virtual uint32_t GetColorAttachmentID() const = 0;
		virtual uint32_t GetColorAttachmemtArrayID(uint32_t index) const = 0;
		virtual uint32_t GetPingPongColorAttachmentID(uint32_t index) const = 0;

		virtual const FramebufferSpecification& GetSpecification() const = 0;

		static Ref<Framebuffer> Create(const FramebufferSpecification& spec);
	};

}

