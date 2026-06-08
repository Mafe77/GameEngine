#include "gepch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGl/OpenGLBuffer.h"

namespace GameEngine
{
	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	GE_CORE_ASSERT(false, "RendererAPI::None not supported."); return nullptr;
			case RendererAPI::API::OpenGL:	return  CreateRef<OpenGLVertexBuffer>(size);
		}

		GE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	GE_CORE_ASSERT(false, "RendererAPI::None not supported."); return nullptr;
			case RendererAPI::API::OpenGL:	return  CreateRef<OpenGLVertexBuffer>(vertices, size);
		}

		GE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	GE_CORE_ASSERT(false, "RendererAPI::None not supported."); return nullptr;
			case RendererAPI::API::OpenGL:	return CreateRef<OpenGLIndexBuffer>(indices, count);
		}

		GE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}