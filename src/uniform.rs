use wgpu::{BindGroupLayoutEntry, util::DeviceExt};

pub struct Uniform {
    pub layout: wgpu::BindGroupLayout,
    pub bind_group: wgpu::BindGroup,
}

impl Uniform {
    pub fn new(
        device: &wgpu::Device,
        layout: &wgpu::BindGroupLayoutDescriptor,
        resources: Vec<wgpu::BindingResource>,
        label: Option<&str>,
    ) -> Uniform {
        let layout = device.create_bind_group_layout(layout);

        let resources: Vec<_> = resources
            .into_iter()
            .enumerate()
            .map(|(i, r)| -> wgpu::BindGroupEntry {
                wgpu::BindGroupEntry {
                    binding: i as u32,
                    resource: r,
                }
            })
            .collect();

        let bind_group = device.create_bind_group(&wgpu::BindGroupDescriptor {
            layout: &layout,
            entries: resources.as_slice(),
            label,
        });

        Uniform { layout, bind_group }
    }

    pub fn new_with_buffer<T: bytemuck::Pod>(device: &wgpu::Device, contents: &[T]) -> Uniform {
        let buffer = device.create_buffer_init(&wgpu::util::BufferInitDescriptor {
            label: None,
            contents: bytemuck::cast_slice(contents),
            usage: wgpu::BufferUsages::UNIFORM | wgpu::BufferUsages::COPY_DST,
        });

        Self::new(
            device,
            &wgpu::BindGroupLayoutDescriptor {
                label: None,
                entries: &[BindGroupLayoutEntry {
                    binding: 0,
                    visibility: wgpu::ShaderStages::VERTEX_FRAGMENT,
                    ty: wgpu::BindingType::Buffer {
                        ty: wgpu::BufferBindingType::Uniform,
                        has_dynamic_offset: false,
                        min_binding_size: None,
                    },
                    count: None,
                }],
            },
            vec![buffer.as_entire_binding()],
            None,
        )
    }
}
