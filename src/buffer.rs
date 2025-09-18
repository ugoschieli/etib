use bytemuck::Pod;
use wgpu::util::DeviceExt;

pub struct VertexBuffer<'a, T: Pod> {
    pub buffer: wgpu::Buffer,
    pub content: &'a [T],
    pub layout: wgpu::VertexBufferLayout<'static>,
}

impl<'a, T: Pod> VertexBuffer<'a, T> {
    pub fn new(
        device: &wgpu::Device,
        content: &'a [T],
        layout: wgpu::VertexBufferLayout<'static>,
    ) -> VertexBuffer<'a, T> {
        let buffer = device.create_buffer_init(&wgpu::util::BufferInitDescriptor {
            label: Some("Vertex Buffer"),
            contents: bytemuck::cast_slice(content),
            usage: wgpu::BufferUsages::VERTEX,
        });

        VertexBuffer {
            buffer,
            content,
            layout,
        }
    }
}

pub trait BufferExt<'a, T: Pod> {
    fn create_vertex_buffer(
        &self,
        content: &'a [T],
        layout: wgpu::VertexBufferLayout<'static>,
    ) -> VertexBuffer<'a, T>;
}

impl<'a, T: Pod> BufferExt<'a, T> for wgpu::Device {
    fn create_vertex_buffer(
        &self,
        content: &'a [T],
        layout: wgpu::VertexBufferLayout<'static>,
    ) -> VertexBuffer<'a, T> {
        VertexBuffer::new(self, content, layout)
    }
}
