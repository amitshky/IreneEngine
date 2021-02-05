#pragma once

#include "Irene/Renderer/Framebuffer.h"

namespace irene {

	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification& spec);
		virtual ~OpenGLFramebuffer();

		void Invalidate();
		void MultisampleInvalidate(); // for MSAA
		void BloomInvalidate(); // for Bloom

		virtual void Bind() override;
		virtual void BindPingPongFramebuffer(uint32_t index) override; // for Bloom // remove later
		virtual void Unbind() override;
		virtual void Blit() override;	// for MSAA
		virtual void BindColorAttachment(uint32_t slot = 0) override;
		virtual void BindColorAttachmentArray(uint32_t index, uint32_t slot = 0) override; // for Bloom
		virtual void BindPingPongColorAttachment(uint32_t index, uint32_t slot = 0) override; // for Bloom

		virtual void Resize(uint32_t width, uint32_t height) override;

		virtual uint32_t GetScreenTextureID() const override { return m_ScreenTextureID; }
		virtual uint32_t GetColorAttachmentID() const override { return m_ColorAttachment; }
		virtual uint32_t GetColorAttachmemtArrayID(uint32_t index) const override { return m_ColorAttachmentArray[index]; }
		virtual uint32_t GetPingPongColorAttachmentID(uint32_t index) const override { return m_PingPongColorAttachment[index]; }

		virtual const FramebufferSpecification& GetSpecification() const override { return m_Specification; }

	private:
		uint32_t m_RendererID = 0;
		uint32_t m_ColorAttachment = 0;
		uint32_t m_DepthAttachment = 0;

		// for Bloom
		uint32_t m_ColorAttachmentArray[2] = { 0 };
		uint32_t m_PingPongColorAttachment[2] = { 0 };
		uint32_t m_PingPongRendererID[2] = { 0 };
		
		// for MSAA
		uint32_t m_IntRendererID = 0;
		uint32_t m_ScreenTextureID = 0;

		FramebufferSpecification m_Specification;
	};

}

