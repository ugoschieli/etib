use crate::gfx::Gfx;

use std::sync::Arc;
use std::time::Instant;
use winit::application::ApplicationHandler;
use winit::error::EventLoopError;
use winit::event::WindowEvent;
use winit::event_loop::{ActiveEventLoop, ControlFlow, EventLoop};
use winit::window::{Window, WindowId};

pub struct App {
    pub window: Option<Arc<Window>>,
    pub gfx: Option<Gfx>,
    pub dt: f32,
    last_time: Instant,
}

impl App {
    pub fn new() -> (App, EventLoop<()>) {
        let event_loop = EventLoop::new().unwrap();
        event_loop.set_control_flow(ControlFlow::Poll);

        (
            App {
                window: None,
                gfx: None,
                dt: 0.,
                last_time: Instant::now(),
            },
            event_loop,
        )
    }

    pub fn run(&mut self, event_loop: EventLoop<()>) -> Result<(), EventLoopError> {
        event_loop.run_app(self)
    }

    fn tick(&mut self) {
        let now = Instant::now();
        let dt = now.duration_since(self.last_time).as_secs_f32();
        self.dt = dt;
        self.last_time = now;
        println!("dt = {}, fps = {}", 1000. * dt, 1. / dt);
    }
}

impl ApplicationHandler for App {
    fn resumed(&mut self, event_loop: &ActiveEventLoop) {
        let mut attributes = Window::default_attributes();
        attributes.title = "ETIB".to_owned();
        let window = Arc::new(event_loop.create_window(attributes).unwrap());

        let gfx = Gfx::new(window.clone());

        self.window = Some(window);
        self.gfx = Some(gfx);
    }

    fn window_event(&mut self, event_loop: &ActiveEventLoop, _: WindowId, event: WindowEvent) {
        match event {
            WindowEvent::CloseRequested => {
                println!("The close button was pressed; stopping");
                event_loop.exit();
            }
            WindowEvent::Resized(size) => {
                if let Some(gfx) = &mut self.gfx {
                    gfx.reconfigure_surface_size(size);

                    if let Some(window) = &self.window {
                        window.request_redraw();
                    }
                }
            }
            WindowEvent::RedrawRequested => {
                if let Some(gfx) = &mut self.gfx {
                    gfx.render();
                }

                self.tick();
                self.window.as_ref().unwrap().request_redraw();
            }
            _ => (),
        }
    }
}
