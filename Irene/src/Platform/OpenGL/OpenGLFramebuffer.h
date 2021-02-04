#pragma once

#include "Irene/Renderer/Framebuffer.h"

namespace irene {

	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification& spec, bool antiAliasing = false);
		virtual ~OpenGLFramebuffer();

		void Invalidate();
		void MultisampleInvalidate(); // for MSAA


		virtual void Bind() override;
		virtual void Unbind() override;
		virtual void Blit() override;	// for MSAA
		virtual void BindColorAttachment(uint32_t slot = 0) override;

		virtual void Resize(uint32_t width, uint32_t height) override;

		virtual uint32_t GetColorAttachmentRendererID() const override { return m_ScreenTextureID; }

		virtual const FramebufferSpecification& GetSpecification() const override { return m_Specification; }

	private:
		uint32_t m_RendererID = 0;
		uint32_t m_ColorAttachment = 0;
		uint32_t m_DepthAttachment = 0;
		
		// for MSAA
		uint32_t m_IntRendererID = 0;
		uint32_t m_ScreenTextureID = 0;

		bool m_Multisample;
		FramebufferSpecification m_Specification;
	};

}

