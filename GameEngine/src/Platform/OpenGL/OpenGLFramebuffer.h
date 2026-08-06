#pragma once

#include "GameEngine/Renderer/Framebuffer.h"

namespace GameEngine
{
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpec& spec);
		virtual ~OpenGLFramebuffer();

		void Invalidate();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void Resize(uint32_t width, uint32_t height) override;
		virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) override;

		virtual void ClearAttachment(uint32_t attachmentIndex, int value) override;

		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const override 
		{
			GE_CORE_ASSERT(index < m_ColorAttachments.size(), "ColorAttachment wrong size."); 
			return m_ColorAttachments[index];
		}

		virtual const FramebufferSpec& GetSpecification() const override { return m_Specification; }

	private:
		uint32_t m_RendererID = 0;
		FramebufferSpec m_Specification;

		std::vector<FramebufferTextureSpec> m_ColorAttachmentSpec;
		FramebufferTextureSpec m_DepthAttachmentSpec = FramebufferTextureFormat::None;

		std::vector<uint32_t> m_ColorAttachments;
		uint32_t m_DepthAttachment = 0;

	};
}