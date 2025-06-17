pub struct Shader {
    pub module: wgpu::ShaderModule,
}

impl Shader {
    pub fn new(source: &str, device: &wgpu::Device, label: Option<&str>) -> Shader {
        let module = device.create_shader_module(wgpu::ShaderModuleDescriptor {
            label,
            source: wgpu::ShaderSource::Wgsl(source.into()),
        });

        Shader { module }
    }
}
